#include "CGame.h"

#include "include_sfml.h"
#include <iostream>

void testingBasics()
{
	// loading a texture from a file
	sf::Texture* pTexture = new sf::Texture();
	pTexture->loadFromFile("res/room 1x1.png");
	pTexture->setSmooth(true);
	pTexture->setRepeated(false);

	// creating a sprite with arbitary sizes then applying the texture to it
	sf::Sprite* pSprite = new sf::Sprite();
	pSprite->setTexture(*pTexture);

	sf::RenderWindow* pWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Testing");
	pWindow->setFramerateLimit(60);
	while (pWindow->isOpen())
	{
		sf::Event event;
		while (pWindow->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed ||
			        event.key.code == sf::Keyboard::Escape)
			{
				pWindow->close();
				return;
			}
		}

		pWindow->clear(sf::Color::White);

		pWindow->draw(*pSprite);

		pWindow->display();
	}
}

class Test
{
public:
	Test() {}
	void run()
	{
		for (int i = 0; i < 100; ++i)
		{
			std::cout << ">> Object" << std::endl;
			sf::sleep(sf::milliseconds(15));
		}
	}
};

void func()
{
	for (int i = 0; i < 100; ++i)
	{
		std::cout << "-- Function" << std::endl;
		sf::sleep(sf::milliseconds(20));
	}
}
void testingThreads()
{
	sf::Thread functionThread(&func); // arguments are possible, but only 1
	functionThread.launch();

	Test* testObj = new Test();
	sf::Thread objThread(&Test::run, testObj); // note the obj* and NO arguments
	objThread.launch();

	for (int i = 0; i < 100; ++i)
	{
		std::cout << "Main" << std::endl;
		sf::sleep(sf::milliseconds(10));
	}
}


int main()
{
//	testingBasics();
//	testingThreads();


	CGame* pGame = new CGame();

	pGame->startGame();
	delete pGame;
	pGame = NULL;

	return EXIT_SUCCESS;
}
