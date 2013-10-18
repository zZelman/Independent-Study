#include "CPhysics.h"
#include "include_sfml.h"

CPhysics::CPhysics()
{
	sf::Vector2<float> v(0.0f, 0.0f);
	velosity_default = v;
	velosity = v;

	isFalling = false;

	pGravityClock = NULL;
}


CPhysics::CPhysics(sf::Vector2<float> defaultVelosity)
{
	velosity_default = defaultVelosity;
	velosity = defaultVelosity;

	isFalling = true;

	pGravityClock = new sf::Clock();
}


CPhysics::~CPhysics()
{
	if (pGravityClock != NULL)
	{
		delete pGravityClock;
		pGravityClock = NULL;
	}
}
