#include "zPlayer.h"

zPlayer::zPlayer()
{
	m_health = 100.0;
	m_walkSpeed = 0.1;
	m_walkAbsSpeed = 0.1;
	m_damage = 3.0;
}

zPlayer::~zPlayer()
{

}

float zPlayer::getHealth()
{
	return m_health;
}

float zPlayer::getWalkSpeed()
{
	return m_walkSpeed;
}

float zPlayer::getWalkAbsSpeed()
{
	return m_walkAbsSpeed;
}

float zPlayer::getDamage()
{
	return m_damage;
}

void zPlayer::setHealth(float h)
{
	m_health = h;
}

void zPlayer::setWalkSpeed(float ws)
{
	m_walkSpeed = ws;
}

void zPlayer::setWalkAbsSpeed(float was)
{
	m_walkAbsSpeed = was;
}

void zPlayer::setDamage(float d)
{
	m_damage = d;
}