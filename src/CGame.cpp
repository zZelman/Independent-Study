#include "CGame.h"
#include "include_sfml.h"
#include "CSprite.h"
#include "CTexture.h"
#include "CMap.h"
#include <iostream>

CGame::CGame()
{
	initWindow();

	m_pTestMap = new CMap(m_pGameWindow,
	                      "res/tile sets/testing.txt");
	m_pTestMap->load();
//	sf::Thread mapThread(&CMap::load, m_pTestMap);
//	mapThread.launch();

	sf::Vector2<int> subSize(32, 46);
	sf::Vector2<int> subNum(6, 2);
	m_pTestUnit = new CUnit(m_pGameWindow,
	                        "res/ninja (46h 32w).png",
	                        subSize,
	                        subNum);
	m_pTestUnit->load();
	m_pTestUnit->setPosition(0, 0);
//	sf::Thread unitThread(&CUnit::load, m_pTestUnit);
//	unitThread.launch();

	// ... [load other things] ...

	// cannot begin the game until everything is loaded
//	mapThread.wait();
//	unitThread.wait();

	isRunning = false;
	isPaused = false;
}


CGame::~CGame()
{
	delete m_pGameWindow;
	m_pGameWindow = NULL;

	delete m_pTestMap;
	m_pTestMap = NULL;

	delete m_pTestUnit;
	m_pTestUnit = NULL;
}


void CGame::startGame()
{
	gameLoop();
}


void CGame::stopGame()
{
	isRunning = false;
}


void CGame::initWindow()
{
	m_pGameWindow 	= new sf::RenderWindow(sf::VideoMode(500, 500), "Independent Study");

	// NOTE: do not use Virtual Sync and fixed frame rate at once
//	m_pGameWindow->setVerticalSyncEnabled(true);
	m_pGameWindow->setFramerateLimit(60);
}


void CGame::gameLoop()
{
	isRunning = true;

	while (m_pGameWindow->isOpen() && isRunning)
	{

		// NOTE: events must be polled within the main window thread
		sf::Event event;
		while (m_pGameWindow->pollEvent(event))
		{
			// window was closed by user
			if (event.type == sf::Event::Closed)
			{
				m_pGameWindow->close();
				return;
			}

			// update game system information (size, focus, etc)
			bool stateConsumed = input_gameSystem(&event);

			// only allow the user to supply input to the game when not paused
			//		and the input was not a system call
			if (!isPaused && !stateConsumed)
			{
				input_user(&event);
			}
		}

		if (!isPaused) // only update states if game is actively running
		{
			update(); // update all game states
		}

		render(); // render all game things based on their states
	}

	// if the program flow gets here, its because isRunning was requested as being false
	//		therefore, you still need to close the window
	m_pGameWindow->close();
}


bool CGame::input_user(sf::Event* pEvent)
{

	// keyboard key-press DOWN
	if (pEvent->type == sf::Event::KeyPressed)
	{
		switch (pEvent->key.code)
		{
		case sf::Keyboard::Escape:
			m_pGameWindow->close();
			return true;
			break;
		default:
			break;
		}
	}

	// user pressed a mouse button within the game
	if (pEvent->type == sf::Event::MouseButtonPressed)
	{
		if (pEvent->mouseButton.button == sf::Mouse::Right)
		{
			return true;
		}
		if (pEvent->mouseButton.button == sf::Mouse::Left)
		{
			return true;
		}
	}

	return false;
}


bool CGame::input_gameSystem(sf::Event* pEvent)
{
	// user is not looking at game
	if (pEvent->type == sf::Event::LostFocus)
	{
		isPaused = true;
		return true;
	}

	// user is looking at the game now
	if (pEvent->type == sf::Event::GainedFocus)
	{
		isPaused = false;
		return true;
	}

	// user changed the window size
	if (pEvent->type == sf::Event::Resized)
	{
		// TODO: assign new values for window resized
//		m_pGameWindow->setSize(sf::Vector2<uint>(pEvent->size.width, pEvent->size.height));
//		std::cout << m_pGameWindow->getSize().x << ", " << m_pGameWindow->getSize().y << std::endl;
		return true;
	}

	return false;
}


void CGame::update()
{
	m_pTestMap->update();
	m_pTestUnit->update();
}


void CGame::render()
{
	m_pGameWindow->clear(sf::Color::White); // clear screen with a black background


	// drawing here...
	m_pTestMap->render();
	m_pTestUnit->render();

	m_pGameWindow->display(); // displays what has been rendered since last clear
}
