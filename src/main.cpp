#include "CGame.h"

int main()
{
	CGame* pGame = new CGame();

	pGame->startGame();
	delete pGame;

	return EXIT_SUCCESS;
}
