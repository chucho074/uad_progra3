#include "..\Include\CCamera.h"

/**/
CCamera::CCamera(CVector3 WorldUp, CVector3 EyePos, CVector3 LookAt, int FBW, int FBH, float FOV, float NearPl, float FarPl) {

	

}

/**/
CCamera::~CCamera() {



}


void CCamera::updateFrameBufferSize(int w, int h) {



}


void CCamera::update(float deltaTime) {



}


void CCamera::moveForward(float deltaMove) {



}


void CCamera::moveUp(float deltaMove) {



}


void CCamera::strafe(float deltaMove) {



}


bool CCamera::isAABBVisible(AABB_2D & aabb) {
	if (!mCacheValid) {
		recalculateViewMatrix();
		recalculateViewFrustum();
	}

	// If the AABB is either completely visible (all corners inside the frustum), or intersecting (at least one corner inside the frustum)
	return (
		mViewFrustum.isAABBVisible(aabb) == CFrustum::FRUSTUM_VISIBILITY_TEST_RESULT::INTERSECT ||
		mViewFrustum.isAABBVisible(aabb) == CFrustum::FRUSTUM_VISIBILITY_TEST_RESULT::INSIDE
		);
}


void CCamera::orbitArroundLookAt(float deltaMove) {



}


void CCamera::recalculateViewMatrix() {



}


void CCamera::recalculateProjectionMatrix() {



}


void CCamera::recalculateViewFrustum() {

	// Avoid division by zero
	if (mFrameBufferHeight > 0)
	{
		// Geometric approach
		mViewFrustum.update(
			mEyePos,
			mLookAt,
			mUp,
			mRight,
			mNearPlane,
			mFarPlane,
			mFov,
			(float)mFrameBufferWidth / (float)mFrameBufferHeight);
	}

}