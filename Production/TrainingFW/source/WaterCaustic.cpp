#include "WaterCaustic.h"

#define DEG2RAD(deg) deg*3.14f/180.0f

WaterCaustic::WaterCaustic()
{
	m_affCoe.translateX = 0.0;
	m_affCoe.translateY = 0.0;
	m_affCoe.translateZ = 0.0;

	m_affCoe.rotateX = 0.0;
	m_affCoe.rotateY = 0.0;
	m_affCoe.rotateZ = 0.0;

	m_affCoe.scaleX = 1.0;
	m_affCoe.scaleY = 1.0;
	m_affCoe.scaleZ = 1.0;
	
	m_drawable = true;
	deltaT = 0.01f;
}

WaterCaustic::WaterCaustic(const WaterCaustic &Obj)
{
	m_pos = Obj.m_pos;
	m_texBase = Obj.m_texBase;
	m_texDisp = Obj.m_texDisp;
	m_affCoe = Obj.m_affCoe;
	m_maModel = Matrix(Obj.m_maModel);
	maView = Obj.maView;
	maProjection = Obj.maProjection;
	maMVP = Obj.maMVP;
	m_shader = Obj.m_shader;
}

WaterCaustic::~WaterCaustic()
{
	m_shader = NULL;
}

void WaterCaustic::Init(int modelPos, int texBase, int texDisp, int shaderID)
{
	m_pos = ResourceManager::getInstance()->m_vModelsData.at(modelPos);
	m_texBase = ResourceManager::getInstance()->m_vTextureID.at(texBase);
	m_texDisp = ResourceManager::getInstance()->m_vTextureID.at(texDisp);
	m_shader = ResourceManager::getInstance()->m_vShaders.at(shaderID);

	//glEnable(GL_BLEND);//
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//

	//glUseProgram(m_shader->getProgramId());
	//glUniform1i(m_shader->getUniform("u_texBase"), 1);
	//glUniform1i(m_shader->getUniform("u_texDisp"), 2);

	//glUniform3f(m_shader->getUniform("u_camPos"), 1.0f, 1.0f, -1.0f);
	m_maModel.SetIdentity();//
}

void WaterCaustic::Draw()
{
	if (!this->m_drawable)
		return;

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(m_shader->getProgramId());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texBase->getGlTexId());

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_texDisp->getGlTexId());

	glBindBuffer(GL_ARRAY_BUFFER, m_pos.vbold);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pos.ibold);

	glUniform1i(m_shader->getUniform("u_texBase"), 1);//
	glUniform1i(m_shader->getUniform("u_texDisp"), 2);//
	//glUniformMatrix4fv(m_shader->getUniform("u_WVP"), 1, GL_FALSE, m_maModel.m[0]);

	GLint mvpMatrixLoc = glGetUniformLocation(m_shader->getProgramId(), "u_WVP");
	maMVP.Transpose();
	glUniformMatrix4fv(mvpMatrixLoc, 1, GL_FALSE, &maMVP.m[0][0]);

	glUniform1f(m_shader->getUniform("u_time"), deltaT);
	//if (deltaT < 0.9f)
		//deltaT += 0.001f;
	//if (deltaT > 0.1f)
	//	deltaT = 0.001f;

	//vertex pointer
	if (m_shader->getAttrib("a_posL") != -1)
	{
		glEnableVertexAttribArray(m_shader->getAttrib("a_posL"));
		glVertexAttribPointer(m_shader->getAttrib("a_posL"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	//indices
	if (m_shader->getAttrib("a_uv") != -1)
	{
		glEnableVertexAttribArray(m_shader->getAttrib("a_uv"));
		glVertexAttribPointer(m_shader->getAttrib("a_uv"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3)+sizeof(Vector4));
	}

	glDrawElements(GL_TRIANGLES, m_pos.numIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void WaterCaustic::Update()
{
	//glUseProgram(m_shader->getProgramId());

	/*Matrix finalMatrix;
	m_maModel = finalMatrix.SetScale(m_affCoe.scaleX, m_affCoe.scaleY, m_affCoe.scaleZ);
	m_maModel = m_maModel * finalMatrix.SetRotationZ(DEG2RAD(m_affCoe.rotateZ));
	m_maModel = m_maModel * finalMatrix.SetRotationX(DEG2RAD(m_affCoe.rotateX));
	m_maModel = m_maModel * finalMatrix.SetRotationY(DEG2RAD(m_affCoe.rotateY));
	m_maModel = m_maModel * finalMatrix.SetTranslation(m_affCoe.translateX, m_affCoe.translateY, m_affCoe.translateZ);*/
	deltaT += 0.001f;
	Matrix maRotate, maRotateZ, maRotateX, maRotateY, maScale, maTranslation;
	maScale.SetScale(m_affCoe.scaleX, m_affCoe.scaleY, m_affCoe.scaleZ);
	maRotateX.SetRotationX(DEG2RAD(m_affCoe.rotateX));
	maRotateY.SetRotationY(DEG2RAD(m_affCoe.rotateY));
	maRotateZ.SetRotationZ(DEG2RAD(m_affCoe.rotateZ));
	maRotate = maRotateY * maRotateX * maRotateZ;
	
	maTranslation.SetTranslation(m_affCoe.translateX, m_affCoe.translateY, m_affCoe.translateZ);

	m_maModel = maScale * maRotate * maTranslation;
	maMVP = m_maModel * maView * maProjection;//
	//maMVP = maModel * maView * maProjection;
}

void WaterCaustic::SetPosition(float vPos[3]) {
	m_affCoe.translateX = vPos[0];
	m_affCoe.translateY = vPos[1];
	m_affCoe.translateZ = vPos[2];
}

void WaterCaustic::SetRotation(float fRotateAngles[3]) {
	m_affCoe.rotateX = fRotateAngles[0];
	m_affCoe.rotateY = fRotateAngles[1];
	m_affCoe.rotateZ = fRotateAngles[2];

}

void  WaterCaustic::SetScale(float fScale[3]) {
	m_affCoe.scaleX = fScale[0];
	m_affCoe.scaleY = fScale[1];
	m_affCoe.scaleZ = fScale[2];
}

void WaterCaustic::SetViewMatrix(Matrix matView) {
	maView = matView;
}

void WaterCaustic::SetProjectionMatrix(Matrix matProjection) {
	maProjection = matProjection;
}