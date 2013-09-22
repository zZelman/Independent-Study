/*
 * CPhysicsEngine.cpp
 *
 *  Created on: Sep 22, 2013
 *      Author: zZelman
 */

#include "CPhysicsEngine.h"
#include "CMap.h"
#include "CTile.h"
#include "CUnit.h"
#include <iostream>

CPhysicsEngine::CPhysicsEngine(CMap* pMap, CUnit* pUnit)
{
	m_pVector_tiles = pMap->getTiles();
	m_pVector_units = NULL;
	m_pUnit = pUnit;
}


CPhysicsEngine::~CPhysicsEngine()
{
	// dont delete anything! everything is just pointers!
}


void CPhysicsEngine::update()
{
	for (uint i = 0; i < m_pVector_tiles->size(); ++i)
	{
		sf::FloatRect tileRect = m_pVector_tiles->at(i)->getRect();
		if (m_pUnit->intersects(&tileRect))
		{
			std::cout << "intersects" << std::endl;
		}
	}
}
