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
	CMap(sf::RenderWindow* pWindow,	// window that everything will be rendered
	     std::string mapPath);		// path to the map representation file
	~CMap();

	const std::vector<CTile*>* getTiles();
	sf::Vector2<int> getMapNum() const;
	sf::Vector2<int> getTileSubNum() const;
	sf::Vector2<int> getTileSize() const;

	void load();

	void update();
	void render();

private:
	sf::RenderWindow* m_pWindow;	// where this map will be rendered
	std::vector<CTile*> m_tiles;	// pointers to all of the tile spites
	CTexture* m_pTexture;			// the texture that all of the spites will use

	std::string m_mapPath;	// relative path to the map data file
	sf::Vector2<int> m_mapNum; // LENGTH number of tiles per (x = col; y = row)

	std::string m_tileSetPath;		// relative path to the texture that all sub-images come from
	sf::Vector2<int> m_tileSize; 	// x = width; y = height
	sf::Vector2<int> m_tileSubNum;	// x = cols, y = rows;

	// * reads all of the data from the file into the member variables
	// * does not create anything with 'new'
	// * mapData is a reference to the map int representation within the file
	//		it is MODIFIED in this function, and then EXTERNALLY passed down the line
	//		(to loadMap)
	void readData(std::vector<std::vector<int> >* mapData);

	// * uses the instance variables loaded by 'readData' to 'new' things into memory
	// * 'mapData' is the 2D int representation of the actual map itself
	//		where the individual indices corespond to a sub-image on the texture
	void loadMap(std::vector<std::vector<int> >* mapData);

	int stringToInt(std::string str);
};

#endif /* CMAP_H_ */
