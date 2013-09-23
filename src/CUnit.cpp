/*
 * CUnit.cpp
 *
 *  Created on: Sep 20, 2013
 *      Author: zZelman
 */

#include <iostream>
#include "CUnit.h"
#include "CPhysics.h"
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
	isStoped		= true;

	sf::Vector2<float> velosity(3, 3);
	m_sPhysics = new CPhysics(velosity);

	m_animTimerMS = 80;

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


bool CUnit::isLeft() {
	return isMove_left;
}


bool CUnit::isRight() {
	return isMove_right;
}


bool CUnit::isUp() {
	return isMove_up;
}


bool CUnit::isDown() {
	return isMove_down;
}


sf::FloatRect CUnit::getRect()
{
	return m_pSprite->getRect();
}


sf::Vector2<int> CUnit::getSize()
{
	return m_subSize;
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

		m_sPhysics->pGravityClock->restart();

		isFirstUpdate = false;
	}

	// if is not moving, set the not-moving flag
	if (!isMove_left && !isMove_right && !isMove_up && !isMove_down)
	{
		isStoped = true;
	}
	else
	{
		isStoped = false;
	}

	// update image shown
	sf::Time elapsed = m_pAnimationClock->getElapsedTime();
	if (elapsed.asMilliseconds() >= m_animTimerMS && !isStoped)
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
		m_currSub.y = 1;
		m_pSprite->move(-m_sPhysics->velosity.x, 0);
	}

	if (isMove_right)
	{
		m_currSub.y = 2;
		m_pSprite->move(m_sPhysics->velosity.x, 0);
	}

	if (isMove_up)
	{
		m_pSprite->move(0, -m_sPhysics->velosity.y);
	}

	if (isMove_down)
	{
		m_pSprite->move(0, m_sPhysics->velosity.y);
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


void CUnit::setScale(float x, float y)
{
	m_pSprite->setScale(x, y);
}


void CUnit::setScale(const sf::Vector2<float>* scale)
{
	m_pSprite->setScale(scale);
}


void CUnit::scale(float x, float y)
{
	m_pSprite->scale(x, y);
}


void CUnit::scale(const sf::Vector2<float>* scale)
{
	m_pSprite->scale(scale);
}


bool CUnit::contains(const sf::Vector2<float>* point) const
{
	sf::FloatRect thisRect = m_pSprite->getRect();
	return thisRect.contains(*point);
}


bool CUnit::intersects(const sf::Rect<float>* rectangle) const
{
	sf::FloatRect thisRect = m_pSprite->getRect();
	return thisRect.intersects(*rectangle);
}
