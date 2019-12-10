#pragma once
#ifndef CAppQuadtree_H
#define CAppQuadtree_H
#include "Globals.h"
#include "CHexaGrid.h"
#include "CAppHexaGrid.h"
#include "CQuadTreeNode.h"
#include "CApp.h"
#include "CQuadTree.h"

/*
TODO:
> Funciones de APP
> W,A,S,D
> Handles de los threads

Thread 1:
Cargar objetos y construir el grid

Thread 2:
Construir quadtree

*/

class CAppQuadtree : public CApp {
public:
	CAppQuadtree();
	CAppQuadtree(int, int);
	~CAppQuadtree();

private:
	void initialize();
	void update(double);
	void run();
	void render();
	bool initializeMenu();

	CQuadTree Tree;

	CHexaGrid * Grid;
	//CAppHexaGrid *HexaG;
	DWORD ThreadID[2];
	HANDLE GridThread;
	float m_currentDeltaTime;
	

	unsigned int m_hexaVertexArrayObject;					// An OpenGL Vertex Array Object is a reference to graphics memory that tells OpenGL where to look for the geometry of the object. 
	unsigned int m_colorModelShaderId;						// OpenGL Shader Program for the color-only object
	bool m_initialized;
public:
	bool StartGridThread() {
		// Get shader for color objects
		// -------------------------------------------------------------------------------------------------------------

		m_colorModelShaderId = getOpenGLRenderer()->getShaderProgramID(SHADER_PROGRAM_COLOR_OBJECT);

		if (m_colorModelShaderId == 0) {
			cout << "ERROR: Unable to load color shader" << endl;
			//return;
		}
		Grid = new CHexaGrid();
		Grid->createHexaGeometry(getOpenGLRenderer(), m_colorModelShaderId, m_hexaVertexArrayObject);
		return true;
	}

	//void moveCamera(float);
	void onArrowUp(int mods);
	void onArrowDown(int mods);
	void onArrowLeft(int mods);
	void onArrowRight(int mods);

};


#endif CAppQuadtree_H