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

		// tile info pulled out
		float tile_width 	= tileRect.width;
		float tile_height 	= tileRect.height;
		float tile_topX		= tileRect.left;
		float tile_topY		= tileRect.top;

		if (m_pUnit->isRight())
		{
			// unit info pulled out
			sf::FloatRect unitRect = m_pUnit->getRect();
			float unit_width 	= unitRect.width;
			float unit_height 	= unitRect.height;
			float unit_topX 	= unitRect.left + m_pUnit->m_sPhysics->velosity.x;
			float unit_topY 	= unitRect.top;

			const sf::FloatRect nextUnitStep(unit_topX, unit_topY, unit_width, unit_height);

			if (nextUnitStep.intersects(tileRect))
			{
				m_pUnit->setPosition(tile_topX - unit_width, unit_topY);
			}
		}

		if (m_pUnit->isLeft())
		{
			// unit info pulled out
			sf::FloatRect unitRect = m_pUnit->getRect();
			float unit_width 	= unitRect.width;
			float unit_height 	= unitRect.height;
			float unit_topX 	= unitRect.left - m_pUnit->m_sPhysics->velosity.x;
			float unit_topY 	= unitRect.top;

			const sf::FloatRect nextUnitStep(unit_topX, unit_topY, unit_width, unit_height);

			if (nextUnitStep.intersects(tileRect))
			{
				m_pUnit->setPosition(tile_topX + tile_width, unit_topY);
			}
		}

		if (m_pUnit->isUp())
		{
			// unit info pulled out
			sf::FloatRect unitRect = m_pUnit->getRect();
			float unit_width 	= unitRect.width;
			float unit_height 	= unitRect.height;
			float unit_topX 	= unitRect.left;
			float unit_topY 	= unitRect.top - m_pUnit->m_sPhysics->velosity.y;

			const sf::FloatRect nextUnitStep(unit_topX, unit_topY, unit_width, unit_height);

			if (nextUnitStep.intersects(tileRect))
			{
				m_pUnit->setPosition(unit_topX, tile_topY + tile_height);
			}
		}

		if (m_pUnit->isDown())
		{
			// unit info pulled out
			sf::FloatRect unitRect = m_pUnit->getRect();
			float unit_width 	= unitRect.width;
			float unit_height 	= unitRect.height;
			float unit_topX 	= unitRect.left;
			float unit_topY 	= unitRect.top + m_pUnit->m_sPhysics->velosity.y;

			const sf::FloatRect nextUnitStep(unit_topX, unit_topY, unit_width, unit_height);

			if (nextUnitStep.intersects(tileRect))
			{
				m_pUnit->setPosition(unit_topX, tile_topY - unit_height);
			}
		}

	}
}
