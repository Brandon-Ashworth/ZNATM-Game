#pragma once

#include <math.h>
#include <Windows.h>

/**
 *  \brief struct that organises and keeps related data together
 *  
 *  \author group collaboration 
 */

struct camVec
{
	float m_x;
	float m_y;
	float m_z;

	/**
	 *  \brief default constructor with no inputs
	 */
	camVec(){}
	/**
	 *  \brief a constructor that assigns 3 points to the member variables 
	 */
	camVec(float new_x, float new_y, float new_z)
	{
		m_x = new_x;
		m_y = new_y;
		m_z = new_z;
	}

	/**
	 *  \brief overloads the + operator to allow for adding of multiple camVec types
	 */	
	camVec operator+(camVec vVector) {return camVec(vVector.m_x + m_x, vVector.m_y + m_y, vVector.m_z + m_z);}
	/**
	 *  \brief overloads the - operator to allow for subtracting  of multiple camVec types
	 */	
	camVec operator-(camVec vVector) {return camVec(m_x - vVector.m_x, m_y - vVector.m_y, m_z - vVector.m_z);}
	/**
	 *  \brief overloads the * operator to allow for multiplying of ... multiple camVec types
	 */	
	camVec operator*(float number)	 {return camVec(m_x * number, m_y * number, m_z * number);}
	/**
	 *  \brief overloads the / operator to allow for dividing of multiple camVec types
	 */	
	camVec operator/(float number)	 {return camVec(m_x / number, m_y / number, m_z / number);}

};
/**
 *  \brief 
 *  
 *  
 *  \bug
 *  \note
 *  \author Welsley Gai-Yeen Lui
 *  \date 
 */
class zCamera
{
public:

	zCamera();
	~zCamera();

	/**
	 *  \brief takes in a speed and applies that to the movement (left or right)
	 *  
	 *  \param float if the number is negative is will move right left for positive
	 */
	void strafe(float speed);

	/**
	 *  \brief takes the width and height of the window tries to keep the mouse the the centre of the window
	 *  
	 *  
	 *  \param int width, int height
	 *  \bug does not fulfill all of it's intended goals 
	 */	
	void Mouse(int Width,int Height);
	/**
	 *  \brief takes in a float number and moves the camera.
	 *  
	 *  This function takes in a float number as an input and moves the camera forward if it is positive and back if it is negative.
	 *  
	 *  \param float speed
	 */
	void Move(float speed);
	/**
	 *  \brief rotates the camera
	 *  
	 *  This function is called upon by one of our other function to assist in angling the mouse during camera
	 *  
	 *  \param float speed (speed at which the rotate will happen left = positive
	 */
	void Rotate(float speed);
	/**
	 *  \brief a set collection for this camera.
	 */
	void camPos(float pos_x, float pos_y,float pos_z,
			 	float view_x, float view_y, float view_z,
				float up_x,   float up_y,   float up_z);
	/**
	 *  \brief get x position of camera
	 *  
	 *  \param void
	 *  \return float xPosition
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	float getPos_x();
	/**
	 *  \brief get camera y position
	 *  
	 *  \param void
	 *  \return float yPosition
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	float getPos_y();
	/**
	 *  \brief get camera z position
	 *  
	 *  \param void
	 *  \return float zPosition
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	float getPos_z();
	/**
	 *  \brief sets camera x position
	 *  
	 *  \param float xPosition
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	void setPos_x(float x);
	/**
	 *  \brief sets camera y position
	 *  
	 *  \param float yPosition
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	void setPos_y(float y);
	/**
	 *  \brief sets camera z position
	 *  
	 *  \param float zPosition
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	void setPos_z(float z);
	/**
	 *  \brief gets x view position
	 *  
	 *  \param void
	 *  \return float xView
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	float getView_x();
	/**
	 *  \brief gets y view position
	 *  
	 *  \param void
	 *  \return float yView
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	float getView_y();
	/**
	 *  \brief gets z view position
	 *  
	 *  \param void
	 *  \return float zView
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	float getView_z();
	/**
	 *  \brief sets x view Position
	 *  
	 *  \param float xPosition
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	void setView_x(float x);
	/**
	 *  \brief sets y view position
	 *  
	 *  \param float yPosition
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	void setView_y(float y);
	/**
	 *  \brief sets z view position
	 *  
	 *  \param float zPosition
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	void setView_z(float z);
	/**
	 *  \brief get the Roll on the x axis
	 *  
	 *  \param void
	 *  \return float xUp
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	float getUp_x();
	/**
	 *  \brief get the Roll on the y axis
	 *  
	 *  \param void
	 *  \return float yUp
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	float getUp_y();
	/**
	 *  \brief get the Roll on the z axis
	 *  
	 *  \param void
	 *  \return float zUp
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	float getUp_z();
	/**
	 *  \brief get the x velocity
	 *  
	 *  \param void
	 *  \return float xVelocity
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	float getVel_x();
	/**
	 *  \brief get the y velocity
	 *  
	 *  \param void
	 *  \return float yVerlocity
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	float getVel_y();
	/**
	 *  \brief get the z velocity
	 *  
	 *  \param void
	 *  \return float zVelocity
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	float getVel_z();
	/**
	 *  \brief set the y velocity
	 *  
	 *  \param float yVelocity
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui, Brandon Ashworth, Umar Badat
	 *  \date
	 */
	void setVel_y(float y);

	/**
	 *  \brief allows for ascending and descending through jumping and gravity.
	 *  
	 *  \param float frameTime for the "time" factor in velocity calculations.
	 */
	void calcYVel(float frameTime);

private:
	camVec m_Pos;
	camVec m_View;
	camVec m_up;
	camVec m_Vel;
};