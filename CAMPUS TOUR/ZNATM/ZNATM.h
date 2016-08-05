#pragma once

#include "../freeglut.h"
#include <vector>
#include "zCamera.h"
#include "zAABB.h"
#include "zObject.h"
#include "zInventory.h"
#include "zZombie.h"
#include "zPlayer.h"
#include "zKey.h"
#include <cmath>
#include <vector>
#include "Sound.h"
#include <sstream>
#include <string>

class ZombieNight
{
public:
	ZombieNight();
	~ZombieNight();
	void drawWorld();
	void initialize();
	bool getTransition();
	void setTransitionFalse();


private:
	static void draw();
	static void AABBWireframe(bool wireframe, GLfloat thickness);
	static void reshape(int w, int h);
	static void idle();
	static void moveKeyboard(unsigned char key, int x, int y);
	static void nomoveKeyboard(unsigned char key, int x, int y);
	static void calcTime();
	static void createZombies();
	static void drawZombies();
	static void spawnZombies(zZombie &z, zKey &k);
	static void pipeAnimation();
	static void drawHUD();
	static void mouse(int button, int state, int x, int y);
};