#include "ShayWorld.h"
#include "ZNATM\ZNATM.h"
#include "freeglut.h"
#include "lib\IL\il.h"
#include "lib\IL\ilu.h"
#include "lib\IL\ilut.h"

#include "ZNATM\Sound.h"
#include "ZNATM\MTL.h"

//--------------------------------------------------------------------------------------
//  Main function 
//--------------------------------------------------------------------------------------

void Mouse(int, int, int, int);
void movementKeys(int, int, int);
void releaseKey(int, int, int);
void releaseKeys(unsigned char, int, int);
void keys(unsigned char, int, int);
void reshape(int, int);

int main(int argc, char **argv)
{
	static bool firstRun = true;
	GLint oldLight;
	GLint lol;


	Sound Key(1);
	Key.Load("key.wav");
	Key.setRep(1);
	//Key.play();
	ZombieNight* zombienight = new ZombieNight;
	std::vector<std::string> imgLoc;
	std::vector<GLuint> imgTex;
	//MTL* lighter = new MTL(&imgLoc, &imgTex);

	ShayWorld* shayworld = new ShayWorld; // This is a good name for a Shay's World object

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,500);
	glutCreateWindow("Murdoch University Campus Tour");

	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	int counter = 0;
	int scounter = 0;
	//glutMainLoop();

	while(1)
	{
		if(!shayworld->getTransition())//!shayworld.getTransition()
		{
			glutSetCursor(GLUT_CURSOR_INHERIT);
			if (scounter == 0)
			{
				shayworld->myinit();
				if(firstRun)
				{
					
					glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &lol);
					//oldLight = lighter->findLight();
					firstRun = false;
				}
				scounter++;
			}
			//lighter.noLight();
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,lol);
			glutMainLoopEvent();
			shayworld->Step();
			counter = 0;
		}
		else
		{
			//ZombieNight* zombienight = new ZombieNight;
			glutSetCursor(GLUT_CURSOR_NONE);
			scounter = 0;
			if(!zombienight->getTransition())
			{
				if (counter == 0)
				{
					zombienight->initialize();

					counter++;
				}
				//lighter.ourLight();
				glutMainLoopEvent();
				zombienight->drawWorld();
			}
			else
			{
				//ShayWorld* shayworld = new ShayWorld;
				zombienight->setTransitionFalse();
				shayworld->setTransitionFalse();
			}
		}
	}
	
	// ONLY USE IF REQUIRE MOUSE MOVEMENT
	//glutPassiveMotionFunc(mouseMove);
	//ShowCursor(FALSE);

	//glutMainLoop();
	return(0);
}
