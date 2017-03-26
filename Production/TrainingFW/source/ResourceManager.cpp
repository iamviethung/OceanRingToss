#include "ResourceManager.h"


ResourceManager* ResourceManager::m_Instance = NULL;

ResourceManager* ResourceManager::getInstance() {
	LOGV("ResourceManager -> Vao getInstance");
	if (m_Instance == NULL) {
		LOGV("ResourceManager -> Tao Instance Moi");
		m_Instance = new ResourceManager();
	}
	LOGV("ResourceManager -> Ket thuc getInstance");
	return m_Instance;
}

ResourceManager::ResourceManager() {  }

void ResourceManager::GetFullPath(string &paths){
#ifndef _WIN32
	string androidpath = ANDROID_PREFIX;
	string mypath = paths;
	paths= androidpath + mypath;
#endif
}

void ResourceManager::LoadOBJ(char *fileName)
{
	LOGI("Load OBJ");
	ModelData modelData;
	vector< GLuint > vertexIndices, textureIndices;
	vector< Vector3 > temp_vertices;
	vector< Vector2 > temp_uvs;
	ifstream myFile(fileName);
	if (!myFile.good()){
		LOGE("Impossible to open the file !\n");
		return;
	}
	string str;
	while (1){
		// doc 1 tu trong file

		myFile >> str;

		if (myFile.eof())
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		if (strcmp(str.c_str(), "v") == 0){
			Vector3 vertex;
			myFile >> vertex.x;
			myFile >> vertex.y;
			myFile >> vertex.z;
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(str.c_str(), "vt") == 0){
			Vector2 uv;
			myFile >> uv.x;
			myFile >> uv.y;
			temp_uvs.push_back(uv);
		}
		else if (strcmp(str.c_str(), "f") == 0){
			GLuint vertexindice;
			GLuint textureindices;
			for (int i = 0; i < 3; i++){
				myFile >> str;
				sscanf(str.c_str(), "%d/%d", &vertexindice, &textureindices);
				vertexIndices.push_back(vertexindice);
				textureIndices.push_back(textureindices);
			}
		}
	}
	myFile.close();
	modelData.numVertices = vertexIndices.size();
	modelData.verticesData = new Vertex[modelData.numVertices];
	GLuint vertexIndex;
	GLuint textureIndex;
	Vector3 vertices;
	Vector2 texture;
	for (int i = 0; i < modelData.numVertices; i++)
	{
		vertexIndex = vertexIndices[i];
		vertices = temp_vertices[vertexIndex - 1];
		modelData.verticesData[i].pos.x = vertices.x;
		modelData.verticesData[i].pos.y = vertices.y;
		modelData.verticesData[i].pos.z = vertices.z;
		textureIndex = textureIndices[i];
		texture = temp_uvs[textureIndex - 1];
		modelData.verticesData[i].uv.x = texture.x;
		modelData.verticesData[i].uv.y = texture.y;
	}
	modelData.numIndices = modelData.numVertices;
	modelData.indicesData = new GLuint[modelData.numIndices];
	for (int i = 0; i < modelData.numIndices; i++)
	{
		modelData.indicesData[i] = i;
	}


	glGenBuffers(1, &modelData.vbold);
	glBindBuffer(GL_ARRAY_BUFFER, modelData.vbold);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*modelData.numVertices, modelData.verticesData, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &modelData.ibold);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelData.ibold);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*modelData.numIndices, modelData.indicesData, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_vModelsData.push_back(modelData);

	//delete file;
}

void ResourceManager::LoadNFG(char* sFileName) {

	ifstream myfile(sFileName);
	string line;
	string str;
	getline(myfile, line);

	ModelData modelData;

	float temp = 0;

	sscanf(line.c_str(), "NrVertices: %d", &modelData.numVertices);

	modelData.verticesData = new Vertex[modelData.numVertices];
	
	for(int i=0; i < modelData.numVertices; i++) {

		getline(myfile, line);
		line = line.substr(line.find("pos"));

		sscanf(line.c_str(), "pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", 
			&modelData.verticesData[i].pos.x, &modelData.verticesData[i].pos.y, &modelData.verticesData[i].pos.z, 
			&modelData.verticesData[i].normal.x, &modelData.verticesData[i].normal.y, &modelData.verticesData[i].normal.z, 
			&modelData.verticesData[i].binormal.x, &modelData.verticesData[i].binormal.y, &modelData.verticesData[i].binormal.z, 
			&modelData.verticesData[i].tangent.x, &modelData.verticesData[i].tangent.y, &modelData.verticesData[i].tangent.z, 
			&modelData.verticesData[i].uv.x, &modelData.verticesData[i].uv.y);
	}

	getline(myfile, line);
	sscanf(line.c_str(), "NrIndices: %d", &modelData.numIndices);
	
	modelData.indicesData = new GLuint[modelData.numIndices];

	for(int i=0; i < modelData.numIndices / 3; i++) {
		getline(myfile, line);
		line = line.substr(line.find(".") + 1);

		sscanf(line.c_str(), "    %d,    %d,    %d", &modelData.indicesData[i*3], &modelData.indicesData[i*3 + 1], &modelData.indicesData[i*3 + 2]);
	}


	glGenBuffers(1, &modelData.vbold);
	glBindBuffer(GL_ARRAY_BUFFER, modelData.vbold);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*modelData.numVertices, modelData.verticesData, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &modelData.ibold);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelData.ibold);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*modelData.numIndices, modelData.indicesData, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_vModelsData.push_back(modelData);
}

void ResourceManager::LoadTexture(char* dir){
	Texture* texture = new Texture(dir);
	texture->setTiledMode(GL_REPEAT);
	texture->loadTexture();
	m_vTextureID.push_back(texture);
	texture = NULL;
	delete texture;
}

void ResourceManager::LoadResources() {
	LOGV("Resource Manager -> LoadResources");
	
	string directory = "data/Resources/ResourceManager/RM.txt";
	GetFullPath(directory);
	LOGE("[LOADED] Model: %s\n", (char*)directory.c_str());
	ifstream myFile(directory.c_str()); 
	int modelCount, textureCount, shaderCount, sceneCount;
	char* dirVS;
	char* dirFS;
	string str;
	char* dir;

	dir = new char[512];
	dirVS = new char[512];
	dirFS = new char[512];

	getline(myFile, str);
	LOGV("Resource Manager -> LoadModel");
	LOGE("[LOADED] Model: %s\n", (char*)str.c_str());
	sscanf(str.c_str(), "#Models: %d", &modelCount);

	for (int i = 0; i < modelCount; i++)
	{ 
		getline(myFile, str);
		getline(myFile, str);
		LOGV("RS -> md1");
		LOGE("[LOADED] Model: %s \n", (char*)str.c_str());
		sscanf(str.c_str(), "FILE %s", dir);
		//LOGV(dir);
		if (str.find(".nfg")!=-1){	
			string strTemp = dir;
			GetFullPath(strTemp); 
			LOGE("[LOADED] Model: %s\n", (char*)strTemp.c_str());
			LoadNFG((char*)strTemp.c_str());
			LOGV("RS -> md2");
		}
		else if(str.find(".obj")!=-1){	
			string strTemp = dir;
			GetFullPath(strTemp); 
			LOGE("[LOADED] Model: %s\n", (char*)strTemp.c_str());
			LoadOBJ((char*)strTemp.c_str());
			LOGV("RS -> md2");
		}
	}
	getline(myFile, str);
	LOGI("%s",str.c_str());
	sscanf(str.c_str(), "#2D Textures: %d", &textureCount);
	for (int j = 0; j < textureCount; j++)
	{
		getline(myFile, str);
		getline(myFile, str);
		LOGI("%s",str.c_str());
		sscanf(str.c_str(), "FILE %s", dir);
		string strTemp = dir;
		GetFullPath(strTemp);
		LoadTexture((char*)strTemp.c_str());
		LOGV("Game -> Dm3");
	}
	LOGV("Game -> Dm4");
	getline(myFile, str);
	sscanf(str.c_str(), "#Shader: %d", &shaderCount);
	for (int i = 0; i < shaderCount; i++) {
		LOGV("Game -> Dm40");
		getline(myFile, str);
		getline(myFile, str);
		LOGV(str.c_str());
		sscanf(str.c_str(), "VS %s", dirVS);
		getline(myFile, str);
		LOGV(str.c_str());
		sscanf(str.c_str(), "FS %s", dirFS);
		LOGV("Game -> Dm41");
		string strTempVS = dirVS;
		string strTempFS = dirFS;
		GetFullPath(strTempVS);
		GetFullPath(strTempFS);
		Program* shader = new Program((char*)strTempVS.c_str(), (char*)strTempFS.c_str());
		m_vShaders.push_back(shader);
		m_vShaders.back()->loadShaders();
		shader = NULL;
		delete shader;
	}

	getline(myFile, str);
	sscanf(str.c_str(), "#ScenePath %d", &sceneCount);
	for (int i = 0; i < sceneCount; i++) {
		getline(myFile, str);
		getline(myFile, str);
		LOGV(str.c_str());
		sscanf(str.c_str(), "PATH %s", dir);
		string strTemp = dir;
		GetFullPath(strTemp);
		//str = strTemp;
		m_vScenePath.push_back(strTemp);
	}

	getline(myFile, str);
	sscanf(str.c_str(), "#MenuPath %d", &sceneCount);
	for (int i = 0; i < sceneCount; i++) {
		getline(myFile, str);
		getline(myFile, str);
		LOGV(str.c_str());
		sscanf(str.c_str(), "PATH %s", dir);
		string strTemp = dir;
		GetFullPath(strTemp);
		//str = strTemp;
		m_vMenuPath.push_back(strTemp);
	}
	myFile.close();
	delete dir;
	delete dirVS;
	delete dirFS;
}

ResourceManager::~ResourceManager(){
	for (int i = 0; i < m_vModelsData.size(); i++){
		delete[] m_vModelsData.at(i).verticesData;
		delete[] m_vModelsData.at(i).indicesData;
	}
}
