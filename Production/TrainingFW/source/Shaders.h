#pragma once
#include "stdafx.h"
//#include "esUtil.h"

class Shaders 
{
public:
	GLuint program;
	//GLuint vertexShader, fragmentShader;
	char* vertexShader, *fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint colorAttribute;
	GLint textureAttribute;

	char* readFileShader(char* fileShader);
	int Init(char * fileVertexShader, char * fileFragmentShader);
	GLuint esLoadProgram(const char *vertShaderSrc, const char *fragShaderSrc);
	GLuint esLoadShader(GLenum type, const char *shaderSrc);
	Shaders CopyShader();
	~Shaders();
};