#pragma once

#ifndef C3DMODEL_H_FBX
#define C3DMODEL_H_FBX

#include <string>
using namespace std;

#include "C3DModel.h"

class C3DModelFbx : public C3DModel {

private:
	int m_currentVertex, m_currentNormal, m_currentUV, m_currentFace, m_currentUVIndex;	// Aux counters used when loading an object from file

	bool readFbxFile(const char * const filename, bool countOnly);		// Read object from file 
	bool parseFbxLine(													// Parse line
		std::string line,
		bool countOnly,
		int lineNumber,
		const char * filename);
	bool readMtllib(std::string mtlLibFilename);

protected:
	void reset();														// Cleanup any allocated memory
	bool loadFromFile(const char * const filename);

public:
	C3DModelFbx();
	~C3DModelFbx();

};

#endif // !C3DMODEL_H_FBX

