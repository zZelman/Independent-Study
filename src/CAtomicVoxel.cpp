/*
 * CAtomicVoxel.cpp
 *
 *  Created on: Oct 14, 2013
 *      Author: zZelman
 */

#include "CAtomicVoxel.h"
#include "include_sfml.h"
#include <iostream>
#include <assert.h>

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

	m_isEdge.trueALL();

	m_pTexture = texture;

	m_pSprite = new CSprite(window, texture, currSub);
	setScreenPos();
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
	CAtomicVoxel* returnMe = this;

	while (returnMe->m_pParentAV != NULL)
	{
		returnMe = returnMe->m_pParentAV;
	}

	return returnMe;
}


void CAtomicVoxel::setParent(CAtomicVoxel* AV)
{
#ifdef DEBUG
	assert(m_pParentAV == NULL);
#endif

	m_pParentAV = AV;
}


void CAtomicVoxel::move(const sf::Vector2<int>& delta)
{
	move(delta.x, delta.y);
}


void CAtomicVoxel::move(int dx, int dy)
{
	// remove this structure from data structure
	removePointersFromDataStructure();

	if (dx != 0)
	{
		if (canMove_x(dx))
		{
			if (isCollisionDetected_x(dx) == true)
			{
			}
			else
			{
				move_x(dx);
			}
		}
	}

	if (dy != 0)
	{
		if (canMove_y(dy))
		{
			if (isCollisionDetected_y(dy) == true)
			{
			}
			else
			{
				move_y(dy);
			}
		}
	}

	addPointersToDataStructure();
}


bool CAtomicVoxel::canMove_x(int dx)
{
	sf::Vector2<int> gridSize = m_pGrid->getGridSize();
	int futureX = m_gridPos.x + dx;

	bool canMove = true;
	bool selfMove = true;

	// self
	if (!(futureX >= 0) || !(futureX < gridSize.x))
	{
		canMove = false;
		selfMove = false;
	}

	// children
	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		bool tempBool = m_childrenAV[i]->canMove_x(dx);
		if (tempBool == false || selfMove == false)
			canMove = false;
	}
	return canMove;
}


bool CAtomicVoxel::canMove_y(int dy)
{
	sf::Vector2<int> gridSize = m_pGrid->getGridSize();
	int futureY = m_gridPos.y + dy;

	bool canMove = true;
	bool selfMove = true;

	// self
	if (!(futureY >= 0) || !(futureY < gridSize.y))
	{
		canMove = false;
		selfMove = false;
	}

	// children
	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		bool tempBool = m_childrenAV[i]->canMove_y(dy);
		if (tempBool == false || selfMove == false)
			canMove = false;

	}
	return canMove;
}


void CAtomicVoxel::move_x(int dx)
{
	m_gridPos.x += dx;
	setScreenPos();

	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		m_childrenAV[i]->move_x(dx);
	}
}


void CAtomicVoxel::move_y(int dy)
{
	m_gridPos.y += dy;
	setScreenPos();

	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		m_childrenAV[i]->move_y(dy);
	}
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
	m_childrenAV.push_back(AV);
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


void CAtomicVoxel::setScreenPos()
{
	m_screenPos = m_gridPos;
	m_pGrid->gridToScreen(&m_screenPos);
	m_pSprite->setPosition(m_screenPos);
}


void CAtomicVoxel::removePointersFromDataStructure()
{
	m_pGrid->setPos(m_gridPos, NULL);
	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		m_childrenAV[i]->removePointersFromDataStructure();
	}
}


void CAtomicVoxel::addPointersToDataStructure()
{
	m_pGrid->setPos(m_gridPos, this);
	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		m_childrenAV[i]->addPointersToDataStructure();
	}
}


bool CAtomicVoxel::isCollisionDetected_x(int dx)
{
	bool isCollision = false;

	int futureX = m_gridPos.x + dx;
	CAtomicVoxel* possibleAV = m_pGrid->returnPos(futureX, m_gridPos.y);

	bool isBound = false;
	if (possibleAV != NULL) // collision
	{
		CAtomicVoxel* otherAP = possibleAV->findAnchorParent();
		bindAVasChild(otherAP);
		otherAP->setParent(this);

		m_pGrid->removeAnchorParent(otherAP);

		removePointersFromDataStructure();

		isCollision = true;
		isBound = true;
	}

	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		isCollision = m_childrenAV[i]->isCollisionDetected_x(dx);
		if (isCollision == true || isBound)
			isCollision = true;
	}

	return isCollision;
}


bool CAtomicVoxel::isCollisionDetected_y(int dy)
{
	bool isCollision = false;

	int futureY = m_gridPos.y + dy;
	CAtomicVoxel* possibleAV = m_pGrid->returnPos(m_gridPos.x, futureY);

	bool isBound = false;
	if (possibleAV != NULL) // collision
	{
		CAtomicVoxel* otherAP = possibleAV->findAnchorParent();
		bindAVasChild(otherAP);
		otherAP->setParent(this);

		m_pGrid->removeAnchorParent(otherAP);

		removePointersFromDataStructure();

		isCollision = true;
		isBound = true;
	}

	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		bool tempBool = m_childrenAV[i]->isCollisionDetected_y(dy);
		if (tempBool == true || isBound == true)
			isCollision = true;
	}

	return isCollision;
}
