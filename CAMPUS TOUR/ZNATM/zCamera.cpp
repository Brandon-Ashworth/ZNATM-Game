#include "zCamera.h"

zCamera::zCamera()
{
	m_Pos.m_x = 0.0f;
	m_Pos.m_y = 5.0f;
	m_Pos.m_z = 5.0f;
	m_View.m_x = 0.0f;
	m_View.m_y = 5.0f;
	m_View.m_z = 0.0f;
	m_up.m_x = 0.0f;
	m_up.m_y = 1.0f;
	m_up.m_z = 0.0f;
	m_Vel.m_x = 0.0f;
	m_Vel.m_y = 0.0f;
	m_Vel.m_z = 0.0f;
}

zCamera::~zCamera()
{

}

void zCamera::camPos(float pos_x, float pos_y,float pos_z,
			 	     float view_x, float view_y, float view_z,
				     float up_x,   float up_y,   float up_z)
{
	m_Pos = camVec(pos_x, pos_y, pos_z);
	m_View = camVec(view_x, view_y, view_z);
	m_up = camVec(up_x, up_y, up_z);
}

void zCamera::Move(float speed)
{
	camVec view = m_View - m_Pos;

	m_Pos.m_x += view.m_x * speed;
	m_Pos.m_z += view.m_z * speed;
	m_View.m_x += view.m_x * speed;
	m_View.m_z += view.m_z * speed;
}

void zCamera::Rotate(float speed)
{
	camVec view = m_View - m_Pos;

	m_View.m_z = (float) (m_Pos.m_z + sin(speed) * view.m_x + cos(speed)*view.m_z);
	m_View.m_x = (float) (m_Pos.m_x + cos(speed) * view.m_x - sin(speed) *view.m_z);
}

void zCamera::strafe(float speed)
{
	camVec view = m_View - m_Pos;
	camVec ortho;

	ortho.m_x = -view.m_z;
	ortho.m_z = view.m_x;

	m_Pos.m_x += ortho.m_x * speed;
	m_Pos.m_z += ortho.m_z * speed;
	m_View.m_x += ortho.m_x * speed;
	m_View.m_z += ortho.m_z * speed;
}

void zCamera::Mouse(int Width,int Height)
{
	POINT mousePos;
	int mid_x = Width >> 1;
	int mid_y = Height >> 1;
	float angle_y = 0.0f;
	float angle_z = 0.0f;

	GetCursorPos(&mousePos);

	if ((mousePos.x == mid_x) && (mousePos.y == mid_y))
		return;

	SetCursorPos(mid_x, mid_y);

	angle_y = (float) ((mid_x - mousePos.x)) /1000;
	angle_z = (float) ((mid_y - mousePos.y)) /250;

	//alter the speed looking around
	m_View.m_y += angle_z *2;

	//rotaion limit
	if((m_View.m_y - m_Pos.m_y) > 60)
		m_View.m_y = m_Pos.m_y + 60;

	if((m_View.m_y - m_Pos.m_y) < -60) 
		m_View.m_y = m_Pos.m_y - 60;

	Rotate(-angle_y); // rotate

}

float zCamera::getPos_x()
{
	return (m_Pos.m_x);
}

float zCamera::getPos_y()
{
	return (m_Pos.m_y);
}

float zCamera::getPos_z()
{
	return (m_Pos.m_z);
}

void zCamera::setPos_x(float x)
{
	m_Pos.m_x = x;
}

void zCamera::setPos_y(float y)
{
	m_Pos.m_y = y;
}

void zCamera::setPos_z(float z)
{
	m_Pos.m_z = z;
}

float zCamera::getView_x()
{
	return (m_View.m_x);
}

float zCamera::getView_y()
{
	return (m_View.m_y);
}

float zCamera::getView_z()
{
	return (m_View.m_z);
}

void zCamera::setView_x(float x)
{
	m_View.m_x = x;
}

void zCamera::setView_y(float y)
{
	m_View.m_y = y;
}

void zCamera::setView_z(float z)
{
	m_View.m_z = z;
}

float zCamera::getUp_x()
{
	return (m_up.m_x);
}

float zCamera::getUp_y()
{
	return (m_up.m_y);
}

float zCamera::getUp_z()
{
	return (m_up.m_z);
}

float zCamera::getVel_y()
{
	return (m_Vel.m_y);
}

void zCamera::setVel_y(float y)
{
	m_Vel.m_y = y;
}

void zCamera::calcYVel(float frameTime)
{
	m_Pos.m_y += m_Vel.m_y * frameTime;
	m_View.m_y += m_Vel.m_y * frameTime;
}