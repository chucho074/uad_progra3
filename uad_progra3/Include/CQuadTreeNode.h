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

	void subdivide(int, AABB_2D, std::vector<CHexa *>, vector<vector<CHexa>>, int, int);
	void render(COpenGLRenderer *, unsigned int );

	void setBounds(AABB_2D);
	void getBounds(AABB_2D);
	void setLimits(AABB_2D limits);

	AABB_2D bounds;
private:
	CQuadTreeNode * h1;
	CQuadTreeNode * h2;
	CQuadTreeNode * h3;
	CQuadTreeNode * h4;

	vector<CHexa *> mData;
	vector<vector<CHexa>> SV;

};


#endif CQuadTreeNode _H