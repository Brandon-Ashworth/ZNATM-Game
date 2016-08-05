#include "ZNATM.h"
//#include <iostream>

Sound key(1);
Sound lock(1);
Sound music(1);
Sound walk(1);
Sound hit(1);
Sound open(1);

zCamera m_cam;

zAABB cambox;

zInventory playerInventory;

std::vector<zZombie*> zombies;

std::vector<zKey*> keys;

zPlayer player;

zObject objects;

float jumpPower;
float pipeAnimTimer;
float lockTimer;

bool ztransition;
bool moveF;
bool moveB;
bool moveL;
bool moveR;
bool moveJ;
bool moveC;
bool moveI;
bool moveA;

bool hitable;

float playerHeight;
float playerAbsHeight;
float playerHPRegen;

float camStartx;
float camStartz;

float lastXPos;
float lastYPos;
float lastZPos;
float lastXView;
float lastYView;
float lastZView;

int zombieLimit;
int zombieLimitInit;

static bool firstRun;

//keysounds
//Sound *key;

ZombieNight::ZombieNight()
{
	firstRun = true;
	pipeAnimTimer = 5.0;
	lockTimer = 50.0;

	jumpPower = 225.0f;
	
	zombieLimit = 29;
	zombieLimitInit = 2;

	ztransition = false;
	moveF = false;
	moveB = false;
	moveL = false;
	moveR = false;
	moveJ = false;
	moveC = false;
	moveI = false;
	moveA = false;
	hitable = false;
	
	playerHeight = 60.5f;
	playerAbsHeight = 60.5f;
	playerHPRegen = 0.01;

	camStartx = 1450.0f;
	camStartz = -2550.0f;

	m_cam.camPos(camStartx, playerHeight+15.0f, camStartz,
				 camStartx, playerHeight+15.0f, camStartz+35.0,
				      0.0f,               1.0f,          0.0f);
	cambox.SetX(camStartx - 2.5f, camStartx + 2.5f);
	cambox.SetY(15.0f, playerHeight + 20.0f);
	cambox.SetZ(camStartz - 2.5f, camStartz + 2.5f);
	
	lastXPos = m_cam.getPos_x();
	lastYPos = m_cam.getPos_y();
	lastZPos = m_cam.getPos_z();
	lastXView = m_cam.getView_x();
	lastYView = m_cam.getView_y();
	lastZView = m_cam.getView_z();


}

ZombieNight::~ZombieNight()
{

}

void ZombieNight::drawWorld()
{
	draw();
	idle();
}

void ZombieNight::initialize()
{
	ztransition = false;

	glClearColor(150.0f, 150.0f, 150.0f, 1.0f);
	glColor4f(255.0f, 255.0f, 255.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	if(firstRun)
	{
		objects.load();
		objects.setTakenPipe(false);
		objects.setstoryKeyAquired(false);
		playerInventory.haveStoryKey(false);
		playerInventory.addItemLoc("test/Pipe.obj");
		key.Load("music/key.wav");
		lock.Load("music/Locked.wav");
		music.Load("music/creep.wav");
		music.setVolume(35.0);
		music.setRep(1);
		walk.Load("music/Walk3.wav");
		hit.Load("music/Hit.wav");
		open.Load("music/Door.wav");

		for(int i = 0; i < zombieLimitInit; i++)
		{
			createZombies();
		}
	}
	/*glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(moveKeyboard);
	glutIgnoreKeyRepeat(1);
	glutKeyboardUpFunc(nomoveKeyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	glEnable(GLUT_DOUBLE);

	glDisable(GL_TEXTURE_2D);

	GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};

	glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);
	//glEnable(GL_FLAT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light_position[] = {2100,71,-3385,0.0};

	glEnable(GL_COLOR_MATERIAL);

	/*GLfloat whiteSpec[] = {1.0,1.0,1.0};
	GLfloat blackAmb[] = {0.0,0.0,0.0};
	GLfloat whiteDiff[] = {1.0,1.0,1.0};
	GLfloat redDiff[] = {1.0,0.0,0.0};

	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiff);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//GLfloat ambCol[] = {0.2f,0.2f,0.2f,1.0f};
	GLfloat ambCol[] = {1.0f,1.0f,1.0f,1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambCol);*/
}

void ZombieNight::createZombies()
{
	zombies.push_back(new zZombie("test/SlenderZombie.obj"));
	keys.push_back(new zKey("test/SilverKey.obj"));
	zombies[zombies.size() - 1]->findPos();
	keys[keys.size() - 1]->findBox();
	zombies[zombies.size() - 1]->setInitPos();
	keys[keys.size() - 1]->setInitPos();
	zombies[zombies.size() - 1]->calcMinMax();
	keys[keys.size() - 1]->calcMinMax();
	spawnZombies(*zombies[zombies.size() - 1], *keys[keys.size() - 1]);
	zombies[zombies.size() - 1]->setVelY(0.0);
	zombies[zombies.size() - 1]->calcLastPosView();
	zombies[zombies.size() - 1]->setSpawnCD((rand() % 201) + 400);
}

void ZombieNight::spawnZombies(zZombie &z, zKey &k)
{
	int temprand = rand() % 3;
	switch(temprand)
	{
	case 0:
		z.setPos(2100.0, 100.0, -3400.0);
		k.setPos(z.getXPos(), z.getYPos() + 10000.0, z.getZPos());
		z.setDesiredViewX(z.getXPos());
		z.setDesiredViewZ(z.getZPos() + 500.0);
		break;
	case 1:
		z.setPos(1900.0, 100.0, -3100.0);
		k.setPos(z.getXPos(), z.getYPos() + 10000.0, z.getZPos());
		z.setDesiredViewX(z.getXPos());
		z.setDesiredViewZ(z.getZPos() + 500.0);
		break;
	case 2:
		z.setPos(1650.0, 100.0, -3300.0);
		k.setPos(z.getXPos(), z.getYPos() + 10000.0, z.getZPos());
		z.setDesiredViewX(z.getXPos());
		z.setDesiredViewZ(z.getZPos() + 500.0);
		break;
	}
}

void ZombieNight::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_TEXTURE_2D);

	AABBWireframe(false, 5.0f);

	objects.draw();
	//objects.AABBWireframeStaticOn();

	drawZombies();

	playerInventory.drawItems();

	drawHUD();

	//glFlush();
	glutSwapBuffers();
}

void ZombieNight::drawHUD()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0 , glutGet(GLUT_WINDOW_HEIGHT));
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			// ---------------------------------------------------------------------------------------------------- //
			glTranslatef(0, 0, 0);
			std::stringstream ss (std::stringstream::in | std::stringstream::out);
			ss << player.getHealth();
			std::string tempstr = ss.str();
			glRasterPos2f(50.0, 50.0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'H');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'h');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
			for(int i = 0; i < tempstr.size(); i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tempstr[i]);
			}
			std::stringstream ss2 (std::stringstream::in | std::stringstream::out);
			ss2 << playerInventory.getKeys();
			tempstr = ss2.str();
			glRasterPos2f(glutGet(GLUT_WINDOW_WIDTH)-150.0, 50.0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'K');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
			for(int i = 0; i < tempstr.size(); i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tempstr[i]);
			}
			// ---------------------------------------------------------------------------------------------------- //
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

void ZombieNight::AABBWireframe(bool wireframe, GLfloat thickness)
{
	if (wireframe)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glLineWidth(thickness);
		glBegin(GL_LINES);
			glVertex3f(cambox.GetXMin(), cambox.GetYMin(), cambox.GetZMin());
			glVertex3f(cambox.GetXMax(), cambox.GetYMin(), cambox.GetZMin());
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(cambox.GetXMax(), cambox.GetYMin(), cambox.GetZMin());
			glVertex3f(cambox.GetXMax(), cambox.GetYMax(), cambox.GetZMin());
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(cambox.GetXMax(), cambox.GetYMax(), cambox.GetZMin());
			glVertex3f(cambox.GetXMin(), cambox.GetYMax(), cambox.GetZMin());
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(cambox.GetXMin(), cambox.GetYMax(), cambox.GetZMin());
			glVertex3f(cambox.GetXMin(), cambox.GetYMin(), cambox.GetZMin());
		glEnd();

		// -------------------------------------------------- //

		glBegin(GL_LINES);
			glVertex3f(cambox.GetXMin(), cambox.GetYMin(), cambox.GetZMax());
			glVertex3f(cambox.GetXMax(), cambox.GetYMin(), cambox.GetZMax());
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(cambox.GetXMax(), cambox.GetYMin(), cambox.GetZMax());
			glVertex3f(cambox.GetXMax(), cambox.GetYMax(), cambox.GetZMax());
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(cambox.GetXMax(), cambox.GetYMax(), cambox.GetZMax());
			glVertex3f(cambox.GetXMin(), cambox.GetYMax(), cambox.GetZMax());
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(cambox.GetXMin(), cambox.GetYMax(), cambox.GetZMax());
			glVertex3f(cambox.GetXMin(), cambox.GetYMin(), cambox.GetZMax());
		glEnd();

		// -------------------------------------------------- //

		glBegin(GL_LINES);
			glVertex3f(cambox.GetXMin(), cambox.GetYMin(), cambox.GetZMin());
			glVertex3f(cambox.GetXMin(), cambox.GetYMin(), cambox.GetZMax());
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(cambox.GetXMin(), cambox.GetYMax(), cambox.GetZMin());
			glVertex3f(cambox.GetXMin(), cambox.GetYMax(), cambox.GetZMax());
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(cambox.GetXMax(), cambox.GetYMax(), cambox.GetZMin());
			glVertex3f(cambox.GetXMax(), cambox.GetYMax(), cambox.GetZMax());
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(cambox.GetXMax(), cambox.GetYMin(), cambox.GetZMin());
			glVertex3f(cambox.GetXMax(), cambox.GetYMin(), cambox.GetZMax());
		glEnd();
		glLineWidth(1.0f);
	}
}

void ZombieNight::reshape(int w, int h)
{
	if (h == 0)
	{
		h = 1;
	}
	float ratio = (w / h) * 1.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60.0f, ratio, 0.1f, 2000.0f);	
	glMatrixMode(GL_MODELVIEW);
}

void ZombieNight::idle()
{
	srand(time(NULL));
	objects.calcTime();

	firstRun = false;
	glutPostRedisplay();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(m_cam.getPos_x(), m_cam.getPos_y(), m_cam.getPos_z(),
		      m_cam.getView_x(), m_cam.getView_y(), m_cam.getView_z(),
			  m_cam.getUp_x(), m_cam.getUp_y(), m_cam.getUp_z());
	/*
	std::cout <<m_cam.getPos_x() <<" " <<m_cam.getPos_y()<<" "<< m_cam.getPos_z()
		      <<" "<<m_cam.getView_x()<<" "<< m_cam.getView_y()<<" "<< m_cam.getView_z()
			  <<" "<<m_cam.getUp_x()<<" " <<m_cam.getUp_y()<<" " <<m_cam.getUp_z() <<std::endl <<std::endl;
	*/ // prints out the cameras location

	cambox.SetX(m_cam.getPos_x() - 10.0f, m_cam.getPos_x() + 10.0f);
	cambox.SetY(m_cam.getPos_y() - playerHeight, m_cam.getPos_y() + 5.0f);
	cambox.SetZ(m_cam.getPos_z() - 10.0f, m_cam.getPos_z() + 10.0f);

	if(ztransition)
	{
		music.pause();
	}
	else
	{
		if((music.isPlaying() == 0) || (music.isPlaying() == 1))
		{
			music.play();
		}
	}

	if(m_cam.getVel_y() <= -600)
	{
		m_cam.setVel_y(0.0);
		m_cam.setView_x(lastXView);
		m_cam.setView_y(lastYView + 20.0);
		m_cam.setView_z(lastZView);
		m_cam.setPos_x(lastXPos);
		m_cam.setPos_y(lastYPos + 20.0);
		m_cam.setPos_z(lastZPos);
	}

	int windowWidth, windowHeight;
	windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

	m_cam.Mouse(windowWidth, windowHeight);

	if((player.getHealth() < 100.0) && (player.getHealth() > 0.0))
	{
		player.setHealth(player.getHealth()+playerHPRegen);
	}
	if(player.getHealth() <= 0.0)
	{
		playerInventory.setKeys(0);
		playerInventory.haveStoryKey(false);
		objects.setKeyMoved(false);
		player.setHealth(100.0);
		m_cam.camPos(camStartx, playerHeight+15.0f, camStartz,
				 camStartx, playerHeight+15.0f, camStartz+35.0,
				      0.0f,               1.0f,          0.0f);
	}

	//std::cout << "\nCamera: " << m_cam.getPos_x() << ", " << m_cam.getPos_y() << ", " << m_cam.getPos_z();

	for(int i = 0; i < zombies.size(); i++)
	{
		//std::cout << "\nZOMBIE" << i << " - X: " << zombies[i]->getXPos() << "   ---   Y: " << zombies[i]->getYPos() << "   ---   Z: " << zombies[i]->getZPos();
		//std::cout << "\nZOMBIE - X: " << zombies[i]->getXPos() << "   ---   Y: " << zombies[i]->getYPos() << "   ---   Z: " << zombies[i]->getZPos();
		//std::cout << "\nkey - X: " << keys[i]->getXPos() << "   ---   Y: " << keys[i]->getYPos() << "   ---   Z: " << keys[i]->getZPos();
		zombies[i]->calcMinMax();
		bool tempZBool = false;
		bool tempZBool2 = false;

		zAABB tempBox;
		tempBox.SetX(zombies[i]->getMinX(), zombies[i]->getMaxX());
		tempBox.SetY(zombies[i]->getMinY(), zombies[i]->getMaxY());
		tempBox.SetZ(zombies[i]->getMinZ(), zombies[i]->getMaxZ());

		tempZBool = objects.collideZStatic(zombies[i], tempBox);
		tempZBool2 = objects.collideZStair(zombies[i], tempBox);
		objects.collideZDoor(*zombies[i], tempBox);
		objects.collideZFirstDoor(*zombies[i], tempBox);

		if(zombies[i]->getHealth() > 0.0)
		{
			zombies[i]->calcYVel(objects.getFrameTime());
			zombies[i]->walk(true);
			zombies[i]->run(false);
		}

		if(tempZBool || tempZBool2)
		{
			zombies[i]->setVelY(0.0);
		}
		else
		{
			float tempZombieVelY = zombies[i]->getVelY();
			objects.gravitize(tempZombieVelY);
			zombies[i]->setVelY(tempZombieVelY);
		}

		if(zombies[i]->getVelY() <= -500.0)
		{
			zombies[i]->setVelY(0.0);
			zombies[i]->setPos(zombies[i]->getLastXPos(), zombies[i]->getLastYPos() + 20.0, zombies[i]->getLastZPos());
			zombies[i]->setDesiredViewX(zombies[i]->getLastXView());
			zombies[i]->setDesiredViewZ(zombies[i]->getLastZView());
			zombies[i]->calcMinMax();
		}

		if((cambox.isColliding(tempBox)) && (zombies[i]->getHealth() > 0.0))
		{
			player.setHealth(player.getHealth() - zombies[i]->getDamage());
		}
		float tempDist = sqrt((m_cam.getPos_x()-zombies[i]->getXPos())*(m_cam.getPos_x()-zombies[i]->getXPos()) + (m_cam.getPos_z()-zombies[i]->getZPos())*(m_cam.getPos_z()-zombies[i]->getZPos()));
		if(tempDist <= 350.0)
		{
			if(zombies[i]->getHealth() > 0.0)
			{
				if((cambox.GetYMax() > zombies[i]->getMinY()) && (cambox.GetYMin() < zombies[i]->getMaxY()))
				{
					zombies[i]->setDesiredViewX(m_cam.getPos_x());
					zombies[i]->setDesiredViewZ(m_cam.getPos_z());
					zombies[i]->run(true);
					zombies[i]->walk(false);
				}
			}
		}
		else
		{
			if(zombies[i]->getDirectionTimer() > 0.0)
			{
				zombies[i]->setDirectionTimer(zombies[i]->getDirectionTimer() - 1.0);
			}
			else
			{
				zombies[i]->setDirectionTimer((rand() % 51) + 50);
				zombies[i]->randomizeDirection();
			}
		}
		if(zombies[i]->getSpawnCD() <= 0)
		{
			if(zombies[i]->getHealth() <= 0.0)
			{
				zombies[i]->setSpawnCD((rand() % 201) + 400);
				zombies[i]->setHealth(100.0);
				spawnZombies(*zombies[i], *keys[i]);
			}
		}
		else
		{
			if(zombies[i]->getHealth() <= 0.0)
			{
				zombies[i]->walk(false);
				zombies[i]->run(false);
				zombies[i]->setSpawnCD(zombies[i]->getSpawnCD() - 1);
			}
			else
			{
				zombies[i]->setSpawnCD((rand() % 201) + 400);
				keys[i]->setPos(zombies[i]->getXPos(), zombies[i]->getYPos() + 10000.0, zombies[i]->getZPos());
			}
		}
		if(hitable)
		{
			zAABB tempHitBox;
			tempHitBox.SetX(m_cam.getView_x()-20.0, m_cam.getView_x()+20.0);
			tempHitBox.SetY(m_cam.getView_y()-20.0, m_cam.getView_y()+20.0);
			tempHitBox.SetZ(m_cam.getView_z()-20.0, m_cam.getView_z()+20.0);
			zAABB tempZombieBox;
			tempZombieBox.SetX(zombies[i]->getMinX(), zombies[i]->getMaxX());
			tempZombieBox.SetY(zombies[i]->getMinY(), zombies[i]->getMaxY());
			tempZombieBox.SetZ(zombies[i]->getMinZ(), zombies[i]->getMaxZ());
			if(tempHitBox.isColliding(tempZombieBox))
			{
				zombies[i]->setHealth(zombies[i]->getHealth()-player.getDamage());
				hit.play();
			}
		}
	}
	
	bool tempBool = false;
	bool tempBool2 = false;
	bool tempBool3 = false;
	bool tempBool4 = false;
	bool tempBoolDoor = false;

	tempBool = objects.collideStatic(m_cam, cambox);
	tempBool2 = objects.collideStair(m_cam, cambox, playerHeight);
	tempBool3 = objects.collideStoryKey(cambox);

	tempBool4 = objects.collideDoor(m_cam, cambox, playerInventory, tempBoolDoor);
	objects.collideFirstDoor(m_cam, cambox, playerInventory);
	if(objects.collideStoryDoor(m_cam, cambox))
	{
		if(playerInventory.getStoryKey())
		{
			ztransition = true;
		}
	}

	if(tempBool || tempBool2)
	{
		m_cam.setVel_y(0.0);
		if(moveJ)
		{
			m_cam.setVel_y(jumpPower);
		}
		lastXPos = m_cam.getPos_x();
		lastYPos = m_cam.getPos_y();
		lastZPos = m_cam.getPos_z();
	}
	else
	{
		float tempCamVelY = m_cam.getVel_y();
		objects.gravitize(tempCamVelY);
		m_cam.setVel_y(tempCamVelY);
	}

	if(tempBool3)
	{
		playerInventory.haveStoryKey(true);
		if((key.isPlaying() == 0) || (key.isPlaying() == 1))
		{
			key.play();
		}
	}

	if(tempBoolDoor)
	{
		if(zombies.size() <= zombieLimit)
		{
			createZombies();
		}
		if((open.isPlaying() == 0) || (open.isPlaying() == 1))
		{
			open.play();
		}
	}
	else if(tempBool4)
	{
		if((lock.isPlaying() == 0) || (lock.isPlaying() == 1))
		{
			if(lockTimer >= 50.0)
			{
				lock.play();
				lockTimer = 0;
			}
		}
	}
	if(lockTimer < 50.0)
	{
		lockTimer += 1.0;
	}
	else if(lockTimer > 50.0)
	{
		lockTimer = 50.0;
	}

	if((playerInventory.getStoryKey()) && (tempBool4))
	{
		ztransition = true;
	}

	m_cam.calcYVel(objects.getFrameTime());

	if(moveF)
	{
		m_cam.Move(player.getWalkSpeed());
		if((walk.isPlaying() == 0) || (walk.isPlaying() == 1))
		{
			walk.play();
		}
	}
	else
	{
		m_cam.Move(0);
	}
	if(moveB)
	{
		m_cam.Move(-(player.getWalkSpeed()));
		if((walk.isPlaying() == 0) || (walk.isPlaying() == 1))
		{
			walk.play();
		}
	}
	else
	{
		m_cam.Move(0);
	}
	if(moveL)
	{
		m_cam.strafe(-(player.getWalkSpeed()));
		if((walk.isPlaying() == 0) || (walk.isPlaying() == 1))
		{
			walk.play();
		}
	}
	else
	{
		m_cam.strafe(0);
	}
	if(moveR)
	{
		m_cam.strafe(player.getWalkSpeed());
		if((walk.isPlaying() == 0) || (walk.isPlaying() == 1))
		{
			walk.play();
		}
	}
	else
	{
		m_cam.strafe(0);
	}
	if(moveC)
	{
		if(playerHeight > playerAbsHeight / 2.0f)
		{
			playerHeight -= 5.0f;
		}
		else
		{
			playerHeight = playerAbsHeight / 2.0f;
			player.setWalkSpeed(player.getWalkAbsSpeed() * 0.4);
		}
	}
	else
	{
		if(playerHeight < playerAbsHeight)
		{
			playerHeight += 5.0f;
		}
		else
		{
			playerHeight = playerAbsHeight;
			player.setWalkSpeed(player.getWalkAbsSpeed());
		}
	}
	if(moveI)
	{
		if(objects.collidePipe(m_cam, cambox))
		{
			playerInventory.replaceItem1(1);
			objects.setTakenPipe(true);
		}
	}
	playerInventory.processItems();
	if(moveA)
	{
		pipeAnimation();
		pipeAnimTimer -= 1.0;
		if(pipeAnimTimer <= 0.0)
		{
			moveA = false;
			pipeAnimTimer = 5.0;
		}
	}
	else
	{
		playerInventory.setItem1XYZ(m_cam.getPos_x()+(-(m_cam.getView_z()-m_cam.getPos_z())*sin(-5.9)+(m_cam.getView_x()-m_cam.getPos_x())*cos(-5.9)), m_cam.getView_y()-10.0, m_cam.getPos_z()+((m_cam.getView_z()-m_cam.getPos_z())*cos(-5.9)+(m_cam.getView_x()-m_cam.getPos_x())*sin(-5.9)));
	}
}

void ZombieNight::drawZombies()
{
	// keySound
	//key = new Sound;
	//key->Load("music\key.wav");
	//key.setVolume(100);

	int i = 0;

	for(i = 0; i < zombies.size(); i++)
	{
		if(zombies[i]->getHealth() > 0.0)
		{
			zombies[i]->draw();
			keys[i]->setAquired(false);
		}
		else
		{
			if(zombies[i]->getSpawnCD() > 0)
			{
				zAABB tempBox;
				keys[i]->getMinMax(tempBox);
				zombies[i]->walk(false);
				zombies[i]->run(false);

				if(tempBox.isColliding(cambox))
				{
					keys[i]->setAquired(true);
					playerInventory.addKeys(1);
					key.play();
					keys[i]->setPos(zombies[i]->getXPos(), zombies[i]->getYPos() + 10000.0, zombies[i]->getZPos());
				}
				if(keys[i]->getAquired() == false)
				{
					keys[i]->setPos(zombies[i]->getXPos(), zombies[i]->getYPos() - 20.0, zombies[i]->getZPos());
				}
			}
		}
		keys[i]->draw();
	}
}

void ZombieNight::pipeAnimation()
{
	if(pipeAnimTimer >= 3.0)
	{
		playerInventory.setItem1XYZ(m_cam.getView_x(), m_cam.getView_y()-20.0, m_cam.getView_z());
		hitable = true;
	}
	else
	{
		hitable = false;
		playerInventory.setItem1XYZ(m_cam.getPos_x()+(-(m_cam.getView_z()-m_cam.getPos_z())*sin(-5.9)+(m_cam.getView_x()-m_cam.getPos_x())*cos(-5.9)), m_cam.getView_y()-10.0, m_cam.getPos_z()+((m_cam.getView_z()-m_cam.getPos_z())*cos(-5.9)+(m_cam.getView_x()-m_cam.getPos_x())*sin(-5.9)));
	}
}

void ZombieNight::moveKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		moveF = true;
		break;
	case 's':
	case 'S':
		moveB = true;
		break;
	case 'a':
	case 'A':
		moveL = true;
		break;
	case 'd':
	case 'D':
		moveR = true;
		break;
	case 'c':
	case 'C':
		moveC = true;
		break;
	case 'e':
	case 'E':
		moveI = true;
		break;
	case ' ':
		moveJ = true;
		break;
	}
}

void ZombieNight::nomoveKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		moveF = false;
		break;
	case 's':
	case 'S':
		moveB = false;
		break;
	case 'a':
	case 'A':
		moveL = false;
		break;
	case 'd':
	case 'D':
		moveR = false;
		break;
	case 'c':
	case 'C':
		moveC = false;
		break;
	case 'e':
	case 'E':
		moveI = false;
		break;
	case ' ':
		moveJ = false;
		break;
	case 27:
		ztransition = true;
		break;
	}
}

bool ZombieNight::getTransition()
{
	return ztransition;
}

void ZombieNight::setTransitionFalse()
{
	ztransition = false;
}

void ZombieNight::mouse(int button, int state, int x, int y)
{
	if((button == GLUT_LEFT_BUTTON)&& (state == GLUT_DOWN))
	{
		if(pipeAnimTimer == 5.0)
		{
			moveA = true;
		}
	}
}