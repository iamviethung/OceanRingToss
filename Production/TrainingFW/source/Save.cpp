#include "Save.h"

Save::Save(){
	for (int i = 0; i < 3; i++){
		if (i == 0)
			save[i] = 0;
		else
			save[i] = -1;
	}
}

void Save::GetFullPath(string &paths){
#ifndef _WIN32
	string androidpath = ANDROID_PREFIX;
	string mypath = paths;
	paths = androidpath + mypath;
#endif
}

void Save::Saved(){
	pathSave="data/Resources/Save/savefile.txt";
	GetFullPath(pathSave);
	std::ofstream myFile(pathSave.c_str(), ios::trunc|ios::out);
	myFile << "Number of Level " << 3 << "\n";
	for (int i = 0; i < 3; i++)
	{
		myFile << "Level " << i + 1 << "\n";
		myFile << save[i]  << "\n";
	}

	myFile.close();
}

//void Save::Loaded(){
//#ifdef _WIN32
//	 pathSave = "data/Resources/Save/save.txt";
//#else
//	 string temp = "data/Resources/Save/save.txt";
//	 string pathSave = ANDROID_PREFIX + temp;
//#endif
//	 fstream saveFile;
//	 string strTemp;
//	 int level=0, star=0;
//	 saveFile.open(pathSave,ios::in);
//	 for (int i = 0; i < 3; i++){
//		 getline(saveFile, strTemp);
//		 sscanf(strTemp.c_str(), "%d %d", &level, &star);
//		 dataFile[i][0] = level;
//		 dataFile[i][1] = star;
//	 }
//}

void Save::Loaded(){
	pathSave="data/Resources/Save/savefile.txt";
	GetFullPath(pathSave);
	ifstream myFile(pathSave.c_str(),ios::in);
	string str;
	std::getline(myFile, str);
	//sscanf(str.c_str(), "Number of Level %d", &numLevel);
	
	for (int i = 0; i < 3; i++)
	{
		getline(myFile, str);
		getline(myFile, str);
		sscanf(str.c_str(), "%d", &save[i]);
	}
	myFile.close();
}

Save::~Save(){
	
}