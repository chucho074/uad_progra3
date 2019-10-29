#pragma once
#ifndef CWORLD_H
#define CWORLD_H
#include "Globals.h"
#include "CApp.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

//TODO:
//Puntero de una instancia de CHexaGrid
//Implementar JSON


class CWorld {
public:
	CWorld();
	nlohmann::json j;

	~CWorld();

	void readMod();
	

};

#endif CWORLD_H