#include "stdafx.h"

class Save{
private:
	//int level,numStar;
	string pathSave;
public:
	Save();
	~Save();
	int save[3];
	//int numLevel;
	void Saved();
	void Loaded();
	void GetFullPath(string &paths);
};