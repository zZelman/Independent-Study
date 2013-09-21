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

	m_pTexture = pTexture;

	m_pSprite = new sf::Sprite();
	m_pSprite->setTexture(m_pTexture->getTexture());

	setSubImage(currRow, currCol);
	chooseSubImage();
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

void CSprite::setSubImage(int row, int col)
{
#ifdef DEBUG
	assert(col <= m_pTexture->getSubNum().x && col > 0);
	assert(row <= m_pTexture->getSubNum().y && row > 0);
#endif
	currSub.x = col;
	currSub.y = row;

	chooseSubImage();
}


void CSprite::setSubImage(const sf::Vector2<int>* currSub)
{
	int col = currSub->x;
	int row = currSub->y;

#ifdef DEBUG
	assert(col <= m_pTexture->getSubNum().x && col > 0);
	assert(row <= m_pTexture->getSubNum().y && row > 0);
#endif
	this->currSub.x = col;
	this->currSub.y = row;

	chooseSubImage();
}


void CSprite::setPosition(float x, float y)
{
	m_pSprite->setPosition(x, y);
}


void CSprite::move(float x, float y)
{
	m_pSprite->move(x, y);
}


void CSprite::render()
{
	m_pWindow->draw(*m_pSprite);
}

void CSprite::chooseSubImage()
{
	// selects a sub-section of the texture
	int w = m_pTexture->getSubSize().x;
	int h = m_pTexture->getSubSize().y;
	int topX = w * (currSub.x - 1);
	int topY = h * (currSub.y - 1);
	m_pSprite->setTextureRect(sf::IntRect(topX, topY, w, h));
}
