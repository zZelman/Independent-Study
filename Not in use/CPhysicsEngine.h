/*
 * CPhysicsEngine.h
 *
 *  Created on: Sep 22, 2013
 *      Author: zZelman
 */

#ifndef CPHYSICSENGINE_H_
#define CPHYSICSENGINE_H_

#include "CTile.h"
#include "CMap.h"
#include "CUnit.h"

class CPhysicsEngine
{
public:
	CPhysicsEngine(CMap* pMap, CUnit* pUnit);
	~CPhysicsEngine();

	// * updates by manipulates all of the instance vars to account for collision
	// * checks unit-tile collision atm
	void update();

private:
	const std::vector<CTile*>* m_pVector_tiles;
	const std::vector<CUnit*>* m_pVector_units;

	CUnit* m_pUnit;
};

#endif /* CPHYSICSENGINE_H_ */
