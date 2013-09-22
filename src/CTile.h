/*
 * CTile.h
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#ifndef CTILE_H_
#define CTILE_H_

#include "CSprite.h"
#include "include_sfml.h"

class CTile
{
public:
	CTile(sf::RenderWindow* pWindow,	// rendering window
	      CTexture* pTexture,			// texture that this sprite will be rendering with
	      sf::Vector2<int> currSub);	// LENGTH current sub-image being rendered
	~CTile();

	// * returns the top left (x,y) coord, and the width & height
	// * Screen space
	sf::FloatRect getRect();

	void setPosition(float x, float y);

	void render();


private:
	CSprite* m_pSprite; // has-a sprite
};

#endif /* CTILE_H_ */
