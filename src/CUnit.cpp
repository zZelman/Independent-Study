/*
 * CUnit.cpp
 *
 *  Created on: Sep 20, 2013
 *      Author: zZelman
 */

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


bool CUnit::input()
{
	return false;
}


void CUnit::update()
{
	if (isFirstUpdate)
	{
		m_pAnimationClock->restart();
		isFirstUpdate = false;
	}

	sf::Time elapsed = m_pAnimationClock->getElapsedTime();

	if (elapsed.asMilliseconds() >= m_animTimerMS)
	{
		// update image shown
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
	m_pSprite->move(m_moveStepSize, m_moveStepSize);
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
