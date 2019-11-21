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

	//void subdivide(...);
	//CHexa * render(Camera * cam	);

	void setBounds(AABB);
	void getBounds(AABB);

private:
	AABB bounds;

};


#endif CQuadTreeNode _H