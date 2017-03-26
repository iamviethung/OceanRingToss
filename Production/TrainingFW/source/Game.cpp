#include "stdafx.h"
#include <string>
using namespace std;

#include "Game.h"
#include "Platform/Platform.h"
#include "Platform/InputManager.h"
#include "Utils/FPSLimiter.h"
#include "SceneManager.h"
#include "Menu.h"

bool CallBackFunc(btManifoldPoint &btmanifoldpoint, const btCollisionObjectWrapper *obj1, int part_1, int index_1, const btCollisionObjectWrapper *obj2, int part_2, int index_2)  {


	if ((obj1->getCollisionObject()->getUserIndex() == 50 && obj2->getCollisionObject()->getUserIndex() == 90) ||
		(obj1->getCollisionObject()->getUserIndex() == 90 && obj2->getCollisionObject()->getUserIndex() == 50)) {
		//if (obj1->getCollisionObject()->getWorldTransform().getOrigin().getY() <= (obj2->getCollisionObject()->getWorldTransform().getOrigin().getY()))
		//{
		if (obj1->getCollisionObject()->getUserIndex() == 50) {
			cout << endl << "Vong " << obj1->getCollisionObject()->getCollisionShape()->getUserIndex() << " VAO !";
			SceneManager::getInstance()->listObject[obj1->getCollisionObject()->getCollisionShape()->getUserIndex()].rigidHole->setUserIndex(49);
		}
		else {
			cout << endl << "Vong " << obj2->getCollisionObject()->getCollisionShape()->getUserIndex() << " VAO !";
			SceneManager::getInstance()->listObject[obj2->getCollisionObject()->getCollisionShape()->getUserIndex()].rigidHole->setUserIndex(49);
		}
		LOGE("AMEN");
		SceneManager::getInstance()->ringCount++;
		SceneManager::getInstance()->object2D[5].textureID = ResourceManager::getInstance()->m_vTextureID.at(SceneManager::getInstance()->ringCount + 65);
		//}
	}

	if ((obj1->getCollisionObject()->getUserIndex() == 49 && obj2->getCollisionObject()->getUserIndex() == 80) ||
		(obj1->getCollisionObject()->getUserIndex() == 80 && obj2->getCollisionObject()->getUserIndex() == 49)) {
		if (obj1->getCollisionObject()->getUserIndex() == 49) {
			cout << endl << "Vong " << obj1->getCollisionObject()->getCollisionShape()->getUserIndex() << "EO VAO !";
			SceneManager::getInstance()->listObject[obj1->getCollisionObject()->getCollisionShape()->getUserIndex()].rigidHole->setUserIndex(50);
		}
		else {
			cout << endl << "Vong " << obj2->getCollisionObject()->getCollisionShape()->getUserIndex() << " EO VAO !";
			SceneManager::getInstance()->listObject[obj2->getCollisionObject()->getCollisionShape()->getUserIndex()].rigidHole->setUserIndex(50);
		}
		LOGE("AMUN");
		SceneManager::getInstance()->ringCount--;
		SceneManager::getInstance()->object2D[5].textureID = ResourceManager::getInstance()->m_vTextureID.at(SceneManager::getInstance()->ringCount + 65);
	}
	return false;
}

Game::Game():
		m_isInit(false),
		m_isRunning(true),	
		m_isPause(false),
		m_isPress(false),
		is_TurnOff(false)
{
	gContactAddedCallback = CallBackFunc;
}

Game::~Game()
{	
	//clean up
}


//init function
void Game::Init(int width, int height)
{
	new FPSLimiter();	
	new InputManager();

	FPS_LMT->setFPS(60);
	FPS_LMT->setEnable(true);

	//call platform to init environment
	PLATFORM->Init(width, height);
	//PLATFORM->Resize(width, height);
	PLATFORM->printSystemSpecs();
	
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	LOGV("Game -> Init");
	/**/
	LOGV("ARRGGHHH");
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	
	ResourceManager::getInstance()->LoadResources();	
	SceneManager::getInstance()->ReadScene();
	Menu::getInstance()->ReadMenu();	
	//Menu::getInstance()->displayWin = true;
	LOGV("Game -> Init End");
}


void SensorControl(){
	float X = 0, Y = 0, Z = 0;
	SensorEvent sensorevent = INPUT_MGR->getCoorSensorEvent();
	float gra = 1.5;
	float a = sqrt(sensorevent.posY*sensorevent.posY + sensorevent.posX*sensorevent.posX + sensorevent.posZ*sensorevent.posZ);
		
	X = gra*2.5*(sensorevent.posY) / a;
	//if ((X) >  0.75*gra)
	//	X = 0.75*gra;
	//else if (X < -0.75*gra)
	//	X = -0.75*gra;
	Y = -gra * 1*(sensorevent.posX) / a;
	//Z = -gra*(sensorevent.posZ -7.5) / a;	
	SceneManager::getInstance()->sceneWorld->setGravity(btVector3(X, Y, Z));
}
//update function
void Game::Update(float dt)
{	
	//update platform - call
	PLATFORM->Update();

	// Press ESC to exit
#ifdef _WIN32
	if (INPUT_MGR->isKeyPressed(VK_ESCAPE))
		setRunning(false);
	if (INPUT_MGR->isKeyPressed('F'))
		SceneManager::getInstance()->RandomAirCanon(Vector3(-3.0, 0, 1), 1, 8, Vector3(0, 1, 0));
	if (INPUT_MGR->isKeyPressed('G'))
		SceneManager::getInstance()->RandomAirCanon(Vector3(3.0, 0, 1), 1, 8, Vector3(0, 1, 0));
	if (INPUT_MGR->isKeyPressed('A'))
		SceneManager::getInstance()->sceneWorld->setGravity(btVector3(-1, 0, 0));
	if (INPUT_MGR->isKeyPressed('D'))
		SceneManager::getInstance()->sceneWorld->setGravity(btVector3(1, 0, 0));
	if (INPUT_MGR->isKeyPressed('S'))
		SceneManager::getInstance()->sceneWorld->setGravity(btVector3(0, -1, 0));
	if (INPUT_MGR->isKeyPressed('W'))
		SceneManager::getInstance()->sceneWorld->setGravity(btVector3(0, 1, 0));
	if (INPUT_MGR->isKeyPressed('Q'))
	{
		//SceneManager::getInstance()->NextLevel();
		//Menu::getInstance()->displayWin = true;
		Menu::getInstance()->displayPause = true;
		//SceneManager::getInstance()->water.m_affCoe.translateZ -= 0.1f;
	}
	if (INPUT_MGR->isKeyPressed('E'))
	{
		//SceneManager::getInstance()->SetPause(true);
		//Menu::getInstance()->displayMission = false;
		//SceneManager::getInstance()->object2D[5].textureID = ResourceManager::getInstance()->m_vTextureID.at(71);
		Menu::getInstance()->displayPause = false;
		Menu::getInstance()->displayWin = true;
		//Menu::getInstance()->turtorObject[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(6);
		//SceneManager::getInstance()->water.m_affCoe.translateZ += 0.1f;
		//setRunning(false);
	}
		
		
#endif

	// Update goes here

	SceneManager::getInstance()->Update();
	//gContactAddedCallback = CallBackFunc;
#ifdef _ANDROID
	SensorControl();
#endif
	Menu::getInstance()->Update();
	//Limit FPS
	FPS_LMT->tick();
}

//render function
void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Render goes here
	LOGE("Game->Render");

	SceneManager::getInstance()->Draw();
	Menu::getInstance()->Draw();

	//swap buffer after render
	PLATFORM->SwapBuffers();
}

void Game::Exit()
{
	m_isRunning = false;
	LOGV("Game -> Exit");
	//clean up
	InputManager::freeInstance();	
	LOGV("Game -> Exit2");
	FPSLimiter::freeInstance();
	LOGV("Game -> Exit3");
	delete SceneManager::getInstance();
	LOGV("Game -> Exit4");
	delete ResourceManager::getInstance();
	LOGV("Game -> Exit5");
	delete Menu::getInstance();

	PLATFORM->Exit();
	LOGV("Game -> Exit6");
}

void Game::Replay(){
	
		SceneManager::getInstance()->ResetScene();
		SceneManager::getInstance()->ReadScene();
	
}

void Game::setPause(bool isPause){
	if (SceneManager::getInstance()->getLevelID() != 0)
		m_isPause = isPause;
}

void Game::setRunning(bool running)
{
	m_isRunning = running;
}