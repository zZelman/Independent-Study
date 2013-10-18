/*
 * CAtomicVoxel.cpp
 *
 *  Created on: Oct 14, 2013
 *      Author: zZelman
 */

#include "CAtomicVoxel.h"
#include "include_sfml.h"
#include <iostream>

CAtomicVoxel::CAtomicVoxel()
{
	m_pParentAV = NULL;

	m_isEdge.trueALL();

	m_pGrid = NULL;

	m_pTexture = NULL;

	m_pSprite = NULL;
}


CAtomicVoxel::CAtomicVoxel(CGrid* grid,
                           const sf::Vector2<int>& gridPos,
                           sf::RenderWindow* window,
                           CTexture* texture,
                           const sf::Vector2<int>& currSub)
{
	m_pParentAV = NULL;

	m_pGrid = grid;

	m_gridPos = gridPos;
	m_screenPos = gridPos;
	grid->gridToScreen(&m_screenPos);

	m_isEdge.trueALL();

	m_pTexture = texture;

	m_pSprite = new CSprite(window, texture, currSub);
	m_pSprite->setPosition(m_screenPos);
	chooseImageBasedOnEdge();
}


CAtomicVoxel::CAtomicVoxel(const CAtomicVoxel& other)
{
	// TODO

}


CAtomicVoxel::~CAtomicVoxel()
{
	// TODO
	delete m_pSprite;
	m_pSprite = NULL;
}


CAtomicVoxel& CAtomicVoxel::operator =(const CAtomicVoxel& other)
{
	if (this == &other)
	{
		return *this;
	}

	// TODO

	return *this;
}


void CAtomicVoxel::setSpriteScreenPos(int x, int y)
{
	// TODO

}


void CAtomicVoxel::setSpriteScreenPos(const sf::Vector2<int>& pos)
{
	// TODO

}


void CAtomicVoxel::update()
{
}


void CAtomicVoxel::render()
{
	m_pSprite->render();
}


CAtomicVoxel* CAtomicVoxel::findAnchorParent()
{
	// TODO

	return this;
}


void CAtomicVoxel::move(sf::Vector2<int> delta)
{
	// TODO

}


void CAtomicVoxel::move(int dx, int dy)
{
}


void CAtomicVoxel::setPosition(const sf::Vector2<int>& pos)
{
	// TODO

}


void CAtomicVoxel::setPosition(int x, int y)
{
	// TODO

}


void CAtomicVoxel::updateEdge_add(CAtomicVoxel* anchorParent)
{
	// TODO

}


void CAtomicVoxel::updateEdge_remove(CAtomicVoxel* anchorParent)
{
	// TODO

}


void CAtomicVoxel::bindAVasChild(CAtomicVoxel* AV)
{
	// TODO

}


void CAtomicVoxel::damage_remove()
{
	// TODO

}


void CAtomicVoxel::damage_breakChildBond()
{
	// TODO

}


void CAtomicVoxel::damage_breakParentBond()
{
	// TODO

}


void CAtomicVoxel::chooseImageBasedOnEdge()
{
	// TODO
	if (m_isEdge.up && m_isEdge.down && m_isEdge.left && m_isEdge.right)
	{
		m_pSprite->setSubImage(1, 1);
	}

}

