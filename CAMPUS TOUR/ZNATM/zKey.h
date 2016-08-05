#pragma once

#include <string>
#include "Loader.h"
#include "zAABB.h"

/**
 *  \brief handles the keys in the game
 *  
 *  
 *  \bug
 *  \note
 *  \author Welsley Gai-Yeen Lui
 *  \date 
 */
class zKey
{
public:
	/**
	 *  \brief constructor 
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	zKey();
	/**
	 *  \brief generate an object based on the 
	 *  
	 *  
	 *  \param string objLocation
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	zKey(std::string l);
	~zKey();
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
	 *  \brief finds the depth,width and height
	 *  
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void findBox();
	/**
	 *  \brief sets the position of the object
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
	 *  \brief gets the Y Position
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
	 *  \brief gets the z Position
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
	 *  \brief 
	 *  
	 *  
	 *  \param 
	 *  \return 
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void getMinMax(zAABB &tempBox);
	/**
	 *  \brief 
	 *  
	 *  
	 *  \param 
	 *  \return 
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setInitPos();
	/**
	 *  \brief 
	 *  
	 *  
	 *  \param 
	 *  \return 
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void calcMinMax();
	/**
	 *  \brief 
	 *  
	 *  
	 *  \param void
	 *  \return bool - returns true if it has been collected
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	bool getAquired();
	/**
	 *  \brief 
	 *  
	 *  
	 *  \param bool 
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setAquired(bool a);

private:
	bool m_aquired;
	float m_xPos;
	float m_yPos;
	float m_zPos;
	float m_width;
	float m_height;
	float m_depth;
	float m_maxX;
	float m_minX;
	float m_maxY;
	float m_minY;
	float m_maxZ;
	float m_minZ;
	Loader m_models;
	std::vector<std::string> imgLoc;
	std::vector<GLuint> imgTex;
};