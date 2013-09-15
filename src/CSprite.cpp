/*
 * CSprite.cpp
 *
 *  Created on: Sep 14, 2013
 *      Author: zZelman
 */

#include "CSprite.h"
#include "include_sfml.h"
#include "CTexture.h"
#include <assert.h>

CSprite::CSprite(sf::RenderWindow* pWindow,
                 CTexture* pTexture,
                 int currRow, int currCol)
{
	m_pWindow	= pWindow;
	currSub.y	= currRow;
	currSub.x	= currCol;

	m_pTexture = pTexture;

	m_pSprite = new sf::Sprite();
	m_pSprite->setTexture(m_pTexture->getTexture());
}


CSprite::~CSprite()
{
	delete m_pSprite;
	m_pSprite = NULL;
}


void CSprite::update()
{
	m_pSprite->move(1.0f, 1.0f);

	if (currSub.x + 1 > m_pTexture->getSubNum().x)
	{
		currSub.x = 1;
	}
	else
	{
		++currSub.x;
	}

	// selects a sub-section of the texture
	int w = m_pTexture->getSubSize().x;
	int h = m_pTexture->getSubSize().y;
	int topX = w * (currSub.x - 1);
	int topY = h * (currSub.y - 1);
	m_pSprite->setTextureRect(sf::IntRect(topX, topY, w, h));
}


void CSprite::render()
{
	m_pWindow->draw(*m_pSprite);
}
