/*
 * CTile.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#include "CTile.h"
#include "CSprite.h"

CTile::CTile(sf::RenderWindow* pWindow,
             CTexture* pTexture,
             sf::Vector2<int> currSub)
{
	m_pSprite = new CSprite(pWindow, pTexture, currSub);
}


CTile::~CTile()
{
	delete m_pSprite;
	m_pSprite = NULL;
}


sf::FloatRect CTile::getRect()
{
	return m_pSprite->getRect();
}


void CTile::setPosition(float x, float y)
{
	m_pSprite->setPosition(x, y);
}


void CTile::render()
{
	m_pSprite->render();
}
