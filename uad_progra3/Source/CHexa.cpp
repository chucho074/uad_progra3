#include "../stdafx.h"
#include <assert.h>
#include "../Include/Globals.h"
#include "../Include/CHexa.h"
#include "../Include/CWideStringHelper.h"


//Constructor
CHexa::CHexa() {



}


//Constructor c/Parametros
CHexa::CHexa(CVector3 cent, CVector3* inVect) {
	mCellModel = nullptr;
	mModelScale = 0.0f;
	centerX = cent;
	for (int i = 0; i <= 6; i++) {
		Corners[i] = inVect[i];
	}
}

//Destructor
CHexa::~CHexa() {



}


//Calcular los vertices de los hexagonos
CVector3 CHexa::calcPoint(CVector3 center, int numPoint, float cellSize, bool pointy) {

	CVector3 point;
	float angle;
	if (pointy == true) {
		angle = 60 * numPoint - 30;
	}
	else if (pointy == false) {
		angle = 60 * numPoint;
	}
	float angleR = angle * PI_OVER_180;
	point.Y = 0.0f;
	point.X = center.X + cellSize * cos(angleR);
	point.Z = center.Y + cellSize * sin(angleR);

	return point;
}


CVector3 CHexa::getCorner(int k) {

	return Corners[k];

}

int CHexa::getTriangleCount() {

	return 0;
}
