#pragma once
#include "stdafx.h"
#include "ModelData.h"

class ResourceManager
{
public:
	static ResourceManager* getInstance();
	void LoadResources();
	~ResourceManager();
	vector<Texture*> m_vTextureID;
	vector<ModelData> m_vModelsData;
	vector<Program*> m_vShaders;
	vector<string> m_vScenePath;
	vector<string> m_vMenuPath;
	ResourceManager();
private:
	void GetFullPath(string &path);
	static ResourceManager *m_Instance;
	void LoadTexture(char* dir);
	void LoadNFG(char* sFileName);
	void LoadOBJ(char *fileName);
};
