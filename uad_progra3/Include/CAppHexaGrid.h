#pragma once
#ifndef CAPPHEXAGRID_H
#define CAPPHEXAGRID_H
#include "Globals.h"
#include "CApp.h"
#include "CHexaGrid.h"
#include "../Dependencies/JSON/nlohmann/json.hpp"
#include <fstream>
#include "C3DModel_Obj.h"

using json = nlohmann::json;

struct ModelParams {
	std::string ModelName;
	std::string ModelPath;
	C3DModel * pModel;

	ModelParams(std::string name, std::string path, C3DModel * model)
	{
		ModelName = name;
		ModelPath = path;
		pModel = model;
	}
	~ModelParams()
	{
		if (pModel != nullptr)
		{
			delete pModel;
		}
	}
};

class CAppHexaGrid : public CApp{
public:
	// ---------------------------------------------------------------
	//					CONSTRUCTOR Y DESTRUCTOR
	// ---------------------------------------------------------------
	CAppHexaGrid();
	CAppHexaGrid(int window_width, int window_height);		//Constructor with parameters
	~CAppHexaGrid();

	// ---------------------------------------------------------------
	//							FUNCIONES
	// ---------------------------------------------------------------
	void initialize();
	void update(double deltaTime);
	void run();
	void render();

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	unsigned int m_hexaVertexArrayObject;					// An OpenGL Vertex Array Object is a reference to graphics memory that tells OpenGL where to look for the geometry of the object. 
	unsigned int m_colorModelShaderId;						// OpenGL Shader Program for the color-only object
private:
	// ---------------------------------------------------------------
	//							VARIABLES
	// ---------------------------------------------------------------
	nlohmann::json j;
	CHexaGrid *Grid;
	C3DModel *p3DModel;
	bool m_initialized;
	unsigned int m_textureID;								// Identifier for the OpenGL Texture Object 
	unsigned int m_texturedModelShaderId;					// OpenGL Shader Program for the textured object
	double m_currentDeltaTime;								// Current delta time (time of the current frame - time of the last frame)
	CVector3 m_objectPosition;								// Current object position
	double m_objectRotation;
	double m_rotationSpeed;
	std::vector<ModelParams*> mModel;

	json Data;

	unsigned int DataCols;
	unsigned int DataRows;
	float DataSize;
	bool DataCelltype;
	std::string sDataCelltype;
															
	// ---------------------------------------------------------------
	//							FUNCIONES
	// ---------------------------------------------------------------
	void moveCamera(float);
	void onMouseMove(float deltaX, float deltaY);			// Called when mouse moves within the window
	void onF2(int mods);									// Override on F2
	void onF3(int mods);									// Override on F3
	void unloadCurrent3DModel();
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:

	bool initializeMenu() { return false; }
};

#endif CAPPHEXAGRID_H