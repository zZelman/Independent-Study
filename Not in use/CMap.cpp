/*
 * CMap.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: zZelman
 */

#include "CMap.h"
#include "CTexture.h"
#include "CSprite.h"
#include <assert.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

CMap::CMap(sf::RenderWindow* pWindow,
           std::string mapPath)
{
	m_pWindow = pWindow;
	m_mapPath = mapPath;

	// just to be sure, set everything else to 0
	m_pTexture = NULL;

	m_mapNum.x = 0;
	m_mapNum.y = 0;

	m_tileSetPath = "";
	m_tileSize.x = 0;
	m_tileSize.y = 0;
	m_tileSubNum.x = 0;
	m_tileSubNum.y = 0;
}


CMap::~CMap()
{
	// delete the texture used by the tiles
	delete m_pTexture;
	m_pTexture = NULL;

	// delete tiles
	for (uint i = 0; i < m_tiles.size(); ++i)
	{
		delete m_tiles[i];
		m_tiles[i] = NULL;
	}
	m_tiles.clear();
}


const std::vector<CTile*>* CMap::getTiles()
{
	return &m_tiles;
}


sf::Vector2<int> CMap::getMapNum() const
{
	return m_mapNum;
}


sf::Vector2<int> CMap::getTileSubNum() const
{
	return m_tileSubNum;
}


sf::Vector2<int> CMap::getTileSize() const
{
	return m_tileSize;
}


void CMap::load()
{
	std::vector<std::vector<int> > mapData;
	readData(&mapData); // read map file
	loadMap(&mapData);	// load map into memory basted on instance vars
}


void CMap::update()
{
}


void CMap::render()
{
	for (uint i = 0; i < m_tiles.size(); ++i)
	{
		m_tiles[i]->render();
	}
}


void CMap::readData(std::vector<std::vector<int> >* mapData)
{
	using namespace std;

	ifstream fileStream;
	fileStream.open(m_mapPath.c_str());
#ifdef DEBUG
	assert(fileStream.is_open());
#endif // DEBUG

	// flags to look for in the file
	string map_cols		= "map_cols=";
	string map_rows		= "map_rows=";

	string tile_set		= "tile_set=";
	string tile_width	= "tile_width=";
	string tile_height	= "tile_height=";
	string tile_subRow	= "tile_subRow=";
	string tile_subCol	= "tile_subCol=";

	string data			= "data=";

	// to stop double findings
	bool found_map_cols		= false;
	bool found_map_rows		= false;

	bool found_tile_set		= false;
	bool found_tile_height	= false;
	bool found_tile_width	= false;
	bool found_tile_subRow	= false;
	bool found_tile_subCol	= false;

	bool found_data			= false;


	string line;
	while (getline(fileStream, line))
	{
		if (line.find(map_cols) != string::npos && !found_map_cols)
		{
			string numStr = line.substr(map_cols.length(), line.length());
			m_mapNum.x = stringToInt(numStr);

			found_map_cols = true;
		}

		if (line.find(map_rows) != string::npos && !found_map_rows)
		{
			string numStr = line.substr(map_rows.length(), line.length());
			m_mapNum.y = stringToInt(numStr);

			found_map_rows = true;
		}

		if (line.find(tile_width) != string::npos && !found_tile_width)
		{
			string numStr = line.substr(tile_width.length(), line.length());
			m_tileSize.x = stringToInt(numStr);

			found_tile_width = true;
		}

		if (line.find(tile_height) != string::npos && !found_tile_height)
		{
			string numStr = line.substr(tile_height.length(), line.length());
			m_tileSize.y = stringToInt(numStr);

			found_tile_height = true;
		}

		if (line.find(tile_set) != string::npos && !found_tile_set)
		{
			string tileSet = line.substr(tile_set.length(), line.length());
			m_tileSetPath = tileSet;

			found_tile_set = true;
		}

		if (line.find(tile_subRow) != string::npos && !found_tile_subRow)
		{
			string numStr = line.substr(tile_subRow.length(), line.length());
			m_tileSubNum.y = stringToInt(numStr);

			found_tile_subRow = true;
		}

		if (line.find(tile_subCol) != string::npos && !found_tile_subCol)
		{
			string numStr = line.substr(tile_subCol.length(), line.length());
			m_tileSubNum.x = stringToInt(numStr);

			found_tile_subCol = true;
		}

		if (line.find(data) != string::npos && !found_data)
		{

			for (int i = 0; i < m_mapNum.y; ++i)
			{
				getline(fileStream, line);

				vector<int> lineVector;
				int lineLength = line.length();
				for (int n = 0; n < lineLength; ++n)
				{
					string delimiter = ",";
					string numStr = line.substr(0, line.find(delimiter));
					int numInt = stringToInt(numStr);
					lineVector.push_back(numInt);

					// this line of code slowly reduces the size of the string
					//		each time a number is found (from the start to the next ',')
					//		it makes a substring from the rest of the line after the ','
					line = line.substr(line.find(delimiter) + 1, line.length());
				}
				// get rid of any spot that was grown by the vector that we don't want
				//		(it is uninitialized data which could be a problem)
				lineVector.resize(m_mapNum.x);

				// push the line vector (map line) onto the given mapData vector
				//	(given in function arguments)
				mapData->push_back(lineVector);
			}
		}

	}

	fileStream.close();

	// debug code
//	cout << "mapCols: " << m_MapColumns << endl;
//	cout << "mapRows: " << m_MapRows << endl;
//
//	cout << "tileSet: " << m_tileSetPath << endl;
//	cout << "tile W : " << m_tileWidth << endl;
//	cout << "tile H : " << m_tileHeight << endl;
//	cout << "subRow : " << m_subRow << endl;
//	cout << "subCol : " << m_subCol << endl;
}


void CMap::loadMap(std::vector<std::vector<int> >* mapData)
{
	// * all data has been extracted from the map file at this point
	// * the actual map representation data is stored within mapData 2D vector


	// this is the texture that all of the tiles will use
	m_pTexture = new CTexture(m_tileSetPath,
	                          m_tileSize,
	                          m_tileSubNum);

	// create and add all of the tiles to the m_tiles 2D vector
	using namespace std;
	for (uint i = 0; i < mapData->size(); ++i)
	{
		vector<int> lineVector = mapData->at(i);
		for (uint n = 0; n < lineVector.size(); ++n)
		{
			// optimization... 0's represent NO tile present
			if (lineVector[n] == 0)
			{
				continue;
			}

			// * the constant 1 here means that the Tiles ATM come from a strip-like sprite sheet
			//		(a row of 1 and n columns)
			// * change this if you want to have a nxm sprite sheet to represent the tiles
			sf::Vector2<int> currSub(lineVector[n], 1);
			CTile* pTile = new CTile(m_pWindow, m_pTexture, currSub);
			float x = n * m_tileSize.x;
			float y = i * m_tileSize.y;
			pTile->setPosition(x, y);
			m_tiles.push_back(pTile);
		}
	}
}


int CMap::stringToInt(std::string str)
{
	int result;
	std::stringstream newInt(str);
	newInt >> result;
	return result;
}
