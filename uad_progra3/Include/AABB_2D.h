#pragma once
#ifndef AABB_2D_H
#define AABB_2D_H
#include "Globals.h"
#include "MathHelper.h"

/*
TODO:
> Metodo que regrese un apuntador al array de esquinas
*/

// Axis-Alinged Bouding Box
class AABB_2D {
public:
	AABB_2D();
	AABB_2D(CVector3 *);
	~AABB_2D();

	void getCorners(CVector3 *);
	void setCorners(CVector3 * inCorners);
	bool pointsInside(CVector3[4]);
	CVector3 corners[4];		//Arreglar el Frustum.cpp
private:


};


#endif AABB_2D_H