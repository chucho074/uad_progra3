#pragma once
#ifndef CQuadTree_H
#define CQuadTree_H
#include "Globals.h"
#include "CQuadTreeNode.h"
#include "CHexaGrid.h"

/*
TODO:
>
*/

class CQuadTree {
public:
	CQuadTree();
	~CQuadTree();

	void subdivide(AABB_2D bounds, std::vector<CHexa *> cells, vector<vector<CHexa>>, int , int);
	CQuadTreeNode * mRoot;
private:
	int mLimitSubdiv;
	

};


#endif CQuadTree_H