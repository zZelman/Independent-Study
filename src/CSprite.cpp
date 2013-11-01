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


CSprite::CSprite()
{
	m_pWindow = NULL;
	m_pTexture = NULL;
//	m_pSprite = NULL;
}


CSprite::CSprite(sf::RenderWindow* pWindow,
                 CTexture* pTexture,
                 const sf::Vector2<int>& currSub)
{
	m_pWindow	= pWindow;

	m_pTexture = pTexture;

//	m_pSprite = new sf::Sprite();
//	m_pSprite->setTexture(*(m_pTexture->getTexture()));
	setTexture(*m_pTexture);

	m_currSub = currSub;
	setSubImage(&currSub);
	chooseSubImage();
}


CSprite::~CSprite()
{
//	delete m_pSprite;
//	m_pSprite = NULL;

	// m_pWindow && m_pTexture are managed externally
}


CSprite::CSprite(const CSprite& other)
{
	// [QUESTION] if a pointer is managed externally, do you need to allocate
	//		a 'new' in a copy constructor/copy assignment?

	m_pWindow = other.m_pWindow; // managed externally

	m_pTexture = other.m_pTexture; // managed externally

//	m_pSprite = new sf::Sprite();
//	*m_pSprite = *(other.m_pSprite);
}


CSprite& CSprite::operator=(const CSprite& other)
{
	if (this == &other)
	{
		return *this;
	}

	// [QUESTION] if a pointer is managed externally, do you need to allocate
	//		a 'new' in a copy constructor/copy assignment?

	m_pWindow = other.m_pWindow; // managed externally

	m_pTexture = other.m_pTexture; // managed externally

	// [QUESTION] should i conditionally delete?
//	if (m_pSprite != NULL)
//	{
//		delete m_pSprite;
//	}
//	m_pSprite = new sf::Sprite();
//	*m_pSprite = *(other.m_pSprite);

	return *this;
}


//sf::FloatRect CSprite::getRect()
//{
//	return m_pSprite->getGlobalBounds();
//}


void CSprite::setSubImage(int col, int row)
{
#ifdef DEBUG
	assert(col <= m_pTexture->getSubNum().x && col > 0);
	assert(row <= m_pTexture->getSubNum().y && row > 0);
#endif
	m_currSub.x = col;
	m_currSub.y = row;

	chooseSubImage();
}


void CSprite::setSubImage(const sf::Vector2<int>* newSub)
{
	int col = newSub->x;
	int row = newSub->y;

#ifdef DEBUG
	if (!(col <= m_pTexture->getSubNum().x && col > 0))
	{
		int i = 0;
	}
	assert(col <= m_pTexture->getSubNum().x && col > 0);

	if (!(row <= m_pTexture->getSubNum().y && row > 0))
	{
		int i = 0;
	}
	assert(row <= m_pTexture->getSubNum().y && row > 0);
#endif
	m_currSub.x = col;
	m_currSub.y = row;

	chooseSubImage();
}


//void CSprite::setPosition(float x, float y)
//{
//	m_pSprite->setPosition(x, y);
//}


//void CSprite::setPosition(const sf::Vector2<int>& pos)
//{
//	setPosition(pos.x, pos.y);
//}


//void CSprite::setScale(float x, float y)
//{
//	m_pSprite->setScale(x, y);
//}


//void CSprite::setScale(const sf::Vector2<float>* scale)
//{
//	m_pSprite->setScale(*scale);
//}


//void CSprite::scale(float x, float y)
//{
//	m_pSprite->scale(x, y);
//}


//void CSprite::scale(const sf::Vector2<float>* scale)
//{
//	m_pSprite->scale(*scale);
//}


//void CSprite::move(float x, float y)
//{
//	m_pSprite->move(x, y);
//}


void CSprite::render()
{
	m_pWindow->draw(*this);
}

void CSprite::chooseSubImage()
{
	// selects a sub-section of the texture
	int w = m_pTexture->getSubSize().x;
	int h = m_pTexture->getSubSize().y;
	int topX = w * (m_currSub.x - 1);
	int topY = h * (m_currSub.y - 1);
	setTextureRect(sf::IntRect(topX, topY, w, h));
}
