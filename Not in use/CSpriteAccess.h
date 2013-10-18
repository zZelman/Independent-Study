/*
 * CSpriteAccess.h
 *
 *  Created on: Oct 10, 2013
 *      Author: zZelman
 */

#ifndef CSPRITEACCESS_H_
#define CSPRITEACCESS_H_
#include "include_sfml.h"

// this is a base class to ease the accessibility of sf::Sprite Methods
class CSpriteAccess
{
public:
	CSpriteAccess();
	CSpriteAccess(const sf::Texture& texture);
	CSpriteAccess(const sf::Texture& texture, const sf::IntRect& rectangle);
	virtual ~CSpriteAccess();

	// * deletes the current sprite and sets it equal to argument sprite
	// * GIVEN SPRITE MUST NOT BE A STACK OBJECT
	void setSprite(sf::Sprite* sprite);

	// Change the source texture of this sprite
	void setTexture(const sf::Texture&, bool resetRect = false);

	// * Selects the sub-image of the texture
	// * Sprite-sheet coords NOT personal CTexture coords
	void setTextureRect(const sf::IntRect& rectangle);

	// not sure if I want a texture here....
	const sf::Texture* getTexture();

	// gets the position of the sprite
	const sf::Vector2f& getPosition();

	// absolute screen space coords
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2<float>& position);

	// Relative position
	void move(float dx, float dy);
	void move(const sf::Vector2<float>& delta);

	// how big the sprite is
	void setScale(float x, float y);
	void setScale(const sf::Vector2<float>& factors);

protected:
	void clear(); // delete on command
	sf::Sprite* m_pSprite; // API sprite

};


#endif /* CSPRITEACCESS_H_ */
