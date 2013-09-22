/*
 * CGame.h
 *
 *  Created on: Sep 14, 2013
 *      Author: zZelman
 */

#ifndef CGAME_H_
#define CGAME_H_

#include "include_sfml.h"
#include "CSprite.h"
#include "CTexture.h"
#include "CMap.h"
#include "CUnit.h"
#include "CPhysicsEngine.h"

class CGame
{
public:
	CGame();
	~CGame();

	void startGame();
	void stopGame();
private:
	sf::RenderWindow* m_pGameWindow;
	CUnit* m_pTestUnit;
	CMap* m_pTestMap;
	CPhysicsEngine* m_pPhysicsEngine;

	bool isRunning;
	bool isPaused;

	void initWindow();

	void gameLoop();

	bool input_user(sf::Event* pEvent);
	bool input_gameSystem(sf::Event* pEvent);
	void update();
	void render();
};

#endif /* CGAME_H_ */
