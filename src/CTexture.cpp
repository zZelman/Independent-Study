/*
 * CTexture.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#include "CTexture.h"
#include "include_sfml.h"
#include <assert.h>


CTexture::CTexture()
{
//	m_pTexture = NULL;
}


CTexture::CTexture(std::string fileName,
                   sf::Vector2<int> subSize,
                   sf::Vector2<int> subNum)
{
	m_subSize = subSize;

	m_subNum = subNum;

//	m_pTexture = new sf::Texture();

	load(fileName);
}


CTexture::~CTexture()
{
//	delete m_pTexture;
//	m_pTexture = NULL;
}


CTexture::CTexture(const CTexture& other)
{
//	m_pTexture = new sf::Texture();
//	*m_pTexture = *(other.m_pTexture);

	m_subSize = other.m_subSize;

	m_subNum = other.m_subNum;
}


CTexture& CTexture::operator=(const CTexture& other)
{
	if (this == &other)
	{
		return *this;
	}

//	if (m_pTexture != NULL)
//	{
//		delete m_pTexture;
//	}
//	m_pTexture = new sf::Texture();
//	*m_pTexture = *(other.m_pTexture);

	m_subSize = other.m_subSize;

	m_subNum = other.m_subNum;

	return *this;
}


//sf::Texture* CTexture::getTexture() const
//{
//	return m_pTexture;
//}


//void CTexture::setTexture(sf::Texture* texture)
//{
//	if (m_pTexture != NULL)
//	{
//		delete m_pTexture;
//	}
//	m_pTexture = texture;
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
//	bool isLoaded = m_pTexture->loadFromFile(fileName);
//#ifdef DEBUG
//	assert(isLoaded);
//#endif
//	m_pTexture->setSmooth(true);
//	m_pTexture->setRepeated(false);

	bool isLoaded = loadFromFile(fileName);
#ifdef DEBUG
	assert(isLoaded);
#endif
	setSmooth(true);
	setRepeated(false);
}
