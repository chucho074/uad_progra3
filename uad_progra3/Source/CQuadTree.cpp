#include "..\Include\CQuadTree.h"

CQuadTree::CQuadTree(){



}

CQuadTree::~CQuadTree() {

	//delete CQuadTreeNode();

}

void CQuadTree::subdivide(AABB_2D bounds,std::vector<CHexa*>* cells) {

	if (mRoot == nullptr) {
		mRoot = new CQuadTreeNode();
		mRoot->setLimits(bounds);
		mRoot->subdivide(mLimitSubdiv, bounds, cells );
	}

}
