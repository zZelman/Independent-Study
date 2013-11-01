/*
 * CTexture.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#include "CTexture.h"
#include "include_sfml.h"
#include <assert.h>


CTexture::CTexture() : Texture()
{

}


CTexture::CTexture(std::string fileName,
                   sf::Vector2<int> subSize,
                   sf::Vector2<int> subNum)
{
	m_subSize = subSize;

	m_subNum = subNum;

	load(fileName);
}


CTexture::CTexture(const CTexture& other) : Texture(other)
{
	m_subSize = other.m_subSize;

	m_subNum = other.m_subNum;
}


CTexture& CTexture::operator=(const CTexture& other)
{
	if (this == &other)
	{
		return *this;
	}

	sf::Texture::operator =(other);

	m_subSize = other.m_subSize;

	m_subNum = other.m_subNum;

	return *this;
}


const sf::Vector2<int>& CTexture::getSubNum() const
{
	return m_subNum;
}


const sf::Vector2<int>& CTexture::getSubSize() const
{
	return m_subSize;
}


void CTexture::load(std::string fileName)
{
	bool isLoaded = loadFromFile(fileName);
#ifdef DEBUG
	assert(isLoaded);
#endif
	setSmooth(true);
	setRepeated(false);
}
