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
#include "IRenderable.h"

class CSprite : public IRenderable, public sf::Sprite
{
public:
	CSprite();
	CSprite(sf::RenderWindow* pWindow,	// rendering window
	        CTexture* pTexture,			// texture that this sprite will be rendering with
	        const sf::Vector2<int>& currSub);	// LENGTH current sub-image being rendered
	~CSprite();
	CSprite(const CSprite& other);

	// sets the current sub image being rendered from the texture
	void setSubImage(int col, int row);
	void setSubImage(const sf::Vector2<int>* newSub);

	// renders the sprite to the target window
	void render();


private:
	sf::RenderWindow* m_pWindow;	// target rendering window
	CTexture* m_pTexture;			// full texture of this sprite

	// * LENGTH Current sub section that is being rendered
	// * y = row; x = col
	sf::Vector2<int> m_currSub;

	// selects a sub-section of the texture
	void chooseSubImage();

};

#endif /* CSPRITE_H_ */
