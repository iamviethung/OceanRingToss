#pragma once
#include "ResourceManager.h"

class Object2D {
public:
	ModelData *modelData;
	Texture* textureID;
	Program* gShader;
	bool isOn = true;
	
	float rot[3];
	float scale[3];

	Vector3 pos;

	~Object2D();
	Object2D();
	Object2D(const Object2D &obj);

	void SetPosition(Vector3 vPos);
	void SetRotation(float fRotateAngles[3]);
	void SetScale(float fScale[3]);
	void SetViewMatrix(Matrix	maView);
	void SetProjectionMatrix(Matrix maProjection);

	void Init(int modelID, int imageID, int shaderID);
	void Update();
	void Draw();
	float GetHeight();
	float GetWidth();
private:
	Matrix maModel;
	Matrix maView;
	Matrix maProjection;
	Matrix maMVP;	
};