#pragma once
#ifndef CHEXA_H
#define CHEXA_H
#include "Globals.h"
#include "CTextureLoader.h"

class CHexa {
public:
	// ---------------------------------------------------------------
	//					Constructors and destructor
	// ---------------------------------------------------------------

	CHexa();
	CHexa(CVector3);												//Constructor
	~CHexa();												//Destructor

	CVector3 centerX;
	// ---------------------------------------------------------------
	//							Functions
	// ---------------------------------------------------------------

	CVector3 calcPoint(CVector3 center, int numPoint, float cellSize, bool pointy);

	//CVector3 calcPoint(CVector3, int, float, bool);			// Calcular los vertices
	

	

};
#endif CHEXA_H