#pragma once
#ifndef CHEXA_H
#define CHEXA_H
#include "Globals.h"
#include "CTextureLoader.h"
#include "C3DModel.h"

class CHexa {
public:
	// ---------------------------------------------------------------
	//					Constructors and destructor
	// ---------------------------------------------------------------

	CHexa();
	CHexa(CVector3, CVector3*);								//Constructor
	~CHexa();												//Destructor
	
	// ---------------------------------------------------------------
	//							Variables
	// ---------------------------------------------------------------
	CVector3 centerX;
	CVector3 Corners[6];
	C3DModel * mCellModel;
	float mModelScale;
	float mModelrotation[3];

	// ---------------------------------------------------------------
	//							Functions
	// ---------------------------------------------------------------
	CVector3 calcPoint(CVector3, int, float, bool);			// Calcular los vertices
	CVector3 getCorner(int);
	int getTriangleCount();

	

};
#endif CHEXA_H