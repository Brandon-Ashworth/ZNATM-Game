#include "zAABB.h"

zAABB::zAABB()
{
	m_XMin = 0;
	m_XMax = 1;
	m_YMin = 0;
	m_YMax = 1;
	m_ZMin = 0;
	m_ZMax = 1;
}

zAABB::zAABB(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
	m_XMin = xmin;
	m_XMax = xmax;
	m_YMin = ymin;
	m_YMax = ymax;
	m_ZMin = zmin;
	m_ZMax = zmax;
}

zAABB::~zAABB()
{
}

void zAABB::SetX(float xmin, float xmax)
{
	m_XMin = xmin;
	m_XMax = xmax;
}

float zAABB::GetXMin() const
{
	return m_XMin;
}

float zAABB::GetXMax() const
{
	return m_XMax;
}

void zAABB::SetY(float ymin, float ymax)
{
	m_YMin = ymin;
	m_YMax = ymax;
}

float zAABB::GetYMin() const
{
	return m_YMin;
}

float zAABB::GetYMax() const
{
	return m_YMax;
}

void zAABB::SetZ(float zmin, float zmax)
{
	m_ZMin = zmin;
	m_ZMax = zmax;
}

float zAABB::GetZMin() const
{
	return m_ZMin;
}

float zAABB::GetZMax() const
{
	return m_ZMax;
}

bool zAABB::isColliding(const zAABB &bbox) const
{
	if (m_XMin > bbox.GetXMax())
	{
		return false;
	}
	if (m_XMax < bbox.GetXMin())
	{
		return false;
	}
	if(m_YMin > bbox.GetYMax())
	{
		return false;
	}
	if(m_YMax < bbox.GetYMin())
	{
		return false;
	}
	if(m_ZMin > bbox.GetZMax())
	{
		return false;
	}
	if(m_ZMax < bbox.GetZMin())
	{
		return false;
	}
	return true;
}

bool zAABB::isColliding(const zAABB* bbox) const
{
	if (m_XMin > bbox->GetXMax())
	{
		return false;
	}
	if (m_XMax < bbox->GetXMin())
	{
		return false;
	}
	if(m_YMin > bbox->GetYMax())
	{
		return false;
	}
	if(m_YMax < bbox->GetYMin())
	{
		return false;
	}
	if(m_ZMin > bbox->GetZMax())
	{
		return false;
	}
	if(m_ZMax < bbox->GetZMin())
	{
		return false;
	}
	return true;
}