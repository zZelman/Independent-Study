#include "CGame.h"

#include "include_sfml.h"

void testing()
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


int main()
{
//	testing();


	CGame* pGame = new CGame();

	pGame->startGame();
	delete pGame;
	pGame = NULL;

	return EXIT_SUCCESS;
}
