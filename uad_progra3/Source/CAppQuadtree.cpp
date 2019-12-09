#include "..\Include\CAppQuadtree.h"

DWORD WINAPI ThreadCreateGrid(LPVOID p);

CAppQuadtree::CAppQuadtree() {


}

CAppQuadtree::CAppQuadtree(int window_width, int window_height) :
	CApp(window_width, window_height),
	m_currentDeltaTime{ 0.0 },
	Grid(nullptr) {
	cout << "Constructor: CAppHexaGrid(int window_width, int window_height)" << endl;

}
CAppQuadtree::~CAppQuadtree() {



}

void CAppQuadtree::initialize() {

	GridThread = CreateThread(NULL, 0, ThreadCreateGrid, this, 0, &ThreadID[0]);
	WaitForSingleObject(GridThread,INFINITE);

	m_initialized = true;

	int cols = Grid->numCols;
	int rows = Grid->numRows;
	float minX, maxX, minZ, maxZ;
	minX = 0.0f; 
	maxX = 0.0f;
	minZ = 0.0f;
	maxZ = 0.0f;

	for (int i = 0; i < cols; ++i) {
		for (int j = 0; j < rows; ++j) {
			CHexa cell = Grid->getCell(i,j);
			for (int k = 0; k < 6; ++k) {
				CVector3 corner = cell.getCorner(k);
				if (corner.X < minX) {
					minX = corner.X;
				}
				if (corner.X > maxX) {
					maxX = corner.X;
				}
				if (corner.Z < minZ) {
					minZ = corner.Z;
				}
				if (corner.Z > maxZ) {
					maxZ = corner.Z;
				}
			}
		}
	}

}

void CAppQuadtree::update(double delta_time) {

	// Do not update if delta time is < 0
	if (delta_time <= 0.0f) {
		return;
	}

	// Save current delta time
	m_currentDeltaTime = delta_time;

}

void CAppQuadtree::run() {
	// Check if CGameWindow object AND Graphics API specific Window library have been initialized
	if (canRun()) {
		// Create the Window 
		if (getGameWindow()->create(CAPP_PROGRA3_CAppQuadtree_WINDOW_TITLE)) {
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

void CAppQuadtree::render() {
	//El nodo es visible para la camara?


	//(Si) Repite para los 4 hijos (agregar las celdas a la lista)


	//(No) Termina


	//renderLine();

	CGameMenu *menu = getMenu();

	// If menu is active, render menu
	if (menu != NULL && menu->isInitialized() && menu->isActive()) {

		//...

	}
	else {										// Otherwise, render app-specific stuff here...

		float color[3] = { 1.0f, 1.0f, 1.0f };
		unsigned int noTexture = 0;
		double degresRotation = 0.0;
		MathHelper::Matrix4 modelMatrix;

		//Hexagono :D
		if (m_hexaVertexArrayObject == 0 && Grid->m_numFacesHexa > 0) {
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

bool CAppQuadtree::initializeMenu()
{
	return false;
}


//void CAppQuadtree::moveCamera(float dir) {
	//if (getOpenGLRenderer() != nullptr) {
	//	getOpenGLRenderer()->set;
	//}
	
//}

void CAppQuadtree::onArrowUp(int mods) { 

	/*if (mods & KEY_MOD_SHIFT) {
		moveCamera(-1.f);
	}
	else {
		moveCamera(1.f);
	}*/
	std::cout << "arriba" << std::endl;

}

void CAppQuadtree::onArrowDown(int mods) {

	std::cout << "abajo" << std::endl;

}

void CAppQuadtree::onArrowLeft(int mods) {

	std::cout << "izq" << std::endl;
}

void CAppQuadtree::onArrowRight(int mods) {

	std::cout << "der" << std::endl;

}


/*CREAR EL THREAD DEL GRID*/
DWORD WINAPI ThreadCreateGrid(LPVOID p) {

	CAppQuadtree * appQuadTree = (CAppQuadtree *)p;
	appQuadTree->StartGridThread();
	return 0;
}
