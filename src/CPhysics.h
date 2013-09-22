/*
 * SAttributes.h
 *
 *  Created on: Sep 22, 2013
 *      Author: zZelman
 */

#ifndef SPHYSICS_H_
#define SPHYSICS_H_

#include "include_sfml.h"

// This struct defines the physics properties of an object
class CPhysics
{
public:
	// * the current movement increment of the object
	// * x = x-step; y = y-step
	sf::Vector2<float> velosity;

	// * the default movement increment of the object
	// * x = x-step; y = y-step
	sf::Vector2<float> velosity_default;

	// a mesure of how long this object has been falling
	sf::Clock* pGravityClock;

	// a flag to tell whether this object is CURRENTLY falling
	bool isFalling;

	CPhysics();
	~CPhysics();
	CPhysics(sf::Vector2<float> defaultVelosity);
};


#endif /* SPHYSICS_H_ */
