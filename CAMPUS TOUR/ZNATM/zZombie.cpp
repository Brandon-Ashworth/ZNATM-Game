#include "zZombie.h"

zZombie::zZombie()
{
	m_health = 100;
	m_walkSpeed = 0.005;
	m_runSpeed = 0.04;
	m_damage = 2.0;
	m_VelY = 0.0;
	m_View.m_x = m_Pos.m_x;
	m_View.m_y = m_Pos.m_y;
	m_View.m_z = m_Pos.m_z + 500.0;
	m_directionTimer = 25;
	m_spawnCD = 25;
}

zZombie::zZombie(std::string l)
{
	m_health = 100;
	m_walkSpeed = 0.005;
	m_runSpeed = 0.04;
	m_damage = 2.0;
	m_VelY = 0.0;
	m_View.m_x = m_Pos.m_x;
	m_View.m_y = m_Pos.m_y;
	m_View.m_z = m_Pos.m_z + 500.0;
	m_directionTimer = 25;
	m_spawnCD = 25;
	m_zombieModelLocation = l;
	m_zModel.process(l, &imgLoc, &imgTex);
}

zZombie::~zZombie()
{
}

float zZombie::getHealth()
{
	return m_health;
}

float zZombie::getWalkSpeed()
{
	return m_walkSpeed;
}

float zZombie::getRunSpeed()
{
	return m_runSpeed;
}

float zZombie::getDamage()
{
	return m_damage;
}

float zZombie::getXPos()
{
	return m_Pos.m_x;
}

float zZombie::getYPos()
{
	return m_Pos.m_y;
}

float zZombie::getZPos()
{
	return m_Pos.m_z;
}

float zZombie::getViewX()
{
	return m_View.m_x;
}

float zZombie::getViewZ()
{
	return m_View.m_z;
}

float zZombie::getMinX()
{
	return m_MinX;
}

float zZombie::getMaxX()
{
	return m_MaxX;
}

float zZombie::getMinY()
{
	return m_MinY;
}

float zZombie::getMaxY()
{
	return m_MaxY;
}

float zZombie::getMinZ()
{
	return m_MinZ;
}

float zZombie::getMaxZ()
{
	return m_MaxZ;
}

float zZombie::getVelY()
{
	return m_VelY;
}

void zZombie::setHealth(float h)
{
	m_health = h;
}

void zZombie::setWalkSpeed(float ws)
{
	m_walkSpeed = ws;
}

void zZombie::setRunSpeed(float rs)
{
	m_runSpeed = rs;
}

void zZombie::setDamage(float d)
{
	m_damage = d;
}

void zZombie::setDesiredViewX(float x)
{
	float limit = 3.1415/2;
	
	if((x - m_Pos.m_x) > ((sin(limit)) * 500.0))
	{
		x = m_Pos.m_x + ((sin(limit)) * 500.0);
	}
	else if((x - m_Pos.m_x) < -((sin(limit)) * 500.0))
	{
		x = m_Pos.m_x - ((sin(limit)) * 500.0);
	}

	m_View.m_x = x;
}

void zZombie::setDesiredViewZ(float z)
{
	float limit = 3.1415/2;
	
	if((z - m_Pos.m_z) > ((sin(limit)) * 500.0))
	{
		z = m_Pos.m_z + ((sin(limit)) * 500.0);
	}
	else if((z - m_Pos.m_z) < -((sin(limit)) * 500.0))
	{
		z = m_Pos.m_z - ((sin(limit)) * 500.0);
	}

	m_View.m_z = z;
}

void zZombie::setVelY(float y)
{
	m_VelY = y;
}

void zZombie::setPos(float x, float y, float z)
{
	m_zModel.move(x - m_Pos.m_x, y - m_Pos.m_y, z - m_Pos.m_z);
	m_Pos.m_x = x;
	m_Pos.m_y = y;
	m_Pos.m_z = z;
}

void zZombie::setInitPos()
{
	m_Pos.m_x = m_MaxX - (m_width/2.0);
	m_Pos.m_y = m_MaxY - (m_height/2.0);
	m_Pos.m_z = m_MaxZ - (m_depth/2.0);
}

void zZombie::setZombieModelLocation(std::string l)
{
	m_zombieModelLocation = l;
}

void zZombie::draw()
{
	m_zModel.draw();
}

void zZombie::walk(bool w)
{
	if(w)
	{
		zcamVec view = m_View - m_Pos;
		/*
		float limit = 3.1415;
	
		if(view.m_x > 5 * cos(limit))
		{
			view.m_x = 5 * cos(limit);
		}
		if(view.m_z > 5 * tan(limit))
		{
			view.m_z = 5 * tan(limit);
		}
		if(view.m_x < -(5 * cos(limit)))
		{
			view.m_x = -(5 * cos(limit));
		}
		if(view.m_z < -(5 * tan(limit)))
		{
			view.m_z = -(5 * tan(limit));
		}
		*/

		m_Pos.m_x += view.m_x * m_walkSpeed;
		m_zModel.move(view.m_x * m_walkSpeed, 0.0, 0.0);
		m_Pos.m_z += view.m_z * m_walkSpeed;
		m_zModel.move(0.0, 0.0, view.m_z * m_walkSpeed);
		setDesiredViewX(m_View.m_x + view.m_x * m_walkSpeed);
		//m_View.m_x += view.m_x * m_walkSpeed;
		setDesiredViewZ(m_View.m_z + view.m_z * m_walkSpeed);
		//m_View.m_z += view.m_z * m_walkSpeed;
	}
}

void zZombie::run(bool r)
{
	if(r)
	{
		zcamVec view = m_View - m_Pos;
		/*
		float limit = 3.1415;
	
		if(view.m_x > 5 * cos(limit))
		{
			view.m_x = 5 * cos(limit);
		}
		if(view.m_z > 5 * tan(limit))
		{
			view.m_z = 5 * tan(limit);
		}
		if(view.m_x < -(5 * cos(limit)))
		{
			view.m_x = -(5 * cos(limit));
		}
		if(view.m_z < -(5 * tan(limit)))
		{
			view.m_z = -(5 * tan(limit));
		}
		*/
		m_Pos.m_x += view.m_x * m_runSpeed;
		m_zModel.move(view.m_x * m_runSpeed, 0.0, 0.0);
		m_Pos.m_z += view.m_z * m_runSpeed;
		m_zModel.move(0.0, 0.0, view.m_z * m_runSpeed);
		setDesiredViewX(m_View.m_x + view.m_x * m_runSpeed);
		//m_View.m_x += view.m_x * m_runSpeed;
		setDesiredViewZ(m_View.m_z + view.m_z * m_runSpeed);
		//m_View.m_z += view.m_z * m_runSpeed;
	}
}

void zZombie::calcYVel(float frameTime)
{
	m_Pos.m_y += m_VelY * frameTime;
	m_zModel.move(0.0, m_VelY * frameTime, 0.0);
}

void zZombie::findPos()
{
	m_zModel.find_box(m_MaxX, m_MinX, m_MaxY, m_MinY, m_MaxZ, m_MinZ);
	m_width = m_MaxX - m_MinX;
	m_height = m_MaxY - m_MinY;
	m_depth = m_MaxZ - m_MinZ;
}

int zZombie::getDirectionTimer()
{
	return m_directionTimer;
}

void zZombie::setDirectionTimer(int t)
{
	m_directionTimer = t;
}

int zZombie::getSpawnCD()
{
	return m_spawnCD;
}

void zZombie::setSpawnCD(int cd)
{
	m_spawnCD = cd;
}

void zZombie::randomizeDirection()
{
	float limit = float((rand()%(31415))/10000.0)/2.0;
	float randX = 0;
	float limit2 = float((rand()%(31415))/10000.0)/2.0;
	float randZ = 0;
	if(rand()%2 == 0)
	{
		randX = -(500.0 * sin(limit));
	}
	else
	{
		randX = 500.0 * sin(limit);
	}
	if(rand()%2 == 0)
	{
		randZ = -(500.0 * sin(limit2));
	}
	else
	{
		randZ = 500.0 * sin(limit2);
	}

	setDesiredViewX(getXPos() + randX);
	setDesiredViewZ(getZPos() + randZ);
}

void zZombie::calcLastPosView()
{
	m_lastPos.m_x = m_Pos.m_x;
	m_lastPos.m_y = m_Pos.m_y;
	m_lastPos.m_z = m_Pos.m_z;
	m_lastView.m_x = m_View.m_x;
	m_lastView.m_z = m_View.m_z;
}

float zZombie::getLastXPos()
{
	return m_lastPos.m_x;
}

float zZombie::getLastYPos()
{
	return m_lastPos.m_y;
}

float zZombie::getLastZPos()
{
	return m_lastPos.m_z;
}

float zZombie::getLastXView()
{
	return m_lastView.m_x;
}

float zZombie::getLastZView()
{
	return m_lastView.m_z;
}

void zZombie::calcMinMax()
{
	m_MinX = m_Pos.m_x - (m_width/2.0);
	m_MaxX = m_Pos.m_x + (m_width/2.0);
	m_MinY = m_Pos.m_y - (m_height/2.0);
	m_MaxY = m_Pos.m_y + (m_height/2.0);
	m_MinZ = m_Pos.m_z - (m_depth/2.0);
	m_MaxZ = m_Pos.m_z + (m_depth/2.0);
}