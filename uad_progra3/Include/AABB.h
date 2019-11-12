#pragma once
#ifndef AABB_H
#define AABB_H
#include "Globals.h"
#include "MathHelper.h"

/*
TODO:
>
*/

class AABB {
public:
	AABB();
	~AABB();

private:
	CVector3 corners[4];

};


#endif AABB_H