#include "CGame.h"
#include "include_sfml.h"
#include "CSprite.h"
#include "CTexture.h"
#include <iostream>
#include <assert.h>

CGame::CGame()
{
	initWindow(); // m_pGameWindow new'ed here

	sf::Vector2<int> gridSize(35, 35);
	sf::Vector2<int> gridSubSize(20, 20); // 1 cell is 20x20 pixels
	m_pGrid = new CGrid(m_pGameWindow,
	                    gridSize, gridSubSize,
	                    "res/Atomic Voxels/AV placeholder art(20w 20h).png",
	                    sf::Vector2<int>(20, 20),
	                    sf::Vector2<int>(4, 6));

	isRunning = false;
	isPaused = false;
}


CGame::CGame(const CGame& other)
{
//	m_pGameWindow = new sf::RenderWindow();
//	*m_pGameWindow = *(other.m_pGameWindow);

	std::cout << "CGame copy constructor called, exiting" << std::endl;
	assert(false);

	m_pGrid = new CGrid();
	*m_pGrid = *(other.m_pGrid);

	isRunning = other.isRunning;
	isPaused = other.isPaused;
}


CGame::~CGame()
{
	delete m_pGameWindow;
	m_pGameWindow = NULL;

	delete m_pGrid;
	m_pGrid = NULL;

}


CGame& CGame::operator=(const CGame& other)
{
	if (this == &other)
	{
		return *this;
	}

	std::cout << "CGame operator= called, exiting" << std::endl;
	assert(false);

	// [QUESTION] not sure if need delete?
//	if (m_pGameWindow != NULL)
//	{
//		delete m_pGameWindow;
//	}
//	m_pGameWindow = new sf::RenderWindow();
//	*m_pGameWindow = *(other.m_pGameWindow);

	// [QUESTION] not sure if need delete?
	if (m_pGrid != NULL)
	{
		delete m_pGrid;
	}
	m_pGrid = new CGrid();
	*m_pGrid = *(other.m_pGrid);

	isRunning = other.isRunning;
	isPaused = other.isPaused;

	return *this;
}


sf::RenderWindow* CGame::getGameWindow()
{
	return m_pGameWindow;
}


bool CGame::getIsRunning()
{
	return isRunning;
}


bool CGame::getIsPaused()
{
	return isPaused;
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
	int numTiles = 35;
	int sizeTile = 20;
	m_pGameWindow 	= new sf::RenderWindow(sf::VideoMode(sizeTile * numTiles, sizeTile * numTiles), "Independent Study");

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

	// keyboard
	if (pEvent->type == sf::Event::KeyPressed) // press
	{
		if (pEvent->key.code == sf::Keyboard::Escape)
		{
			m_pGameWindow->close();
			return true;
		}

		if (m_pGrid->userInput_keyPress(pEvent) == true)
		{
			return true;
		}

	}
	else if (pEvent->type == sf::Event::KeyReleased) // release
	{
		if (m_pGrid->userInput_keyRelease(pEvent) == true)
		{
			return true;
		}
	}

	// mouse
	if (pEvent->type == sf::Event::MouseButtonPressed) // press
	{
		if (m_pGrid->userInput_mousePress(pEvent) == true)
		{
			return true;
		}
	}
	else if (pEvent->type == sf::Event::MouseButtonReleased) // release
	{
		if (m_pGrid->userInput_mouseRelease(pEvent) == true)
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
	m_pGrid->update();
}


void CGame::render()
{
	m_pGameWindow->clear(sf::Color::White); // clear screen with a black background

	// drawing here...
	m_pGrid->render();

//	sf::Vertex line[] =
//	{
//			sf::Vertex(sf::Vector2f(10, 10), sf::Color::Blue),
//			sf::Vertex(sf::Vector2f(150, 150), sf::Color::Blue)
//	};
//
//	m_pGameWindow->draw(line, 2, sf::Lines);

	m_pGameWindow->display(); // displays what has been rendered since last clear
}
