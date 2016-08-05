#pragma once

#include "Loader.h"
#include <string>

struct bag
{
	int m_item1;
	int m_item2;
	int m_keys;
	bool m_storyKey;

	bag(){}

	bag(int item1, int item2, int keys, bool storyKey)
	{
		m_item1 = item1;
		m_item2 = item2;
		m_keys = keys;
		m_storyKey = storyKey;
	}
};

/**
 *  \brief handles the inventory of the player
 *  
 *  
 *  \bug
 *  \note
 *  \author Welsley Gai-Yeen Lui
 *  \date 
 */
class zInventory
{
public:
	/**
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	zInventory();
	~zInventory();
	/**
	 *  \brief passes in an item number
	 *  
	 *  
	 *  \param int item
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void replaceItem1(int item1);
	/**
	 *  \brief gets the item number
	 *  
	 *  
	 *  \param void
	 *  \return int item
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	int getItem1();
	/**
	 *  \brief passes in another item number
	 *  
	 *  
	 *  \param int item2
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void replaceItem2(int item2);
	/**
	 *  \brief gets the item number
	 *  
	 *  
	 *  \param void
	 *  \return int item2
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	int getItem2();
	/**
	 *  \brief adds keys to the inventory
	 *  
	 *  
	 *  \param int keyNumber
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void addKeys(int keys);
	/**
	 *  \brief sets if the player has the story key or not
	 *  
	 *  
	 *  \param bool storyKey
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void haveStoryKey(bool storyKey);
	/**
	 *  \brief checks if the player has the story key
	 *  
	 *  
	 *  \param void
	 *  \return bool hasKey  
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	bool getStoryKey();
	/**
	 *  \brief checks to see how many silver key the player has
	 *  
	 *  
	 *  \param void
	 *  \return int keyNumber
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	int getKeys();
	/**
	 *  \brief 
	 *  
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void processItems();
	/**
	 *  \brief
	 *  
	 *  
	 *  \param float x, float y, float z
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setItem1XYZ(float x, float y, float z);
	/**
	 *  \brief
	 *  
	 *  
	 *  \param float x, float y, float z
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void setItem2XYZ(float x, float y, float z);

	float getItem1X();
	float getItem1Y();
	float getItem1Z();
	float getItem2X();
	float getItem2Y();
	float getItem2Z();
	/**
	 *  \brief swaps the item with the secondary
	 *  
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void swapItems();
	/**
	 *  \brief
	 *  
	 *  
	 *  \param string
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void addItemLoc(std::string l);
	/**
	 *  \brief
	 *  
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void removeLastItemLoc();
	/**
	 *  \brief sets the item object to draw
	 *  
	 *  
	 *  \param void
	 *  \return void
	 *  
	 *  \author Welsley Gai-Yeen Lui
	 *  \date
	 */
	void drawItems();

	void setKeys(int k);

private:
	bag m_inventory;
	std::vector<std::string> m_itemLoc;
	Loader* m_item[2];
	float m_xPos[2];
	float m_yPos[2];
	float m_zPos[2];
	float m_width[2];
	float m_height[2];
	float m_depth[2];
	float m_maxX[2];
	float m_minX[2];
	float m_maxY[2];
	float m_minY[2];
	float m_maxZ[2];
	float m_minZ[2];
	std::vector<std::string> imgLoc;
	std::vector<GLuint> imgTex;
};