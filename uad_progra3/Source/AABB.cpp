#include "..\Include\AABB.h"

AABB::AABB() {
	


}


AABB::AABB(CVector3 * esq) {

	corners[0] = *esq;	esq++;
	corners[1] = *esq;	esq++;
	corners[2] = *esq;	esq++;
	corners[3] = *esq;	esq++;

}


AABB::~AABB() {


}


void AABB::getCorners(CVector3 * c) {

	*c = corners[0];	c++;
	*c = corners[1];	c++;
	*c = corners[2];	c++;
	*c = corners[3];	c++;

}
