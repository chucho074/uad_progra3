#include "..\Include\CCamera.h"

/**/
CCamera::CCamera(CVector3 WorldUp, CVector3 EyePos, CVector3 LookAt, int FBW, int FBH, float FOV, float NearPl, float FarPl) {



}

/**/
CCamera::~CCamera() {



}

void CCamera::updateFrameBufferSize(int w, int h)
{
}

void CCamera::update(float deltaTime)
{
}

void CCamera::moveForward(float deltaMove)
{
}

void CCamera::moveUp(float deltaMove)
{
}

void CCamera::strafe(float deltaMove)
{
}

bool CCamera::isAABBVisible(AABB & aabb)
{
	return false;
}

void CCamera::orbitArroundLookAt(float deltaMove)
{
}

void CCamera::recalculateViewMatrix()
{
}

void CCamera::recalculateProjectionMatrix()
{
}

void CCamera::recalculateViewFrustum()
{
}
