#pragma once

#ifndef CHEXA_H
#define CHEXA_H

#include "Globals.h"
#include "CApp.h"


class CHexa : public CApp {
private:

	bool m_initialized;

	// Variables used for controlling the rotation and object position
	// ---------------------------------------------------------------
	
	double m_currentDeltaTime;								// Current delta time (time of the current frame - time of the last frame)
	
	CVector3 m_objectPosition;								// Current object position

	// Variables used for storing OpenGL identifiers
	// ---------------------------------------------------------------
	
	unsigned int m_colorModelShaderId;						// OpenGL Shader Program for the color-only object
	
	unsigned int m_texturedModelShaderId;					// OpenGL Shader Program for the textured object

	unsigned int m_hexaVertexArrayObject;					// An OpenGL Vertex Array Object is a reference to graphics memory that tells OpenGL where to look for the geometry of the object. 
															// It needs to be initialized using the allocateGraphicsMemory() method from the renderer.

	unsigned int m_textureID;								// Identifier for the OpenGL Texture Object 

	// Other variables
	// ---------------------------------------------------------------

	int m_numFacesHexa;
	int m_renderPolygonMode;


	//Functions
	// ---------------------------------------------------------------

	void createHexaGeometry();								//Crear la geometria del hexagono

protected:

	bool initializeMenu() { return false; }

public:

	// Constructors and destructor
	// ---------------------------------------------------------------

	CHexa();												//Constructor
	CHexa(int window_width, int window_height);				//Constructor with parameters
	~CHexa();


	// ---------------------------------------------------------------

	void initialize();										// Method to initialize any objects for this class
	void update(double deltaTime);							// Method to update any objecs based on time elapsed since last frame
	void run();												// Method to run the app
	void render();											// Method to render the app
	
	void onMouseMove(float deltaX, float deltaY);			// Called when mouse moves within the window
	
	void onF2(int mods);									// Override on F2
	void onF3(int mods);									// Override on F3


	// ---------------------------------------------------------------

	CVector3 calcPoint(CVector3, int, float, bool);			// Calcular los vertices
	

};

#endif CHEXA_H