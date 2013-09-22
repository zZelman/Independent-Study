/*
 * CTexture.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#include "CTexture.h"
#include "include_sfml.h"
#include <assert.h>

CTexture::CTexture(std::string fileName,
                   sf::Vector2<int> subSize,
                   sf::Vector2<int> subNum)
{
	m_subSize = subSize;

	m_subNum = subNum;

	load(fileName);
}


CTexture::~CTexture()
{
}


const sf::Texture& CTexture::getTexture() const
{
	return m_texture;
}

void CTexture::setTexture(const sf::Texture& texture)
{
	m_texture = texture;
}


//void CTexture::setCurrSub(sf::Vector2<int> currSub) {
//#ifdef DEBUG
//	assert(currSub.y > 0 && currSub.x > 0);
//	assert(currSub.y <= subNum.y && currSub.x <= subNum.x);
//#endif
//
//	this->currSub = currSub;
//}


sf::Vector2<int> CTexture::getSubNum() const
{
	return m_subNum;
}


sf::Vector2<int> CTexture::getSubSize() const
{
	return m_subSize;
}


void CTexture::load(std::string fileName)
{
	bool isLoaded = m_texture.loadFromFile(fileName);
#ifdef DEBUG
	assert(isLoaded);
#endif
	m_texture.setSmooth(true);
	m_texture.setRepeated(false);
}
