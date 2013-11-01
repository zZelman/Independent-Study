/*
 * CTexture.h
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#ifndef CTEXTURE_H_
#define CTEXTURE_H_

#include "include_sfml.h"

class CTexture : public sf::Texture
{
public:
	CTexture();
	CTexture(std::string fileName,		// Relative path to the texture image
	         sf::Vector2<int> subSize,	// LENGTH sub-image height/width
	         sf::Vector2<int> subNum);	// LENGTH number of sub images
	CTexture(const CTexture& other);

	CTexture& operator=(const CTexture& other);

	// * LENGTH number of sub-section images on the texture
	// * x = cols; y = rows
	const sf::Vector2<int>& getSubNum() const;

	// * LENGTH height/width of the sub-section images on the texture
	// * x = width; y = height
	const sf::Vector2<int>& getSubSize() const;

	void load(std::string fileName);	// Relative path to the texture image


private:
	// * LENGTH height/width of the sub-section images on the texture
	// * x = width; y = height
	sf::Vector2<int> m_subSize;

	// * LENGTH number of sub-section images on the texture
	// * x = cols; y = rows
	sf::Vector2<int> m_subNum;

};

#endif /* CTEXTURE_H_ */
