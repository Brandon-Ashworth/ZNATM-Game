#include "zObject.h"

zObject::zObject()
{
	m_gravity = 650.0f;
	m_frameTime = 0.0;
	m_lastTime = 0.0;
	m_storyKeyNo = 0;
	m_storyKeyAquired = false;
	m_firstDoorNo = 0;
	m_firstDoorOpened = false;
	m_storyDoorNo = 0;
	m_storyDoorOpened = false;

	std::string location;
	std::string type;
	float x;
	float y;
	float z;

	m_inFile.open("ZNATM/dat.ass");
	
	m_inFile >> location;
	do {
		m_inFile >> type;
		m_oList.insert(std::pair<std::string, std::string>(location, type));
		m_inFile >> location;
	} while (!m_inFile.eof());
	m_inFile.close();
}

zObject::~zObject()
{

}

void zObject::load()
{
	std::string temp;
	std::string temp2;
	float box[6];

	for (auto iter = m_oList.begin(); iter != m_oList.end(); ++iter) 
	{
		temp = iter->first;
		temp2 = iter->second;
		m_models.push_back(new Loader(temp, &imgLoc, &imgTex));
		m_types.push_back(temp2);

		Loader(temp, &imgLoc, &imgTex).find_box(box[1], box[0], box[3], box[2], box[5], box[4]);
		m_box.push_back(new zAABB(box[0], box[1], box[2], box[3], box[4], box[5]));
	}
	for (int i = 0; i < m_models.size(); i++)
	{
		if(m_types[i].compare("static") == 0)
		{
			m_staticNo.push_back(i);
		}
		if(m_types[i].compare("stair") == 0)
		{
			m_stairNo.push_back(i);
		}
		if(m_types[i].compare("nothing") == 0)
		{
			m_nothingNo.push_back(i);
		}
		if(m_types[i].compare("storykey") == 0)
		{
			m_storyKeyNo = i;
			m_models[i]->find_box(storyKeyPosXMax, storyKeyPosXMin, storyKeyPosYMax, storyKeyPosYMin, storyKeyPosZMax, storyKeyPosZMin);
		}
		if(m_types[i].compare("door") == 0)
		{
			m_doorNo.push_back(i);
		}
		if(m_types[i].compare("firstdoor") == 0)
		{
			m_firstDoorNo = i;
		}
		if(m_types[i].compare("storydoor") == 0)
		{
			m_storyDoorNo = i;
		}
		if(m_types[i].compare("pipe") == 0)
		{
			m_pipeNo = i;
		}
	}
}

void zObject::draw()
{
	int i;
	
	superDraw(m_staticNo);
	superDraw(m_stairNo);
	superDraw(m_nothingNo);
	superDraw(m_doorNo);
	superDraw(m_storyDoorNo);

	if(!m_takenPipe)
	{
		superDraw(m_pipeNo);
		superDraw(m_firstDoorNo);
	}

	if(!m_storyKeyAquired)
	{
		superDraw(m_storyKeyNo);
	}

	if(!m_keymoved)
	{
		srand(time(NULL));
		int temprand = rand() % 7;
		float tempX, tempY, tempZ;

		switch(temprand)
		{
		case 0:
			tempX = 100.0;
			tempY = 10.0;
			tempZ = -450.0;
			break;
		case 1:
			tempX = 150.0;
			tempY = 140.0;
			tempZ = -550.0;
			break;
		case 2:
			tempX = 490.0;
			tempY = 140.0;
			tempZ = -1800.0;
			break;
		case 3:
			tempX = 1580.0;
			tempY = 180.0;
			tempZ = -2350.0;
			break;
		case 4:
			tempX = 1400.0;
			tempY = 140.0;
			tempZ = -750.0;
			break;
		case 5:
			tempX = 1570.0;
			tempY = 180.0;
			tempZ = -75.0;
			break;
		case 6:
			tempX = 1180.0;
			tempY = 10.0;
			tempZ = -1900.0;
			break;
		}
		storyKeyTransitionedX = tempX;
		storyKeyTransitionedY = tempY;
		storyKeyTransitionedZ = tempZ;
		m_models[m_storyKeyNo]->move(tempX, tempY, tempZ);
		m_box[m_storyKeyNo]->SetX(storyKeyPosXMin+tempX, storyKeyPosXMax+tempX);
		m_box[m_storyKeyNo]->SetY(storyKeyPosYMin+tempY, storyKeyPosYMax+tempY);
		m_box[m_storyKeyNo]->SetZ(storyKeyPosZMin+tempZ, storyKeyPosZMax+tempZ);
		m_keymoved = true;
	}
}

void zObject::superDraw(const std::vector<int> &number)
{
	int i;
	for (i = 0; i < number.size(); i++)
	{
		m_models[number[i]]->draw();
	}
}

void zObject::superDraw(const int &number)
{
	m_models[number]->draw();
}

void zObject::setstoryKeyAquired(bool a)
{
	m_storyKeyAquired = a;
}

bool zObject::getstoryKeyAquired()
{
	return m_storyKeyAquired;
}

bool zObject::collideStoryKey(const zAABB &tempBox)
{
	bool storyKeyCollide = false;

	if(tempBox.isColliding(m_box[m_storyKeyNo]))
	{
		storyKeyCollide = true;
		m_models[m_storyKeyNo]->move(0.0f, 10000.0f, 0.0f);
		m_box[m_storyKeyNo]->SetY(m_box[m_storyKeyNo]->GetYMin()+10000.0f, m_box[m_storyKeyNo]->GetYMax()+10000.0f);
		m_storyKeyAquired = true;
	}

	return storyKeyCollide;
}

bool zObject::collideDoor(zCamera &tempCam, const zAABB &tempBox, zInventory &tempInventory, bool &opened)
{
	bool doorCollide = false;
	bool colliding = false;
	int i, i2;
	float distance[4];

	opened = false;
	
	for(i = 0; i < m_doorNo.size(); i++)
	{
		colliding = tempBox.isColliding(m_box[m_doorNo[i]]);
		if(colliding)
		{
			if(tempInventory.getKeys() <= 0)
			{
				distance[0] = tempBox.GetXMax() - m_box[m_doorNo[i]]->GetXMin();
				distance[1] = m_box[m_doorNo[i]]->GetXMax() - tempBox.GetXMin();
				distance[2] = tempBox.GetZMax() - m_box[m_doorNo[i]]->GetZMin();
				distance[3] = m_box[m_doorNo[i]]->GetZMax() - tempBox.GetZMin();
				
				float minDistance = distance[0];
				// Find shortest distance.
				for(i2 = 0; i2 < 4; i2++)
				{
					if(distance[i2] < minDistance)
					{
						minDistance = distance[i2];
					}
				}
				// Resolve shortest distance.
				if(minDistance == distance[0])
				{
					float tempfloat = tempCam.getPos_x() - minDistance;
					float tempfloat2 = tempCam.getView_x() - minDistance;
					tempCam.setPos_x(tempfloat);
					tempCam.setView_x(tempfloat2);
				}
				if(minDistance == distance[1])
				{
					float tempfloat = tempCam.getPos_x() + minDistance;
					float tempfloat2 = tempCam.getView_x() + minDistance;
					tempCam.setPos_x(tempfloat);
					tempCam.setView_x(tempfloat2);
				}
				if(minDistance == distance[2])
				{
					float tempfloat = tempCam.getPos_z() - minDistance;
					float tempfloat2 = tempCam.getView_z() - minDistance;
					tempCam.setPos_z(tempfloat);
					tempCam.setView_z(tempfloat2);
				}
				if(minDistance == distance[3])
				{
					float tempfloat = tempCam.getPos_z() + minDistance;
					float tempfloat2 = tempCam.getView_z() + minDistance;
					tempCam.setPos_z(tempfloat);
					tempCam.setView_z(tempfloat2);
				}
				doorCollide = true;
			}
			else
			{
				tempInventory.addKeys(-1);
				m_models[m_doorNo[i]]->move(0.0, 10000.0, 0.0);
				m_box[m_doorNo[i]]->SetY(m_box[m_doorNo[i]]->GetYMin()+10000.0, m_box[m_doorNo[i]]->GetYMax()+10000.0);
				opened = true;
			}
		}
	}

	return doorCollide;
}

bool zObject::collideStatic(zCamera &tempCam, const zAABB &tempBox)
{
	bool staticCollide = false;
	bool colliding = false;
	int i, i2;
	float distance[6];
	
	for(i = 0; i < m_staticNo.size(); i++)
	{
		colliding = tempBox.isColliding(m_box[m_staticNo[i]]);
		if (colliding)
		{
			distance[0] = tempBox.GetXMax() - m_box[m_staticNo[i]]->GetXMin();
			distance[1] = m_box[m_staticNo[i]]->GetXMax() - tempBox.GetXMin();
			distance[2] = tempBox.GetYMax() - m_box[m_staticNo[i]]->GetYMin();
			distance[3] = m_box[m_staticNo[i]]->GetYMax() - tempBox.GetYMin();
			distance[4] = tempBox.GetZMax() - m_box[m_staticNo[i]]->GetZMin();
			distance[5] = m_box[m_staticNo[i]]->GetZMax() - tempBox.GetZMin();
				
			float minDistance = distance[0];
			// Find shortest distance.
			for(i2 = 0; i2 < 6; i2++)
			{
				if(distance[i2] < minDistance)
				{
					minDistance = distance[i2];
				}
			}
			// Resolve shortest distance.
			if(minDistance == distance[0])
			{
				float tempfloat = tempCam.getPos_x() - minDistance;
				float tempfloat2 = tempCam.getView_x() - minDistance;
				tempCam.setPos_x(tempfloat);
				tempCam.setView_x(tempfloat2);
			}
			if(minDistance == distance[1])
			{
				float tempfloat = tempCam.getPos_x() + minDistance;
				float tempfloat2 = tempCam.getView_x() + minDistance;
				tempCam.setPos_x(tempfloat);
				tempCam.setView_x(tempfloat2);
			}
			if(minDistance == distance[2])
			{
				float tempfloat = tempCam.getPos_y() - minDistance-1.0;
				float tempfloat2 = tempCam.getView_y() - minDistance-1.0;
				tempCam.setVel_y(0.0);
				tempCam.setPos_y(tempfloat);
				tempCam.setView_y(tempfloat2);
			}
			if(minDistance == distance[3])
			{
				float tempfloat = tempCam.getPos_y() + minDistance-0.5;
				float tempfloat2 = tempCam.getView_y() + minDistance-0.5;
				tempCam.setPos_y(tempfloat);
				tempCam.setView_y(tempfloat2);
				staticCollide = true;
			}
			if(minDistance == distance[4])
			{
				float tempfloat = tempCam.getPos_z() - minDistance;
				float tempfloat2 = tempCam.getView_z() - minDistance;
				tempCam.setPos_z(tempfloat);
				tempCam.setView_z(tempfloat2);
			}
			if(minDistance == distance[5])
			{
				float tempfloat = tempCam.getPos_z() + minDistance;
				float tempfloat2 = tempCam.getView_z() + minDistance;
				tempCam.setPos_z(tempfloat);
				tempCam.setView_z(tempfloat2);
			}
		}
	}

	return staticCollide;
}

bool zObject::collideStair(zCamera &tempCam, const zAABB &tempBox, float camHeight)
{
	bool stairCollide = false;
	bool colliding = false;
	int i, i2;
	
	for(i = 0; i < m_stairNo.size(); i++)
	{
		colliding = tempBox.isColliding(m_box[m_stairNo[i]]);
			if (colliding)
			{
				float tempfloat = tempCam.getView_y() - tempCam.getPos_y();
				if(tempCam.getPos_y() < m_box[m_stairNo[i]]->GetYMax() + camHeight-0.5)
				{
					tempCam.setPos_y(tempCam.getPos_y() + 0.08);
				}
				if(tempCam.getPos_y() < m_box[m_stairNo[i]]->GetYMax() + camHeight-1.0)
				{
					tempCam.setPos_y(tempCam.getPos_y() + 0.3);
				}
				if(tempCam.getPos_y() < m_box[m_stairNo[i]]->GetYMax() + camHeight-2.0)
				{
					tempCam.setPos_y(tempCam.getPos_y() + 1.3);
				}
				tempCam.setView_y(tempCam.getPos_y() + tempfloat);
				stairCollide = true;
			}
	}
	
	return stairCollide;
}

bool zObject::collideFirstDoor(zCamera &tempCam, const zAABB &tempBox, zInventory tempInventory)
{
	bool firstDoorCollide = false;
	bool colliding = false;
	int i;
	float distance[4];
	
	if(tempInventory.getItem1() == 0)
	{
		if(tempInventory.getItem2() == 0)
		{
		colliding = tempBox.isColliding(m_box[m_firstDoorNo]);
		if(colliding)
		{
			distance[0] = tempBox.GetXMax() - m_box[m_firstDoorNo]->GetXMin();
			distance[1] = m_box[m_firstDoorNo]->GetXMax() - tempBox.GetXMin();
			distance[2] = tempBox.GetZMax() - m_box[m_firstDoorNo]->GetZMin();
			distance[3] = m_box[m_firstDoorNo]->GetZMax() - tempBox.GetZMin();
				
			float minDistance = distance[0];
			// Find shortest distance.
			for(i = 0; i < 4; i++)
			{
				if(distance[i] < minDistance)
				{
					minDistance = distance[i];
				}
			}
			// Resolve shortest distance.
			if(minDistance == distance[0])
			{
				float tempfloat = tempCam.getPos_x() - minDistance;
				float tempfloat2 = tempCam.getView_x() - minDistance;
				tempCam.setPos_x(tempfloat);
				tempCam.setView_x(tempfloat2);
			}
			if(minDistance == distance[1])
			{
				float tempfloat = tempCam.getPos_x() + minDistance;
				float tempfloat2 = tempCam.getView_x() + minDistance;
				tempCam.setPos_x(tempfloat);
				tempCam.setView_x(tempfloat2);
			}
			if(minDistance == distance[2])
			{
				float tempfloat = tempCam.getPos_z() - minDistance;
				float tempfloat2 = tempCam.getView_z() - minDistance;
				tempCam.setPos_z(tempfloat);
				tempCam.setView_z(tempfloat2);
			}
			if(minDistance == distance[3])
			{
				float tempfloat = tempCam.getPos_z() + minDistance;
				float tempfloat2 = tempCam.getView_z() + minDistance;
				tempCam.setPos_z(tempfloat);
				tempCam.setView_z(tempfloat2);
			}
			firstDoorCollide = true;
		}
		}
	}

	return firstDoorCollide;
}

bool zObject::collideZFirstDoor(zZombie &tempZombie, const zAABB &tempBox)
{
	bool zFirstDoorCollide = false;
	bool colliding = false;
	int i;
	float distance[4];
	
	colliding = tempBox.isColliding(m_box[m_firstDoorNo]);
	if (colliding)
	{
		distance[0] = tempBox.GetXMax() - m_box[m_firstDoorNo]->GetXMin();
		distance[1] = m_box[m_firstDoorNo]->GetXMax() - tempBox.GetXMin();
		distance[2] = tempBox.GetZMax() - m_box[m_firstDoorNo]->GetZMin();
		distance[3] = m_box[m_firstDoorNo]->GetZMax() - tempBox.GetZMin();
				
		float minDistance = distance[0];
		// Find shortest distance.
		for(i = 0; i < 4; i++)
		{
			if(distance[i] < minDistance)
			{
				minDistance = distance[i];
			}
		}
		// Resolve shortest distance.
		if(minDistance == distance[0])
		{
			float tempfloat = tempZombie.getXPos() - minDistance;
			float tempfloat2 = tempZombie.getViewX() - minDistance;
			tempZombie.setPos(tempfloat, tempZombie.getYPos(), tempZombie.getZPos());
			tempZombie.setDesiredViewX(tempfloat2);
		}
		if(minDistance == distance[1])
		{
			float tempfloat = tempZombie.getXPos() + minDistance;
			float tempfloat2 = tempZombie.getViewX() + minDistance;
			tempZombie.setPos(tempfloat, tempZombie.getYPos(), tempZombie.getZPos());
			tempZombie.setDesiredViewX(tempfloat2);
		}
		if(minDistance == distance[2])
		{
			float tempfloat = tempZombie.getZPos() - minDistance;
			float tempfloat2 = tempZombie.getViewZ() - minDistance;
			tempZombie.setPos(tempZombie.getXPos(), tempZombie.getYPos(), tempfloat);
			tempZombie.setDesiredViewZ(tempfloat2);
		}
		if(minDistance == distance[3])
		{
			float tempfloat = tempZombie.getZPos() + minDistance;
			float tempfloat2 = tempZombie.getViewZ() + minDistance;
			tempZombie.setPos(tempZombie.getXPos(), tempZombie.getYPos(), tempfloat);
			tempZombie.setDesiredViewZ(tempfloat2);
		}
		zFirstDoorCollide = true;
		tempZombie.calcMinMax();
	}
	
	return zFirstDoorCollide;
}

bool zObject::collideZStatic(zZombie *tempZombie, const zAABB &tempBox)
{
	bool zStaticCollide = false;
	bool colliding = false;
	int i, i2;
	float distance[6];
	
	for(i = 0; i < m_staticNo.size(); i++)
	{
		colliding = tempBox.isColliding(m_box[m_staticNo[i]]);
		if (colliding)
		{
			distance[0] = tempBox.GetXMax() - m_box[m_staticNo[i]]->GetXMin();
			distance[1] = m_box[m_staticNo[i]]->GetXMax() - tempBox.GetXMin();
			distance[2] = tempBox.GetYMax() - m_box[m_staticNo[i]]->GetYMin();
			distance[3] = m_box[m_staticNo[i]]->GetYMax() - tempBox.GetYMin();
			distance[4] = tempBox.GetZMax() - m_box[m_staticNo[i]]->GetZMin();
			distance[5] = m_box[m_staticNo[i]]->GetZMax() - tempBox.GetZMin();
				
			float minDistance = distance[0];
			// Find shortest distance.
			for(i2 = 0; i2 < 6; i2++)
			{
				if(distance[i2] < minDistance)
				{
					minDistance = distance[i2];
				}
			}
			// Resolve shortest distance.
			if(minDistance == distance[0])
			{
				float tempfloat = tempZombie->getXPos() - minDistance;
				float tempfloat2 = tempZombie->getViewX() - minDistance;
				tempZombie->setPos(tempfloat, tempZombie->getYPos(), tempZombie->getZPos());
				tempZombie->setDesiredViewX(tempfloat2);
			}
			if(minDistance == distance[1])
			{
				float tempfloat = tempZombie->getXPos() + minDistance;
				float tempfloat2 = tempZombie->getViewX() + minDistance;
				tempZombie->setPos(tempfloat, tempZombie->getYPos(), tempZombie->getZPos());
				tempZombie->setDesiredViewX(tempfloat2);
			}
			if(minDistance == distance[2])
			{
				float tempfloat = tempZombie->getYPos() - minDistance-1.0;
				tempZombie->setVelY(0.0);
				tempZombie->setPos(tempZombie->getXPos(), tempfloat, tempZombie->getZPos());
			}
			if(minDistance == distance[3])
			{
				float tempfloat = tempZombie->getYPos() + minDistance-0.5;
				tempZombie->setPos(tempZombie->getXPos(), tempfloat, tempZombie->getZPos());
				zStaticCollide = true;
			}
			if(minDistance == distance[4])
			{
				float tempfloat = tempZombie->getZPos() - minDistance;
				float tempfloat2 = tempZombie->getViewZ() - minDistance;
				tempZombie->setPos(tempZombie->getXPos(), tempZombie->getYPos(), tempfloat);
				tempZombie->setDesiredViewZ(tempfloat2);
			}
			if(minDistance == distance[5])
			{
				float tempfloat = tempZombie->getZPos() + minDistance;
				float tempfloat2 = tempZombie->getViewZ() + minDistance;
				tempZombie->setPos(tempZombie->getXPos(), tempZombie->getYPos(), tempfloat);
				tempZombie->setDesiredViewZ(tempfloat2);
			}
			tempZombie->calcMinMax();
		}
	}
	
	return zStaticCollide;
}

bool zObject::collideZDoor(zZombie &tempZombie, const zAABB &tempBox)
{
	bool zDoorCollide = false;
	bool colliding = false;
	int i, i2;
	float distance[4];
	
	for(i = 0; i < m_doorNo.size(); i++)
	{
		colliding = tempBox.isColliding(m_box[m_doorNo[i]]);
		if (colliding)
		{
			distance[0] = tempBox.GetXMax() - m_box[m_doorNo[i]]->GetXMin();
			distance[1] = m_box[m_doorNo[i]]->GetXMax() - tempBox.GetXMin();
			distance[2] = tempBox.GetZMax() - m_box[m_doorNo[i]]->GetZMin();
			distance[3] = m_box[m_doorNo[i]]->GetZMax() - tempBox.GetZMin();
				
			float minDistance = distance[0];
			// Find shortest distance.
			for(i2 = 0; i2 < 4; i2++)
			{
				if(distance[i2] < minDistance)
				{
					minDistance = distance[i2];
				}
			}
			// Resolve shortest distance.
			if(minDistance == distance[0])
			{
				float tempfloat = tempZombie.getXPos() - minDistance;
				float tempfloat2 = tempZombie.getViewX() - minDistance;
				tempZombie.setPos(tempfloat, tempZombie.getYPos(), tempZombie.getZPos());
				tempZombie.setDesiredViewX(tempfloat2);
			}
			if(minDistance == distance[1])
			{
				float tempfloat = tempZombie.getXPos() + minDistance;
				float tempfloat2 = tempZombie.getViewX() + minDistance;
				tempZombie.setPos(tempfloat, tempZombie.getYPos(), tempZombie.getZPos());
				tempZombie.setDesiredViewX(tempfloat2);
			}
			if(minDistance == distance[2])
			{
				float tempfloat = tempZombie.getZPos() - minDistance;
				float tempfloat2 = tempZombie.getViewZ() - minDistance;
				tempZombie.setPos(tempZombie.getXPos(), tempZombie.getYPos(), tempfloat);
				tempZombie.setDesiredViewZ(tempfloat2);
			}
			if(minDistance == distance[3])
			{
				float tempfloat = tempZombie.getZPos() + minDistance;
				float tempfloat2 = tempZombie.getViewZ() + minDistance;
				tempZombie.setPos(tempZombie.getXPos(), tempZombie.getYPos(), tempfloat);
				tempZombie.setDesiredViewZ(tempfloat2);
			}
			tempZombie.calcMinMax();
		}
	}
	
	return zDoorCollide;
}

bool zObject::collideZStair(zZombie *tempZombie, const zAABB &tempBox)
{
	bool zStairCollide = false;
	bool colliding = false;
	int i;
	
	for(i = 0; i < m_stairNo.size(); i++)
	{
		colliding = tempBox.isColliding(m_box[m_stairNo[i]]);
		if (colliding)
		{
			if(tempZombie->getMinY() < m_box[m_stairNo[i]]->GetYMax() - 0.5)
			{
				tempZombie->setPos(tempZombie->getXPos(), tempZombie->getYPos() + 0.1, tempZombie->getZPos());
			}
			if(tempZombie->getMinY() < m_box[m_stairNo[i]]->GetYMax() - 1.5)
			{
				tempZombie->setPos(tempZombie->getXPos(), tempZombie->getYPos() + 0.5, tempZombie->getZPos());
			}
			if(tempZombie->getMinY() < m_box[m_stairNo[i]]->GetYMax() - 2.5)
			{
				tempZombie->setPos(tempZombie->getXPos(), tempZombie->getYPos() + 1.0, tempZombie->getZPos());
			}
			if(tempZombie->getMinY() < m_box[m_stairNo[i]]->GetYMax() - 3.5)
			{
				tempZombie->setPos(tempZombie->getXPos(), tempZombie->getYPos() + 1.5, tempZombie->getZPos());
			}
			zStairCollide = true;
			tempZombie->calcMinMax();
		}
	}
	
	return zStairCollide;
}

bool zObject::collidePipe(zCamera &tempCam, const zAABB &tempBox)
{
	bool pipeCollide = false;

	if(tempBox.isColliding(m_box[m_pipeNo]))
	{
		pipeCollide = true;
		m_models[m_pipeNo]->move(0.0f, 10000.0f, 0.0f);
		m_box[m_pipeNo]->SetY(m_box[m_pipeNo]->GetYMin()+10000.0f, m_box[m_pipeNo]->GetYMax()+10000.0f);
	}

	return pipeCollide;
}

bool zObject::collideStoryDoor(zCamera &tempCam, const zAABB &tempBox)
{
	bool storyDoorCollide = false;

	if(tempBox.isColliding(m_box[m_storyDoorNo]))
	{
		storyDoorCollide = true;
	}

	return storyDoorCollide;
}

void zObject::AABBWireframeStaticOn()
{
	int i;
	for(i = 0; i < m_box.size(); i++)
	{
		if((m_types[i].compare("static") == 0) || (m_types[i].compare("stair") == 0) || (m_types[i].compare("storykey") == 0))
		{
			glColor3f(0.0f, 0.0f, 0.0f);
			glLineWidth(5);
			glBegin(GL_LINES);
				glVertex3f(m_box[i]->GetXMin(), m_box[i]->GetYMin(), m_box[i]->GetZMin());
				glVertex3f(m_box[i]->GetXMax(), m_box[i]->GetYMin(), m_box[i]->GetZMin());
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(m_box[i]->GetXMax(), m_box[i]->GetYMin(), m_box[i]->GetZMin());
				glVertex3f(m_box[i]->GetXMax(), m_box[i]->GetYMax(), m_box[i]->GetZMin());
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(m_box[i]->GetXMax(), m_box[i]->GetYMax(), m_box[i]->GetZMin());
				glVertex3f(m_box[i]->GetXMin(), m_box[i]->GetYMax(), m_box[i]->GetZMin());
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(m_box[i]->GetXMin(), m_box[i]->GetYMax(), m_box[i]->GetZMin());
				glVertex3f(m_box[i]->GetXMin(), m_box[i]->GetYMin(), m_box[i]->GetZMin());
			glEnd();
			// -------------------------------------------------- //
			glBegin(GL_LINES);
				glVertex3f(m_box[i]->GetXMin(), m_box[i]->GetYMin(), m_box[i]->GetZMax());
				glVertex3f(m_box[i]->GetXMax(), m_box[i]->GetYMin(), m_box[i]->GetZMax());
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(m_box[i]->GetXMax(), m_box[i]->GetYMin(), m_box[i]->GetZMax());
				glVertex3f(m_box[i]->GetXMax(), m_box[i]->GetYMax(), m_box[i]->GetZMax());
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(m_box[i]->GetXMax(), m_box[i]->GetYMax(), m_box[i]->GetZMax());
				glVertex3f(m_box[i]->GetXMin(), m_box[i]->GetYMax(), m_box[i]->GetZMax());
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(m_box[i]->GetXMin(), m_box[i]->GetYMax(), m_box[i]->GetZMax());
				glVertex3f(m_box[i]->GetXMin(), m_box[i]->GetYMin(), m_box[i]->GetZMax());
			glEnd();

			// -------------------------------------------------- //

			glBegin(GL_LINES);
				glVertex3f(m_box[i]->GetXMin(), m_box[i]->GetYMin(), m_box[i]->GetZMin());
				glVertex3f(m_box[i]->GetXMin(), m_box[i]->GetYMin(), m_box[i]->GetZMax());
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(m_box[i]->GetXMin(), m_box[i]->GetYMax(), m_box[i]->GetZMin());
				glVertex3f(m_box[i]->GetXMin(), m_box[i]->GetYMax(), m_box[i]->GetZMax());
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(m_box[i]->GetXMax(), m_box[i]->GetYMax(), m_box[i]->GetZMin());
				glVertex3f(m_box[i]->GetXMax(), m_box[i]->GetYMax(), m_box[i]->GetZMax());
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(m_box[i]->GetXMax(), m_box[i]->GetYMin(), m_box[i]->GetZMin());
				glVertex3f(m_box[i]->GetXMax(), m_box[i]->GetYMin(), m_box[i]->GetZMax());
			glEnd();
			glLineWidth(1.0f);
		}
	}
}

void zObject::gravitize(float &y)
{
	if(y < -m_gravity)
	{
		y = -m_gravity;
	}
	else
	{
		y -= m_gravity * m_frameTime;
	}
}

void zObject::calcTime()
{
    float currentTime = 0;

    currentTime = glutGet(GLUT_ELAPSED_TIME);
    m_frameTime = (currentTime - m_lastTime) / 1000.0f;
    m_lastTime = currentTime;
}

float zObject::getFrameTime()
{
	return m_frameTime;
}

void zObject::setTakenPipe(bool t)
{
	m_takenPipe = t;
}

bool zObject::getKeyMoved()
{
	return m_keymoved;
}

void zObject::setKeyMoved(bool k)
{
	m_keymoved = k;
	if(!k)
	{
		if(m_storyKeyAquired)
		{
			m_models[m_storyKeyNo]->move(-storyKeyTransitionedX, -10000.0-storyKeyTransitionedY, -storyKeyTransitionedZ);
			m_storyKeyAquired = false;
		}
		else
		{
			m_models[m_storyKeyNo]->move(-storyKeyTransitionedX, -storyKeyTransitionedY, -storyKeyTransitionedZ);
		}
	}
}