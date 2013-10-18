/*
 * CGrid.cpp
 *
 *  Created on: Oct 14, 2013
 *      Author: zZelman
 */

#include "CGrid.h"
#include "CAtomicVoxel.h"
#include <iostream>
#include <assert.h>


CGrid::CGrid()
{
	m_pScreen = NULL;
	m_pAVTexture = NULL;
	m_gridDataStructure = NULL;
	m_pTestAV = NULL;
}


CGrid::CGrid(sf::RenderWindow* window,
             const sf::Vector2<int>& gridSize, // how many cells are in the grid
             const sf::Vector2<int>& gridSubSize,  // pix size of an individual cell
             const std::string& filePath,		// Relative path to the sprite sheet
             const sf::Vector2<int>& subSize,	// size of a single sub-image
             const sf::Vector2<int>& subNum)	// number of sub images on the 2D sheet
{
	m_pScreen = window;

	m_gridSize = gridSize;

	m_gridSubSize = gridSubSize;

	m_gridDataStructure = new CAtomicVoxel*[gridSize.y * gridSize.x];
	for (int i = 0; i < gridSize.y; ++i)
	{
		for (int n = 0; n < gridSize.x; ++n)
		{
			setPos(n, i, NULL);
		}
	}

	m_pAVTexture = new CTexture(filePath, subSize, subNum);

	sf::Vector2<int> gridPos(1, 1);
	m_pTestAV = new CAtomicVoxel(this, gridPos,
	                             window, m_pAVTexture, sf::Vector2<int>(1, 1));
	setPos(gridPos, m_pTestAV);
	addAnchorParent(m_pTestAV);

}


CGrid::~CGrid()
{
	delete m_pAVTexture;
	m_pAVTexture = NULL;

	delete m_pTestAV;

	// m_pScreen is managed externally

	// 2D data structure
	for (int i = 0; i < (m_gridSize.y * m_gridSize.x); ++i)
	{
		if (m_gridDataStructure[i] != NULL)
		{
			delete m_gridDataStructure[i];
			m_gridDataStructure[i] = NULL;
		}
	}
	delete [] m_gridDataStructure;

	// anchor parents just to be sure
	for (uint i = 0; i < m_anchorParents.size(); ++i)
	{
		if (m_anchorParents[i] != NULL)
		{
			delete m_anchorParents[i];
			m_anchorParents[i] = NULL;
		}
	}
}


CGrid::CGrid(const CGrid& other)
{
	m_pScreen = other.m_pScreen; // managed externally

	m_pAVTexture = new CTexture();
	*m_pAVTexture = *(other.m_pAVTexture);

	m_gridSize = other.m_gridSize;
	m_gridSubSize = other.m_gridSubSize;
	m_gridDataStructure = new CAtomicVoxel*[m_gridSize.y * m_gridSize.x];
	for (int i = 0; i < (m_gridSize.y * m_gridSize.x); ++i)
	{
		// [QUESTION] am i doing this correctly?
		*(m_gridDataStructure[i]) = *(other.m_gridDataStructure[i]);
	}

	m_anchorParents = other.m_anchorParents;

	m_pTestAV = new CAtomicVoxel();
	*m_pTestAV = *(other.m_pTestAV);
}


CGrid& CGrid::operator =(const CGrid& other)
{
	if (this == &other)
	{
		return *this;
	}

	m_pScreen = other.m_pScreen; // managed externally

	if (m_pAVTexture != NULL)
	{
		delete m_pAVTexture;
	}
	m_pAVTexture = new CTexture();
	*m_pAVTexture = *(other.m_pAVTexture);

	m_gridSize = other.m_gridSize;
	m_gridSubSize = other.m_gridSubSize;

	for (int i = 0; i < (m_gridSize.y * m_gridSize.x); ++i)
	{
		if (m_gridDataStructure[i] != NULL)
		{
			delete m_gridDataStructure[i];
			m_gridDataStructure[i] = NULL;
		}
	}
	delete [] m_gridDataStructure;
	m_gridDataStructure = new CAtomicVoxel*[m_gridSize.y * m_gridSize.x];
	for (int i = 0; i < (m_gridSize.y * m_gridSize.x); ++i)
	{
		// [QUESTION] am i doing this correctly?
		*(m_gridDataStructure[i]) = *(other.m_gridDataStructure[i]);
	}


	m_anchorParents = other.m_anchorParents;

	return *this;
}


sf::Vector2<int> CGrid::getGridSize()
{
	return m_gridSize;
}


bool CGrid::userInput(sf::Event* pEvent)
{
	bool isConsumed = false;

	// arrow keys
	if (pEvent->key.code == sf::Keyboard::Left)
	{
		m_pTestAV->move(-1, 0);
		isConsumed = true;
	}
	else if (pEvent->key.code == sf::Keyboard::Right)
	{
		m_pTestAV->move(1, 0);
		isConsumed = true;
	}
	else if (pEvent->key.code == sf::Keyboard::Up)
	{
		m_pTestAV->move(0, -1);
		isConsumed = true;
	}
	else if (pEvent->key.code == sf::Keyboard::Down)
	{
		m_pTestAV->move(0, 1);
		isConsumed = true;
	}


	// left mouse
	if (pEvent->mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2<int> pos = sf::Mouse::getPosition(*m_pScreen);
		createAP(&pos);
		isConsumed = true;
	}

	// key p
	if (pEvent->key.code == sf::Keyboard::P)
	{
		printDataStructure();
	}

	return isConsumed;
}


void CGrid::update()
{
}


void CGrid::render()
{
	for (int i = 0; i < (m_gridSize.y * m_gridSize.x); ++i)
	{
		if (m_gridDataStructure[i] == NULL)
		{
			continue;
		}
		m_gridDataStructure[i]->render();
	}
}


bool CGrid::isOpen(const sf::Vector2<int>& pos)
{
	return false;
}


bool CGrid::isOpen(int x, int y)
{
	return false;
}


CAtomicVoxel* CGrid::returnPos(int x, int y)
{
	return m_gridDataStructure[y * m_gridSize.y + x];
}


CAtomicVoxel* CGrid::returnPos(const sf::Vector2<int>& pos)
{
	return returnPos(pos.x, pos.y);
}


void CGrid::setPos(int x, int y, CAtomicVoxel* AV)
{
	m_gridDataStructure[y * m_gridSize.y + x] = AV;
}


void CGrid::setPos(const sf::Vector2<int>& pos, CAtomicVoxel* AV)
{
	setPos(pos.x, pos.y, AV);
}


void CGrid::removeStructure(CAtomicVoxel* anchorParent)
{
}


void CGrid::condenseStructureList()
{
}


void CGrid::gridToScreen(int* x, int* y)
{
	*x = m_gridSubSize.x * (*x);
	*y = m_gridSubSize.y * (*y);
}


void CGrid::gridToScreen(sf::Vector2<int>* pos)
{
	gridToScreen(&(pos->x), &(pos->y));
}


void CGrid::screenToGrid(int* x, int* y)
{
	*x = ((*x) * m_gridSize.x) / m_pScreen->getSize().x;
	*y = ((*y) * m_gridSize.y) / m_pScreen->getSize().y;
}


void CGrid::screenToGrid(sf::Vector2<int>* pos)
{
	screenToGrid(&(pos->x), &(pos->y));
}


void CGrid::addAnchorParent(CAtomicVoxel* AP)
{
	m_anchorParents.push_back(AP);
}


void CGrid::removeAnchorParent(CAtomicVoxel* AP)
{
	for (int i = 0; i < m_anchorParents.size(); ++i)
	{
		if (AP == m_anchorParents[i])
		{
			m_anchorParents.erase(m_anchorParents.begin() + i);
			return;
		}
	}

	// should never get here
	bool isAPremoved = false;
	assert(isAPremoved);
}


void CGrid::createAP(sf::Vector2<int>* screenPos)
{
	sf::Vector2<int> gridPos = *screenPos;
	screenToGrid(&gridPos);

	if (returnPos(gridPos) == NULL)
	{
		CAtomicVoxel* newAP = new CAtomicVoxel(this, gridPos,
		                                       m_pScreen, m_pAVTexture, sf::Vector2<int>(1, 1));
		setPos(gridPos, newAP);
		m_anchorParents.push_back(newAP);
	}
}


void CGrid::removeAV(int x, int y)
{
}


void CGrid::removeAV(const sf::Vector2<int>& pos)
{
}


void CGrid::printDataStructure()
{
	std::cout << "----" << std::endl;
	for (int i = 0; i < m_gridSize.y; ++i)
	{
		for (int n = 0; n < m_gridSize.x; ++n)
		{
			CAtomicVoxel* temp = returnPos(n, i);
			int p = 0;
			if (temp != NULL)
			{
				p = 1;
			}
			std::cout << p << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "----" << std::endl;
}

