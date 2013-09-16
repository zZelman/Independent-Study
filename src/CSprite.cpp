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

	// selects a sub-section of the texture
	int w = m_pTexture->getSubSize().x;
	int h = m_pTexture->getSubSize().y;
	int topX = w * (currSub.x - 1);
	int topY = h * (currSub.y - 1);
	m_pSprite->setTextureRect(sf::IntRect(topX, topY, w, h));
}


CSprite::~CSprite()
{
	delete m_pSprite;
	m_pSprite = NULL;
}


sf::FloatRect CSprite::getRect()
{
	return m_pSprite->getGlobalBounds();
}


void CSprite::setPosition(float x, float y)
{
	m_pSprite->setPosition(x, y);
}


void CSprite::move(float x, float y)
{
	m_pSprite->move(x, y);
}


void CSprite::update()
{
}


void CSprite::render()
{
	m_pWindow->draw(*m_pSprite);
}
