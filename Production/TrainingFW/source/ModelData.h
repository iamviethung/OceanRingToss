#pragma once
#include "Vertex.h"

struct ModelData {
	Vertex* verticesData;
	GLuint* indicesData;
	int numVertices;
	int numIndices;
	GLuint vbold;
	GLuint ibold;
};