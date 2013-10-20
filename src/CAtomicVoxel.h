/*
 * CAtomicVoxel.h
 *
 *  Created on: Oct 8, 2013
 *      Author: zZelman
 */

#ifndef CATOMICVOXEL_H_
#define CATOMICVOXEL_H_

#include <vector>
#include "include_sfml.h"
#include "CGrid.h"
#include "CTexture.h"
#include "CSprite.h"
#include "IUpdateable.h"

class CGrid;

struct SEdgeBools
{
	bool up;
	bool down;
	bool left;
	bool right;
	inline void trueALL()
	{
		up = true;
		down = true;
		left = true;
		right = true;
	}
};

class CAtomicVoxel : public IUpdateable, public IRenderable
{
public:
	CAtomicVoxel();
	CAtomicVoxel(CGrid* grid,						// grid that this AV exists
	             const sf::Vector2<int>& gridPos, 	// position on grid
	             sf::RenderWindow* window,			// where to render
	             CTexture* texture,					// sprite sheet used to render
	             const sf::Vector2<int>& currSub); 	// sub image on texture
	CAtomicVoxel(const CAtomicVoxel& other);
	virtual ~CAtomicVoxel();

	CAtomicVoxel& operator=(const CAtomicVoxel& other);

	// access method for sprite
	void setSpriteScreenPos(int x, int y);
	void setSpriteScreenPos(const sf::Vector2<int>& pos);

	void update();
	void render();

	// returns the anchor parent of the structure that this AV is within
	CAtomicVoxel* findAnchorParent();
	void setParent(CAtomicVoxel* AV);

	// * relative movement based on current position
	// * MOVES CHILDREN TOO
	void move(const sf::Vector2<int>& delta);
	void move(int dx, int dy);

	// * sets absolute position of the AV
	// * calculates the delta x and y then calls move() on the children of this AV
	void setPosition(const sf::Vector2<int>& pos);
	void setPosition(int x, int y);

	// updates the edge state bools for each case
	void updateEdge_add(CAtomicVoxel* anchorParent);	// only true -> false
	void updateEdge_remove(CAtomicVoxel* anchorParent);	// only false -> true;

	// adds the given AV to the children of this AV
	void bindAVasChild(CAtomicVoxel* AV);

	// removes the given pointer from the children vector
	void removeChild(CAtomicVoxel* AV);

	// 3 different options to deal with what damage to this AV does

	// deletes this AV and makes all of its children an AP
	void damage_remove();
	// does not delete this AV, but does make children APs
	void damage_breakChildBond();
	// does not delete this AV, but makes this AV a AP
	void damage_breakParentBond();

	// removes this structure's AV pointers from the 2D Grid
	void removeStructure_fromGrid();

	// re-adds this structure's AV pointers to the 2D grid
	void addStructure_toGrid();

	// re-addresses the edge conditions for the ENTIRE structure that his AV is in
	void setEdgeBools_add();
	void setEdgeBools_remove();

private:
	// tree data-structure that each AV-structure must abide by
	//		1 - [] - n
	CAtomicVoxel* m_pParentAV;
	std::vector<CAtomicVoxel*> m_childrenAV;

	// * representation of the edges of this AV
	//	* true if there is an edge, false if there is another
	//		AV within the structure to that direction
	SEdgeBools m_isEdge;

	CGrid* m_pGrid; // pointer to the gird where this AV queries for things

	sf::Vector2<int> m_gridPos; // grid space coords of this AV within the 2D data-structure
	sf::Vector2<int> m_screenPos; // position of upper left corner to decrease render calculations

	CTexture* m_pTexture;
	CSprite* m_pSprite;

	bool isStructureRemoved; // keep Track of what state the structure is in

	// hard coded edge conditions to choose an image corresponding to the current
	//		edge conditions
	void chooseImageBasedOnEdge();

	// * checks the 4 coords around the addedAV and then sets the edges accordingly
	// * the "sub" stands for: being called by setEdgeBools_add()
	//		this is necessary because I don't want the children of this (and all subsequent)
	//		to do repetitive things ---> increase effichancy
	void setEdgeBools_add_sub();
	void setEdgeBools_remove_sub(); // same comment applies (above), in respect to "remove"

	// * update the screen position based on the grid position
	// * also updates the m_pSprite
	void setScreenPos();

	// decompositions of the move function
	void move_x(int dx);
	void move_y(int dy);

	// * check to see if ALL of the structure can move in the direction
	// * checks only grid edges
	// * NOT COLLISION
	bool canMove_x(int dx);
	bool canMove_y(int dy);

	// * checks for collision of other AV on the 2D data structure
	// * adds them to this children if collision happens
	// * checks with FUTURE movement, does not move this AV
	bool isCollisionDetected_x(int dx);
	bool isCollisionDetected_y(int dy);
};


#endif /* CATOMICVOXEL_H_ */
