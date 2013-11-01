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

	isStructureRemoved = true;
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

	updateCenter();

	isStructureRemoved = false;
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


const sf::Vector2<float>& CAtomicVoxel::getCenter()
{
	return m_selfCenter;
}


std::vector<CAtomicVoxel*>& CAtomicVoxel::getChildren()
{
	return m_childrenAV;
}


bool CAtomicVoxel::isAnchorParent()
{
	return m_pParentAV == NULL;
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
	removeStructure_fromGrid();

	if (dx != 0)
	{
		if (canMove_x(dx))
		{
			if (isCollisionDetected_x(dx) == true)
			{
				setEdgeBools_add();
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
				setEdgeBools_add();
			}
			else
			{
				move_y(dy);
			}
		}
	}

	addStructure_toGrid();
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
		{
			canMove = false;
		}
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
		{
			canMove = false;
		}

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

	updateCenter();
}


void CAtomicVoxel::move_y(int dy)
{
	m_gridPos.y += dy;
	setScreenPos();


	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		m_childrenAV[i]->move_y(dy);
	}

	updateCenter();
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


void CAtomicVoxel::removeChild(CAtomicVoxel* AV)
{
	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		if (m_childrenAV[i] == AV)
		{
			m_childrenAV.erase(m_childrenAV.begin() + i);
			return;
		}
	}

	// code flow should never get here
	bool removeChild = false;
	assert(removeChild);
}


void CAtomicVoxel::damage_remove()
{
	if (m_pParentAV == NULL)
	{
		m_pGrid->removeAnchorParent(this);
	}

	if (m_pParentAV != NULL)
	{
		// remove this as a child of parent
		m_pParentAV->removeChild(this);

		// tell parent to re-check edge conditions
		m_pParentAV->findAnchorParent()->setEdgeBools_remove();

		// set parent to null in this
		m_pParentAV = NULL;

	}

	// for (each child)
	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		CAtomicVoxel* child = m_childrenAV[i];

		// set parent to null
		child->m_pParentAV = NULL;

		// add to anchor parents in CGrid
		child->m_pGrid->addAnchorParent(child);

		// re-check edge conditions
		child->setEdgeBools_remove();
	}

	// remove all children from this
	m_childrenAV.clear();

	// remove this from the 2D data structure
	m_pGrid->setPos(m_gridPos, NULL);

	// remove this from CGrid anchor parents
//	m_pGrid->removeAnchorParent(this);
	// this is already accomplished somewhere...?

	// delete this (in calling function)
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
	// full edge
	if (m_isEdge.up && m_isEdge.down && m_isEdge.left && m_isEdge.right)
	{
		m_pSprite->setSubImage(1, 1);
		return;
	}

	// 3 edge
	if (m_isEdge.up && m_isEdge.down && m_isEdge.left && !m_isEdge.right)
	{
		m_pSprite->setSubImage(1, 2);
		return;
	}
	if (m_isEdge.up && !m_isEdge.down && m_isEdge.left && m_isEdge.right)
	{
		m_pSprite->setSubImage(2, 2);
		return;
	}
	if (m_isEdge.up && m_isEdge.down && !m_isEdge.left && m_isEdge.right)
	{
		m_pSprite->setSubImage(3, 2);
		return;
	}
	if (!m_isEdge.up && m_isEdge.down && m_isEdge.left && m_isEdge.right)
	{
		m_pSprite->setSubImage(4, 2);
		return;
	}

	// 2 edge
	if (!m_isEdge.up && m_isEdge.down && !m_isEdge.left && m_isEdge.right)
	{
		m_pSprite->setSubImage(1, 3);
		return;
	}
	if (!m_isEdge.up && m_isEdge.down && m_isEdge.left && !m_isEdge.right)
	{
		m_pSprite->setSubImage(2, 3);
		return;
	}
	if (m_isEdge.up && !m_isEdge.down && m_isEdge.left && !m_isEdge.right)
	{
		m_pSprite->setSubImage(3, 3);
		return;
	}
	if (m_isEdge.up && !m_isEdge.down && !m_isEdge.left && m_isEdge.right)
	{
		m_pSprite->setSubImage(4, 3);
		return;
	}
	if (m_isEdge.up && m_isEdge.down && !m_isEdge.left && !m_isEdge.right)
	{
		m_pSprite->setSubImage(1, 4);
		return;
	}
	if (!m_isEdge.up && !m_isEdge.down && m_isEdge.left && m_isEdge.right)
	{
		m_pSprite->setSubImage(2, 4);
		return;
	}

	// 1 edge
	if (!m_isEdge.up && !m_isEdge.down && !m_isEdge.left && m_isEdge.right)
	{
		m_pSprite->setSubImage(1, 5);
		return;
	}
	if (!m_isEdge.up && m_isEdge.down && !m_isEdge.left && !m_isEdge.right)
	{
		m_pSprite->setSubImage(2, 5);
		return;
	}
	if (!m_isEdge.up && !m_isEdge.down && m_isEdge.left && !m_isEdge.right)
	{
		m_pSprite->setSubImage(3, 5);
		return;
	}
	if (m_isEdge.up && !m_isEdge.down && !m_isEdge.left && !m_isEdge.right)
	{
		m_pSprite->setSubImage(4, 5);
		return;
	}

	// no edge
	if (!m_isEdge.up && !m_isEdge.down && !m_isEdge.left && !m_isEdge.right)
	{
		m_pSprite->setSubImage(1, 6);
		return;
	}
}


void CAtomicVoxel::setEdgeBools_add_sub()
{
	if (m_isEdge.up)
	{
		CAtomicVoxel* neighbor = m_pGrid->returnPos(m_gridPos.x, m_gridPos.y - 1);
		if (neighbor != NULL)
		{
			m_isEdge.up = false;
			neighbor->m_isEdge.down = false;

			chooseImageBasedOnEdge();
			neighbor->chooseImageBasedOnEdge();
		}
	}
	if (m_isEdge.down)
	{
		CAtomicVoxel* neighbor = m_pGrid->returnPos(m_gridPos.x, m_gridPos.y + 1);
		if (neighbor != NULL)
		{
			m_isEdge.down = false;
			neighbor->m_isEdge.up = false;

			chooseImageBasedOnEdge();
			neighbor->chooseImageBasedOnEdge();
		}
	}

	if (m_isEdge.left)
	{
		CAtomicVoxel* neighbor = m_pGrid->returnPos(m_gridPos.x - 1, m_gridPos.y);
		if (neighbor != NULL)
		{
			m_isEdge.left = false;
			neighbor->m_isEdge.right = false;

			chooseImageBasedOnEdge();
			neighbor->chooseImageBasedOnEdge();
		}
	}
	if (m_isEdge.right)
	{
		CAtomicVoxel* neighbor = m_pGrid->returnPos(m_gridPos.x + 1, m_gridPos.y);
		if (neighbor != NULL)
		{
			m_isEdge.right = false;
			neighbor->m_isEdge.left = false;

			chooseImageBasedOnEdge();
			neighbor->chooseImageBasedOnEdge();
		}
	}

	// children
	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		m_childrenAV[i]->setEdgeBools_add_sub();
	}
}


void CAtomicVoxel::setEdgeBools_remove_sub()
{
	if (!m_isEdge.up)
	{
		CAtomicVoxel* neighbor = m_pGrid->returnPos(m_gridPos.x, m_gridPos.y - 1);
		if (neighbor == NULL)
		{
			m_isEdge.up = true;
		}
	}
	if (!m_isEdge.down)
	{
		CAtomicVoxel* neighbor = m_pGrid->returnPos(m_gridPos.x, m_gridPos.y + 1);
		if (neighbor == NULL)
		{
			m_isEdge.down = true;
		}
	}

	if (!m_isEdge.left)
	{
		CAtomicVoxel* neighbor = m_pGrid->returnPos(m_gridPos.x - 1, m_gridPos.y);
		if (neighbor == NULL)
		{
			m_isEdge.left = true;
		}
	}
	if (!m_isEdge.right)
	{
		CAtomicVoxel* neighbor = m_pGrid->returnPos(m_gridPos.x + 1, m_gridPos.y);
		if (neighbor == NULL)
		{
			m_isEdge.right = true;
		}
	}

	chooseImageBasedOnEdge();

	// children
	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		m_childrenAV[i]->setEdgeBools_remove_sub();
	}
}


void CAtomicVoxel::setScreenPos()
{
	m_screenPos = m_gridPos;
	m_pGrid->gridToScreen(&m_screenPos);
	m_pSprite->setPosition(m_screenPos.x, m_screenPos.y);
}


void CAtomicVoxel::removeStructure_fromGrid()
{
	m_pGrid->setPos(m_gridPos, NULL);
	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		m_childrenAV[i]->removeStructure_fromGrid();
	}

	isStructureRemoved = true;
}


void CAtomicVoxel::addStructure_toGrid()
{
	m_pGrid->setPos(m_gridPos, this);
	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		m_childrenAV[i]->addStructure_toGrid();
	}

	isStructureRemoved = false;
}


void CAtomicVoxel::setEdgeBools_add()
{
	m_pGrid->nullALL_onGrid();

	findAnchorParent()->addStructure_toGrid();
	setEdgeBools_add_sub();

	m_pGrid->applyAPstructures_toGrid();
}


void CAtomicVoxel::setEdgeBools_remove()
{
	m_pGrid->nullALL_onGrid();

	findAnchorParent()->addStructure_toGrid();
	setEdgeBools_remove_sub();

	m_pGrid->applyAPstructures_toGrid();
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

		removeStructure_fromGrid();

		isCollision = true;
		isBound = true;
	}

	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		bool tempBool = m_childrenAV[i]->isCollisionDetected_x(dx);
		if (tempBool == true || isBound == true)
		{
			isCollision = true;
		}
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

		removeStructure_fromGrid();

		isCollision = true;
		isBound = true;
	}

	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		bool tempBool = m_childrenAV[i]->isCollisionDetected_y(dy);
		if (tempBool == true || isBound == true)
		{
			isCollision = true;
		}
	}

	return isCollision;
}


void CAtomicVoxel::updateCenter()
{
	sf::FloatRect curPos = m_pSprite->getGlobalBounds();

	m_selfCenter.x = curPos.left + (curPos.width / 2);
	m_selfCenter.y = curPos.top + (curPos.height / 2);

	for (uint i = 0; i < m_childrenAV.size(); ++i)
	{
		m_childrenAV.at(i)->updateCenter();
	}
}
