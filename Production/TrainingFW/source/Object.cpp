#include "Object.h"

#define DEG2RAD(deg) deg*3.14f/180.0f


void Object::Draw() {

	glUseProgram(gShader->getProgramId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID->getGlTexId());

	glBindBuffer(GL_ARRAY_BUFFER, modelData->vbold);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelData->ibold);

	GLint mvpMatrixLoc = glGetUniformLocation(gShader->getProgramId(), "u_MVPMatrix");
	maMVP.Transpose();
	glUniformMatrix4fv(mvpMatrixLoc, 1, GL_FALSE, &maMVP.m[0][0]);

	if (gShader->getAttrib("a_posL") != -1)
	{
		glEnableVertexAttribArray(gShader->getAttrib("a_posL"));
		//glVertexAttribPointer(gShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &verticesData[0].pos.x);
		glVertexAttribPointer(gShader->getAttrib("a_posL"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (gShader->getAttrib("a_uv") != -1 )
	{
		glEnableVertexAttribArray(gShader->getAttrib("a_uv"));
		//glVertexAttribPointer(gShader.textureAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &verticesData[0].uv.x);
		glVertexAttribPointer(gShader->getAttrib("a_uv"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3)+sizeof(Vector4));
	}

	glDrawElements(GL_TRIANGLES, modelData->numIndices, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Object::Update() {

	Matrix maRotate, maRotateZ, maRotateX, maRotateY, maScale, maTranslation;

	maRotateX.SetRotationX(DEG2RAD(rot[0]));
	maRotateY.SetRotationY(DEG2RAD(rot[1]));
	maRotateZ.SetRotationZ(DEG2RAD(rot[2]));
	//maRotate = maRotateY * maRotateX * maRotateZ;
	maRotate = maRotateY * maRotateX * maRotateZ;

	maScale.SetScale(scale[0], scale[1], scale[2]);

	maTranslation.SetTranslation(pos);

	if (rigidShape != 0)
		maModel = maScale * maRotate * maRigidBody;
	else
		maModel = maScale * maRotate * maTranslation;
	maMVP = maModel * maView * maProjection;

	if (rigidShape == 2)
		rigidBody->setActivationState(1);
	if (rigidShape == 7) {
		rigidBody->setActivationState(1);
		//rigidHole->setActivationState(1);
		rigidHole->setWorldTransform(rigidBody->getWorldTransform());
	}

	if (rigidShape == 8) {
		MoveAnchor();
	}

}

void Object::Init(int modelID, int imageID, int shaderID) {

	modelData = &ResourceManager::getInstance()->m_vModelsData.at(modelID);
	textureID = ResourceManager::getInstance()->m_vTextureID.at(imageID);
	gShader = ResourceManager::getInstance()->m_vShaders.at(shaderID);

	maModel.SetIdentity();
}

void Object::SetPosition(Vector3 vPos) {
	pos = vPos;
}

void Object::SetRotation(float fRotateAngles[3]) {
	rot[0] = fRotateAngles[0];
	rot[1] = fRotateAngles[1];
	rot[2] = fRotateAngles[2];

}

void Object::SetScale(float fScale[3]) {
	scale[0] = fScale[0];
	scale[1] = fScale[1];
	scale[2] = fScale[2];
}


void Object::SetViewMatrix(Matrix matView) {
	maView = matView;
}

void Object::SetProjectionMatrix(Matrix matProjection) {
	maProjection = matProjection;
}

Vector3 Object::GetPosition() {
	return pos;
}

Object::~Object(){

}

float Object::GetHeight()
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

float Object::GetWidth()
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

float Object::GetThick()
{
	float min = modelData->verticesData[0].pos.z;
	float max = modelData->verticesData[0].pos.z;
	for (int i = 1; i < modelData->numVertices; i++)
	{
		if (modelData->verticesData[i].pos.z > max)
			max = modelData->verticesData[i].pos.z;
		if (modelData->verticesData[i].pos.z < min)
			min = modelData->verticesData[i].pos.z;
	}
	return (max - min)*scale[2];
}

void Object::MovingButton(){
	if (isMove){
		btTransform transButton;
		rigidBody->getMotionState()->getWorldTransform(transButton);
		if (moveEndX >= pos.y){
			if ((moveDirection == 1 && transButton.getOrigin().getY() >= moveEndX) ||
				(moveDirection == -1 && transButton.getOrigin().getY() <= pos.y)){
				moveDirection *= -1;
			}
		}
		else{
			if ((moveDirection == 1 && transButton.getOrigin().getY() >= pos.y) ||
				(moveDirection == -1 && transButton.getOrigin().getY() <= moveEndX))
				moveDirection *= -1;
		}
		transButton.setOrigin(btVector3(transButton.getOrigin().getX(), transButton.getOrigin().getY() + moveDirection*0.001f, transButton.getOrigin().getZ()));
		rigidBody->setWorldTransform(transButton);
		rigidBody->getMotionState()->setWorldTransform(transButton);
	}
}

void Object::MoveAnchor() {
	if (isMove) {
		btTransform transAnchor;
		btTransform transPoleCenter;
		btTransform transPoleOut;
		rigidBody->getMotionState()->getWorldTransform(transAnchor);
		rigidPoleCenter->getMotionState()->getWorldTransform(transPoleCenter);
		rigidOut->getMotionState()->getWorldTransform(transPoleOut);

		if (moveEndX >= pos.x) {
			if ((moveDirection == 1 && transAnchor.getOrigin().getX() >= moveEndX) ||
				(moveDirection == -1 && transAnchor.getOrigin().getX() <= pos.x))
				moveDirection = -moveDirection;
		}
		else {
			if ((moveDirection == 1 && transAnchor.getOrigin().getX() >= pos.x) ||
				(moveDirection == -1 && transAnchor.getOrigin().getX() <= moveEndX))
				moveDirection = -moveDirection;
		}

		transAnchor.setOrigin(btVector3(transAnchor.getOrigin().getX() + moveDirection * 0.01f, transAnchor.getOrigin().getY(), transAnchor.getOrigin().getZ()));
		transPoleCenter.setOrigin(btVector3(transAnchor.getOrigin().getX() + moveDirection * 0.01f, transPoleCenter.getOrigin().getY(), transAnchor.getOrigin().getZ()));
		transPoleOut.setOrigin(btVector3(transAnchor.getOrigin().getX() + moveDirection * 0.01f, transPoleOut.getOrigin().getY(), transAnchor.getOrigin().getZ()));
		rigidBody->setWorldTransform(transAnchor);
		rigidBody->getMotionState()->setWorldTransform(transAnchor);
		rigidPoleCenter->setWorldTransform(transPoleCenter);
		rigidOut->setWorldTransform(transPoleOut);
	}
}