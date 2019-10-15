#include "../stdafx.h"

#include <iostream>
using namespace std;

#include <assert.h>
#include "../Include/Globals.h"
#include "../Include/CHexa.h"
#include "../Include/CWideStringHelper.h"
#include "../Include/CTextureLoader.h"


/* */
CHexa::CHexa() : CHexa(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT) {



}

/* */
CHexa::CHexa(int window_width, int window_height) : CApp(window_width, window_height), m_currentDeltaTime{ 0.0 }, /*m_objectRotation{ 0.0 },*/ m_objectPosition{ -1.5f, 0.0f, 0.0f }, /*m_rotationSpeed{ DEFAULT_ROTATION_SPEED },*/ m_hexaVertexArrayObject{ 0 }, m_numFacesHexa{ 0 }, m_renderPolygonMode{ 0 } {
	cout << "Constructor: CHexa(int window_width, int window_height)" << endl;

}

/* */
CHexa::~CHexa() {
	cout << "Destructor: ~CHexa()" << endl;

	// Free memory allocated in this class instance here
	// =================================================
	//
	if (m_textureID > 0) {
		getOpenGLRenderer()->deleteTexture(&m_textureID);
	}

	if (m_hexaVertexArrayObject > 0) {
		getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_hexaVertexArrayObject);
	}
	// =================================================
}

/* */
void CHexa::initialize() {
	// Initialize app-specific stuff here
	// ==================================
	//
	// Get shader for color objects
	// -------------------------------------------------------------------------------------------------------------

	m_colorModelShaderId = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_COLOR_OBJECT);

	if (m_colorModelShaderId == 0) {
		cout << "ERROR: Unable to load color shader" << endl;
		return;
	}

	// Get shader for textured objects
	// -------------------------------------------------------------------------------------------------------------

	m_texturedModelShaderId = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_TEXTURED_OBJECT);

	if (m_texturedModelShaderId == 0) {
		cout << "ERROR: Unable to load texture shader" << endl;
		return;
	}

	// Texture
	// Load texture file, create OpenGL Texture Object
	// -------------------------------------------------------------------------------------------------------------
	std::wstring wresourceFilenameTexture;
	std::string resourceFilenameTexture;

	// Check texture file exists for the textured cube
	if (!CWideStringHelper::GetResourceFullPath(MC_LEAVES_TEXTURE, wresourceFilenameTexture, resourceFilenameTexture)) {
		cout << "ERROR: Unable to find one or more resources: " << endl;
		cout << "  " << MC_LEAVES_TEXTURE << endl;
		return;
	}

	// Initialize the texture
	m_textureID = 0;
	if (!CTextureLoader::loadTexture(resourceFilenameTexture.c_str(), &m_textureID, getOpenGLRenderer())) {
		cout << "ERROR: Unable load texture:" << endl;
		cout << "  " << MC_LEAVES_TEXTURE << endl;
		return;
	}

	m_initialized = true;
	//createPyramidGeometry();
	createHexaGeometry();
}

/* */
void CHexa::run() {
	// Check if CGameWindow object AND Graphics API specific Window library have been initialized
	if (canRun()) {
		// Create the Window 
		if (getGameWindow()->create(CAPP_PROGRA3_HEX_WINDOW_TITLE)) {
			// ALWAYS call initialize AFTER creating the window
			initialize();

			// Set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.25f, 0.0f, 0.75f);

			if (m_initialized) {
				getOpenGLRenderer()->setWireframePolygonMode();

				// Enter main loop
				cout << "Entering Main loop" << endl;
				getGameWindow()->mainLoop(this);
			}
		}
	}
}

/* */
void CHexa::update(double deltaTime) {
	// Do not update if delta time is < 0
	if (deltaTime <= 0.0f) {
		return;
	}

	// Save current delta time
	m_currentDeltaTime = deltaTime;

}

/* */
void CHexa::render()	 {
	CGameMenu *menu = getMenu();

	// If menu is active, render menu
	if (menu != NULL && menu->isInitialized() && menu->isActive()) {
		
		//...
	
	}
	else {																		// Otherwise, render app-specific stuff here...
	
		float color[3] = { 1.0f, 1.0f, 1.0f };
		unsigned int noTexture = 0;

		MathHelper::Matrix4 modelMatrix;

		//Hexagono :D
		if (m_hexaVertexArrayObject > 0 && m_numFacesHexa > 0) {
			CVector3 pos2 = m_objectPosition;
			pos2 += CVector3(3.0f, 0.0f, 0.0f);
			MathHelper::Matrix4 modelMatrix2;

			// Render pyramid in the first position, using the color shader
			getOpenGLRenderer()->renderObject(&m_colorModelShaderId, &m_hexaVertexArrayObject, &noTexture, m_numFacesHexa, color, &modelMatrix, COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES, false);
			
		}
		// =================================
	}
}


/* */
void CHexa::onMouseMove(float deltaX, float deltaY) {
	// Update app-specific stuff when mouse moves here 
	// ===============================================
	//
	// ===============================================
}

/* */
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

/* */
void CHexa::onF2(int mods) {



}

/* */
void CHexa::onF3(int mods) {
	if (m_renderPolygonMode == 0) {
		getOpenGLRenderer()->setFillPolygonMode();
		m_renderPolygonMode = 1;
	}
	else {
		getOpenGLRenderer()->setWireframePolygonMode();
		m_renderPolygonMode = 0;
	}
}
