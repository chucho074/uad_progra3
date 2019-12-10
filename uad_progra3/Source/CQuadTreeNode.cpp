#include "..\Include\CQuadTreeNode.h"

CQuadTreeNode::CQuadTreeNode() {

	h1 = nullptr;
	h2 = nullptr;
	h3 = nullptr;
	h4 = nullptr;

}

CQuadTreeNode::~CQuadTreeNode() {


}

void CQuadTreeNode::subdivide(int limit, AABB_2D parentBounds, std::vector<CHexa*>  cells, vector<vector<CHexa>> inSV, int divactual, int divmax) {

	bool useType = false;

	int tricount = 0;
	
	//Caso: usa SuperVector
	if (inSV.size() > 0) {
		for (int i = 0; i < inSV.size(); i++) {
			for (int j = 0; j < inSV[i].size(); j++) {
				tricount += inSV[i][j].getTriangleCount();
			}
		}
		useType = true;
	}
	
	//Caso: usa la Celda
	else if (cells.size() > 0) {
		for (int i = 0; i < cells.size(); ++i) {
			tricount += cells.at(i)->getTriangleCount();
		}
	}
	
	//Caso: usa la celda
	if (!useType) {
		//Ya está dividido al máximo
		if (cells.size() == 1 || tricount <= limit || divactual >= divmax) {
			h1 = h2 = h3 = h4 = nullptr;
			mData = cells;
		}
		//Segir dividiendo xd
		else {
			
			CVector3 corners[4];
			AABB_2D childBounds[4];

			parentBounds.getCorners(corners);
			corners[1].X = (corners[1].getX() / 2) + (corners[0].getX() / 2);
			corners[3].X = (corners[3].getX() / 2) + (corners[0].getX() / 2);
			corners[2].Z = (corners[2].getZ() / 2) + (corners[0].getZ() / 2);
			corners[3].Z = (corners[3].getZ() / 2) + (corners[0].getZ() / 2);
			childBounds[0].setCorners(corners);

			parentBounds.getCorners(corners);
			corners[0].X = (corners[0].getX() / 2) + (corners[1].getX() / 2);
			corners[2].X = (corners[2].getX() / 2) + (corners[1].getX() / 2);
			corners[2].Z = (corners[2].getZ() / 2) + (corners[1].getZ() / 2);
			corners[3].Z = (corners[3].getZ() / 2) + (corners[1].getZ() / 2);
			childBounds[1].setCorners(corners);

			parentBounds.getCorners(corners);
			corners[1].X = (corners[1].getX() / 2) + (corners[2].getX() / 2);
			corners[3].X = (corners[3].getX() / 2) + (corners[2].getX() / 2);
			corners[0].Z = (corners[0].getZ() / 2) + (corners[2].getZ() / 2);
			corners[1].Z = (corners[1].getZ() / 2) + (corners[2].getZ() / 2);
			childBounds[2].setCorners(corners);

			parentBounds.getCorners(corners);
			corners[0].X = (corners[0].getX() / 2) + (corners[3].getX() / 2);
			corners[2].X = (corners[2].getX() / 2) + (corners[3].getX() / 2);
			corners[1].Z = (corners[1].getZ() / 2) + (corners[3].getZ() / 2);
			corners[0].Z = (corners[0].getZ() / 2) + (corners[3].getZ() / 2);
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
			for (int i = 0; i < cells.size(); ++i) {
				CHexa *cell = cells.at(i);
				CVector3 corners[4];
				//Obtener esquinas de la celda
				if (childBounds[0].pointsInside(corners)) {
					childCells[0].push_back(cell);
				}
				if (childBounds[1].pointsInside(corners)) {
					childCells[1].push_back(cell);
				}
				if (childBounds[2].pointsInside(corners)) {
					childCells[2].push_back(cell);
				}
				if (childBounds[3].pointsInside(corners)) {
					childCells[3].push_back(cell);
				}

			}
			h1->subdivide(limit, childBounds[0], childCells[0], inSV, divactual + 1, divmax);
			h2->subdivide(limit, childBounds[1], childCells[1], inSV, divactual + 1, divmax);
			h2->subdivide(limit, childBounds[2], childCells[2], inSV, divactual + 1, divmax);
			h2->subdivide(limit, childBounds[2], childCells[3], inSV, divactual + 1, divmax);
		}
	}

	//Caso: usa SuperVector
	else if (useType) {
		//
		if ((inSV.size() * inSV[0].size()) == 1 || tricount <= limit || divactual >= divmax) {
			h1 = h2 = h3 = h4 = nullptr;
			SV = inSV;
		}

		//
		else {
			CVector3 corners[4];
			AABB_2D childBounds[4];

			parentBounds.getCorners(corners);
			corners[1].X = (corners[1].getX() / 2) + (corners[0].getX() / 2);
			corners[3].X = (corners[3].getX() / 2) + (corners[0].getX() / 2);
			corners[2].Z = (corners[2].getZ() / 2) + (corners[0].getZ() / 2);
			corners[3].Z = (corners[3].getZ() / 2) + (corners[0].getZ() / 2);
			childBounds[0].setCorners(corners);

			parentBounds.getCorners(corners);
			corners[0].X = (corners[0].getX() / 2) + (corners[1].getX() / 2);
			corners[2].X = (corners[2].getX() / 2) + (corners[1].getX() / 2);
			corners[2].Z = (corners[2].getZ() / 2) + (corners[1].getZ() / 2);
			corners[3].Z = (corners[3].getZ() / 2) + (corners[1].getZ() / 2);
			childBounds[1].setCorners(corners);

			parentBounds.getCorners(corners);
			corners[1].X = (corners[1].getX() / 2) + (corners[2].getX() / 2);
			corners[3].X = (corners[3].getX() / 2) + (corners[2].getX() / 2);
			corners[0].Z = (corners[0].getZ() / 2) + (corners[2].getZ() / 2);
			corners[1].Z = (corners[1].getZ() / 2) + (corners[2].getZ() / 2);
			childBounds[2].setCorners(corners);

			parentBounds.getCorners(corners);
			corners[0].X = (corners[0].getX() / 2) + (corners[3].getX() / 2);
			corners[2].X = (corners[2].getX() / 2) + (corners[3].getX() / 2);
			corners[1].Z = (corners[1].getZ() / 2) + (corners[3].getZ() / 2);
			corners[0].Z = (corners[0].getZ() / 2) + (corners[3].getZ() / 2);
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
			for (int i = 0; i < cells.size(); ++i) {
				CHexa *cell = cells.at(i);
				CVector3 corners[4];
				//Obtener esquinas de la celda
				if (childBounds[0].pointsInside(corners)) {
					childCells[0].push_back(cell);
				}
				if (childBounds[1].pointsInside(corners)) {
					childCells[1].push_back(cell);
				}
				if (childBounds[2].pointsInside(corners)) {
					childCells[2].push_back(cell);
				}
				if (childBounds[3].pointsInside(corners)) {
					childCells[3].push_back(cell);
				}

			}
			vector<vector<CHexa>> SV_0;
			h1->subdivide(limit, childBounds[0], childCells[0], SV_0, divactual + 1, divmax);
			h2->subdivide(limit, childBounds[1], childCells[1], SV_0, divactual + 1, divmax);
			h2->subdivide(limit, childBounds[2], childCells[2], SV_0, divactual + 1, divmax);
			h2->subdivide(limit, childBounds[2], childCells[3], SV_0, divactual + 1, divmax);
		}	
		
	}

}

void CQuadTreeNode::render(COpenGLRenderer * inRenderer, unsigned int inShaderID) {
	float color[3] = {0.3f, 0.3f, 0.3f};
	MathHelper::Matrix4 matriz;
	matriz = MathHelper::SimpleModelMatrixRotationTranslation(0.0f, {0.0f, 0.0f, 0.0f});
	inRenderer->renderObject(
		&inShaderID,
		&bounds.mVAO,
		0,
		2,
		color,
		&matriz,
		COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
		false
		);

}

void CQuadTreeNode::setBounds(AABB_2D inBounds) {

	bounds = inBounds;

}

void CQuadTreeNode::getBounds(AABB_2D) {

	//Aiudaaaaaaaaa

}

void CQuadTreeNode::setLimits(AABB_2D limits) {



}


