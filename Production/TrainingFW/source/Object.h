#pragma once
#include "ResourceManager.h"

class Object {
public:
	ModelData *modelData;
	Texture* textureID;
	Program* gShader;

	Vector3 pos;
	Matrix maRigidBody;

	float rot[3];
	float scale[3];
	bool isMove;
	float moveEndX;

	btRigidBody* rigidBody;
	btRigidBody* rigidHole;
	btRigidBody* rigidPoleCenter;
	btRigidBody* rigidOut;

	float moveDirection;

	int rigidShape;
	float rigidMass;

	Vector3 GetPosition();
	float GetHeight();
	float GetWidth();
	float GetThick();

	void SetPosition(Vector3 vPos);
	void SetRotation(float fRotateAngles[3]);
	void SetScale(float fScale[3]);
	void SetViewMatrix(Matrix	maView);
	void SetProjectionMatrix(Matrix maProjection);

	~Object();
	void Init(int modelID, int imageID, int shaderID);
	void Update();
	void Draw();

private:
	Matrix maModel;
	Matrix maView;
	Matrix maProjection;
	Matrix maMVP;

	void MoveAnchor();
	void MovingButton();
};