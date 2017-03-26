#include "Camera.h"

#define DEG2RAD(deg) deg*3.14f/180.0f

void Camera::Update() {

	Matrix maRotate, maRotateZ, maRotateX, maRotateY, maScale, maTranslation;

	maRotateX.SetRotationX(DEG2RAD(rot[0]));
	maRotateY.SetRotationY(DEG2RAD(rot[1]));
	maRotateZ.SetRotationZ(DEG2RAD(rot[2]));

	maRotate = maRotateY * maRotateX * maRotateZ;

	maScale.SetScale(scale[0], scale[1], scale[2]);

	maTranslation.SetTranslation(pos);

	maModel = maScale * maRotate * maTranslation;
	maMVP = maModel * maView * maProjection;
		
}

void Camera::SetPosition(Vector3 vPos) {
	pos = vPos;
}

void Camera::SetRotation(float fRotateAngles[3]) {
	rot[0] = fRotateAngles[0];
	rot[1] = fRotateAngles[1];
	rot[2] = fRotateAngles[2];

}

void Camera::SetScale(float fScale[3]) {
	scale[0] = fScale[0];
	scale[1] = fScale[1];
	scale[2] = fScale[2];
}


void Camera::SetViewMatrix(Matrix matView) {
	maView = matView;
}

void Camera::SetProjectionMatrix(Matrix matProjection) {
	maProjection = matProjection;
}