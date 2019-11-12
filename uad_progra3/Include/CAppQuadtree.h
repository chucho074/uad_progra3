#pragma once
#ifndef CAppQuadtree_H
#define CAppQuadtree_H
#include "Globals.h"
#include "CApp.h"

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

class CAppQuadtree {
public:
	CAppQuadtree();
	~CAppQuadtree();

private:
	void initialize();
	void update(double);
	void run();
	void render();
};


#endif CAppQuadtree_H