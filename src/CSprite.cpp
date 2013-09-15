/*
 * CSprite.cpp
 *
 *  Created on: Sep 14, 2013
 *      Author: zZelman
 */

#include "CSprite.h"
#include "include_sfml.h"
#include <assert.h>

CSprite::CSprite(sf::RenderWindow* pWindow,
                 std::string fileName,
                 int subH, int subW,
                 int numRow, int numCol,
                 int currRow, int currCol)
{
#ifdef DEBUG
	assert(numRow > 0);
	assert(numCol > 0);

	assert(currRow <= numRow);
	assert(currRow > 0);

	assert(currCol <= numCol);
	assert(currCol > 0);
#endif

	m_pWindow 		= pWindow;
	this->subH 		= subH;
	this->subW 		= subW;
	this->numRow 	= numRow;
	this->numCol 	= numCol;
	this->currRow	= currRow;
	this->currCol	= currCol;

	m_pTexture = new sf::Texture();
	m_pSprite = new sf::Sprite();

	load(fileName);
}

CSprite::~CSprite()
{
	delete m_pTexture;
	m_pTexture = NULL;

	delete m_pSprite;
	m_pSprite = NULL;
}

void CSprite::update()
{
	m_pSprite->move(1.0f, 0.0f);

	if (currCol + 1 <= numCol)
	{
		++currCol;
	}
	else
	{
		currCol = 1;
	}

	// selects a sub-section of the texture
	int topX = subW * (currCol - 1);
	int topY = subH * (currRow - 1);
	m_pSprite->setTextureRect(sf::IntRect(topX, topY, subW, subH));
}

void CSprite::render()
{
	m_pWindow->draw(*m_pSprite);
}

void CSprite::load(std::string fileName)
{
	bool isLoaded = m_pTexture->loadFromFile(fileName);
#ifdef DEBUG
	assert(isLoaded);
#endif
	m_pTexture->setSmooth(true);
	m_pTexture->setRepeated(false);


	m_pSprite->setTexture(*m_pTexture);
}
