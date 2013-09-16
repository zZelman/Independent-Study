/*
 * CMap.h
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#ifndef CMAP_H_
#define CMAP_H_

#include "include_sfml.h"
#include "CTile.h"

class CMap
{
public:
	CMap(sf::RenderWindow* pWindow,		// window that everything will be rendered
	     std::string texturePath,	// path to the texture image
	     int subH, int subW,			// height and width of a sub-image on the texture
	     int numRow,	int numCol,		// number of sub-images on the texture
	     std::string mapPath);		// path to the map representation file
	~CMap();

	std::vector<CTile*>* getTiles();

	void update();
	void render();


private:
	sf::RenderWindow* m_pWindow;	// where this map will be rendered
	std::vector<CTile*> m_tiles;	// pointers to all of the tile spites
	CTexture* m_pTexture;			// the texture that all of the spites will use

	void loadTexture(std::string texturePath, // loads a whole texture into memory
	                 int subH, int subW,
	                 int numRow,	int numCol);

	void loadMap(std::string mapPath); // loads spites into memory based on the file given
};

#endif /* CMAP_H_ */
