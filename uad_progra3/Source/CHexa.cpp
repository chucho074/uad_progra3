#include "../stdafx.h"

//#include <iostream>
//using namespace std;

#include <assert.h>
#include "../Include/Globals.h"
#include "../Include/CHexa.h"
#include "../Include/CWideStringHelper.h"
//#include "../Include/CTextureLoader.h"

/**/
CHexa::CHexa() {



}


/* */
CHexa::~CHexa() {

}




/* 
void CHexa::createHexaGeometry() {

	float height = 2.25f;
	float sideHalfX = 0.75f;
	float sideHalfZ = 1.0f;
	bool loaded = false;
	CVector3 v1, v2, v3, v1v2, v1v3, norm;
	CVector3 Centro = { 0,0,0 };


	//Vertex
	float vertexData[6 * 3] = {
		//Holi :)
	};

	int count = 0;

	for (int i = 0; i < 6; i++) {									//Introducir los datos con los angulos

		CVector3 CoordVertex = calcPoint(Centro, i, 1, false);		//Manda a llamar la funcion para crear los puntos con los grados
		vertexData[count++] = CoordVertex.getX();					//Pasamos X
		vertexData[count++] = CoordVertex.getY();					//Pasamos Y
		vertexData[count++] = CoordVertex.getZ();					//Pasamos Z

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
	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_colorModelShaderId,
		&m_hexaVertexArrayObject,
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

		if (m_hexaVertexArrayObject > 0) {
			getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_hexaVertexArrayObject);
			m_hexaVertexArrayObject = 0;
		}
	}

}
*/

/* */
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

