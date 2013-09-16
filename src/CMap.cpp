/*
 * CMap.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#include "CMap.h"
#include "CTexture.h"
#include "CSprite.h"

CMap::CMap(sf::RenderWindow* pWindow,
           std::string texturePath,
           int subH, int subW,
           int numRow,	int numCol,
           std::string mapPath)
{
	m_pWindow = pWindow;

	loadTexture(texturePath, subH, subW, numRow, numCol);
	loadMap(mapPath);
}


CMap::~CMap()
{
	// delete the texture used by the tiles
	delete m_pTexture;
	m_pTexture = NULL;

	// delete tiles
	for (uint i = 0; i < m_tiles.size(); ++i)
	{
		delete m_tiles[i];
		m_tiles[i] = NULL;
	}
	m_tiles.clear();
}


std::vector<CTile*>* CMap::getTiles()
{
	return &m_tiles;
}


void CMap::update()
{
}


void CMap::render()
{
	for (uint i = 0; i < m_tiles.size(); ++i)
	{
		m_tiles[i]->render();
	}
}


void CMap::loadTexture(std::string texturePath,
                       int subH, int subW,
                       int numRow,	int numCol)
{
	m_pTexture = new CTexture(texturePath,
	                          subH, subW,
	                          numRow, numCol);
}


void CMap::loadMap(std::string mapPath)
{
	CTile* pTile = new CTile(m_pWindow, m_pTexture, 1, 1);
	pTile->setPosition(100, 100);
	m_tiles.push_back(pTile);
}
