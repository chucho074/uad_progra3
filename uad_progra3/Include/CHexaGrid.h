#pragma once
#ifndef CHEXAGRID_H
#define CHEXAGRID_H
#include "Globals.h"
#include "CApp.h"
#include "CHexa.h"
#include "C3DModel.h"
#include "json.hpp"
#include <fstream>
#include <iostream>


class CHexaGrid {
public: 
	// ---------------------------------------------------------------
	//					CONSTRUCTOR Y DESTRUCTOR
	// ---------------------------------------------------------------
	CHexaGrid();
	~CHexaGrid();

	// ---------------------------------------------------------------
	//							VARIABLES
	// ---------------------------------------------------------------
	nlohmann::json j; 
	bool m_initialized;
	int m_numFacesHexa;
	int m_renderPolygonMode;
	vector<vector<CHexa>> SuperVector;
	int numCols;
	int numRows;
	float cellSize;
	string orientation;
	bool pointy = false;

	// ---------------------------------------------------------------
	//							FUNCIONES
	// ---------------------------------------------------------------
	void createHexaGeometry(COpenGLRenderer * const, unsigned int &, unsigned int &);
	CHexa getCell(int, int);
};

#endif CHEXAGRID_H