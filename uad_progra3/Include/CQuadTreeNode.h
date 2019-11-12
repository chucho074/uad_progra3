#pragma once
#ifndef CQuadTreeNode _H
#define CQuadTreeNode_H
#include "Globals.h"
#include "AABB.h"
#include "CHexa.h"

/*
TODO:
> Implementar la divicion
*/

class CQuadTreeNode {
public:
	CQuadTreeNode();
	~CQuadTreeNode();

private:
	AABB bounds;
public:
	//void subdivide(...);
	//CHexa * render(Camera * cam	);

};


#endif CQuadTreeNode _H