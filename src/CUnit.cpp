/*
 * CUnit.cpp
 *
 *  Created on: Sep 20, 2013
 *      Author: zZelman
 */

#include <iostream>
#include "CUnit.h"
#include "include_sfml.h"

CUnit::CUnit(sf::RenderWindow* pWindow,
             std::string texturePath,
             sf::Vector2<int> subSize,
             sf::Vector2<int> subNum)
{
	m_pWindow = pWindow;
	m_texturePath = texturePath;

	m_subSize = subSize;

	m_subNum = subNum;

	m_currSub.x = 1;
	m_currSub.y = 2;

	isMove_right 	= false;
	isMove_left 	= false;
	isMove_up 		= false;
	isMove_down 	= false;

	m_moveStepSize = 3;

	m_animTimerMS = 70;

	isFirstUpdate = true;

	m_pTexture 			= NULL;
	m_pSprite 			= NULL;
	m_pAnimationClock 	= NULL;
}


CUnit::~CUnit()
{
	delete m_pTexture;
	m_pTexture = NULL;

	delete m_pSprite;
	m_pSprite = NULL;

	delete m_pAnimationClock;
	m_pAnimationClock = NULL;
}


void CUnit::load()
{
	m_pTexture = new CTexture(m_texturePath,
	                          m_subSize,
	                          m_subNum);

	m_pSprite = new CSprite(m_pWindow,
	                        m_pTexture,
	                        m_currSub);

	m_pAnimationClock = new sf::Clock();
}


bool CUnit::input(sf::Keyboard::Key* key, bool isPressed)
{
	if (isPressed)
	{
		if (*key == sf::Keyboard::Left)
		{
			isMove_left = true;
			return true;
		}
		if (*key == sf::Keyboard::Right)
		{
			isMove_right = true;
			return true;
		}
		if (*key == sf::Keyboard::Up)
		{
			isMove_up = true;
			return true;
		}
		if (*key == sf::Keyboard::Down)
		{
			isMove_down = true;
			return true;
		}
	}
	else
	{
		if (*key == sf::Keyboard::Left)
		{
			isMove_left = false;
			return true;
		}
		if (*key == sf::Keyboard::Right)
		{
			isMove_right = false;
			return true;
		}
		if (*key == sf::Keyboard::Up)
		{
			isMove_up = false;
			return true;
		}
		if (*key == sf::Keyboard::Down)
		{
			isMove_down = false;
			return true;
		}
	}

	return false;
}


void CUnit::update()
{
	// don't want the first update to be wanky
	if (isFirstUpdate)
	{
		m_pAnimationClock->restart();
		isFirstUpdate = false;
	}

	// update image shown
	sf::Time elapsed = m_pAnimationClock->getElapsedTime();
	if (elapsed.asMilliseconds() >= m_animTimerMS)
	{
		if (m_currSub.x + 1 > m_subNum.x)
		{
			m_currSub.x = 1;
			m_pSprite->setSubImage(&m_currSub);
		}
		else
		{
			++m_currSub.x;
			m_pSprite->setSubImage(&m_currSub);
		}

		m_pAnimationClock->restart();
	}

	// update position
	if (isMove_left)
	{
		m_pSprite->move(-m_moveStepSize, 0);
		m_currSub.y = 1;
	}
	if (isMove_right)
	{
		m_pSprite->move(m_moveStepSize, 0);
		m_currSub.y = 2;
	}
	if (isMove_up)
	{
		m_pSprite->move(0, -m_moveStepSize);
	}
	if (isMove_down)
	{
		m_pSprite->move(0, m_moveStepSize);
	}
}


void CUnit::render()
{
	m_pSprite->render();
}


void CUnit::move(float x, float y)
{
	m_pSprite->move(x, y);
}


void CUnit::setPosition(float x, float y)
{
	m_pSprite->setPosition(x, y);
}
