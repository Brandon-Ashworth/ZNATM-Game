#pragma once

#include "Loader.h"
#include <string>
#include "zAABB.h"
#include <time.h>

struct zcamVec
{
	float m_x;
	float m_y;
	float m_z;

	/**
	 *  \brief default constructor with no inputs
	 */
	zcamVec(){}
	/**
	 *  \brief a constructor that assigns 3 points to the member variables 
	 */
	zcamVec(float new_x, float new_y, float new_z)
	{
		m_x = new_x;
		m_y = new_y;
		m_z = new_z;
	}

	/**
	 *  \brief overloads the + operator to allow for adding of multiple camVec types
	 */	
	zcamVec operator+(zcamVec vVector) {return zcamVec(vVector.m_x + m_x, vVector.m_y + m_y, vVector.m_z + m_z);}
	/**
	 *  \brief overloads the - operator to allow for subtracting  of multiple camVec types
	 */	
	zcamVec operator-(zcamVec vVector) {return zcamVec(m_x - vVector.m_x, m_y - vVector.m_y, m_z - vVector.m_z);}
	/**
	 *  \brief overloads the * operator to allow for multiplying of ... multiple camVec types
	 */	
	zcamVec operator*(float number)	 {return zcamVec(m_x * number, m_y * number, m_z * number);}
	/**
	 *  \brief overloads the / operator to allow for dividing of multiple camVec types
	 */	
	zcamVec operator/(float number)	 {return zcamVec(m_x / number, m_y / number, m_z / number);}
};

/**
 *  \brief handles the zombie details
 *  
 *  
 *  \bug
 *  \note
 *  \author Welsley Gai-Yeen Lui
 *  \date 
 */
class zZombie
{
public:
	/**
	 *  \brief sets the zombie vairables
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	zZombie();
	/**
	 *  \brief sets the zombie details and creates the model
	 *  
	 *  
	 *  \param string objLocation
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	zZombie(std::string l);
	~zZombie();
	/**
	 *  \brief gets the zombies health
	 *  
	 *  
	 *  \param void
	 *  \return float Health
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getHealth();
	/**
	 *  \brief gets the walk speed of the zombie
	 *  
	 *  
	 *  \param void
	 *  \return float speed
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getWalkSpeed();
	/**
	 *  \brief gets the zombies run speed
	 *  
	 *  
	 *  \param void
	 *  \return float speed
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getRunSpeed();
	/**
	 *  \brief gets the zombies damage
	 *  
	 *  
	 *  \param void
	 *  \return float Damage
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getDamage();
	/**
	 *  \brief gets the X position
	 *  
	 *  
	 *  \param void
	 *  \return float xPosition
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getXPos();
	/**
	 *  \brief gets y position
	 *  
	 *  
	 *  \param void 
	 *  \return float yPosition
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getYPos();
	/**
	 *  \brief gets z position
	 *  
	 *  
	 *  \param void 
	 *  \return float zPosition
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getZPos();

	/**
	 *  \brief gets the X view
	 *  
	 *  
	 *  \param void
	 *  \return float xView
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getViewX();
	/**
	 *  \brief gets the Y View
	 *  
	 *  
	 *  \param void
	 *  \return float zView
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getViewZ();
	/**
	 *  \brief get x minimum 
	 *  
	 *  
	 *  \param void
	 *  \return float xMinimum
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getMinX();
	/**
	 *  \brief get x maximum 
	 *  
	 *  
	 *  \param void
	 *  \return float xMaximum 
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 */
	float getMaxX();
	/**
	 *  \brief get y minimum
	 *  
	 *  
	 *  \param void
	 *  \return float yMinimum
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getMinY();
	/**
	 *  \brief get y Maximum
	 *  
	 *  
	 *  \param void
	 *  \return float yMaximum 
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getMaxY();
	/**
	 *  \brief get z minimum
	 *  
	 *  
	 *  \param void
	 *  \return float zMinimum
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getMinZ();
	/**
	 *  \brief get z maximum 
	 *  
	 *  
	 *  \param void
	 *  \return float zMaximum
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getMaxZ();
	/**
	 *  \brief get Y velocity
	 *  
	 *  
	 *  \param void
	 *  \return float yVelocity
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getVelY();
	/**
	 *  \brief returns the direction timer, counts down till changes direction
	 *  
	 *  
	 *  \param void
	 *  \return int directionTime
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	int getDirectionTimer();
	/**
	 *  \brief returns spawn count down
	 *  
	 *  
	 *  \param void
	 *  \return int CoolDown
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	int getSpawnCD();
	/**
	 *  \brief sets the zombies health
	 *  
	 *  
	 *  \param float health
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setHealth(float h);
	/**
	 *  \brief sets the zombie walk speed
	 *  
	 *  
	 *  \param float WalkSpeed
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setWalkSpeed(float ws);
	/**
	 *  \brief sets the zombie run speed
	 *  
	 *  
	 *  \param float run speed
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setRunSpeed(float rs);
	/**
	 *  \brief sets zombie damage
	 *  
	 *  
	 *  \param float damage
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setDamage(float d);
	/**
	 *  \brief sets the zombie's view 
	 *  
	 *  
	 *  \param float x
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setDesiredViewX(float x);
	/**
	 *  \brief sets the zombies view
	 *  
	 *  
	 *  \param float z
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setDesiredViewZ(float z);
	/**
	 *  \brief sets the zombies velocity
	 *  
	 *  
	 *  \param float yVelocity
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setVelY(float y);
	/**
	 *  \brief sets the zombie position
	 *  
	 *  
	 *  \param float x, float y, float z
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setPos(float x, float y, float z);
	/**
	 *  \brief set the zombie back to it's initial position
	 *  
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setInitPos();
	/**
	 *  \brief assigns a model to the zombie class
	 *  
	 *  
	 *  \param string ObjLocation
	 *  \return 
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setZombieModelLocation(std::string l);
	/**
	 *  \brief draws the model
	 *  
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void draw();
	/**
	 *  \brief sets the zombie to walk speed
	 *  
	 *  
	 *  \param bool
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void walk(bool w);
	/**
	 *  \brief sets the zombie to run speed
	 *  
	 *  
	 *  \param bool
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void run(bool r);
	/**
	 *  \brief calculate y velocity
	 *  
	 *  
	 *  \param float frameTime
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void calcYVel(float frameTime);
	/**
	 *  \brief set direction timer
	 *  
	 *  
	 *  \param int time
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setDirectionTimer(int t);
	/**
	 *  \brief sets spawn cool down
	 *  
	 *  
	 *  \param int coolDown
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setSpawnCD(int cd);
	/**
	 *  \brief find the width, depth and height of the zombie
	 *  
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void findPos();
	/**
	 *  \brief calculate the maximum and minimum
	 *  
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void calcMinMax();
	/**
	 *  \brief randomises the direction they move
	 *  
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void randomizeDirection();
	/**
	 *  \brief calculates last position view
	 *  
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void calcLastPosView();
	/**
	 *  \brief finds last x position
	 *  
	 *  
	 *  \param void
	 *  \return float xPosition
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getLastXPos();
	/**
	 *  \brief finds last y position
	 *  
	 *  
	 *  \param void
	 *  \return float yPosition
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getLastYPos();
	/**
	 *  \brief finds last z position
	 *  
	 *  
	 *  \param zPosition
	 *  \return float zPosition
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getLastZPos();
	/**
	 *  \brief finds last x view
	 *  
	 *  
	 *  \param void
	 *  \return float xView
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getLastXView();
	/**
	 *  \brief finds last Z view
	 *  
	 *  
	 *  \param void
	 *  \return float zView
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getLastZView();

private:
	float m_health;
	float m_walkSpeed;
	float m_runSpeed;
	float m_damage;
	std::string m_zombieModelLocation;
	Loader m_zModel;
	float m_MinX;
	float m_MaxX;
	float m_width;
	float m_MinY;
	float m_MaxY;
	float m_height;
	float m_MinZ;
	float m_MaxZ;
	float m_depth;
	float m_VelY;
	zcamVec m_Pos;
	zcamVec m_View;
	zcamVec m_lastPos;
	zcamVec m_lastView;
	int m_directionTimer;
	int m_spawnCD;
	std::vector<std::string> imgLoc;
	std::vector<GLuint> imgTex;
};