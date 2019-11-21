#pragma once
#ifndef AABB_H
#define AABB_H
#include "Globals.h"
#include "MathHelper.h"

/*
TODO:
> Metodo que regrese un apuntador al array de esquinas
*/

// Axis-Alinged Bouding Box
class AABB {
public:
	AABB();
	AABB(CVector3 *);
	~AABB();

private:
	CVector3 corners[4];

	void getCorners(CVector3 *);

};


#endif AABB_H