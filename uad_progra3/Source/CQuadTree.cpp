#include "..\Include\CQuadTree.h"

CQuadTree::CQuadTree(){

	mRoot = nullptr;

}

CQuadTree::~CQuadTree() {

	//delete CQuadTreeNode();

}

void CQuadTree::subdivide(AABB_2D bounds,std::vector<CHexa*> cells, vector<vector<CHexa>> inSV, int maxdivisiones, int maxtriangulos) {

	if (mRoot == nullptr) {
		mRoot = new CQuadTreeNode();
		mRoot->setLimits(bounds);
		mRoot->subdivide(maxtriangulos, bounds, cells, inSV, 0, maxdivisiones);
	}
}
