#ifndef __WATERCAUSTIC_H__
#define __WATERCAUSTIC_H__

//#include "Coordinate.h"
#include "ResourceManager.h"

struct Coordinate
{
	float translateX, translateY, translateZ;
	float rotateX, rotateY, rotateZ;
	float scaleX, scaleY, scaleZ;
};

class WaterCaustic
{
public:
	WaterCaustic();
	WaterCaustic(const WaterCaustic &wc);
	~WaterCaustic();

	void Init(int modelPos, int texBase, int texDisp, int shaderID);
	void Draw();
	void Update();

public:
	bool m_drawable; // If true - draw
	Texture *m_texBase;
	Texture *m_texDisp;
	ModelData m_pos; // Vertices and indices info
	
	Matrix m_maModel; // Model Matrix
	Matrix maView;
	Matrix maProjection;
	Matrix maMVP;
	Program* m_shader; // Shader object
	void SetPosition(float vPos[3]);
	void SetRotation(float fRotateAngles[3]);
	void SetScale(float fScale[3]);
	void SetViewMatrix(Matrix maView);
	void SetProjectionMatrix(Matrix maProjection);

private:
	float deltaT;
	Coordinate m_affCoe; // Affine
};

#endif