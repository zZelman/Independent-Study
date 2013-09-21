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
#include <inttypes.h>

class CUnit
{
public:
	CUnit(sf::RenderWindow* pWindow,
	      std::string texturePath,	// Relative path to the texture file on disk
	      int subH, int subW,		// LENGTH sub-image height/width
	      int numRow, int numCol);	// LENGTH number of sub images
	~CUnit();

	// method that loads based on instance variables
	void load();

	// Receives input from the outside world to edit the instance
	//		vars inside of this unit which affect how this unit acts/moves
	bool input();

	void update(); // updates this units state(s)
	void render(); // renders unit @ m_pWindow

	// Relative movement of the unit based on its current position
	void move(float x, float y);

	// sets the absolute position of the unit in SCREEN SPACE
	void setPosition(float x, float y);

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

	// static movement size of each step that this unit takes
	int m_moveStepSize;

	// vars that control how the unit moves
	bool isMove_right;
	bool isMove_left;
	bool isMove_up;
	bool isMove_down;
};

#endif /* CUNIT_H_ */
