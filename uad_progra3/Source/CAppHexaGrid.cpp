#include "../stdafx.h"
#include <iostream>
using namespace std;

#include <assert.h>
#include "../Include/Globals.h"
#include "../Include/CAppHexaGrid.h"
#include "../Include/CWideStringHelper.h"
#include "../Include/CTextureLoader.h"
#include "../Include/C3DModel.h"

/* */
CAppHexaGrid::CAppHexaGrid() : CAppHexaGrid(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT) {



}

/* */
CAppHexaGrid::CAppHexaGrid(int window_width, int window_height) : 
	CApp(window_width, window_height), 
	p3DModel(nullptr),
	m_currentDeltaTime{ 0.0 }, 
	m_objectRotation{ 0.0 }, 
	m_objectPosition{ 0.0f, 0.0f, 0.0f }, 
	m_rotationSpeed{ DEFAULT_ROTATION_SPEED }, 
	Grid(nullptr) {
	cout << "Constructor: CAppHexaGrid(int window_width, int window_height)" << endl;

}


CAppHexaGrid::~CAppHexaGrid() {
	cout << "Destructor: ~CAppHexaGrid()" << endl;
	unloadCurrent3DModel();
	if (Grid != nullptr) {
		delete Grid;
	}
}


void CAppHexaGrid::initialize() {
	
	
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

	//TODO:
	//Tomar los datos del json
	//Meterlos a las variables correspondientes
	Grid = new CHexaGrid();
	Grid->createHexaGeometry(getOpenGLRenderer(),m_colorModelShaderId, m_hexaVertexArrayObject);
}


void CAppHexaGrid::update(double deltaTime) {

	// Do not update if delta time is < 0
	if (deltaTime <= 0.0f) {
		return;
	}

	// Save current delta time
	m_currentDeltaTime = deltaTime;


}


void CAppHexaGrid::run() {
	// Check if CGameWindow object AND Graphics API specific Window library have been initialized
	if (canRun()) {
		// Create the Window 
		if (getGameWindow()->create(CAPP_PROGRA3_HEXGRID_WINDOW_TITLE)) {
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


void CAppHexaGrid::render() {
	CGameMenu *menu = getMenu();

	// If menu is active, render menu
	if (menu != NULL && menu->isInitialized() && menu->isActive()) {

		//...

	}
	else {										// Otherwise, render app-specific stuff here...

		float color[3] = { 1.0f, 1.0f, 1.0f };
		unsigned int noTexture = 0;
		double degresRotation = m_objectRotation * PI_OVER_180;
		MathHelper::Matrix4 modelMatrix;

		//Hexagono :D
		if (m_hexaVertexArrayObject > 0 && Grid->m_numFacesHexa > 0) {
			//CVector3 pos2 = m_objectPosition;
			//pos2 += CVector3(3.0f, 0.0f, 0.0f);
			//MathHelper::Matrix4 modelMatrix2;
			for (int i = 0; i < Grid->numRows; i++) {
				for (int j = 0; j < Grid->numCols; j++) {
					modelMatrix = MathHelper::SimpleModelMatrixRotationTranslation((float)degresRotation, Grid->SuperVector[i][j].centerX);
					getOpenGLRenderer()->renderObject(&m_colorModelShaderId, &m_hexaVertexArrayObject, &noTexture, Grid->m_numFacesHexa, color, &modelMatrix, COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES, false);
					
				}
			}
			// Render Hexa in the first position, using the color shader

		}
		// =================================
	}
}

/**/
void CAppHexaGrid::moveCamera(float dir) {
	if (getOpenGLRenderer() != nullptr) {
		getOpenGLRenderer()->simpleCameraZoom(dir);
	}
}

/* */
void CAppHexaGrid::onMouseMove(float deltaX, float deltaY) {
	if (deltaX < 100.f && deltaY < 100.f) {
		float moveX = -deltaX * DEFAULT_CAMERA_MOVE_SPEED;
		float moveZ = -deltaY * DEFAULT_CAMERA_MOVE_SPEED;
		float currentPos[3];
		for (int i = 0; i < Grid->numRows; i++) {
			for (int j = 0; j < Grid->numCols; j++) {
				Grid->SuperVector[i][j].centerX.getValues(currentPos);
				currentPos[0] += moveX;
				currentPos[2] += moveZ;
				Grid->SuperVector[i][j].centerX.setValues(currentPos);
			}
		}
	}
}

/* */
void CAppHexaGrid::onF2(int mods) {

	if (mods & KEY_MOD_SHIFT) {
		moveCamera(-1.f);
	}
	else {
		moveCamera(1.f);
	}

}

/* */
void CAppHexaGrid::onF3(int mods) {
	if (Grid->m_renderPolygonMode == 0) {
		getOpenGLRenderer()->setFillPolygonMode();
		Grid->m_renderPolygonMode = 1;
	}
	else {
		getOpenGLRenderer()->setWireframePolygonMode();
		Grid->m_renderPolygonMode = 0;
	}
}

void CAppHexaGrid::unloadCurrent3DModel()
{
}
