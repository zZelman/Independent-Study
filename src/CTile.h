/*
 * CTile.h
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#ifndef CTILE_H_
#define CTILE_H_

#include "CSprite.h"

class CTile: public CSprite
{
public:
	CTile(sf::RenderWindow* pWindow,	// rendering window
	      CTexture* pTexture,			// texture that this sprite will be rendering with
	      int currRow, int currCol);	// LENGTH current sub-image being rendered
	~CTile();

	void update();
	void render();
};

#endif /* CTILE_H_ */
