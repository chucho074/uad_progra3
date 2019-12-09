#pragma once
#ifndef CQuadTreeNode _H
#define CQuadTreeNode_H
#include "Globals.h"
#include "AABB_2D.h"
#include "CHexa.h"
#include "CCamera.h"
#include <vector>

/*
TODO:
> Implementar la divicion
*/

class CQuadTreeNode {
public:
	CQuadTreeNode();
	~CQuadTreeNode();

	void subdivide(int limit, AABB_2D parentBounds, std::vector<CHexa *> *cells);
	void render(CCamera *cam, std::vector<CHexa *> result);

	void setBounds(AABB_2D);
	void getBounds(AABB_2D);
	void setLimits(AABB_2D limits);

private:
	CQuadTreeNode * h1;
	CQuadTreeNode * h2;
	CQuadTreeNode * h3;
	CQuadTreeNode * h4;

	AABB_2D bounds;
	std::vector<CHexa *> mData;

};


#endif CQuadTreeNode _H