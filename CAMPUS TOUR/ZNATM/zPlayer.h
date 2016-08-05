#pragma once

/**
 *  \brief handles the player
 *  
 *  
 *  \bug
 *  \note
 *  \author Welsley Gai-Yeen Lui
 *  \date 
 */
class zPlayer
{
public:
	zPlayer();
	~zPlayer();
	/**
	 *  \brief gets the helth of the player
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
	 *  \brief gets the walk speed of the player
	 *  
	 *  
	 *  \param void
	 *  \return float Speed
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getWalkSpeed();
	/**
	 *  \brief gets the original speed of the player
	 *  
	 *  
	 *  \param void
	 *  \return float speed
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	float getWalkAbsSpeed();
	/**
	*	\brief gets the attack damage of the plaer
	*
	*	\param void
	*	\return float PlayerDamage
	*
	*	\author Welsley Gai-Yeen Lui
	*/
	float getDamage();
	/**
	 *  \brief sets the players health
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
	 *  \brief sets the walk speed of the player
	 *  
	 *  
	 *  \param float walkSpeed
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setWalkSpeed(float ws);
	/**
	 *  \brief sets the original walkSpeed of the player
	 *  
	 *  
	 *  \param float walkSpeed
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setWalkAbsSpeed(float was);
	/**
	 *  \brief sets the damage the player can deal
	 *  
	 *  
	 *  \param float DamageInput
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setDamage(float d);

private:
	float m_health;
	float m_walkSpeed;
	float m_walkAbsSpeed;
	float m_damage;
};