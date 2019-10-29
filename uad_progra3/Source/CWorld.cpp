#include "../stdafx.h"
#include <iostream>
using namespace std;

#include <assert.h>
#include "../Include/Globals.h"
#include "../Include/CWorld.h"
#include "../Include/CWideStringHelper.h"
#include "../Include/CTextureLoader.h"


CWorld::CWorld() {



}

CWorld::~CWorld() {



}

void CWorld::readMod() {

		ifstream file_json("hexgrid_cfg.json", ifstream::binary);
		file_json >> j;

		cout << "Models form the json file" << endl;
		cout << j["Models"];

		file_json.close();
		j.clear();
	
}