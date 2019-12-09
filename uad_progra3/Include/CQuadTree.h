#pragma once
#ifndef CQuadTree_H
#define CQuadTree_H
#include "Globals.h"
#include "CQuadTreeNode.h"

/*
TODO:
>
*/

class CQuadTree {
public:
	CQuadTree();
	~CQuadTree();

	void subdivide(AABB_2D bounds, std::vector<CHexa *> *cells);
private:
	int mLimitSubdiv;
	CQuadTreeNode * mRoot;
	

};


#endif CQuadTree_H