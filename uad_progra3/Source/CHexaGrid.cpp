#include "../stdafx.h"
#include <iostream>
using namespace std;

#include <assert.h>
#include "../Include/Globals.h"
#include "../Include/CHexaGrid.h"
#include "../Include/CWideStringHelper.h"
#include "../Include/CTextureLoader.h"



CHexaGrid::CHexaGrid() {
	ifstream file_json("hexgrid_cfg.json", ifstream::binary);
	file_json >> j;
	numCols = j["HexGrid"]["numCols"];
	numRows = j["HexGrid"]["numRows"];
	cellSize = j["HexGrid"]["cellSize"];
	orientation = j["HexGrid"]["orientation"].get<string>();
	if (orientation == "pointy") {
		pointy = true;
	}
}


CHexaGrid::~CHexaGrid() {

	//Cerrar el archivo

}



void CHexaGrid::createHexaGeometry(COpenGLRenderer * const render, unsigned int & shaderID, unsigned int & VAO) {

	CHexa Cell;
	bool loaded = false;
	CVector3 Centro = { 0,0,0 };



	//Vertex
	float vertexData[6 * 3] = {
	

	};

	int count = 0;

	for (int i = 1; i < 7; i++) {										//Introducir los datos con los angulos

		CVector3 CoordVertex = Cell.calcPoint(Centro, i, cellSize, pointy);		//Manda a llamar la funcion para crear los puntos con los grados
		vertexData[count++] = CoordVertex.getX();						//Pasamos X
		vertexData[count++] = CoordVertex.getY();						//Pasamos Y
		vertexData[count++] = CoordVertex.getZ();						//Pasamos Z

	}



	float vertexUVs[6] = {
		0.0f,  0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f
	};

	m_numFacesHexa = 4;

	unsigned short faceIndices[12] = {
		0, 5, 1,
		1, 5, 4,
		1, 4, 2,
		2, 4, 3
	};

	float normalData[12] = {
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0
	};

	unsigned short faceNormalIndices[12] = {
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0
	};


	// Allocate graphics memory for object
	loaded = render->allocateGraphicsMemoryForObject(
		&shaderID,
		&VAO,
		vertexData,
		6,        // Numero de vertices, internamente el codigo multiplica sizeof(float) * numVertices * 3
		normalData,
		6,
		vertexUVs,
		6,
		faceIndices,
		4,        // Numero de indices, internamente el codigo multiplica sizeof(unsigned short) * numIndicesVert * 3
		faceNormalIndices,
		6,
		faceIndices,
		6
	);

	if (!loaded) {
		m_numFacesHexa = 0;

		if (VAO > 0) {
			render->freeGraphicsMemoryForObject(&VAO);
			VAO = 0;
		}
	}

}