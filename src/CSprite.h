/*
 * CSprite.h
 *
 *  Created on: Sep 14, 2013
 *      Author: zZelman
 */

#ifndef CSPRITE_H_
#define CSPRITE_H_

#include "include_sfml.h"

class CSprite
{
public:
	CSprite(sf::RenderWindow* pWindow,	// rendering window
	        std::string fileName,		// relative path to texture File (from project root)
	        int subH, int subW,			// LENGTH sub-image height/width
	        int numRow, int numCol,		// LENGTH number of sub images
	        int currRow, int currCol);	// LENGTH current sub-image being rendered
	~CSprite();

	void update(); // updates this sprite's state
	void render(); // renders the sprite to the target window

private:
	sf::RenderWindow* m_pWindow;	// target rendering window
	sf::Texture* m_pTexture;		// full texture of this sprite
	sf::Sprite* m_pSprite;			// sub-section of the texture being rendered

	int subH, subW; 		// LENGTH height/width of the sub-section images on the texture
	int numRow, numCol; 	// LENGTH number of sub-section images on the texture
	int currRow, currCol;	// LENGTH Current (row, col) that is being rendered

	void load(std::string fileName);
};

#endif /* CSPRITE_H_ */
