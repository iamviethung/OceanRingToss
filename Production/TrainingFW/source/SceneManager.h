#pragma once
#include "Object.h"
#include "Object2D.h"
#include "Camera.h"
#include "SwimingFishWithoutFuckingAnimation.h"
#include "Platform/InputManager.h"
#include "Menu.h"
#include "Game.h"
#include <time.h>
#include "WaterCaustic.h"

using namespace std;

class SceneManager
{
public:
	static SceneManager* getInstance();
	int ringCount;
	int levelID;
	~SceneManager();
	
	btDynamicsWorld* sceneWorld;
	Matrix maView;
	Matrix maProjection;
		
	void ReadScene();
	void Draw();
	void Update();
	inline int getLevelID(){ return levelID; };
	void SetCameraPosition(Vector3 vCameraPos);
	void SetObjectPosition(int iObjectID, Vector3 vObjectPos);
	void SetObjectRotation(int iObjectID, float zAngle, float xAngle, float yAngle);
	void SetObjectScale(int iObjectID, float xScale, float yScale, float zScale);

	void RandomAirCanon(Vector3 pos, float rad, float height, Vector3 force);
	void AddBubbles(int num, Vector3 pos, float radCanon, float minScale, float maxScale);

	void AddBartime();

	btRigidBody* AddSphere(float rad, float x, float y, float z, float mass);
	btRigidBody* AddBox(float width, float height, float thick, float x, float y, float z, float mass);
	btRigidBody* AddCylinder(float width, float height, float thick, float x, float y, float z, float mass);
	btRigidBody* AddWall(float upX, float upY, float upZ, float x, float y, float z);
	btRigidBody* AddRing(float rad, float thick, float x, float y, float z, float mass);
	btRigidBody* AddTriangleMesh(Object obj, float x, float y, float z);
	btRigidBody* AddCapsule(float height, float rad, float x, float y, float z, float mass);

	void SwimmingFishWithoutFuckingAnimation(Vector3 modelID, Vector3 textureID, Vector3 pos, Vector3 scale, Vector3 rot, Vector3 moveAngle, Vector3 angle, float maxAngle, float dist, float moveAngleStride, Vector3 sign, float velocity, float range);
	void UpdateSwimmingFishWithoutFuckingAnimation();
	void JellyFish(int modelHeadID, int modelTailID, int textureID, Vector3 pos, float rotZ, float scale, float range);
	void UpdateJellyFish();

	float PointToLineDistance(Vector3 A, Vector3 B, Vector3 P);
	Vector3 BulletToVector(const btVector3 &vechihi);
	Vector3 UnProject(Vector3 winCoord);
	void TouchControl(int x, int y, int state);
	void TouchUpdate();

	btVector3 VectorToBullet(Vector3 vec);
	Vector3 CalPoint(Vector3 vec, Matrix ma);
	void NextLevel();
	void ResetScene();
	void SetPause(bool ispause){ isActive = ispause; Menu::getInstance()->displayPause = !ispause; }
	Object* listObject;
	Object2D *object2D;
	WaterCaustic water;
protected:
	SceneManager();
	static SceneManager* m_Instance;
private:
	int modelCount;
	int textTureCount;
	int modelCount2D;
	
	float delay = 0;
	int level = 18;

	bool isSoundOff = false;
	vector<SwimingFishing*> fishes;
	JellyFishStruct* jellyfishes;

	clock_t startTime;
	int sceneDuration,currentDuration;
	Camera camera;
	int cameraType;
	Vector3 vCamPos;
	Vector3 vLookAt;
	vector<Object2D> bubble;
		
	btBroadphaseInterface* broadphase;
	btCollisionConfiguration* collisionConfiguration;
	btDispatcher* dispatcher;
	btConstraintSolver* solver;
	vector<btRigidBody*> vRigidBody;
	vector<btCollisionShape*> vCollisionShape;

	float m_near;
	float m_far;
	float m_FOV;
	bool isActive;
	bool isPressed;
	
	int bubbleModelID;
	int bubbleTextureID;
	void LookAt(Vector3 vEye, Vector3 vLook, Vector3 vUp, Matrix& maResult);
};

