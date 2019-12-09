#pragma once
#ifndef CCamera_H
#define CCamera_H
#include "Globals.h"
#include "MathHelper.h"
#include "AABB_2D.h"
#include "CFrustum.h"

/*
TODO:
>
*/

class CCamera {
public:
	CCamera(CVector3, CVector3, CVector3, int, int, float, float, float);
	~CCamera();

	void updateFrameBufferSize(int w, int h);

	void update(float deltaTime);

	void moveForward(float deltaMove);			//W,S		Mover sobre lookAt

	void moveUp(float deltaMove);				//Flechas o Q & E		Mover sobre el up de la camara (mUp)

	void strafe(float deltaMove);				//A,D			Mover sobre mRight

	bool isAABBVisible(AABB_2D & aabb);

	void orbitArroundLookAt(float deltaMove);	//

	//Get para proj y view matrix
	//Get para mEyePos, mLookAt, mUp

private:
	float mFov, mNearPlane/*0.1*/, mFarPlane/*1000*/;
	CVector3 mWorldUp/*0,1,0*/, mEyePos, mLookAt, mUp/*= cross(mLookAt,mRight);*/, mRight/*= cross(mWorldUp, mLookAt);*/;		//mRight producto cruz de mWorldUp y mLookAt
	int mFrameBufferWidth, mFrameBufferHeight;
	MathHelper::Matrix4 mProyectionMatrix, mViewMatrix;
	CFrustum mViewFrustum;
	bool mCacheValid;

	void recalculateViewMatrix();
	void recalculateProjectionMatrix();
	void recalculateViewFrustum();
};


#endif CCamera_H