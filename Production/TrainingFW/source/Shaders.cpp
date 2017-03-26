#include "Shaders.h"

GLuint Shaders::esLoadShader(GLenum type, const char *shaderSrc)
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader(type);

	if (shader == 0)
		return 0;

	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);

			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			//esLogMessage("Error compiling shader:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;

}

/// \brief Create a program object, link program.
//         Errors output to log.
/// \param vertShaderSrc Vertex shader source code
/// \param fragShaderSrc Fragment shader source code
/// \return A new program object linked with the vertex/fragment shader pair, 0 on failure

GLuint Shaders::esLoadProgram(const char *vertShaderSrc, const char *fragShaderSrc)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint linked;

	// Load the vertex/fragment shaders
	vertexShader = this->esLoadShader(GL_VERTEX_SHADER, vertShaderSrc);
	if (vertexShader == 0)
		return 0;

	fragmentShader = this->esLoadShader(GL_FRAGMENT_SHADER, fragShaderSrc);
	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return 0;
	}

	// Create the program object
	programObject = glCreateProgram();

	if (programObject == 0)
		return 0;

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	// Link the program
	glLinkProgram(programObject);

	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);

			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
			//esLogMessage("Error linking program:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteProgram(programObject);
		return 0;
	}

	// Free up no longer needed shader resources
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return programObject;
}

char* Shaders::readFileShader(char* fileShader)
{
	// Load the shader source
	FILE* pf = fopen(fileShader, "rb");
	if (pf == 0)
		return NULL;

	fseek(pf, 0, SEEK_END);
	long size = ftell(pf);
	fseek(pf, 0, SEEK_SET);

	char * shaderSrc = new char[size + 1];
	fread(shaderSrc, sizeof(char), size, pf);
	shaderSrc[size] = '\0';
	fclose(pf);

	return shaderSrc;
}

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	LOGV("Game -> Dm42");
	vertexShader = readFileShader(fileVertexShader);
	fragmentShader = readFileShader(fileFragmentShader);

	program = this->esLoadProgram(vertexShader, fragmentShader);
	LOGV("Game -> Dm44");
	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	colorAttribute = glGetAttribLocation(program, "a_colorL");
	textureAttribute = glGetAttribLocation(program, "a_uv");

	//iTextureLoc = glGetUniformLocation(program, "u_texture2");
	//glUniform1i(iTextureLoc, 1);
	LOGV("Game -> Dm43");
	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	/*glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);*/
}