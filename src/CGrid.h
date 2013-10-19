/*
 * CGrid.h
 *
 *  Created on: Oct 8, 2013
 *      Author: zZelman
 */

#ifndef CGRID_H_
#define CGRID_H_

#include <vector>
#include "include_sfml.h"
#include "CAtomicVoxel.h"
#include "CTexture.h"
#include "CSprite.h"
#include "IUpdateable.h"
#include "IRenderable.h"

class CAtomicVoxel;

// this class represents the 2D grid that ALL atomic voxels are within
class CGrid : public IUpdateable, public IRenderable
{
public:
	CGrid();
	CGrid(sf::RenderWindow* window,			// Target rendering window
	      const sf::Vector2<int>& gridSize, // how many cells are in the grid
	      const sf::Vector2<int>& gridSubSize, // pix size of an indevidual cell
	      const std::string& filePath,		// Relative path to the sprite sheet
	      const sf::Vector2<int>& subSize,	// size of a single sub-image
	      const sf::Vector2<int>& subNum);	// number of sub images on the 2D sheet
	virtual ~CGrid();
	CGrid(const CGrid& other);

	CGrid& operator=(const CGrid& other);

	sf::Vector2<int> getGridSize();

	bool userInput(sf::Event* pEvent);

	void update();
	void render();

	// checks the position at (x,y) for "free-ness"
	bool isOpen(const sf::Vector2<int>& pos);
	bool isOpen(int x, int y);

	// * same as "isOpen()" exept if true it returns the pointer to the AV
	// * false == NULL
	CAtomicVoxel* returnPos(int x, int y);
	CAtomicVoxel* returnPos(const sf::Vector2<int>& pos);
	void setPos(int x, int y, CAtomicVoxel* AV);
	void setPos(const sf::Vector2<int>& pos, CAtomicVoxel* AV);

	// removes an entire structure starting at the anchor parent
	void removeStructure(CAtomicVoxel* anchorParent);

	// if something has been removed from the data structure of AP's,
	//		the list must condense to remove gaps
	void condenseStructureList();

	// manipulates the values from grid space into screen space
	void gridToScreen(int* x, int* y);
	void gridToScreen(sf::Vector2<int>* pos);

	// manipulates the values from screen space into grid space
	void screenToGrid(int* x, int* y);
	void screenToGrid(sf::Vector2<int>* pos);

	// adds a AV to the AP data-structure
	void addAnchorParent(CAtomicVoxel* AP);
	void removeAnchorParent(CAtomicVoxel* AP);

	// creates a new AP @ screen pos IF one isnt already there
	void createAP(sf::Vector2<int>* screenPos);

	// finds the AP @ screen pos scructure IF a AV exists there
	//		then sets the m_pTestAV equal to it
	void focusAP(sf::Vector2<int>* screenPos);

	// sets a pointer to NULL within the 2D grid data structure
	void removeAV(int x, int y);
	void removeAV(const sf::Vector2<int>& pos);

	// * methods to remove everything on the 2D array to provide the
	//		functionality that there is only 1 structure on the 2D data structure
	// * this does not cause a memory leak because AP are maintained within the AP vector
	void nullALL_onGrid();
	void applyAPstructures_toGrid();


	// debug
	void printDataStructure();

private:
	CAtomicVoxel* m_pTestAV;

	// * the 2D grid data structure
	// * NULL (0) represents a free spot
	// * dynamic 2D array of pointers
	// * INDEX
	CAtomicVoxel** m_gridDataStructure;

	std::vector<CAtomicVoxel*> m_anchorParents;

	CTexture* m_pAVTexture;

	sf::RenderWindow* m_pScreen;

	sf::Vector2<int> m_gridSize; // total number of cells in (width, height)
	sf::Vector2<int> m_gridSubSize; // pixel size of an individual cell

	bool isDataStructureNULL; // keep track what state the data structure is in

};

#endif /* CGRID_H_ */
