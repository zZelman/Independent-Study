/*
 * CSprite.h
 *
 *  Created on: Sep 14, 2013
 *      Author: zZelman
 */

#ifndef CSPRITE_H_
#define CSPRITE_H_

#include "include_sfml.h"

class CSprite {
public:
	CSprite(sf::RenderWindow* pWindow);
	~CSprite();

	void update();
	void render();

private:
	sf::RenderWindow* m_pWindow;
	sf::Texture* m_pTexture;
	sf::Sprite* m_pSprite;

	void load();
};

#endif /* CSPRITE_H_ */
