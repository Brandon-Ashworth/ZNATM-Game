#pragma once

#include "Loader.h"
#include "..\freeglut.h"
#include "zAABB.h"
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <math.h>
#include <time.h>
#include "zCamera.h"
#include "zZombie.h"
#include "zInventory.h"

class zObject
{
public:
	zObject();
	~zObject();
	void load();
	void draw();
	bool collideStatic(zCamera &tempCam, const zAABB &tempBox);
	bool collideStair(zCamera &tempCam, const zAABB &tempBox, float camHeight);
	bool collideZStatic(zZombie *tempZombie, const zAABB &tempBox);
	bool collideZStair(zZombie *tempZombie, const zAABB &tempBox);
	void AABBWireframeStaticOn();
	void gravityObjects();
	void gravitize(float &y);
	float getFrameTime();
	void calcTime();
	bool collideStoryKey(const zAABB &tempBox);
	bool collideDoor(zCamera &tempCam, const zAABB &tempBox, zInventory &tempInventory, bool &opened);
	bool collideFirstDoor(zCamera &tempCam, const zAABB &tempBox, zInventory tempInventory);
	bool collideZFirstDoor(zZombie &tempZombie, const zAABB &tempBox);
	bool collideZDoor(zZombie &z, const zAABB &tempBox);
	bool collidePipe(zCamera &tempCam, const zAABB &tempBox);
	bool collideStoryDoor(zCamera &tempCam, const zAABB &tempBox);
	void setTakenPipe(bool t);
	void setstoryKeyAquired(bool a);
	bool getstoryKeyAquired();
	bool getKeyMoved();
	void setKeyMoved(bool k);

private:

	float m_lastTime;
	float m_frameTime;
	float m_gravity;
	int m_storyKeyNo;
	bool m_storyKeyAquired;
	int m_firstDoorNo;
	bool m_firstDoorOpened;
	int m_storyDoorNo;
	bool m_storyDoorOpened;
	int m_pipeNo;
	bool m_takenPipe;
	std::ifstream m_inFile;
	std::map<std::string, std::string> m_oList;
	std::vector<Loader*> m_models;
	std::vector<std::string> m_types;
	std::vector<zAABB*> m_box;
	std::vector<int> m_staticNo;
	std::vector<int> m_stairNo;
	std::vector<int> m_nothingNo;
	std::vector<int> m_doorNo;
	std::vector<int> m_doorOpened;
	std::vector<std::string> imgLoc;
	std::vector<GLuint> imgTex;
	bool m_keymoved;
	float storyKeyPosXMin;
	float storyKeyPosXMax;
	float storyKeyPosYMin;
	float storyKeyPosYMax;
	float storyKeyPosZMin;
	float storyKeyPosZMax;
	float storyKeyTransitionedX;
	float storyKeyTransitionedY;
	float storyKeyTransitionedZ;

	void superDraw(const std::vector<int> &number);
	void superDraw(const int &number);
};