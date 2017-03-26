
#pragma once
#include "Object2D.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Save.h"

class Menu{
public:
	static Menu* getInstance();
	void ReadMenu();

	Object2D *pauseObjects;
	Object2D *winObjects;
	Object2D *loseObjects;
	Object2D *missionObjects;
	Object2D *turtorObject;
	Object2D *creditObject;
	Object2D *stageObject;

	int modelCountPause = 0, modelCountTurtorial = 0, modelCountWin = 0, modelCountLose = 0, modelCountMission = 0, modelCountCredit=0, modelCountStage=0;
	bool displayPause , displayWin , displayLose , displayMission , displayTurtorial ,displayCredit ,displayStage;

	Matrix maView;
	Matrix maProjection;
	Save save;
	void Update();
	void Draw();
	~Menu();
private:
	static Menu * m_Instance;
	Camera camera;
	
	void LookAt(Vector3 vEye, Vector3 vLook, Vector3 vUp, Matrix& maResult);

	Menu();
};
