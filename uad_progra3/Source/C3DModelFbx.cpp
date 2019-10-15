#include "../stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "../Include/CVector3.h"
#include "../Include/C3DModel.h"
#include "../Include/C3DModelFbx.h"

//
C3DModelFbx::C3DModelFbx() :
	C3DModel(),
	m_currentVertex(0),
	m_currentNormal(0),
	m_currentUV(0),
	m_currentFace(0)
{
	cout << "Constructor: C3DModelFbx()" << endl;
}

//
C3DModelFbx::~C3DModelFbx()
{
	cout << "Destructor: C3DModelFbx()" << endl;
	reset();
}

//
void C3DModelFbx::reset() {

	C3DModel::reset();
	m_currentVertex = 0;
	m_currentNormal = 0;
	m_currentUV = 0;
	m_currentFace = 0;

}

//
bool C3DModelFbx::loadFromFile(const char * const filename) {

	bool readFileOk = false;

	// Free any previous resources
	reset();

	// First pass is to count the number of vertices, normals, UVs, faces
	readFileOk = readFbxFile(filename, true);

	m_numVertices = m_currentVertex;
	m_numNormals = m_currentNormal;
	m_numUVCoords = m_currentUV;
	m_numFaces = m_currentFace;


	// Display count
	cout << "Finished reading 3D model" << endl;
	cout << "Vertices: " << m_numVertices << endl;
	cout << "Normals: " << m_numNormals << endl;
	cout << "UVCoords: " << m_numUVCoords << endl;
	cout << "Faces: " << m_numFaces << endl;

	if (readFileOk) {

		// Check for MAX number of faces
		if (m_numVertices >= 65535 || m_numNormals >= 65535 || m_numUVCoords >= 65535) {

			cout << "Error: object cannot have more than 65535 vertices" << endl;
			cout << "Object attempted to load has: " << m_numVertices << " vertices" << endl;
			return false;
		
		}

		// If model was read without normals or UVCoords, we'll set a default value for them
		// i.e.:
		//   0,0 for UV coords
		//   face normal for normal
		if (m_numNormals == 0) {

			m_modelHasNormals = false;
			m_numNormals = m_numVertices;
		}
		else {
			m_modelHasNormals = true;
		}

		if (m_numUVCoords == 0) {
			m_numUVCoords = m_numVertices;
			m_modelHasUVs = false;
		}
		else {
			m_modelHasUVs = true;
		}

		// Allocate memory for the arrays

		//// C3DModel variables
		//m_verticesRaw = new float[m_numVertices * 3];
		//m_normalsRaw = new float[m_numNormals * 3];
		//m_uvCoordsRaw = new float[m_numUVCoords * 2];
		//m_vertexIndices = new unsigned short[m_numFaces * 3];
		//m_normalIndices = new unsigned short[m_numFaces * 3];
		//m_UVindices = new unsigned short[m_numFaces * 3];
		//
		//// Zero-out indices arrays
		//memset(m_vertexIndices, 0, sizeof(unsigned short) * m_numFaces * 3);
		//memset(m_normalIndices, 0, sizeof(unsigned short) * m_numFaces * 3);
		//memset(m_UVindices, 0, sizeof(unsigned short) * m_numFaces * 3);
		//memset(m_verticesRaw, 0, sizeof(float) * m_numVertices * 3);
		//memset(m_normalsRaw, 0, sizeof(float) * m_numNormals * 3);
		//memset(m_uvCoordsRaw, 0, sizeof(float) * m_numUVCoords * 2);

		// Second pass is to read the data
		readFileOk = readFbxFile(filename, false);

		if (readFileOk) {
			m_modelGeometryLoaded = true;
			if (!m_modelHasNormals) {
				computeFaceNormals();
			}
		}

	}

	else {
		cout << "Error ocurred while reading 3D model." << endl;
	}

	return readFileOk;

}

//
bool C3DModelFbx::readFbxFile(const char * filename, bool countOnly) {
		
	ifstream inFile;			//El archivo que se abrira
	string lineBuffer;			//Donde se guardara lo leido en la linea
	bool readFileOk = true;		//Flag de lectura
	int lineNumber = 0;			//La linea desde la que se empezara a leer

	inFile.open(filename);		//Abres el archivo con el nombre recibido

	while (!inFile.eof()) {		//Mientras que el archivo no esté vacio

		getline(inFile, lineBuffer);	//Obtienes la linea 
		lineNumber++;					//Aumentas la linea

		if (!(this->parseFbxLine(lineBuffer, countOnly, lineNumber, filename))) {		//Mandas a llamar de si mismo el parse con la linea y los datos guardados

			readFileOk = false;		//Cambiamos la flag
			break;			
		
		}
		// cout << lineBuffer << endl;
	
	}

	inFile.close();			//Se cierra el archivo

	return readFileOk;		//Se regresa la flag de lectura

}

//
bool C3DModelFbx::parseFbxLine(std::string line, bool countOnly, int lineNumber, const char * filename) {		//Se reciben los parametros con los que trabajar

	ifstream inFile;
	inFile.open(filename);													//Abres el archivo con el nombre recibido
	bool parsed = false;													//Flag
	bool unrecognizedLine = false;											//Flag

	bool readingVertex = false;												//Flag
	bool readingPolyVertex = false;											//Flag
	bool readingNormal = false;												//Flag
	bool readingUV = false;													//Flag
	bool readingUVIndex = false;											//Flag
	//bool readingTexture = false;											//Flag

	char *token = NULL;
	//char *token2 = nullptr;
	char *nextToken = NULL;
	char *nextToken2 = nullptr;

	const char *delimiterToken = "\t";										//El delimitador de donde parará de buscar con el token
	const char *delimiterFace = "*";										//El segundo delimitador para los tokens

	int currentToken = 0;													//Token actual
	int numTokens = 0;														//Num total de tokens

	std::string originalLine = line;										//Es donde se guardará  la linea leida

	token = strtok_s((char *)line.c_str(), " ", &nextToken);				//Se busca el token en la linea y se guarda el siguiente token

	// Line without space or tab separators (most likely a null string)
	if (token == NULL) {
		return !parsed;
	}

	// If there are any tokens left
	if (token != NULL) {

		// Vertex
		if (0 == strcmp(token, "Vertices:")) {								//Si es igual a vertices
			line = nextToken;												//Se guarda en la linea lo obtenido en el siguiente token
			readingVertex = true;											//Cambiamos la bandera
			token = strtok_s((char *)line.c_str(), "*", &nextToken);		//Creamos el token para leer el dato despues de el "*"
			istringstream actual(token);									//Eliminamos todo lo que no sea numero ("{")
			actual >> m_currentVertex;										//Guardamos el valor en el total
			m_numVertices = m_currentVertex / 3;							//Creamos los triangulos
			m_verticesRaw = new float[m_currentVertex];						//Guardamos el espacio para las coords
			unsigned int temp = 0;


			while (temp != lineNumber + 1) {								//Leemos hasta llegar a la linea actual +1
				getline(inFile, line);										//Leemos la linea siguiente
				temp += 1;													//Aumentamos lo leido
			}
			lineNumber += 1;
			token = strtok_s((char *)line.c_str(), " ", &nextToken);		//Creamos otro Token para separar
			if (0 == strcmp(token, "a:")) {									//Si encuentra "a:" (punto de inicio de las coords)

				int iden = 0;
				while (token != NULL) {										//Mientras que haya algo en Token

					double coord = 0;										//Donde se guardaran las coords
					token = strtok_s(nextToken, ",", &nextToken2);			//Se crea otro token para poder separar todas las coords
					if (iden < m_currentVertex) {								//Se le da un punto donde terminar al programa
						
						istringstream actual(token);						//Se quita todo lo no numerico y se convierte en valor numerico
						actual >> coord;									//Se guarda en la coord
						m_verticesRaw[iden++] = coord;						//Se guarda la coord en la lista de coordenadas

					}

					else {

						token = NULL;										//Corta el programa al no tener nada mas en el token

					}

					if (*nextToken2 == '\0' || *nextToken2 == ' ' || *nextToken2 == '\n' || *nextToken2 == NULL) {		//En caso de encontrar diferentes casos del archivo

						getline(inFile, line);								//Leemos la linea siguiente

						if (line != "} ") {									//Cuando no sea el final de la lista

							lineNumber += 1;								//Aumentamos la linea actual
							nextToken2 = (char *)line.c_str();				//Guardamos lo que se encuentra en la linea

						}

						else {												//Cuando sea el final

							break;											//Salimos

						}

					}

					nextToken = nextToken2;									//Igualamos

				}
				iden = 0;														//Evitamos problemas :v

			}


		}


		else if (0 == strcmp(token, "PolygonVertexIndex:")) {				//Si es igual a vertices de poligonos 
			line = nextToken;												//Se guarda en la linea lo obtenido en el siguiente token
			readingPolyVertex = true;
			token = strtok_s((char *)line.c_str(), "*", &nextToken);
			line = token;
			token = strtok_s((char *)line.c_str(), " ", &nextToken);
			istringstream actual(token);
			actual >> m_currentFace;
			m_numFaces = m_currentFace / 3;									//Creamos los triangulos
			m_vertexIndices = new unsigned short[m_currentFace];				//Guardamos el espacio para las coords
			unsigned int temp = 0;


			while (temp != lineNumber + 1) {								//Leemos hasta llegar a la linea actual +1
				getline(inFile, line);										//Leemos la linea siguiente
				temp += 1;													//Aumentamos lo leido
			}
			lineNumber += 1;
			token = strtok_s((char *)line.c_str(), " ", &nextToken);		//Creamos otro Token para separar
			if (0 == strcmp(token, "a:")) {									//Si encuentra "a:" (punto de inicio de las coords)

				int iden = 0;
				while (token != NULL) {										//Mientras que haya algo en Token

					double coord = 0;										//Donde se guardaran las coords
					token = strtok_s(nextToken, ",", &nextToken2);			//Se crea otro token para poder separar todas las coords
					if (iden < m_currentFace) {									//Se le da un punto donde terminar al programa
						istringstream actual(token);						//Se quita todo lo no numerico y se convierte en valor numerico
						actual >> coord;									//Se guarda en la coord
						if (coord < 0) {
							coord = (coord * -1) - 1;
						}
						m_vertexIndices[iden++] = coord;						//Se guarda la coord en la lista de coordenadas

					}


					if (*nextToken2 == '\0' || *nextToken2 == ' ' || *nextToken2 == '\n' || *nextToken2 == NULL) {		//En caso de encontrar diferentes casos del archivo

						getline(inFile, line);								//Leemos la linea siguiente

						if (line != "} ") {									//Cuando no sea el final de la lista

							lineNumber += 1;								//Aumentamos la linea actual
							nextToken2 = (char *)line.c_str();				//Guardamos lo que se encuentra en la linea

						}

						else {												//Cuando sea el final

							break;											//Salimos

						}

					}

					nextToken = nextToken2;									//Igualamos

				}
				iden = 0;														//Evitamos problemas :v

			}


		}



		else if (0 == strcmp(token, "Normals:")) {							//Si es igual a normales
			line = nextToken;												//Se guarda en la linea lo obtenido en el siguiente token
			readingNormal = true;
			token = strtok_s((char *)line.c_str(), "*", &nextToken);
			line = token;
			token = strtok_s((char *)line.c_str(), " ", &nextToken);
			istringstream actual(token);
			actual >> m_currentNormal;
			m_numNormals = (m_currentNormal / 3) / 3;						//Creamos los triangulos
			m_normalsRaw = new float[m_currentNormal];							//Guardamos el espacio para las coords
			vector<float> JUSTCHECK;
			unsigned int temp = 0;


			while (temp != lineNumber + 1) {								//Leemos hasta llegar a la linea actual +1
				getline(inFile, line);										//Leemos la linea siguiente
				temp += 1;													//Aumentamos lo leido
			}
			lineNumber += 1;
			token = strtok_s((char *)line.c_str(), " ", &nextToken);		//Creamos otro Token para separar
			if (0 == strcmp(token, "a:")) {									//Si encuentra "a:" (punto de inicio de las coords)

				int iden = 0;
				while (token != NULL) {										//Mientras que haya algo en Token

					float coord = 0;										//Donde se guardaran las coords
					token = strtok_s(nextToken, ",", &nextToken2);			//Se crea otro token para poder separar todas las coords
					if (iden < m_currentNormal) {								//Se le da un punto donde terminar al programa

						istringstream actual(token);						//Se quita todo lo no numerico y se convierte en valor numerico
						actual >> coord;									//Se guarda en la coord
						m_normalsRaw[iden++] = coord; //Se guarda la coord en la lista de coordenadas
						JUSTCHECK.push_back(coord);
						cout << m_normalsRaw[iden - 1] << " ";
					}

					else {

						token = NULL;										//Corta el programa al no tener nada mas en el token

					}

					if (*nextToken2 == '\0' || *nextToken2 == ' ' || *nextToken2 == '\n' || *nextToken2 == NULL) {		//En caso de encontrar diferentes casos del archivo

						getline(inFile, line);								//Leemos la linea siguiente

						if (line != "} ") {									//Cuando no sea el final de la lista

							lineNumber += 1;								//Aumentamos la linea actual
							nextToken2 = (char *)line.c_str();				//Guardamos lo que se encuentra en la linea

						}

						else {												//Cuando sea el final

							break;											//Salimos

						}

					}

					nextToken = nextToken2;									//Igualamos

				}
				iden = 0;														//Evitamos problemas :v

			}


		}





		else if (0 == strcmp(token, "UV:")) {								//Si es igual a UV
			line = nextToken;												//Se guarda en la linea lo obtenido en el siguiente token
			readingUV = true;
			token = strtok_s((char *)line.c_str(), "*", &nextToken);
			line = token;
			token = strtok_s((char *)line.c_str(), " ", &nextToken);
			istringstream actual(token);
			actual >> m_currentUV;

			m_numUVCoords = m_currentUV / 2;								//Creamos los triangulos
			m_uvCoordsRaw = new float[m_currentUV];						//Guardamos el espacio para las coords
			unsigned int temp = 0;


			while (temp != lineNumber + 1) {								//Leemos hasta llegar a la linea actual +1
				getline(inFile, line);										//Leemos la linea siguiente
				temp += 1;													//Aumentamos lo leido
			}
			lineNumber += 1;
			token = strtok_s((char *)line.c_str(), " ", &nextToken);		//Creamos otro Token para separar
			if (0 == strcmp(token, "a:")) {									//Si encuentra "a:" (punto de inicio de las coords)

				int iden = 0;
				while (token != NULL) {										//Mientras que haya algo en Token

					double coord = 0;										//Donde se guardaran las coords
					token = strtok_s(nextToken, ",", &nextToken2);			//Se crea otro token para poder separar todas las coords
					if (iden < m_currentUV) {								//Se le da un punto donde terminar al programa

						istringstream actual(token);						//Se quita todo lo no numerico y se convierte en valor numerico
						actual >> coord;									//Se guarda en la coord
						m_uvCoordsRaw[iden++] = coord;						//Se guarda la coord en la lista de coordenadas

					}

					else {

						token = NULL;										//Corta el programa al no tener nada mas en el token

					}

					if (*nextToken2 == '\0' || *nextToken2 == ' ' || *nextToken2 == '\n' || *nextToken2 == NULL) {		//En caso de encontrar diferentes casos del archivo

						getline(inFile, line);								//Leemos la linea siguiente

						if (line != "} ") {									//Cuando no sea el final de la lista

							lineNumber += 1;								//Aumentamos la linea actual
							nextToken2 = (char *)line.c_str();				//Guardamos lo que se encuentra en la linea

						}

						else {												//Cuando sea el final

							break;											//Salimos

						}

					}

					nextToken = nextToken2;									//Igualamos

				}
				iden = 0;														//Evitamos problemas :v

			}




		}


		else if (0 == strcmp(token, "UVIndex:")) {							//Si es igual a UVIndex
			line = nextToken;												//Se guarda en la linea lo obtenido en el siguiente token
			readingUVIndex = true;
			token = strtok_s((char *)line.c_str(), "*", &nextToken);
			line = token;
			token = strtok_s((char *)line.c_str(), " ", &nextToken);
			istringstream actual(token);
			actual >> m_currentUVIndex;
			m_numUVIndex = m_currentUVIndex / 3;							//Creamos los triangulos
			m_UVindices = new unsigned short[m_currentUVIndex];					//Guardamos el espacio para las coords
			m_normalIndices = new unsigned short[m_currentUVIndex];
			unsigned int temp = 0;


			while (temp != lineNumber + 1) {								//Leemos hasta llegar a la linea actual +1
				getline(inFile, line);										//Leemos la linea siguiente
				temp += 1;													//Aumentamos lo leido
			}
			lineNumber += 1;
			token = strtok_s((char *)line.c_str(), " ", &nextToken);		//Creamos otro Token para separar
			if (0 == strcmp(token, "a:")) {									//Si encuentra "a:" (punto de inicio de las coords)

				int iden = 0;
				while (token != NULL) {										//Mientras que haya algo en Token

					double coord = 0;										//Donde se guardaran las coords
					token = strtok_s(nextToken, ",", &nextToken2);			//Se crea otro token para poder separar todas las coords
					if (iden < m_currentUVIndex) {								//Se le da un punto donde terminar al programa

						istringstream actual(token);						//Se quita todo lo no numerico y se convierte en valor numerico
						actual >> coord;									//Se guarda en la coord
						m_UVindices[iden] = coord;							//Se guarda la coord en la lista de coordenadas
						m_normalIndices[iden++] = coord;
					}					

					if (*nextToken2 == '\0' || *nextToken2 == ' ' || *nextToken2 == '\n' || nextToken2 == NULL) {		//En caso de encontrar diferentes casos del archivo

						getline(inFile, line);								//Leemos la linea siguiente

						if (line != "} ") {									//Cuando no sea el final de la lista

							lineNumber += 1;								//Aumentamos la linea actual
							nextToken2 = (char *)line.c_str();				//Guardamos lo que se encuentra en la linea

						}

						else {												//Cuando sea el final

							break;											//Salimos

						}

					}

					nextToken = nextToken2;									//Igualamos

				}
				iden = 0;														//Evitamos problemas :v

			}

			inFile.close();													//Se cierra el archivo
			return true;
		}

	}
}


//
bool C3DModelFbx::readMtllib(std::string mtlLibFilename) {

	bool readTextureName = false;

	ifstream infile;
	string lineBuffer;
	char *nextToken = nullptr;
	char *token = nullptr;
	const char *delimiterToken = " \t";
	bool readingMaterialName = false;
	bool readingMaterialFilename = false;
	bool readingMaterialColor = false;
	int numToken = 0;
	std::string currentMaterialName;
	float material_red, material_green, material_blue;

	m_materialNames.clear();
	m_materialFilenames.clear();
	m_materialColors.clear();

	infile.open(mtlLibFilename);

	while (!infile.eof()) {

		getline(infile, lineBuffer);

		readingMaterialName = false;
		readingMaterialFilename = false;
		readingMaterialColor = false;
		material_red = 0.0f;
		material_green = 0.0f;
		material_blue = 0.0f;
		numToken = 0;

		token = strtok_s((char *)lineBuffer.c_str(), delimiterToken, &nextToken);
		++numToken;

		// If there are any tokens left
		while (token != nullptr) {

			if (numToken == 1) {

				if (0 == strcmp(token, "newmtl")) {

					readingMaterialName = true;
					readingMaterialColor = false;
					readingMaterialFilename = false;
				}
				else if (0 == strcmp(token, "map_Kd")) {

					readingMaterialName = false;
					readingMaterialColor = false;
					readingMaterialFilename = true;
				}
				else if (0 == strcmp(token, "Kd")) {

					readingMaterialName = false;
					readingMaterialColor = true;
					readingMaterialFilename = false;
				}
			}
			else if (numToken == 2) {

				if (readingMaterialName) {

					currentMaterialName = token;
					m_materialNames.push_back(token);
				}
				else if (readingMaterialFilename && !currentMaterialName.empty()) {

					m_materialFilenames.insert(std::make_pair(currentMaterialName, token));
					readTextureName = true;
					break;
				}
				else if (readingMaterialColor) {

					material_red = (float)atof(token);

					if (material_red < 0.0f || material_red > 1.0f) {

						material_red = 0.0f;
					}
				}
			}
			else if (numToken == 3) {

				if (readingMaterialColor) {

					material_green = (float)atof(token);

					if (material_green < 0.0f || material_green > 1.0f) {

						material_green = 0.0f;
					}
				}
			}
			else if (numToken == 4) {
				if (readingMaterialColor && !currentMaterialName.empty()) {
					material_blue = (float)atof(token);

					if (material_blue < 0.0f || material_blue > 1.0f) {

						material_blue = 0.0f;
					}

					m_materialColors.insert(std::make_pair(currentMaterialName, CVector3(material_red, material_green, material_blue)));
				}
			}

			token = strtok_s(nullptr, delimiterToken, &nextToken);
			++numToken;
		}
	}

	infile.close();

	return (m_materialNames.size() > 0);
}