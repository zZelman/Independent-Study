/*
 * CSprite.cpp
 *
 *  Created on: Sep 14, 2013
 *      Author: zZelman
 */

#include "CSprite.h"
#include "include_sfml.h"
#include <assert.h>

CSprite::CSprite(sf::RenderWindow* pWindow) {
	m_pWindow = pWindow;

	m_pTexture = new sf::Texture();
	m_pSprite = new sf::Sprite();

	load();
}

CSprite::~CSprite() {
	delete m_pTexture;
	m_pTexture = NULL;

	delete m_pSprite;
	m_pSprite = NULL;
}

void CSprite::update() {
	m_pSprite->move(1.0f, 0.0f);
}

void CSprite::render() {
	m_pWindow->draw(*m_pSprite);
}

void CSprite::load() {
	bool isLoaded = m_pTexture->loadFromFile("res/room 1x1.png");
#ifdef DEBUG
	assert(isLoaded);
#endif
	m_pTexture->setSmooth(true);
	m_pTexture->setRepeated(false);


	m_pSprite->setTexture(*m_pTexture);
}
