#include "zKey.h"

zKey::zKey()
{
	m_aquired = false;
}

zKey::zKey(std::string l)
{
	m_aquired = false;
	m_models.process(l, &imgLoc, &imgTex);
}

zKey::~zKey()
{

}

void zKey::draw()
{
	m_models.draw();
}

void zKey::findBox()
{
	m_models.find_box(m_maxX, m_minX, m_maxY, m_minY, m_maxZ, m_minZ);
	
	m_width = m_maxX - m_minX;
	m_height = m_maxY - m_minY;
	m_depth = m_maxZ - m_minZ;
}

void zKey::setPos(float x, float y, float z)
{
	m_models.move(x - m_xPos, y - m_yPos, z - m_zPos);
	m_xPos = x;
	m_yPos = y;
	m_zPos = z;
}

float zKey::getXPos()
{
	return m_xPos;
}

float zKey::getYPos()
{
	return m_yPos;
}

float zKey::getZPos()
{
	return m_zPos;
}

void zKey::getMinMax(zAABB &tempBox)
{
	tempBox.SetX(m_xPos - m_width/2.0, m_xPos + m_width/2.0);
	tempBox.SetY(m_yPos - m_height/2.0, m_yPos + m_height/2.0);
	tempBox.SetZ(m_zPos - m_depth/2.0, m_zPos + m_depth/2.0);
}

void zKey::setInitPos()
{
	m_xPos = m_maxX - (m_width/2.0);
	m_yPos = m_maxY - (m_height/2.0);
	m_zPos = m_maxZ - (m_depth/2.0);
}

void zKey::calcMinMax()
{
	m_minX = m_xPos - (m_width/2.0);
	m_maxX = m_xPos + (m_width/2.0);
	m_minY = m_yPos - (m_height/2.0);
	m_maxY = m_yPos + (m_height/2.0);
	m_minZ = m_zPos - (m_depth/2.0);
	m_maxZ = m_zPos + (m_depth/2.0);
}

bool zKey::getAquired()
{
	return m_aquired;
}

void zKey::setAquired(bool a)
{
	m_aquired = a;
}