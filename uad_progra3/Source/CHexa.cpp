#include "../stdafx.h"
#include <assert.h>
#include "../Include/Globals.h"
#include "../Include/CHexa.h"
#include "../Include/CWideStringHelper.h"


//Constructor
CHexa::CHexa() {



}


//Constructor c/Parametros
CHexa::CHexa(CVector3 cent) {

	centerX = cent;

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

