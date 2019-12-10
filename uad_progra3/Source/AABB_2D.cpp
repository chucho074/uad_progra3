#include "..\Include\AABB_2D.h"

AABB_2D::AABB_2D() {
	


}


AABB_2D::AABB_2D(CVector3 * esq) {

	corners[0] = *esq;	esq++;
	corners[1] = *esq;	esq++;
	corners[2] = *esq;	esq++;
	corners[3] = *esq;	esq++;

}


AABB_2D::~AABB_2D() {


}


void AABB_2D::getCorners(CVector3 * c) {

	*c = corners[0];	c++;
	*c = corners[1];	c++;
	*c = corners[2];	c++;
	*c = corners[3];	c++;

}


void AABB_2D::setCorners(CVector3 * inCorners) {
	
	for (int i = 0; i < 4; i++) {
		corners[i] = inCorners[i];
	}
}


bool AABB_2D::pointsInside(CVector3* inHexData) {

	CVector3 p1, p2, p3, p4, p5, p6;
	p1 = *inHexData;
	inHexData++;
	p2 = *inHexData;
	inHexData++;
	p3 = *inHexData;
	inHexData++;
	p4 = *inHexData;
	inHexData++;
	p5 = *inHexData;
	inHexData++;
	p6 = *inHexData;

	if ( ((p1.getX()>corners[0].getX()) && (p1.getX()<corners[3].getX()) &&
		 ((p1.getZ()>corners[0].getZ()) && (p1.getZ()<corners[3].getZ()))) ) {
		return true;
	}

	if (((p2.getX() > corners[0].getX()) && (p2.getX() < corners[3].getX()) &&
		((p2.getZ() > corners[0].getZ()) && (p2.getZ() < corners[3].getZ())))) {
		return true;
	}

	if (((p3.getX() > corners[0].getX()) && (p3.getX() < corners[3].getX()) &&
		((p3.getZ() > corners[0].getZ()) && (p3.getZ() < corners[3].getZ())))) {
		return true;
	}

	if (((p4.getX() > corners[0].getX()) && (p4.getX() < corners[3].getX()) &&
		((p4.getZ() > corners[0].getZ()) && (p4.getZ() < corners[3].getZ())))) {
		return true;
	}

	if (((p5.getX() > corners[0].getX()) && (p5.getX() < corners[3].getX()) &&
		((p5.getZ() > corners[0].getZ()) && (p5.getZ() < corners[3].getZ())))) {
		return true;
	}

	if (((p6.getX() > corners[0].getX()) && (p6.getX() < corners[3].getX()) &&
		((p6.getZ() > corners[0].getZ()) && (p6.getZ() < corners[3].getZ())))) {
		return true;
	}
	
	return false;
}


bool AABB_2D::ElImportante(COpenGLRenderer * inRenderer, unsigned int & inShaderID) {

	//Vertices
	mVertices[0] = corners[0].getX();	mVertices[1] = corners[0].getY();	mVertices[2] = corners[0].getZ();
	mVertices[3] = corners[1].getX();	mVertices[4] = corners[1].getY();	mVertices[5] = corners[1].getZ();
	mVertices[6] = corners[2].getX();	mVertices[7] = corners[2].getY();	mVertices[8] = corners[2].getZ();
	mVertices[9] = corners[3].getX();	mVertices[10] = corners[3].getY();	mVertices[11] = corners[3].getZ();

	//UV
	mVertexUV[0] = 0.0f;	mVertexUV[1] = 0.0f;
	mVertexUV[2] = 0.0f;	mVertexUV[3] = 0.0f;

	//Face Index
	mFaceIndex[0] = 0;	mFaceIndex[1] = 1;	mFaceIndex[2] = 2;
	mFaceIndex[3] = 2;	mFaceIndex[4] = 1;	mFaceIndex[5] = 3;

	//Normal
	mNormal[0] = 0.0f;	mNormal[1] = 0.0f;	mNormal[2] = 0.0f;
	mNormal[3] = 0.0f;	mNormal[4] = 0.0f;	mNormal[5] = 0.0f;

	//Normal Index
	mFaceNormalIndex[0] = 0;	mFaceNormalIndex[1] = 0;	mFaceNormalIndex[2] = 0;
	mFaceNormalIndex[3] = 0;	mFaceNormalIndex[4] = 0;	mFaceNormalIndex[5] = 0;


	bool loaded = inRenderer->allocateGraphicsMemoryForObject(
	&inShaderID,
	&mVAO,
	mVertices,
	4,
	mNormal,
	2,
	mVertexUV,
	4,
	mFaceIndex,
	2,
	mFaceNormalIndex,
	2,
	mFaceIndex,
	2);

	if (!loaded) {
		inRenderer->freeGraphicsMemoryForObject(&mVAO);
	}
	return loaded;

}
