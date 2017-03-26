#include "Object2D.h"

#define DEG2RAD(deg) deg*3.14f/180.0f

Object2D::~Object2D() {
	
}

Object2D::Object2D(){}

Object2D::Object2D(const Object2D &Object2D){
	modelData = Object2D.modelData;
	textureID = Object2D.textureID;
	gShader = Object2D.gShader;
	maModel = Object2D.maModel;
	maView = Object2D.maView;
	maProjection = Object2D.maProjection;
	maMVP = Object2D.maMVP;
	pos = Object2D.pos;
	for (int i = 0; i < 3; i++)
		scale[i] = Object2D.scale[i];
}

void Object2D::Init(int modelID, int imageID, int shaderID) {

	modelData = &ResourceManager::getInstance()->m_vModelsData.at(modelID);
	textureID = ResourceManager::getInstance()->m_vTextureID.at(imageID);
	gShader = ResourceManager::getInstance()->m_vShaders.at(shaderID);

	maModel.SetIdentity();

}

void Object2D::SetPosition(Vector3 vPos) {
	pos = vPos;
}

void Object2D::SetRotation(float fRotateAngles[3]) {
	rot[0] = fRotateAngles[0];
	rot[1] = fRotateAngles[1];
	rot[2] = fRotateAngles[2];

}

void  Object2D::SetScale(float fScale[3]) {
	scale[0] = fScale[0];
	scale[1] = fScale[1];
	scale[2] = fScale[2];
}

void Object2D::SetViewMatrix(Matrix matView) {
	maView = matView;
}

void Object2D::SetProjectionMatrix(Matrix matProjection) {
	maProjection = matProjection;
}

void Object2D::Draw() {

	glUseProgram(gShader->getProgramId());

	glActiveTexture(GL_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, modelData->vbold);

	GLint mvpMatrixLoc = glGetUniformLocation(gShader->getProgramId(), "u_MVPMatrix");
	maMVP.Transpose();
	glUniformMatrix4fv(mvpMatrixLoc, 1, GL_FALSE, &maMVP.m[0][0]);

	glBindTexture(GL_TEXTURE_2D, textureID->getGlTexId());


	if (gShader->getAttrib("a_posL") != -1)
	{
		glEnableVertexAttribArray(gShader->getAttrib("a_posL"));
		//glVertexAttribPointer(gShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &verticesData[0].pos.x);
		glVertexAttribPointer(gShader->getAttrib("a_posL"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	
	if (gShader->getAttrib("a_uv") != -1)
	{
		glEnableVertexAttribArray(gShader->getAttrib("a_uv"));
		//glVertexAttribPointer(gShader.textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &verticesData[0].uv.x);
		glVertexAttribPointer(gShader->getAttrib("a_uv"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3)+sizeof(Vector4));
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelData->ibold);
	glDrawElements(GL_TRIANGLES, modelData->numIndices, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}



void Object2D::Update() {

	Matrix maRotate, maRotateZ, maRotateX, maRotateY, maScale, maTranslation;

	maRotateX.SetRotationX(DEG2RAD(rot[0]));
	maRotateY.SetRotationY(DEG2RAD(rot[1]));
	maRotateZ.SetRotationZ(DEG2RAD(rot[2]));
	//maRotate = maRotateY * maRotateX * maRotateZ;
	maRotate = maRotateY * maRotateX * maRotateZ;

	maScale.SetScale(scale[0], scale[1], scale[2]);

	maTranslation.SetTranslation(pos);


	maModel = maScale * maRotate * maTranslation;
	maMVP = maModel * maView * maProjection;
}

float Object2D::GetWidth()
{
	float min = modelData->verticesData[0].pos.x;
	float max = modelData->verticesData[0].pos.x;
	for (int i = 1; i < modelData->numVertices; i++)
	{
		if (modelData->verticesData[i].pos.x > max)
			max = modelData->verticesData[i].pos.x;
		if (modelData->verticesData[i].pos.x < min)
			min = modelData->verticesData[i].pos.x;
	}
	return (max - min)*scale[0];
}

float Object2D::GetHeight()
{
	float min = modelData->verticesData[0].pos.y;
	float max = modelData->verticesData[0].pos.y;
	for (int i = 1; i < modelData->numVertices; i++)
	{
		if (modelData->verticesData[i].pos.y > max)
			max = modelData->verticesData[i].pos.y;
		if (modelData->verticesData[i].pos.y < min)
			min = modelData->verticesData[i].pos.y;
	}
	return (max - min)*scale[1];
}