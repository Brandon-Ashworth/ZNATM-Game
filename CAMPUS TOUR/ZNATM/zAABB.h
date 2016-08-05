#pragma once

class zAABB
{
public:
	/**
	 *  \brief 
	 *  
	 *  \author 
	 *  \date 
	 */
	zAABB();
	/**
	 *  \brief constructor 
	 *  
	 *  \param float, float, float, float, float, float 
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	zAABB(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
	~zAABB();
	/**
	 *  \brief sets the xmin and xmax
	 *  
	 *  \param  float, float
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void SetX(float xmin, float xmax);
	/**
	 *  \brief retrieve the minimum x
	 *  
	 *  
	 *  \param void
	 *  \return const float
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float GetXMin() const;
	/**
	 *  \brief retrieve the x Maximum 
	 *  
	 *  \param void
	 *  \return const float
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float GetXMax() const;
	/**
	 *  \brief sets the y min and y max
	 *  
	 *  \param float, float
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void SetY(float ymin, float ymax);
	/**
	 *  \brief gets the y minimum 
	 *  
	 *  \param void
	 *  \return const float
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float GetYMin() const;
	/**
	 *  \brief gets the Y maximum 
	 *  
	 *  \param void
	 *  \return const float
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float GetYMax() const;
	/**
	 *  \brief set the Z minimum and Maximum
	 *  
	 *  \param float xmin, float xMax
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void SetZ(float zmin, float zmax);
	/**
	 *  \brief gets the minimum Z
	 *  
	 *  \param void
	 *  \return const float
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float GetZMin() const;
	/**
	 *  \brief gets the Maximum Z
	 *  
	 *  \param void
	 *  \return const float zMax
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float GetZMax() const;
	/**
	 *  \brief checks the collision 
	 *  
	 *  \param const zAABB &bbox
	 *  \return const bool - if collision return true
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	bool isColliding(const zAABB &bbox) const;
		/**
	 *  \brief check for collision
	 *  
	 *  \param const zAABB *bbox
	 *  \return const bool - if collision return true
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	bool isColliding(const zAABB* bbox) const;

private:
	float m_XMin;
	float m_XMax;
	float m_YMin;
	float m_YMax;
	float m_ZMin;
	float m_ZMax;
};