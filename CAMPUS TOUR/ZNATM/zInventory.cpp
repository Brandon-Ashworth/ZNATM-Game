#include "zInventory.h"

zInventory::zInventory()
{
	m_inventory.m_item1 = 0;
	m_inventory.m_item2 = 0;
	m_inventory.m_keys = 0;
	m_inventory.m_storyKey = false;
	m_item[0] = NULL;
	m_item[1] = NULL;
}

zInventory::~zInventory()
{

}

void zInventory::replaceItem1(int item1)
{
	m_inventory.m_item1 = item1;
}

int zInventory::getItem1()
{
	return m_inventory.m_item1;
}

void zInventory::replaceItem2(int item2)
{
	m_inventory.m_item2 = item2;
}

int zInventory::getItem2()
{
	return m_inventory.m_item2;
}

void zInventory::addKeys(int keys)
{
	m_inventory.m_keys += keys;
}

void zInventory::haveStoryKey(bool storyKey)
{
	m_inventory.m_storyKey = storyKey;
}

bool zInventory::getStoryKey()
{
	return m_inventory.m_storyKey;
}

int zInventory::getKeys()
{
	return m_inventory.m_keys;
}

void zInventory::processItems()
{
	switch(m_inventory.m_item1)
	{
	case 1:
		if(m_item[0] == NULL)
		{
			m_item[0] = new Loader(m_itemLoc[m_inventory.m_item1 - 1], &imgLoc, &imgTex);
			m_item[0]->find_box(m_maxX[0], m_minX[0], m_maxY[0], m_minY[0], m_maxZ[0], m_minZ[0]);
			m_xPos[0] = (m_maxX[0] - m_minX[0])/2.0 + m_minX[0];
			m_yPos[0] = (m_maxY[0] - m_minY[0])/2.0 + m_minY[0];
			m_zPos[0] = (m_maxZ[0] - m_minZ[0])/2.0 + m_minZ[0];
		}
		break;
		// Could add more items here in the future.
	}
	switch(m_inventory.m_item2)
	{
	case 1:
		if(m_item[1] == NULL)
		{
			m_item[1] = new Loader(m_itemLoc[m_inventory.m_item2 - 1], &imgLoc, &imgTex);
			m_item[1]->find_box(m_maxX[1], m_minX[1], m_maxY[1], m_minY[1], m_maxZ[1], m_minZ[1]);
			m_xPos[1] = (m_maxX[1] - m_minX[1])/2.0 + m_minX[1];
			m_yPos[1] = (m_maxY[1] - m_minY[1])/2.0 + m_minY[1];
			m_zPos[1] = (m_maxZ[1] - m_minZ[1])/2.0 + m_minZ[1];
		}
		break;
		// Could add more items here in the future.
	}
}

void zInventory::setItem1XYZ(float x, float y, float z)
{
	if(m_inventory.m_item1 != 0)
	{
		m_item[0]->move(x - m_xPos[0], y - m_yPos[0], z - m_zPos[0]);
		m_xPos[0] = x;
		m_yPos[0] = y;
		m_zPos[0] = z;
	}
}

void zInventory::setItem2XYZ(float x, float y, float z)
{
	if(m_inventory.m_item2 != 0)
	{
		m_item[1]->move(x - m_xPos[1], y - m_yPos[1], z - m_zPos[1]);
		m_xPos[1] = x;
		m_yPos[1] = y;
		m_zPos[1] = z;
	}
}

float zInventory::getItem1X()
{
	return m_xPos[0];
}

float zInventory::getItem1Y()
{
	return m_yPos[0];
}

float zInventory::getItem1Z()
{
	return m_zPos[0];
}

float zInventory::getItem2X()
{
	return m_xPos[1];
}

float zInventory::getItem2Y()
{
	return m_yPos[1];
}

float zInventory::getItem2Z()
{
	return m_zPos[1];
}

void zInventory::swapItems()
{
	Loader* tempItem = m_item[0];
	m_item[0] = m_item[1];
	m_item[1] = m_item[0];
}

void zInventory::addItemLoc(std::string l)
{
	m_itemLoc.push_back(l);
}

void zInventory::removeLastItemLoc()
{
	m_itemLoc.pop_back();
}

void zInventory::drawItems()
{
	if(m_inventory.m_item1 != 0)
	{
		m_item[0]->draw();
	}
}

void zInventory::setKeys(int k)
{
	m_inventory.m_keys = k;
}