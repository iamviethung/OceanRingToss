#include "Menu.h"

Menu* Menu::m_Instance = NULL;

Menu * Menu::getInstance(){
	if (m_Instance == NULL)
		m_Instance = new Menu();
	return m_Instance;
}

Menu::Menu()
{
	displayPause = false, displayWin = false, displayLose = false, displayMission = false, displayTurtorial = false, displayCredit = false, displayStage = false;
}

void Menu::ReadMenu(){
	int modelCount;
	int model2DID;
	int image2DID;
	int shader2DID;
	Vector3 vPos;
	float fRot[3];
	float fScale[3];
	string str;
	save.Loaded();
	int menuCount = ResourceManager::getInstance()->m_vMenuPath.size();
	for (int i = 0; i < menuCount; i++) {

		std::ifstream myFile(ResourceManager::getInstance()->m_vMenuPath.at(i).c_str());
		std::getline(myFile, str);
		sscanf(str.c_str(), "#Object 2D: %d", &modelCount);
		switch (i) {
			case 0:
				modelCountPause = modelCount;
				pauseObjects = new Object2D[modelCount];
				break;
			case 1:
				modelCountLose = modelCount;
				loseObjects = new Object2D[modelCount];
				break;
			case 2:
				modelCountMission = modelCount;
				missionObjects = new Object2D[modelCount];
				break;
			case 3:
				modelCountWin = modelCount;
				winObjects = new Object2D[modelCount];
				break;
			case 4:
				modelCountTurtorial = modelCount;
				turtorObject = new Object2D[modelCount];
				break;
			case 5:
				modelCountCredit = modelCount;
				creditObject = new Object2D[modelCount];
				break;
			case 6:
				modelCountStage = modelCount;
				stageObject = new Object2D[modelCount];
				break;
		}

		for (int j = 0; j < modelCount; j++){
			std::getline(myFile, str);
			std::getline(myFile, str);
			std::getline(myFile, str);
			sscanf(str.c_str(), "MODEL %d", &model2DID);
			std::getline(myFile, str);
			sscanf(str.c_str(), "TEXTURE %d", &image2DID);
			std::getline(myFile, str);
			sscanf(str.c_str(), "SHADER %d", &shader2DID);

			switch (i) {
				case 0:
					pauseObjects[j].Init(model2DID, image2DID, shader2DID);
					break;
				case 1:
					//settingObjects[j].Init(model2DID, image2DID, shader2DID);
					loseObjects[j].Init(model2DID, image2DID, shader2DID);
					break;
				case 2:		
					if (j>0 && j<4){
						if (save.save[j - 1] != -1){
							if (j==2)
								image2DID = 49;
							if (j == 3)
								image2DID = 51;
						}
						else{
							if (j == 2)
								image2DID = 48;
							if (j == 3)
								image2DID = 50;
						}
					}
					else if (j >= 4){
						if (save.save[j-4] == 1)
							image2DID = 39;
						else if (save.save[j-4] == 2)
							image2DID = 63;
						else if (save.save[j-4]==3)
							image2DID = 64;
					}				
					missionObjects[j].Init(model2DID, image2DID, shader2DID);
					break;
				case 3:					
					winObjects[j].Init(model2DID, image2DID, shader2DID);
					break;	
				case 4:
					turtorObject[j].Init(model2DID, image2DID, shader2DID);
					break;
				case 5:
					creditObject[j].Init(model2DID, image2DID, shader2DID);
					break;
				case 6:
					stageObject[j].Init(model2DID, image2DID, shader2DID);
					break;
			}

			std::getline(myFile, str);
			sscanf(str.c_str(), "POSITION %f, %f, %f", &vPos.x, &vPos.y, &vPos.z);

			std::getline(myFile, str);
			sscanf(str.c_str(), "ROTATION %f, %f, %f", &fRot[0], &fRot[1], &fRot[2]);

			std::getline(myFile, str);
			sscanf(str.c_str(), "SCALE %f, %f, %f", &fScale[0], &fScale[1], &fScale[2]);

			switch (i) {
				case 0:
					pauseObjects[j].SetPosition(vPos);
					pauseObjects[j].SetRotation(fRot);
					pauseObjects[j].SetScale(fScale);
					break;
				case 1:
					loseObjects[j].SetPosition(vPos);
					loseObjects[j].SetRotation(fRot);
					loseObjects[j].SetScale(fScale);
					break;
				case 2:
					missionObjects[j].SetPosition(vPos);
					missionObjects[j].SetRotation(fRot);
					missionObjects[j].SetScale(fScale);
					break;
				case 3:
					winObjects[j].SetPosition(vPos);
					winObjects[j].SetRotation(fRot);
					winObjects[j].SetScale(fScale);
					break;
				case 4:
					turtorObject[j].SetPosition(vPos);
					turtorObject[j].SetRotation(fRot);
					turtorObject[j].SetScale(fScale);
					break;
				case 5:
					creditObject[j].SetPosition(vPos);
					creditObject[j].SetRotation(fRot);
					creditObject[j].SetScale(fScale);
					break;
				case 6:
					stageObject[j].SetPosition(vPos);
					stageObject[j].SetRotation(fRot);
					stageObject[j].SetScale(fScale);
					break;
			}
		}
	}

	Matrix maTemp;
	camera.SetPosition(Vector3(0, 5, 13));
	float rotC[3] = { 0.0, 0.0, 0.0 };
	camera.SetRotation(rotC);
	float scaleC[3] = { 0.0, 0.0, 0.0 };
	camera.SetScale(scaleC);
	camera.SetViewMatrix(maTemp.SetIdentity());
	camera.SetProjectionMatrix(maTemp.SetIdentity());
	camera.Update();

	Vector3 vecTemp(0.0, 1.0, 0.0);
	LookAt(Vector3(0, 5, 13), Vector3(0, 5, 0), vecTemp, maView);

	maProjection.SetPerspective(45, 1, 0.0001, 1000);
}

void Menu::Update() {
	for (int i = 0; i < modelCountPause; i++){

		if (displayPause)
			pauseObjects[i].pos.x = 0;
		else
			pauseObjects[i].pos.x = 20;

		pauseObjects[i].SetViewMatrix(maView);
		pauseObjects[i].SetProjectionMatrix(maProjection);
		pauseObjects[i].Update();
	}
		
	for (int i = 0; i < modelCountLose; i++){

		if (displayLose)
			loseObjects[i].pos.x = 0;
		else
			loseObjects[i].pos.x = 20;

		loseObjects[i].SetViewMatrix(maView);
		loseObjects[i].SetProjectionMatrix(maProjection);
		loseObjects[i].Update();
	}

	for (int i = 0; i < modelCountMission; i++){

		if (displayMission){
			missionObjects[i].pos.z = 3.2;
			if (i >= 4){
				if (save.save[i-4]<=0)
					missionObjects[i].pos.z += 20;
				else
					missionObjects[i].pos.z += 0.3f;
			}
		}
		else
			missionObjects[i].pos.z = 20;

		if (i == 0) missionObjects[i].pos.z -= 0.3f;
		
		missionObjects[i].SetViewMatrix(maView);
		missionObjects[i].SetProjectionMatrix(maProjection);
		missionObjects[i].Update();
	}

	for (int i = 0; i < modelCountWin; i++){

		if (displayWin)
			winObjects[i].pos.z = 3.2;
		else
			winObjects[i].pos.z = 20;
		if (i == 0) 
			winObjects[i].pos.z -= 0.3f;		
		winObjects[i].SetViewMatrix(maView);
		winObjects[i].SetProjectionMatrix(maProjection);
		winObjects[i].Update();
	}	
	for (int i = 0; i < modelCountTurtorial; i++){

		if (displayTurtorial)
			turtorObject[i].pos.z = 3.2;
		else
			turtorObject[i].pos.z = 20;
		if (i == 0)
			turtorObject[i].pos.z -= 0.3f;
		turtorObject[i].SetViewMatrix(maView);
		turtorObject[i].SetProjectionMatrix(maProjection);
		turtorObject[i].Update();
	}
	for (int i = 0; i < modelCountCredit; i++){

		if (displayCredit)
			creditObject[i].pos.z = 3.2;
		else
			creditObject[i].pos.z = 20;
		if (i == 0)
			creditObject[i].pos.z -= 0.3f;
		creditObject[i].SetViewMatrix(maView);
		creditObject[i].SetProjectionMatrix(maProjection);
		creditObject[i].Update();
	}
	for (int i = 0; i < modelCountStage; i++){

		if (displayStage)
			stageObject[i].pos.z = 3.2;
		else
			stageObject[i].pos.z = 20;
		if (i == 0)
			stageObject[i].pos.z -= 0.3f;
		stageObject[i].SetViewMatrix(maView);
		stageObject[i].SetProjectionMatrix(maProjection);
		stageObject[i].Update();
	}
}

void Menu::Draw() {
	for (int i = 0; i < modelCountPause; i++)
		pauseObjects[i].Draw();
	/*for (int i = 0; i < modelCountSetting; i++)
		settingObjects[i].Draw();*/
	for (int i = 0; i < modelCountLose; i++)
		loseObjects[i].Draw();
	for (int i = 0; i < modelCountMission; i++)
		missionObjects[i].Draw();
	for (int i = 0; i < modelCountWin; i++)
		winObjects[i].Draw();
	for (int i = 0; i < modelCountTurtorial; i++)
		turtorObject[i].Draw();
	for (int i = 0; i < modelCountCredit; i++)
		creditObject[i].Draw();
	for (int i = 0; i < modelCountStage; i++)
		stageObject[i].Draw();
}

void Menu::LookAt(Vector3 vEye, Vector3 vLook, Vector3 vUp, Matrix& maResult)
{

	Vector3 f;
	(vLook - vEye).Normalize(f);
	Vector3 s;
	f.Cross(vUp).Normalize(s);
	Vector3 u;
	s.Cross(f).Normalize(u);

	maResult.m[0][0] = s.x;
	maResult.m[1][0] = s.y;
	maResult.m[2][0] = s.z;
	maResult.m[3][0] = -s.Dot(vEye);

	maResult.m[0][1] = u.x;
	maResult.m[1][1] = u.y;
	maResult.m[2][1] = u.z;
	maResult.m[3][1] = -u.Dot(vEye);

	maResult.m[0][2] = -f.x;
	maResult.m[1][2] = -f.y;
	maResult.m[2][2] = -f.z;
	maResult.m[3][2] = f.Dot(vEye);

	maResult.m[0][3] = 0.0f;
	maResult.m[1][3] = 0.0f;
	maResult.m[2][3] = 0.0f;
	maResult.m[3][3] = 1.0f;

}

Menu::~Menu(){
	delete[] loseObjects;
	delete[] winObjects;
	delete[] pauseObjects;
	delete[] missionObjects;
	delete[] turtorObject;
	delete[] creditObject;
	delete[] stageObject;
}