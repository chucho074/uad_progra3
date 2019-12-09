#include "..\Include\CQuadTreeNode.h"

CQuadTreeNode::CQuadTreeNode() {

	h1 = nullptr;
	h2 = nullptr;
	h3 = nullptr;
	h4 = nullptr;

}

CQuadTreeNode::~CQuadTreeNode() {


}

void CQuadTreeNode::subdivide(int limit, AABB_2D parentBounds, std::vector<CHexa*> * cells) {

	int tricount = 0;
	for (int i = 0; i < cells->size(); ++i) {
		tricount += cells->at(i)->getTriangleCount();
	}
	if (cells->size() == 1 || tricount < limit) {
		//Copiar elementos de cells a mData
		h1 = h2 = h3 = h4 = nullptr;
	}
	else {
		CVector3 corners[4];
		AABB_2D childBounds[4];
		
		parentBounds.getCorners(corners);
		corners[1].X /= 2;
		corners[3].X /= 2;
		corners[2].Z /= 2;
		corners[3].Z /= 2;
		childBounds[0].setCorners(corners);

		parentBounds.getCorners(corners);
		corners[0].X /= 2;
		corners[2].X /= 2;
		corners[2].Z /= 2;
		corners[3].Z /= 2;
		childBounds[1].setCorners(corners);

		parentBounds.getCorners(corners);
		corners[1].X /= 2;
		corners[3].X /= 2;
		corners[0].Z /= 2;
		corners[1].Z /= 2;
		childBounds[2].setCorners(corners);

		parentBounds.getCorners(corners);
		corners[0].X /= 2;
		corners[2].X /= 2;
		corners[1].Z /= 2;
		corners[0].Z /= 2;
		childBounds[3].setCorners(corners);

		h1 = new CQuadTreeNode();
		h1->setLimits(childBounds[0]);
		h2 = new CQuadTreeNode();
		h2->setLimits(childBounds[1]);
		h3 = new CQuadTreeNode();
		h3->setLimits(childBounds[2]);
		h4 = new CQuadTreeNode();
		h4->setLimits(childBounds[3]);

		std::vector<CHexa *> childCells[4];
		for (int i = 0; i < cells->size(); ++i) {
			CHexa *cell = cells->at(i);
			CVector3 corners[4];
			//Obtener esquinas de la celda
			if (childBounds[0].pointsInside(corners)) {
				childCells[0].push_back(cell);
			}
			//Igual para 1...3
		}
		h1->subdivide(limit, childBounds[0], &childCells[0]);
		//h2,h3,h4
	}

}

void CQuadTreeNode::render(CCamera *cam, std::vector<CHexa*> result) {



}

void CQuadTreeNode::setBounds(AABB_2D) {



}

void CQuadTreeNode::getBounds(AABB_2D) {



}

void CQuadTreeNode::setLimits(AABB_2D limits)
{
}


