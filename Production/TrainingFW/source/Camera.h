#pragma once

#include "ResourceManager.h"

class Camera{
public:
	
	Matrix maModel;
	Matrix maView;
	Matrix maProjection;
	Matrix maMVP;

	Vector3 pos;
	float rot[3];
	float scale[3];

	void SetPosition(Vector3 vPos);
	void SetRotation(float fRotateAngles[3]);
	void SetScale(float fScale[3]);
	void SetViewMatrix(Matrix	maView);
	void SetProjectionMatrix(Matrix maProjection);
	void Update();
};