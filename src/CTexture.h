/*
 * CTexture.h
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#ifndef CTEXTURE_H_
#define CTEXTURE_H_

#include "include_sfml.h"

class CTexture
{
public:
	CTexture(std::string fileName,		// Relative path to the texture image
	         int subH, int subW,			// LENGTH sub-image height/width
	         int numRow, int numCol);	// LENGTH number of sub images
	~CTexture();

	// whole image represented with a texture
	const sf::Texture& getTexture() const;

	// whole image represented with a texture
	void setTexture(const sf::Texture& texture);

	// * LENGTH number of sub-section images on the texture
	// * x = cols; y = rows
	sf::Vector2<int> getSubNum() const;

	// * LENGTH height/width of the sub-section images on the texture
	// * x = width; y = height
	sf::Vector2<int> getSubSize() const;

	void load(std::string fileName);	// Relative path to the texture image


private:
	// whole image represented with a texture
	sf::Texture m_texture;

	// * LENGTH height/width of the sub-section images on the texture
	// * x = width; y = height
	sf::Vector2<int> subSize;

	// * LENGTH number of sub-section images on the texture
	// * x = cols; y = rows
	sf::Vector2<int> subNum;

};

#endif /* CTEXTURE_H_ */
