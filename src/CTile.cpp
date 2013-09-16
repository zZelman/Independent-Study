/*
 * CTile.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#include "CTile.h"
#include "CSprite.h"

CTile::CTile(sf::RenderWindow* pWindow, CTexture* pTexture, int currRow,
             int currCol)
	: CSprite(pWindow, pTexture, currRow, currCol)
{
}

CTile::~CTile()
{
	// NOTE: C++ takes care of calling base-derived destructor,
	//		in reverse order of construction
}

void CTile::update()
{
	// TODO: animated map tiles?
	// NOTE: Tile is derived from Sprite because I want Tile to update differently
}

void CTile::render()
{
	CSprite::render();
}
