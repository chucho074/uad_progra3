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

private:
	int mLimitSubdiv;
	CQuadTreeNode * mRoot;


};


#endif AABB_H