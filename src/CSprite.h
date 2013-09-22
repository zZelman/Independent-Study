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
	        sf::Vector2<int> currSub);	// LENGTH current sub-image being rendered
	virtual ~CSprite();

	// * returns the top left (x,y) coord, and the width & height
	// * Screen space
	sf::FloatRect getRect();

	// sets the current sub image being rendered from the texture
	void setSubImage(int row, int col);
	void setSubImage(const sf::Vector2<int>* newSub);

	// sets the absolute position of the sprite in screen space
	void setPosition(float x, float y);

	// OVERRIGHTS the scale
	void setScale(float x, float y);
	void setScale(const sf::Vector2<float>* scale);

	// NO OVERRIGHTE scales the sprite by the given
	void scale(float x, float y);
	void scale(const sf::Vector2<float>* scale);

	// moves the sprite a relative distance from the current position
	void move(float x, float y);

	// renders the sprite to the target window
	void render();


private:
	sf::RenderWindow* m_pWindow;	// target rendering window
	CTexture* m_pTexture;			// full texture of this sprite
	sf::Sprite* m_pSprite;			// sub-section of the texture being rendered

	// * LENGTH Current sub section that is being rendered
	// * y = row; x = col
	sf::Vector2<int> m_currSub;

	// selects a sub-section of the texture
	void chooseSubImage();

};

#endif /* CSPRITE_H_ */
