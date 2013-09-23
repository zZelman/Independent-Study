/*
 * CUnit.h
 *
 *  Created on: Sep 20, 2013
 *      Author: zZelman
 */

#ifndef CUNIT_H_
#define CUNIT_H_

#include "include_sfml.h"
#include "CTexture.h"
#include "CSprite.h"
#include "CPhysics.h"
#include <inttypes.h>

class CUnit
{
public:
	// physics attributes of this unit
	CPhysics* m_sPhysics;

	CUnit(sf::RenderWindow* pWindow,
	      std::string texturePath,	// Relative path to the texture file on disk
	      sf::Vector2<int> subSize,	// LENGTH sub-image height/width
	      sf::Vector2<int> subNum);	// LENGTH number of sub images
	~CUnit();

	// movement getter methods
	bool isLeft();
	bool isRight();
	bool isUp();
	bool isDown();

	// * returns the top left (x,y) coord, and the width & height
	// * Screen space
	sf::FloatRect getRect();

	// returns the width/height of this sprite
	sf::Vector2<int> getSize();

	// method that loads based on instance variables
	void load();

	// Receives input from the outside world to edit the instance
	//		vars inside of this unit which affect how this unit acts/moves
	bool input(sf::Keyboard::Key* key, bool isPressed);

	void update(); // updates this units state(s)
	void render(); // renders unit @ m_pWindow

	// Relative movement of the unit based on its current position
	void move(float x, float y);

	// sets the absolute position of the unit in SCREEN SPACE
	void setPosition(float x, float y);

	// OVERRIGHTS the scale
	void setScale(float x, float y);
	void setScale(const sf::Vector2<float>* scale);

	// NO OVERRIGHTE scales the sprite by the given
	void scale(float x, float y);
	void scale(const sf::Vector2<float>* scale);

	// checks point intersection within this Unit
	bool contains(const sf::Vector2<float>* point) const;

	// * checks rectangle intersection with this and the given
	// * SCREEN SPACE
	// * takes into consideration rotation/transformations
	bool intersects(const sf::Rect<float>* rectangle) const;

private:
	sf::RenderWindow* m_pWindow; 	// where this unit will be rendered
	CTexture* m_pTexture;			// whole sprite sheet where sub images are taken from
	std::string m_texturePath;		// Relative path to the texture
	CSprite* m_pSprite;				// sub image currently being rendered w/ postiion information

	// * LENGTH height/width of the sub-section images on the texture
	// * x = width; y = height
	sf::Vector2<int> m_subSize;

	// * LENGTH number of sub-section images on the texture
	// * x = cols; y = rows
	sf::Vector2<int> m_subNum;

	// * LENGTH Current sub section that is being rendered
	// * y = row; x = col
	sf::Vector2<int> m_currSub;

	// clock that measures the animation for this unit
	sf::Clock* m_pAnimationClock;
	int64_t m_animTimerMS; // time between image switches

	// allows certain things to happen only on the first update
	bool isFirstUpdate;

	// vars that control how the unit moves
	bool isMove_right;
	bool isMove_left;
	bool isMove_up;
	bool isMove_down;
	bool isStoped;
};

#endif /* CUNIT_H_ */
