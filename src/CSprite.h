/*
 * CSprite.h
 *
 *  Created on: Sep 14, 2013
 *      Author: zZelman
 */

#ifndef CSPRITE_H_
#define CSPRITE_H_

#include "include_sfml.h"
#include "CTexture.h"

class CSprite
{
public:
	CSprite(sf::RenderWindow* pWindow,	// rendering window
	        CTexture* pTexture,			// texture that this sprite will be rendering with
	        int currRow, int currCol);	// LENGTH current sub-image being rendered
	~CSprite();

	void update(); // updates this sprite's state
	void render(); // renders the sprite to the target window

private:
	sf::RenderWindow* m_pWindow;	// target rendering window
	CTexture* m_pTexture;		// full texture of this sprite
	sf::Sprite* m_pSprite;			// sub-section of the texture being rendered

	// * LENGTH Current sub section that is being rendered
	// * y = row; x = col
	sf::Vector2<int> currSub;

};

#endif /* CSPRITE_H_ */
