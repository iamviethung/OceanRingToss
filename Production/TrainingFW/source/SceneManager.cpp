#include "SceneManager.h"

#define DEG2RAD(deg) deg*3.14f/180.0f

SceneManager* SceneManager::m_Instance = NULL;

SceneManager* SceneManager::getInstance() {
	if (m_Instance == NULL)
		m_Instance = new SceneManager();

	return m_Instance;
}

SceneManager::SceneManager()
{
	levelID = 0;
	currentDuration = 0;
}

void SceneManager::ReadScene()
{
	//std::ifstream myFile("../Resources/SceneManager/SM.txt");
	std::ifstream myFile(ResourceManager::getInstance()->m_vScenePath.at(levelID).c_str());
	std::string str;
	int modelID, imageID, shaderID, model2DID, image2DID, shader2DID;
	Vector3 vPos;
	float fRot[3];
	float fScale[3];
	int shapeType;
#undef new
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	sceneWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	sceneWorld->setGravity(btVector3(0, -2, 0));

	AddWall(0, 1, 0, 0, 0, 0);
	if (levelID != 0){
		AddWall(0, 0, 1, 0, 0, 0.4); 
		AddWall(0, 0, -1, 0, 0, 1.6);
	}

	else{
		AddWall(0, 0, 1, 0, 0, -0.8);
		AddWall(0, 0, -1, 0, 0, 2.2);
	}

	AddWall(1, 0, 0, -5, 0, 0);
	AddWall(-1, 0, 0, 5, 0, 0);
	AddWall(0, -1, 0, 0, 9, 0);

	std::getline(myFile, str);
	sscanf(str.c_str(), "#Object: %d", &modelCount);

	listObject = new Object[modelCount];
	for (int i = 0; i < modelCount; i++)
	{
		std::getline(myFile, str);
		std::getline(myFile, str);
		std::getline(myFile, str);
		sscanf(str.c_str(), "MODEL %d", &modelID);

		std::getline(myFile, str);
		sscanf(str.c_str(), "TEXTURE %d", &imageID);

		std::getline(myFile, str);
		sscanf(str.c_str(), "SHADER %d", &shaderID);

		listObject[i].Init(modelID, imageID, shaderID);

		std::getline(myFile, str);
		sscanf(str.c_str(), "POSITION %f, %f, %f", &vPos.x, &vPos.y, &vPos.z);

		std::getline(myFile, str);
		sscanf(str.c_str(), "ROTATION %f, %f, %f", &fRot[0], &fRot[1], &fRot[2]);

		std::getline(myFile, str);
		sscanf(str.c_str(), "SCALE %f, %f, %f", &fScale[0], &fScale[1], &fScale[2]);

		listObject[i].SetPosition(vPos);
		listObject[i].SetRotation(fRot);
		listObject[i].SetScale(fScale);

		getline(myFile, str);
		//cout << str << endl;
		sscanf(str.c_str(), "SHAPE %d", &shapeType);

		getline(myFile, str);
		//cout << str << endl;
		sscanf(str.c_str(), "MASS %f", &listObject[i].rigidMass);

		listObject[i].rigidShape = shapeType;


		if (shapeType == 1) {
			//listObject[i].rigidShape = 1;
			listObject[i].rigidBody = AddBox(listObject[i].GetWidth(), listObject[i].GetHeight(), listObject[i].GetThick(), listObject[i].pos.x, listObject[i].pos.y, listObject[i].pos.z, listObject[i].rigidMass);
		}
		else if (shapeType == 2) {
			//listObject[i].rigidShape = 2;
			listObject[i].rigidBody = AddSphere(listObject[i].GetHeight(), listObject[i].pos.x, listObject[i].pos.y, listObject[i].pos.z, listObject[i].rigidMass);
			
		}
		else if (shapeType == 3) {
			//listObject[i].rigidShape = 3;
			listObject[i].rigidBody = AddCylinder(listObject[i].GetWidth(), listObject[i].GetHeight(), listObject[i].GetThick(), listObject[i].pos.x, listObject[i].pos.y, listObject[i].pos.z, listObject[i].rigidMass);
		}
		else if (shapeType == 7) {
			listObject[i].rigidBody = AddRing(listObject[i].GetWidth() / 2.0, listObject[i].GetHeight(), listObject[i].pos.x, listObject[i].pos.y, listObject[i].pos.z, listObject[i].rigidMass);
			listObject[i].rigidHole = AddCylinder(listObject[i].GetWidth() - listObject[i].GetHeight() * 2+0.1f, 0.03, listObject[i].GetWidth() - listObject[i].GetHeight() * 2+0.1f, listObject[i].pos.x, listObject[i].pos.y, listObject[i].pos.z, listObject[i].rigidMass);
			listObject[i].rigidBody->setUserIndex(i);
			listObject[i].rigidHole->setUserIndex(50);
			listObject[i].rigidHole->getCollisionShape()->setUserIndex(i);
			//listObject[i].rigidBody->setCollisionFlags(listObject[i].rigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
			listObject[i].rigidHole->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
			listObject[i].rigidHole->setCollisionFlags(listObject[i].rigidHole->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);


		}
		else if (shapeType == 8) {
			listObject[i].rigidBody = AddTriangleMesh(listObject[i], listObject[i].pos.x, listObject[i].pos.y, listObject[i].pos.z);		
			listObject[i].rigidPoleCenter = AddCylinder(listObject[i].GetWidth() / 4 - 0.05, 0.3, listObject[i].GetWidth() / 4 - 0.05, listObject[i].pos.x, listObject[i].pos.y + listObject[i].GetHeight() / 2 + 0.3, listObject[i].pos.z, 0);
			listObject[i].rigidOut = AddCylinder(listObject[i].GetWidth() / 4, 0.13, listObject[i].GetWidth() / 4, listObject[i].pos.x, listObject[i].pos.y + listObject[i].GetHeight() + 0.1, listObject[i].pos.z, 0);
			listObject[i].rigidBody->setUserIndex(100);
			listObject[i].rigidPoleCenter->setUserIndex(90);
			listObject[i].rigidOut->setUserIndex(80);
			listObject[i].rigidPoleCenter->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
			listObject[i].rigidOut->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
		
			getline(myFile, str);
			sscanf(str.c_str(), "MOVING %d, %f", &listObject[i].isMove, &listObject[i].moveEndX);
			
			if (listObject[i].moveEndX > listObject[i].pos.x)
				listObject[i].moveDirection = 1;
			else
				listObject[i].moveDirection = -1;
		}

		else if (shapeType == 9) {
			listObject[i].rigidBody = AddCapsule(0.1, 0.5, listObject[i].pos.x, listObject[i].pos.y, listObject[i].pos.z, listObject[i].rigidMass);
			listObject[i].rigidBody->setUserIndex(i);
		}

	}

//Bubble
	std::getline(myFile, str);
	std::getline(myFile, str);	
	sscanf(str.c_str(), "MODEL %d", &bubbleModelID);
	std::getline(myFile, str);
	sscanf(str.c_str(), "TEXTURE %d", &bubbleTextureID);

//Object 2D	
	std::getline(myFile, str);
	sscanf(str.c_str(), "#Object 2D: %d", &modelCount2D);
	object2D = new Object2D[modelCount2D];
	for (int j = 0; j < modelCount2D; j++){
		std::getline(myFile, str);
		std::getline(myFile, str);
		std::getline(myFile, str);
		sscanf(str.c_str(), "MODEL %d", &model2DID);		
		std::getline(myFile, str);
		sscanf(str.c_str(), "TEXTURE %d", &image2DID);
		std::getline(myFile, str);
		sscanf(str.c_str(), "SHADER %d", &shader2DID);
				
		object2D[j].Init(model2DID,image2DID,shader2DID);

		std::getline(myFile, str);
		sscanf(str.c_str(), "POSITION %f, %f, %f", &vPos.x, &vPos.y, &vPos.z);

		std::getline(myFile, str);
		sscanf(str.c_str(), "ROTATION %f, %f, %f", &fRot[0], &fRot[1], &fRot[2]);

		std::getline(myFile, str);
		sscanf(str.c_str(), "SCALE %f, %f, %f", &fScale[0], &fScale[1], &fScale[2]);

		object2D[j].SetPosition(vPos);		
		object2D[j].SetRotation(fRot);
		object2D[j].SetScale(fScale);
	}
	//////
	//Camera
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
	m_FOV = 45;
	m_near = 0.0001;
	m_far = 1000;

	maProjection.SetPerspective(m_FOV, 1, m_near, m_far);
	/////
	//Water Coustic
	/////
		water.Init(2, 37, 38, 1);
		float posWater[3] = {0.0,8.0,3.9};
		float rotateWater[3] = {0.0,0.0,0.0};
		float scaleWater[3] = {5.5,8.0,8.5};
		water.SetPosition(posWater);
		water.SetRotation(rotateWater);
		water.SetScale(scaleWater);
	/////
	std::getline(myFile, str);
	std::getline(myFile, str);
	sscanf(str.c_str(), "TIME %d", &sceneDuration);
	sceneDuration *= 60;

	startTime = clock();
	isActive = true;
	ringCount = 0;
	SwimmingFishWithoutFuckingAnimation(Vector3(11, 10, 12), Vector3(40, 40, 40), Vector3(0.2, 4, -1), Vector3(0.35, 0.525, 0.35), Vector3(180, 0, 0), Vector3(21, 0, -21), Vector3(23, 30, 23), 30, 0.3, 3, Vector3(-1, -1, 1), -0.02, 2.8);
	SwimmingFishWithoutFuckingAnimation(Vector3(8, 7, 9), Vector3(41, 41, 41), Vector3(0.2, 2, -1), Vector3(0.375, 0.625, 0.5), Vector3(0, 0, 0), Vector3(-21, 0, 21), Vector3(23, 30, 23), 30, 0.3, 3, Vector3(-1, -1, 1), 0.02, 2.8);
	SwimmingFishWithoutFuckingAnimation(Vector3(14, 13, 15), Vector3(42, 42, 42), Vector3(0.2, 6, -1), Vector3(0.375, 0.625, 0.5), Vector3(0, 180, 0), Vector3(21, 0, -21), Vector3(23, 30, 23), 30, 0.3, 3, Vector3(-1, -1, 1), -0.01, 2.8);
	JellyFish(18, 0, 43, Vector3(0, -1, -3), 0, 0.7, 12);
	
	myFile.close();
}

void SceneManager::SwimmingFishWithoutFuckingAnimation(Vector3 modelID, Vector3 textureID, Vector3 pos, Vector3 scale, Vector3 rot, Vector3 moveAngle, Vector3 angle, float maxAngle, float dist, float moveAngleStride, Vector3 sign, float velocity, float range)
{
	float r[3]; r[0] = rot.x; r[1] = rot.y; r[2] = rot.z;
	float s[3]; s[0] = scale.x; s[1] = scale.y; s[2] = scale.z;
	SwimingFishing* fish = new SwimingFishing();
	fish->rot = rot;
	fish->head.Init(modelID.x, textureID.x, 0);
	fish->head.rigidShape = 0;
	fish->head.SetScale(s);
	fish->head.SetRotation(r);
	fish->head.SetPosition(pos);//clownFishHeadCut(2)
	//fish->head.rigidBody = AddTriangleMesh(fish->head, pos.x, pos.y, pos.z);
	//fish->head.rigidBody = AddBox(fish->head.GetWidth(), fish->head.GetHeight(), fish->head.GetThick(), pos.x, pos.y, pos.z, 0);
	//fish->head.rigidBody->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

	fish->body.Init(modelID.y, textureID.y, 0);
	fish->body.rigidShape = 0;
	fish->body.SetScale(s);
	fish->body.SetRotation(r);
	fish->body.SetPosition(pos);
	//fish->body.rigidBody = AddTriangleMesh(fish->body, pos.x, pos.y, pos.z);
	//fish->body.rigidBody = AddBox(fish->body.GetWidth(), fish->body.GetHeight(), fish->body.GetThick(), pos.x, pos.y, pos.z, 0);
	//fish->body.rigidBody->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

	fish->tail.Init(modelID.z, textureID.z, 0);
	fish->tail.rigidShape = 0;
	//scale[0] = 0.6;
	fish->tail.SetScale(s);
	fish->tail.SetRotation(r);
	fish->tail.SetPosition(pos);
	//fish->tail.rigidBody = AddTriangleMesh(fish->tail, pos.x, pos.y, pos.z);
	//fish->tail.rigidBody = AddBox(fish->tail.GetWidth(), fish->tail.GetHeight(), fish->tail.GetThick(), pos.x, pos.y, pos.z, 0);
	//fish->tail.rigidBody->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Matrix maTemp;
	maTemp.SetIdentity();
	fish->head.SetViewMatrix(maView);
	fish->head.SetProjectionMatrix(maTemp.SetPerspective(DEG2RAD(m_FOV), 1, m_near, m_far));
	fish->body.SetViewMatrix(maView);
	fish->body.SetProjectionMatrix(maTemp.SetPerspective(DEG2RAD(m_FOV), 1, m_near, m_far));
	fish->tail.SetViewMatrix(maView);
	fish->tail.SetProjectionMatrix(maTemp.SetPerspective(DEG2RAD(m_FOV), 1, m_near, m_far));

	fish->maxAngle = maxAngle;
	fish->moveAngle = moveAngle;
	fish->angle = angle;
	fish->dist = dist;
	fish->moveAngleStride = moveAngleStride;
	fish->sign = sign;
	fish->range = range;
	fish->velocity = velocity;
	fish->pos = pos;

	fishes.push_back(fish);
	fish = NULL; //
	delete fish; //
}

//void SceneManager::UpdateSwimmingFishWithoutFuckingAnimation()
//{
//	if (fishes.size() > 0)
//	{
//		Vector3 pos;
//		Matrix maTemp;
//		Matrix m;
//		btTransform trans;
//		maTemp.SetIdentity();
//		for (int i = 0; i < fishes.size(); i++)
//		{
//			pos = fishes[i]->head.GetPosition();
//			fishes[i]->head.rot[1] += fishes[i]->angle.x;
//			pos.z += fishes[i]->dist*sin((fishes[i]->moveAngle.x)*3.141592 / 180);
//			pos.x += fishes[i]->velocity;
//			fishes[i]->head.SetPosition(pos);
//			/*trans.setIdentity();
//			trans.setOrigin(btVector3(pos.x,pos.y,pos.z));
//			trans.setRotation(btQuaternion(0, 1, 0, fishes[i]->head.rot[1]));
//			fishes[i]->head.rigidBody->setWorldTransform(trans);*/
//			LookAt(vCamPos, vLookAt, Vector3(0.0, 1.0, 0.0), m);
//			fishes[i]->head.SetViewMatrix(m);
//			fishes[i]->head.SetProjectionMatrix(maTemp.SetPerspective(m_FOV, 1, m_near, m_far));
//			fishes[i]->head.Update();
//			pos.z -= fishes[i]->dist*sin((fishes[i]->moveAngle.x)*3.141592 / 180);
//			fishes[i]->head.rot[1] -= fishes[i]->angle.x;
//			fishes[i]->head.SetPosition(pos);
//			fishes[i]->moveAngle.x += fishes[i]->moveAngleStride;
//			fishes[i]->angle.x += fishes[i]->sign.x * fishes[i]->moveAngleStride / (180.0 / (fishes[i]->maxAngle * 2));
//			if (fishes[i]->moveAngle.x >= 360)
//				fishes[i]->moveAngle.x = fishes[i]->moveAngle.x - 360;
//			if (fishes[i]->angle.x >= fishes[i]->maxAngle) fishes[i]->sign.x = -1;
//			if (fishes[i]->angle.x <= -fishes[i]->maxAngle) fishes[i]->sign.x = 1;
//
//
//
//			pos = fishes[i]->body.GetPosition();
//			fishes[i]->body.rot[1] += fishes[i]->angle.y;
//			pos.z += fishes[i]->dist*sin((fishes[i]->moveAngle.y)*3.141592 / 180);
//			pos.x += fishes[i]->velocity;
//			fishes[i]->body.SetPosition(pos);
//			/*trans.setIdentity();
//			trans.setOrigin(btVector3(pos.x, pos.y, pos.z));
//			trans.setRotation(btQuaternion(0, 1, 0, fishes[i]->body.rot[1]));
//			fishes[i]->body.rigidBody->setWorldTransform(trans);*/
//			LookAt(vCamPos, vLookAt, Vector3(0.0, 1.0, 0.0), m);
//			fishes[i]->body.SetViewMatrix(m);
//			fishes[i]->body.SetProjectionMatrix(maTemp.SetPerspective(m_FOV, 1, m_near, m_far));
//			fishes[i]->body.Update();
//			pos.z -= fishes[i]->dist*sin((fishes[i]->moveAngle.y)*3.141592 / 180);
//			fishes[i]->body.rot[1] -= fishes[i]->angle.y;
//			fishes[i]->body.SetPosition(pos);
//			fishes[i]->moveAngle.y += fishes[i]->moveAngleStride;
//			fishes[i]->angle.y += fishes[i]->sign.y * fishes[i]->moveAngleStride / (180.0 / (fishes[i]->maxAngle * 2));
//			if (fishes[i]->moveAngle.y >= 360)
//				fishes[i]->moveAngle.y = fishes[i]->moveAngle.y - 360;
//			if (fishes[i]->angle.y >= fishes[i]->maxAngle) fishes[i]->sign.y = -1;
//			if (fishes[i]->angle.y <= -fishes[i]->maxAngle) fishes[i]->sign.y = 1;
//
//			pos = fishes[i]->tail.GetPosition();
//			fishes[i]->tail.rot[1] += fishes[i]->angle.z;
//			pos.z += fishes[i]->dist*sin((fishes[i]->moveAngle.z)*3.141592 / 180);
//			//pos.z += fish[i]->GetWidth() / 2.0*sin((-moveAngle[0])*3.141592 / 180) + fish[i+1]->GetWidth() / 2.0*sin((-moveAngle[1])*3.141592 / 180);
//			pos.x += fishes[i]->velocity;
//			fishes[i]->tail.SetPosition(pos);
//			/*trans.setIdentity();
//			trans.setOrigin(btVector3(pos.x, pos.y, pos.z));
//			trans.setRotation(btQuaternion(0, 1, 0, fishes[i]->body.rot[1]));
//			fishes[i]->tail.rigidBody->setWorldTransform(trans);*/
//			
//			LookAt(vCamPos, vLookAt, Vector3(0.0, 1.0, 0.0), m);
//			fishes[i]->tail.SetViewMatrix(m);
//			fishes[i]->tail.SetProjectionMatrix(maTemp.SetPerspective(m_FOV, 1, m_near, m_far));
//			fishes[i]->tail.Update();
//			pos.z -= fishes[i]->dist*sin((fishes[i]->moveAngle.z)*3.141592 / 180);
//			fishes[i]->tail.rot[1] -= fishes[i]->angle.z;
//			fishes[i]->tail.SetPosition(pos);
//			fishes[i]->moveAngle.z += fishes[i]->moveAngleStride;
//			fishes[i]->angle.z += fishes[i]->sign.z * fishes[i]->moveAngleStride / (180.0 / (fishes[i]->maxAngle * 2));
//			if (fishes[i]->moveAngle.z >= 360)
//				fishes[i]->moveAngle.z = fishes[i]->moveAngle.z - 360;
//			if (fishes[i]->angle.z >= fishes[i]->maxAngle) fishes[i]->sign.z = -1;
//			if (fishes[i]->angle.z <= -fishes[i]->maxAngle) fishes[i]->sign.z = 1;
//
//			if (abs(pos.x - fishes[i]->pos.x) > abs(fishes[i]->range))
//			{
//				fishes[i]->velocity = -1 * fishes[i]->velocity;
//				if (fishes[i]->rot.y == 180)
//					fishes[i]->rot.y = 0;
//				else if (fishes[i]->rot.y == 0)
//					fishes[i]->rot.y = 180;
//
//				fishes[i]->head.SetPosition(pos);
//				fishes[i]->body.SetPosition(pos);
//				fishes[i]->tail.SetPosition(pos);
//
//				float r[3] = { fishes[i]->rot.x, fishes[i]->rot.y, fishes[i]->rot.z };
//				fishes[i]->head.SetRotation(r);
//				fishes[i]->body.SetRotation(r);
//				fishes[i]->tail.SetRotation(r);
//			}
//
//		}
//	}
//}

void SceneManager::UpdateSwimmingFishWithoutFuckingAnimation()
{
	LOGE("XAGIAO17");
	if (fishes.size() > 0)
	{	
		LOGE("XAGIAO18");
		Vector3 pos;
		Matrix maTemp;
		btTransform trans;
		maTemp.SetIdentity();
		for (int i = 0; i < fishes.size(); i++)
		{
			//Update fish Head
			pos = fishes[i]->head.GetPosition();
			fishes[i]->head.rot[1] += fishes[i]->angle.x;
			pos.z += fishes[i]->dist*sin((fishes[i]->moveAngle.x)*3.141592 / 180);
			pos.x += fishes[i]->velocity;
			fishes[i]->head.SetPosition(pos);
			/*trans.setIdentity();
			trans.setOrigin(btVector3(pos.x,pos.y,pos.z));
			trans.setRotation(btQuaternion(0, 1, 0, fishes[i]->head.rot[1]));
			fishes[i]->head.rigidBody->setWorldTransform(trans);*/
			fishes[i]->head.SetViewMatrix(maView);
			fishes[i]->head.SetProjectionMatrix(maTemp.SetPerspective(m_FOV, 1, m_near, m_far));
			fishes[i]->head.Update();
			pos.z -= fishes[i]->dist*sin((fishes[i]->moveAngle.x)*3.141592 / 180);
			fishes[i]->head.rot[1] -= fishes[i]->angle.x;
			fishes[i]->head.SetPosition(pos);
			fishes[i]->moveAngle.x += fishes[i]->moveAngleStride;
			fishes[i]->angle.x += fishes[i]->sign.x * fishes[i]->moveAngleStride / (180.0 / (fishes[i]->maxAngle * 2));
			if (fishes[i]->moveAngle.x >= 360)
				fishes[i]->moveAngle.x = fishes[i]->moveAngle.x - 360;
			if (fishes[i]->angle.x >= fishes[i]->maxAngle) fishes[i]->sign.x = -1;
			if (fishes[i]->angle.x <= -fishes[i]->maxAngle) fishes[i]->sign.x = 1;
			//Update fish body
			pos = fishes[i]->body.GetPosition();
			fishes[i]->body.rot[1] += fishes[i]->angle.y;
			pos.z += fishes[i]->dist*sin((fishes[i]->moveAngle.y)*3.141592 / 180);
			pos.x += fishes[i]->velocity;
			fishes[i]->body.SetPosition(pos);
			/*trans.setIdentity();
			trans.setOrigin(btVector3(pos.x, pos.y, pos.z));
			trans.setRotation(btQuaternion(0, 1, 0, fishes[i]->body.rot[1]));
			fishes[i]->body.rigidBody->setWorldTransform(trans);*/
			fishes[i]->body.SetViewMatrix(maView);
			fishes[i]->body.SetProjectionMatrix(maTemp.SetPerspective(m_FOV, 1, m_near, m_far));
			fishes[i]->body.Update();
			pos.z -= fishes[i]->dist*sin((fishes[i]->moveAngle.y)*3.141592 / 180);
			fishes[i]->body.rot[1] -= fishes[i]->angle.y;
			fishes[i]->body.SetPosition(pos);
			fishes[i]->moveAngle.y += fishes[i]->moveAngleStride;
			fishes[i]->angle.y += fishes[i]->sign.y * fishes[i]->moveAngleStride / (180.0 / (fishes[i]->maxAngle * 2));
			if (fishes[i]->moveAngle.y >= 360)
				fishes[i]->moveAngle.y = fishes[i]->moveAngle.y - 360;
			if (fishes[i]->angle.y >= fishes[i]->maxAngle) fishes[i]->sign.y = -1;
			if (fishes[i]->angle.y <= -fishes[i]->maxAngle) fishes[i]->sign.y = 1;
			//Update fish tail
			pos = fishes[i]->tail.GetPosition();
			fishes[i]->tail.rot[1] += fishes[i]->angle.z;
			pos.z += fishes[i]->dist*sin((fishes[i]->moveAngle.z)*3.141592 / 180);
			//pos.z += fish[i]->GetWidth() / 2.0*sin((-moveAngle[0])*3.141592 / 180) + fish[i+1]->GetWidth() / 2.0*sin((-moveAngle[1])*3.141592 / 180);
			pos.x += fishes[i]->velocity;
			fishes[i]->tail.SetPosition(pos);
			/*trans.setIdentity();
			trans.setOrigin(btVector3(pos.x, pos.y, pos.z));
			trans.setRotation(btQuaternion(0, 1, 0, fishes[i]->body.rot[1]));
			fishes[i]->tail.rigidBody->setWorldTransform(trans);*/
			fishes[i]->tail.SetViewMatrix(maView);
			fishes[i]->tail.SetProjectionMatrix(maTemp.SetPerspective(m_FOV, 1, m_near, m_far));
			fishes[i]->tail.Update();
			pos.z -= fishes[i]->dist*sin((fishes[i]->moveAngle.z)*3.141592 / 180);
			fishes[i]->tail.rot[1] -= fishes[i]->angle.z;
			fishes[i]->tail.SetPosition(pos);
			fishes[i]->moveAngle.z += fishes[i]->moveAngleStride;
			fishes[i]->angle.z += fishes[i]->sign.z * fishes[i]->moveAngleStride / (180.0 / (fishes[i]->maxAngle * 2));
			if (fishes[i]->moveAngle.z >= 360)
				fishes[i]->moveAngle.z = fishes[i]->moveAngle.z - 360;
			if (fishes[i]->angle.z >= fishes[i]->maxAngle) fishes[i]->sign.z = -1;
			if (fishes[i]->angle.z <= -fishes[i]->maxAngle) fishes[i]->sign.z = 1;

			if (abs(pos.x - fishes[i]->pos.x) > abs(fishes[i]->range))
				{
								fishes[i]->velocity = -1 * fishes[i]->velocity;
								if (fishes[i]->rot.y == 180)
									fishes[i]->rot.y = 0;
								else if (fishes[i]->rot.y == 0)
									fishes[i]->rot.y = 180;
				
								fishes[i]->head.SetPosition(pos);
								fishes[i]->body.SetPosition(pos);
								fishes[i]->tail.SetPosition(pos);
				
								float r[3] = { fishes[i]->rot.x, fishes[i]->rot.y, fishes[i]->rot.z };
								fishes[i]->head.SetRotation(r);
								fishes[i]->body.SetRotation(r);
								fishes[i]->tail.SetRotation(r);
				}

		}
	}
	LOGE("XAGIAO19");
}

void SceneManager::JellyFish(int modelHeadID, int modelTailID, int textureID, Vector3 pos, float rotZ, float scale, float range)
{
	float r[3]; r[0] = 0; r[1] = 0; r[2] = rotZ;
	float s[3]; s[0] = scale; s[1] = scale; s[2] = scale;

	//JellyFishStruct* jelly = new JellyFishStruct();
	jellyfishes = new JellyFishStruct();
	jellyfishes->head.Init(modelHeadID, textureID, 0);
	jellyfishes->head.SetPosition(pos);
	jellyfishes->head.SetRotation(r);
	jellyfishes->head.SetScale(s);
	jellyfishes->head.rigidShape = 0;
	jellyfishes->head.rigidBody = AddTriangleMesh(jellyfishes->head, pos.x, pos.y, pos.z);
	//jelly->head.rigidBody = AddCylinder(jelly->head.GetWidth(), jelly->head.GetHeight(), jelly->head.GetThick(), jelly->pos.x, jelly->pos.y, jelly->pos.z, 0);
	//jelly->vRigidBodyID = vRigidBody.size() - 1;

	jellyfishes->rotZ = rotZ;
	jellyfishes->scale = scale;
	jellyfishes->pos = pos;
	jellyfishes->range = range;

	Matrix maTemp;
	maTemp.SetIdentity();
	Matrix ma;
	ma.SetIdentity();
	Vector3 vecTemp(0.0, 1.0, 0.0);
	LookAt(vCamPos, vLookAt, vecTemp, ma);
	jellyfishes->head.SetViewMatrix(ma);
	jellyfishes->head.SetProjectionMatrix(maTemp.SetPerspective(DEG2RAD(m_FOV), 1, m_near, m_far));

	//jellyfishes.push_back(jelly);
	//jelly = NULL; //
	//delete jelly; //
}

void SceneManager::UpdateJellyFish()
{
	LOGE("XAGIAO20");
	btTransform trans;
	//if (jellyfishes.size() > 0)
	//{
		//for (int i = 0; i < jellyfishes.size(); i++)
		//{
			static int sign = 4;
			float rotZ = jellyfishes->rotZ;
			float s = jellyfishes->scale;
			float ssXZ = 4.0;
			float ssY = 3.0;
			static float scale[3] = { s, s, s };
			float shrink = s / 200 * 3.0;// 0.003;
			float expand = shrink / 3.0*2.0;// 0.002;

			if ((scale[0] >= s) && (scale[2] >= s) && (scale[1] >= s) && sign == 1)
			{
				sign = 4;
			}
			else if ((scale[0] < (s / ssXZ)) && (scale[2] < (s / ssXZ)) && (scale[1] >= (s / ssY)) && sign == 4)
				sign = 3;
			else if ((scale[0] >= (s)) && (scale[2] >= (s)) && (scale[1] >= (s / ssY)) && sign == 3)
				sign = 2;
			else if ((scale[0] >= s) && (scale[2] >= s) && scale[1] < (s / ssY) && sign == 2)
				sign = 1;

			//cout << endl << scale[0] << " " << scale[2] << " " << scale[1] << " " << sign;

			switch (sign){
			case 4:
				scale[0] -= shrink;
				scale[2] -= shrink;
				scale[1] -= shrink / 3.0;
				jellyfishes->head.pos.y += jellyfishes->head.GetHeight() / 20.0*sin((rotZ + 90)*3.141592 / 180.0);
				jellyfishes->head.pos.x += jellyfishes->head.GetWidth() / 20.0*cos((rotZ + 90)*3.141592 / 180.0);
				break;
			case 3:
				scale[0] += expand;
				scale[2] += expand;
				scale[1] -= shrink / 3.0;
				jellyfishes->head.pos.y -= jellyfishes->head.GetHeight() / 75.0*sin((rotZ + 90)*3.141592 / 180.0);
				jellyfishes->head.pos.x -= jellyfishes->head.GetWidth() / 75.0*cos((rotZ + 90)*3.141592 / 180.0);
				break;
			case 2:
				scale[0] += expand / 3.0;
				scale[2] += expand / 3.0;
				scale[1] -= shrink / 3.0;
				jellyfishes->head.pos.y -= jellyfishes->head.GetHeight() / 75.0*sin((rotZ + 90)*3.141592 / 180.0);
				jellyfishes->head.pos.x -= jellyfishes->head.GetWidth() / 75.0*cos((rotZ + 90)*3.141592 / 180.0);
				break;
			case 1:
				scale[1] += expand*2.0;
				jellyfishes->head.pos.y -= jellyfishes->head.GetHeight() / 45.0*sin((rotZ + 90)*3.141592 / 180.0);
				jellyfishes->head.pos.x -= jellyfishes->head.GetWidth() / 45.0*cos((rotZ + 90)*3.141592 / 180.0);
				break;
			default:
				break;
			}

			jellyfishes->head.SetScale(scale);
			jellyfishes->head.SetViewMatrix(maView);
			Matrix maTemp;
			maTemp.SetIdentity();
			jellyfishes->head.SetProjectionMatrix(maTemp.SetPerspective(m_FOV, 1, m_near, m_far));

			trans.setIdentity();
			trans.setOrigin(btVector3(jellyfishes->head.pos.x, jellyfishes->head.pos.y, jellyfishes->head.pos.z));
			jellyfishes->head.rigidBody->setWorldTransform(trans);
			/*sceneWorld->removeRigidBody(jellyfishes[i]->head.rigidBody);
			delete vRigidBody.at(jellyfishes[i]->vRigidBodyID);
			vRigidBody.at(jellyfishes[i]->vRigidBodyID) = NULL;
			vRigidBody.erase(vRigidBody.begin()+jellyfishes[i]->vRigidBodyID);
			jellyfishes[i]->head.rigidBody = AddCylinder(jellyfishes[i]->head.GetWidth(), jellyfishes[i]->head.GetHeight(), jellyfishes[i]->head.GetThick(), jellyfishes[i]->head.pos.x, jellyfishes[i]->head.pos.y, jellyfishes[i]->head.pos.z, 0);*/

			jellyfishes->head.Update();

			if (sqrt((jellyfishes->head.pos.x - jellyfishes->pos.x)*(jellyfishes->head.pos.x - jellyfishes->pos.x) + (jellyfishes->head.pos.y - jellyfishes->pos.y)*(jellyfishes->head.pos.y - jellyfishes->pos.y)) > jellyfishes->range)
				jellyfishes->head.pos = jellyfishes->pos;
		//}
	//}
	LOGE("XAGIAO21");
}

void SceneManager::Draw()
{
	LOGE("Scene->Draw");
	float part;
	for (int i = 0; i < modelCount; i++)
	{
		listObject[i].Draw();
	}

	for (int i = 0; i < bubble.size(); i++)
		bubble[i].Draw();

	for (int i = 0; i < modelCount2D; i++){
		object2D[i].Draw();
		if (i == 1){
			part=object2D[i].GetWidth() / 3;
		}
	}

	for (int i = 0; i < fishes.size(); i++){
		fishes[i]->head.Draw();
		fishes[i]->body.Draw();
		fishes[i]->tail.Draw();
	}

	//for (int i = 0; i < jellyfishes.size(); i++){
		jellyfishes->head.Draw();
	//}
	water.Draw();
	LOGE("Scene->Draw1");
}

void SceneManager::Update()
{
	LOGE("XAGIAO10");
	//int currentDuration;
	int success=5;
	if (levelID == 1)
		success = 2;
	if (ringCount == success) {
		isActive = false;
		cout << endl << "YOU WIN " << levelID;
		if (currentDuration <= sceneDuration / 3){
			Menu::getInstance()->winObjects[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(64);
			Menu::getInstance()->save.save[levelID-1] = 3;			
			Menu::getInstance()->missionObjects[levelID + 3].textureID = ResourceManager::getInstance()->m_vTextureID.at(64);
			if (levelID <= 3){
				if ((levelID + 1)==2)
					Menu::getInstance()->missionObjects[levelID + 1].textureID = ResourceManager::getInstance()->m_vTextureID.at(49);
				else if ((levelID + 1) == 3)
					Menu::getInstance()->missionObjects[levelID + 1].textureID = ResourceManager::getInstance()->m_vTextureID.at(51);
			}
			if (Menu::getInstance()->save.save[levelID] < 0)
				Menu::getInstance()->save.save[levelID] = 0;
			Menu::getInstance()->save.Saved();
		}
		else if (currentDuration <= sceneDuration * 2 / 3){
			Menu::getInstance()->winObjects[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(63);
			if (Menu::getInstance()->save.save[levelID - 1] < 2){
				Menu::getInstance()->save.save[levelID - 1] = 2;				
				Menu::getInstance()->missionObjects[levelID + 3].textureID = ResourceManager::getInstance()->m_vTextureID.at(63);
				if (Menu::getInstance()->save.save[levelID] < 0)
					Menu::getInstance()->save.save[levelID] = 0;
				if (levelID <= 3){
					if ((levelID + 1) == 2)
						Menu::getInstance()->missionObjects[levelID + 1].textureID = ResourceManager::getInstance()->m_vTextureID.at(49);
					else if ((levelID + 1) == 3)
						Menu::getInstance()->missionObjects[levelID + 1].textureID = ResourceManager::getInstance()->m_vTextureID.at(51);
				}
				Menu::getInstance()->save.Saved();
			}
		}
		else{
			Menu::getInstance()->winObjects[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(39);
			Menu::getInstance()->save.save[levelID - 1] = 1;			
			Menu::getInstance()->missionObjects[levelID + 3].textureID = ResourceManager::getInstance()->m_vTextureID.at(39);
			if (Menu::getInstance()->save.save[levelID] < 0)
				Menu::getInstance()->save.save[levelID] = 0;
			if (levelID <= 3){
				if ((levelID + 1) == 2)
					Menu::getInstance()->missionObjects[levelID + 1].textureID = ResourceManager::getInstance()->m_vTextureID.at(49);
				else if ((levelID + 1) == 3)
					Menu::getInstance()->missionObjects[levelID + 1].textureID = ResourceManager::getInstance()->m_vTextureID.at(51);
			}
			Menu::getInstance()->save.Saved();
		}
		Menu::getInstance()->displayWin=true;
	}
	LOGE("XAGIAO11");
	if (isActive) {
		if (levelID != 0){
			currentDuration = ((int)(clock() - startTime)) / CLOCKS_PER_SEC;
			if (currentDuration == sceneDuration / 3)
				object2D[6].pos.y = 20;
			if (currentDuration == sceneDuration*2/3)
				object2D[7].pos.y = 20;
			if (currentDuration == sceneDuration)
				object2D[8].pos.y = 20;
			if (currentDuration >= sceneDuration){
				isActive = false;
				Menu::getInstance()->save.save[levelID - 1] = 0;
				Menu::getInstance()->displayLose = true;
			}
			object2D[0].scale[0] = (((float)(sceneDuration - currentDuration)) / (float)(sceneDuration)) * object2D[1].scale[0];
		}
		LOGE("XAGIAO12");
		Matrix maTemp;
		btTransform trans;
		sceneWorld->stepSimulation(1 / 60.0f, 10);
		float mat[16];
		camera.Update();
		for (int i = 0; i < modelCount; i++)
		{

			listObject[i].SetViewMatrix(maView);
			listObject[i].SetProjectionMatrix(maProjection);
			if (listObject[i].rigidShape != 0)
			{
				(listObject[i].rigidBody)->getMotionState()->getWorldTransform(trans);
				trans.getOpenGLMatrix(mat);
				for (int j = 0; j < 16; j++)
				{
					listObject[i].maRigidBody.m[j / 4][j % 4] = mat[j];
				}
			}

			listObject[i].Update();
		}
		LOGE("XAGIAO13");
		for (int i = 0; i < bubble.size(); i++)
		{
			bubble[i].pos.y = bubble[i].pos.y + 0.06;
			bubble[i].pos.x = bubble[i].pos.x + 0.04*(rand() % 3 - 1)*(rand() % 100) / 100.0;
			bubble[i].pos.z = bubble[i].pos.z + 0.04*(rand() % 3 - 1)*(rand() % 100) / 100.0;
			bubble[i].SetPosition(bubble[i].pos);
			bubble[i].Update();
			if (bubble[i].pos.y > 8)
			{
				/*bubble.at(i) = NULL;
				delete bubble.at(i);*/
				bubble.erase(bubble.begin() + i);
			}
		}		
		LOGE("XAGIAO14");
		for (int i = 0; i < modelCount2D; i++){
			object2D[i].SetViewMatrix(maView);
			object2D[i].SetProjectionMatrix(maProjection);						
			object2D[i].Update();
		}
		LOGE("XAGIAO15");
	}
	LOGE("XAGIAO16");
	UpdateSwimmingFishWithoutFuckingAnimation();
	UpdateJellyFish();
	water.SetViewMatrix(maView);
	water.SetProjectionMatrix(maProjection);
	water.Update();	
	TouchUpdate();
	LOGE("XAGIAO20");
}

void SceneManager::TouchUpdate(){
	PointerEvent touch = INPUT_MGR->getCurPointerEvent();
	switch (touch.state)
	{
	case E_POINTER_PRESSSED:
		isPressed = true;
		TouchControl(touch.posX, touch.posY, 0);
		break;
	case E_POINTER_MOVED:
		break;
	case E_POINTER_RELEASED:
		if (isPressed) {
			LOGE("HIHI1");
			TouchControl(touch.posX, touch.posY, 1);
			LOGE("HIHI2");
			isPressed = false;
		}
		break;
	case E_POINTER_NONE:
		break;
	}
}

void SceneManager::AddBubbles(int num, Vector3 pos, float radCanon, float minScale, float maxScale)
{

	Matrix maTemp;
	maTemp.SetIdentity();
	if (pos.x > 0)
		pos.x += 0.2;
	else
		pos.x -= 0.2;
	radCanon -= 0.2;
	
	for (int i = 0; i < num; i++)
	{
		Object2D bub;		
		bub.Init(bubbleModelID, bubbleTextureID, 0);
	
		float s = minScale + (maxScale - minScale)*(rand() % 100) / 100.0;
		float scale[3] = { s, s, s };
		bub.SetScale(scale);
		float x = pos.x + radCanon*(-1 * rand() % 2)*(rand() % 100) / 100.0;
		float y = pos.y + radCanon*(-1 * rand() % 2)*(rand() % 100) / 100.0 + 1.5;
		//float z = pos.z + radCanon*(-1 * rand() % 2)*(rand() % 100) / 100.0;
		bub.SetPosition(Vector3(x, y, 1.0));
		/*Vector3 vTemp(0.0, 1.0, 0.0);
		LookAt(vCamPos, vLookAt, vTemp, maTemp);
		bub.SetViewMatrix(maTemp);
		bub.SetProjectionMatrix(maTemp.SetPerspective(DEG2RAD(m_FOV), 1, m_near, m_far));*/
		bub.SetViewMatrix(maView);
		bub.SetProjectionMatrix(maProjection);
		bubble.push_back(bub);
	}
	//delete bub;
	//bub = NULL;
}

void SceneManager::SetCameraPosition(Vector3 vCameraPos) {
	vCamPos = vCameraPos;
	camera.SetPosition(vCameraPos);
}

//Vector3 SceneManager::GetCameraPosition() {
//	return camera.GetPosition();
//}

void SceneManager::SetObjectPosition(int iObjectID, Vector3 vObjectPos) {
	listObject[iObjectID].SetPosition(vObjectPos);
}

void SceneManager::SetObjectRotation(int iObjectID, float zAngle, float xAngle, float yAngle) {
	float rot[3];
	rot[0] = zAngle;
	rot[1] = xAngle;
	rot[2] = yAngle;
	listObject[iObjectID].SetRotation(rot);
}

void SceneManager::SetObjectScale(int iObjectID, float xScale, float yScale, float zScale) {
	float scale[3];
	scale[0] = xScale;
	scale[1] = yScale;
	scale[2] = zScale;
	listObject[iObjectID].SetScale(scale);
}

void SceneManager::RandomAirCanon(Vector3 pos, float rad, float height, Vector3 force)
{
	LOGE("DM1");
	srand(time(0));
	for (int i = 0; i < modelCount; i++)
	{
		LOGE("DM2");
		if (listObject[i].rigidShape == 0 || listObject[i].rigidShape == 100) 
			continue;
		else
		{
			LOGE("DM3");
			btTransform trans;
			float mat[16];
			LOGE("DM4");
			listObject[i].rigidBody->getMotionState()->getWorldTransform(trans);
			btVector3 objOrigin = trans.getOrigin();
			float disOrigin = sqrt((pos.x - objOrigin.getX())*(pos.x - objOrigin.getX()) + (pos.z - objOrigin.getZ())*(pos.z - objOrigin.getZ()));//khoang cach tu tam sung den tâm vat the theo mat oxz
			LOGE("DM5");
			if (objOrigin.getY() <= pos.y || objOrigin.getY() >= (pos.y + height)) 
				continue;
			else
			{
				LOGE("DM6");
				if (disOrigin > rad) 
					continue;
				else
				{
					LOGE("DM7");
					float k = (height - (objOrigin.getY() - pos.y)) / height; //lực tác động,tỉ lệ càng lớn lực tác động càng yếu.
					float relPosX = listObject[i].GetWidth()*(-1 * rand() % 2)*(rand() % 30) / 100.0;
					float relPosZ = listObject[i].GetThick()*(-1 * rand() % 2)*(rand()*rand() % 30) / 100.0;
					//listObject[i].rigidBody->setLinearVelocity(btVector3(force.x*k, force.y*k, force.z*k));
					listObject[i].rigidBody->applyImpulse(btVector3(force.x*k, force.y*k, force.z*k), btVector3(relPosX, 0, relPosZ));
					LOGE("DM8");
				}
			}
		}
	}
	LOGE("DM9");
	AddBubbles(5, pos, rad, 0.05, 0.15);
	LOGE("DM10");
}

btRigidBody* SceneManager::AddSphere(float rad, float x, float y, float z, float mass)
{
#undef new
#undef delete
	btTransform t;
	t.setIdentity();
	//trong tam cua vat the
	t.setOrigin(btVector3(x, y, z));
	btSphereShape* sphere = new btSphereShape(rad/2);
	btVector3 inertia(0, 0, 0);
	if (mass != 0)
	{
		sphere->calculateLocalInertia(mass, inertia);
	}	
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, sphere, inertia);
	btRigidBody* body = new btRigidBody(info);
	sceneWorld->addRigidBody(body);
	vRigidBody.push_back(body);
	motion = NULL; //
	delete motion; //
	cout << endl << "SPHERE";
	return body;
}

btRigidBody* SceneManager::AddBox(float width, float height, float thick, float x, float y, float z, float mass)
{
#undef new
#undef delete
	btTransform t;
	t.setIdentity();
	//trong tam cua vat the
	t.setOrigin(btVector3(x, y, z));
	btBoxShape* box = new btBoxShape(btVector3(width / 2.0, height / 2.0, thick / 2.0));
	btVector3 inertia(0, 0, 0);
	if (mass != 0)
	{
		box->calculateLocalInertia(mass, inertia);
	}
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box, inertia);
	btRigidBody* body = new btRigidBody(info);
	sceneWorld->addRigidBody(body);
	vRigidBody.push_back(body);
	vCollisionShape.push_back(box);
	motion = NULL; //
	delete motion; //
	cout << endl << "BOX";
	return body;
}

btRigidBody* SceneManager::AddCylinder(float width, float height, float thick, float x, float y, float z, float mass)
{
#undef new
#undef delete
	btTransform t;
	t.setIdentity();
	//trong tam cua vat the
	t.setOrigin(btVector3(x, y, z));
	//t.setRotation(btQuaternion(0,0,90));
	btCylinderShape* cylinder = new btCylinderShape(btVector3(width / 2.0, height / 2.0, thick / 2.0));
	
	btVector3 inertia(0, 0, 0);
	if (mass != 0)
	{
		cylinder->calculateLocalInertia(mass, inertia);
	}
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cylinder, inertia);
	btRigidBody* body = new btRigidBody(info);
	sceneWorld->addRigidBody(body);
	vRigidBody.push_back(body);
	motion = NULL; //
	delete motion; //
	cout << endl << "CYLINDER";
	return body;
}

btRigidBody* SceneManager::AddWall(float upX, float upY, float upZ, float x, float y, float z) {
#undef new
#undef delete
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(0, 0, 0));
	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(upX, upY, upZ), 0);
	btMotionState*motion = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);
	btRigidBody* groundBody = new btRigidBody(info);
	sceneWorld->addRigidBody(groundBody);
	vRigidBody.push_back(groundBody);
	vCollisionShape.push_back(plane);
	motion = NULL; //
	delete motion; //
	plane = NULL; //
	delete plane; //
	return groundBody;
}

btRigidBody* SceneManager::AddRing(float rad, float thick, float x, float y, float z, float mass)
{
	btTransform t;
	btCompoundShape *comShape = new btCompoundShape;

	/*btSphereShape* sphere = new btSphereShape(thick*2.0f / 3.0);*/
	btSphereShape* sphere = new btSphereShape(thick/1.2f);

	int segment = 36;
	float *masses=new float [segment];

	for (int i = 0; i < segment; i++)
	{
		t.setIdentity();
		t.setOrigin(btVector3((rad - thick / 2.0)*sin(3.14159265359 / 180.0 * 360.0/segment * i), 0, (rad - thick / 2.0)*cos(3.14159265359 / 180.0*360/segment  * i)));
		comShape->addChildShape(t, sphere);
		masses[i] = mass / segment;
	}

	btVector3 inertia(0, 0, 0);
	t.setIdentity();
	comShape->calculatePrincipalAxisTransform(masses, t, inertia);
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));

	btMotionState* motion = new btDefaultMotionState(t);  //set the position (and motion)
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, comShape, inertia);  //create the constructioninfo, you can create multiple bodies with the same info
	btRigidBody* body = new btRigidBody(info);    //let's create the body itself
	//btRigidBody* hole = AddCapsule(0.001, (rad - thick), x, y, z, mass);
	//hole->setUserIndex(1000);

	//listObject[modelID].rigidHole = hole;
	//body->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	sceneWorld->addRigidBody(body);  //and let the world know about it
	//sceneWorld->addRigidBody(hole);
	vRigidBody.push_back(body); //to be easier to clean, I store them a vector
	//vRigidBody.push_back(hole);
	delete[] masses;
	sphere = NULL; //
	delete sphere; //
	comShape = NULL; //
	delete comShape; //
	motion = NULL; //
	delete motion; //
	return body;
}

//btRigidBody* SceneManager::AddRing(float rad, float thick, float x, float y, float z, float mass)
//{
//	btTransform t;
//	btCompoundShape *comShape = new btCompoundShape;
//	btBoxShape *boxX = new btBoxShape(btVector3(rad, thick / 2.0, thick / 2.0));
//	btBoxShape *boxZ = new btBoxShape(btVector3(thick / 2.0, thick / 2.0, rad));
//	float masses[4] = { mass / 4.0, mass / 4.0, mass / 4.0, mass / 4.0, };
//
//	t.setIdentity();
//	t.setOrigin(btVector3(rad - thick / 2.0, 0, 0));
//	comShape->addChildShape(t, boxZ);
//
//	t.setIdentity();
//	t.setOrigin(btVector3(-(rad - thick / 2.0), 0, 0));
//	comShape->addChildShape(t, boxZ);
//
//	t.setIdentity();
//	t.setOrigin(btVector3(0, 0, rad - thick / 2.0));
//	comShape->addChildShape(t, boxX);
//
//	t.setIdentity();
//	t.setOrigin(btVector3(0, 0, -(rad - thick / 2.0)));
//	comShape->addChildShape(t, boxX);
//
//	btVector3 inertia(0, 0, 0);
//	t.setIdentity();
//	comShape->calculatePrincipalAxisTransform(masses, t, inertia);
//	t.setIdentity();
//	t.setOrigin(btVector3(x, y, z));
//
//	btMotionState* motion = new btDefaultMotionState(t);  //set the position (and motion)
//	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, comShape, inertia);  //create the constructioninfo, you can create multiple bodies with the same info
//	btRigidBody* body = new btRigidBody(info);    //let's create the body itself
//
//
//	sceneWorld->addRigidBody(body);
//	vRigidBody.push_back(body);
//	boxZ = NULL; comShape = NULL; motion = NULL; boxX = NULL;
//	return body;
//
//}


btRigidBody* SceneManager::AddCapsule(float height, float rad, float x, float y, float z, float mass)
{
#undef new
#undef delete
	btTransform t;
	t.setIdentity();
	//trong tam cua vat the
	t.setOrigin(btVector3(x, y, z));
	btCapsuleShape* capsule = new btCapsuleShape(rad, height);
	btVector3 inertia(0, 0, 0);
	if (mass != 0)
	{
		capsule->calculateLocalInertia(mass, inertia);
	}
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, capsule, inertia);
	btRigidBody* body = new btRigidBody(info);
	sceneWorld->addRigidBody(body);
	vRigidBody.push_back(body);
	motion = NULL; //
	delete motion; //
	capsule = NULL; //
	delete capsule; //
	return body;
}

btVector3 SceneManager::VectorToBullet(Vector3 vec) {
	btVector3 bVector;
	bVector.setX(vec.x);
	bVector.setY(vec.y);
	bVector.setZ(vec.z);
	return bVector;
}

Vector3 SceneManager::CalPoint(Vector3 vec, Matrix ma) {
	Vector3 result;
	float w;
	w = vec.x * ma.m[0][3] + vec.y * ma.m[1][3] + vec.z * ma.m[2][3] + ma.m[3][3];
	result.x = (vec.x * ma.m[0][0] + vec.y * ma.m[1][0] + vec.z * ma.m[2][0] + ma.m[3][0]) / w;
	result.y = (vec.x * ma.m[0][1] + vec.y * ma.m[1][1] + vec.z * ma.m[2][1] + ma.m[3][1]) / w;
	result.z = (vec.x * ma.m[0][2] + vec.y * ma.m[1][2] + vec.z * ma.m[2][2] + ma.m[3][2]) / w;
	return result;
}

btRigidBody* SceneManager::AddTriangleMesh(Object obj, float x, float y, float z) {
	btTriangleMesh* trimesh = new btTriangleMesh();

	Matrix maRotate, maRotateZ, maRotateX, maRotateY, maScale, maTemp;

	maRotateX.SetRotationX(DEG2RAD(obj.rot[0]));
	maRotateY.SetRotationY(DEG2RAD(obj.rot[1]));
	maRotateZ.SetRotationZ(DEG2RAD(obj.rot[2]));

	maRotate = maRotateY * maRotateX * maRotateZ;

	maScale.SetScale(obj.scale[0], obj.scale[1], obj.scale[2]);

	maTemp = maScale * maRotate;

	for (int i = 0; i < obj.modelData->numIndices / 3; i++) {

		//trimesh->addTriangle(BulletVector(obj.modelData->verticesData[obj.modelData->indicesData[i*3]].pos), BulletVector(obj.modelData->verticesData[obj.modelData->indicesData[i * 3 + 1]].pos), BulletVector(obj.modelData->verticesData[obj.modelData->indicesData[i * 3 + 2]].pos));
		trimesh->addTriangle(VectorToBullet(CalPoint(obj.modelData->verticesData[obj.modelData->indicesData[i * 3]].pos, maTemp)), VectorToBullet(CalPoint(obj.modelData->verticesData[obj.modelData->indicesData[i * 3 + 1]].pos, maTemp)), VectorToBullet(CalPoint(obj.modelData->verticesData[obj.modelData->indicesData[i * 3 + 2]].pos, maTemp)));
	}

	bool useQuantizedBvhTree = true;
	btCollisionShape* trimeshShape = new btBvhTriangleMeshShape(trimesh, useQuantizedBvhTree);

	btTransform t;
	t.setIdentity();
	//trong tam cua vat the
	t.setOrigin(btVector3(x, y, z));

	btVector3 inertia(0, 0, 0);
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(0, motion, trimeshShape, inertia);
	btRigidBody* body = new btRigidBody(info);
	
	sceneWorld->addRigidBody(body);
	vRigidBody.push_back(body);

	motion = NULL; //
	delete motion; //
	trimesh = NULL; //
	delete trimesh; //
	trimeshShape = NULL; //
	delete trimeshShape; //

	return body;
}

void SceneManager::LookAt(Vector3 vEye, Vector3 vLook, Vector3 vUp, Matrix& maResult)
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

void SceneManager::ResetScene(){
	for (int i = 0; i < vRigidBody.size(); i++)
	{
		sceneWorld->removeRigidBody(vRigidBody.at(i));
		delete vRigidBody.at(i)->getMotionState();
		delete vRigidBody.at(i);
	}
	vRigidBody.clear();
	for (int i = 0; i < bubble.size(); i++) {
		bubble.erase(bubble.begin() + i);
	}
	bubble.clear();
	for (int i = 0; i < fishes.size(); i++)
	{
		delete fishes[i];
		fishes.erase(fishes.begin() + i);
	}
	fishes.clear();
	//for (int i = 0; i < jellyfishes.size(); i++)
	//{
		delete jellyfishes;
	//	jellyfishes.erase(jellyfishes.begin() + i);
	//}
	//jellyfishes.clear();
	isActive = false;
	Menu::getInstance()->displayMission = false;
	Menu::getInstance()->displayLose = false;
	Menu::getInstance()->displayWin = false;
	Menu::getInstance()->displayPause = false;
	delete broadphase;
	delete collisionConfiguration;
	delete dispatcher;
	delete solver;
	delete sceneWorld;
	delete[] object2D;
	delete[] listObject;
}

void SceneManager::NextLevel() {
	LOGE("Next Level!");
	if (levelID<3)
		levelID++;
	if (levelID <= 3) {
		ResetScene();
		ReadScene();
	}
}

SceneManager::~SceneManager(){
	ResetScene();
	m_Instance = NULL;
}

float SceneManager::PointToLineDistance(Vector3 A, Vector3 B, Vector3 P) {
	Vector3 AB = B - A;
	Vector3 AP = P - A;

	double projection = AP.Dot(AB) / AB.Dot(AB);
	Vector3 nearPoint = A + AB * projection;

	float len;
	(nearPoint - P).Length(len);

	return len;
}

Vector3 SceneManager::BulletToVector(const btVector3 &vechihi) {
	Vector3 vector;
	vector.x = vechihi.getX();
	vector.y = vechihi.getY();
	vector.z = vechihi.getZ();
	return vector;
}

void SceneManager::TouchControl(int x, int y, int state){
	LOGE("HIHI3");
	Vector3 worldCoordStart;
	Vector3 worldCoordEnd;
	
	worldCoordStart = UnProject(Vector3(x, y, 0.0));
	worldCoordEnd = UnProject(Vector3(x, y, 1.0));
	LOGE("HIHI4");
	LOGE("huhu1");
	if (levelID == 0) {
		//Menu		
		LOGE("huhu2");
		listObject[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(25);
		LOGE("huhu3");
		if (PointToLineDistance(worldCoordStart, worldCoordEnd, BulletToVector(listObject[1].rigidBody->getWorldTransform().getOrigin())) < listObject[1].GetWidth() / 2 && !Menu::getInstance()->displayMission &&
			!Menu::getInstance()->displayTurtorial && !Menu::getInstance()->displayCredit && !Menu::getInstance()->displayStage) {
			LOGE("huhu4");
			if (state == 1){
				LOGE("huhu5");
				listObject[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(25);
				Menu::getInstance()->displayMission = true;
				delay = clock();
				LOGE("huhu8");
			}
			else{
				LOGE("huhu6");
				listObject[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(11);				
				LOGE("huhu7");
			}
		}
		LOGE("huhu9");
		listObject[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(24);
		LOGE("huhu10");
		if (PointToLineDistance(worldCoordStart, worldCoordEnd, BulletToVector(listObject[2].rigidBody->getWorldTransform().getOrigin())) < listObject[2].GetWidth() / 2 && !Menu::getInstance()->displayMission &&
			!Menu::getInstance()->displayTurtorial && !Menu::getInstance()->displayCredit && !Menu::getInstance()->displayStage) {
			LOGE("huhu11");
			if (state == 1){
				LOGE("huhu12");
				listObject[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(24);
				Menu::getInstance()->displayTurtorial = true;
				delay = clock();
				LOGE("huhu13");
			}
			else{
				LOGE("huhu14");
				listObject[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(14);
				LOGE("huhu15");
			}
		}
		LOGE("huhu16");
		listObject[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(23);
		LOGE("huhu17");
		if (PointToLineDistance(worldCoordStart, worldCoordEnd, BulletToVector(listObject[3].rigidBody->getWorldTransform().getOrigin())) < listObject[3].GetWidth() / 2 && !Menu::getInstance()->displayMission &&
			!Menu::getInstance()->displayTurtorial && !Menu::getInstance()->displayCredit && !Menu::getInstance()->displayStage) {
			LOGE("huhu17");
			if (state == 1){
				LOGE("huhu18");
				listObject[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(23);
				Menu::getInstance()->displayStage = true;
				delay = clock();
				LOGE("huhu19");
			}
			else{
				LOGE("huhu20");
				listObject[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(13);
				LOGE("huhu21");
			}
		}
		LOGE("huhu22");
		listObject[4].textureID = ResourceManager::getInstance()->m_vTextureID.at(22);
		if (PointToLineDistance(worldCoordStart, worldCoordEnd, BulletToVector(listObject[4].rigidBody->getWorldTransform().getOrigin())) < listObject[4].GetWidth() / 2 && !Menu::getInstance()->displayMission &&
			!Menu::getInstance()->displayTurtorial && !Menu::getInstance()->displayCredit && !Menu::getInstance()->displayStage) {
			if (state == 1){
				LOGE("huhu23");
				listObject[4].textureID = ResourceManager::getInstance()->m_vTextureID.at(22);
				Menu::getInstance()->displayCredit = true;
				delay = clock();
			}
			else{
				LOGE("huhu24");
				listObject[4].textureID = ResourceManager::getInstance()->m_vTextureID.at(9);
			}
		}
		//Stage
		if (((float)(clock() - delay)) / CLOCKS_PER_SEC >= 0.1){
			if (PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->missionObjects[1].pos) < Menu::getInstance()->missionObjects[1].GetWidth() / 2 && Menu::getInstance()->displayMission == true){
				NextLevel();
			}
			if (PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->missionObjects[2].pos) < Menu::getInstance()->missionObjects[2].GetWidth() / 2 && Menu::getInstance()->displayMission == true && Menu::getInstance()->save.save[1] >= 0){
				levelID = 2;
				ResetScene();
				ReadScene();
			}
			if (PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->missionObjects[3].pos) < Menu::getInstance()->missionObjects[3].GetWidth() / 2 && Menu::getInstance()->displayMission == true && Menu::getInstance()->save.save[2] >= 0){
				levelID = 3;
				ResetScene();
				ReadScene();
			}
			
			Menu::getInstance()->creditObject[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(16);
			if (PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->creditObject[1].pos) < Menu::getInstance()->creditObject[1].GetHeight() / 2 && Menu::getInstance()->displayCredit){
				if (state == 1){
					Menu::getInstance()->creditObject[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(16);
					Menu::getInstance()->displayCredit = false;
				}
				else{
					LOGE("huhu27");
					Menu::getInstance()->creditObject[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(58);
				}
			}
			//Turtorial next
			Menu::getInstance()->turtorObject[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(53);
			if (PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->turtorObject[2].pos) < Menu::getInstance()->turtorObject[2].GetHeight() && Menu::getInstance()->displayTurtorial){
				if (state == 1){
					Menu::getInstance()->turtorObject[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(53);
					Menu::getInstance()->turtorObject[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(6);
				}
				else
					Menu::getInstance()->turtorObject[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(54);
			}
			Menu::getInstance()->turtorObject[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(16);
			if (PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->turtorObject[3].pos) < Menu::getInstance()->turtorObject[3].GetHeight() && Menu::getInstance()->displayTurtorial){
				if (state == 1){
					Menu::getInstance()->turtorObject[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(16);
					Menu::getInstance()->turtorObject[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(5);
					Menu::getInstance()->displayTurtorial = false;
				}
				else{
					Menu::getInstance()->turtorObject[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(58);
				}
			}

			//In Stage
			Menu::getInstance()->stageObject[4].textureID = ResourceManager::getInstance()->m_vTextureID.at(16);
			if (PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->stageObject[4].pos) < Menu::getInstance()->stageObject[4].GetHeight() && Menu::getInstance()->displayStage){
				if (state == 1){
					Menu::getInstance()->stageObject[4].textureID = ResourceManager::getInstance()->m_vTextureID.at(16);
					Menu::getInstance()->stageObject[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(18);
					Menu::getInstance()->displayStage = false;
				}
				else{
					Menu::getInstance()->stageObject[4].textureID = ResourceManager::getInstance()->m_vTextureID.at(58);
				}
			}

			Menu::getInstance()->stageObject[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(53);
			if (PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->stageObject[2].pos) < Menu::getInstance()->stageObject[2].GetHeight() && Menu::getInstance()->displayStage){
				if (state == 1){
					Menu::getInstance()->stageObject[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(53);					
					if (level < 20){
						level++;						
					}
					Menu::getInstance()->stageObject[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(level);
				}
				else{
					Menu::getInstance()->stageObject[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(54);
				}
			}

			Menu::getInstance()->stageObject[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(12);
			if (PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->stageObject[3].pos) < Menu::getInstance()->stageObject[3].GetHeight() && Menu::getInstance()->displayStage){
				if (state == 1){
					Menu::getInstance()->stageObject[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(12);
					if (level > 18){
						level--;						
					}
					Menu::getInstance()->stageObject[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(level);
				}
				else{
					Menu::getInstance()->stageObject[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(17);
				}
			}
		}
		LOGE("HIHI5");
	}	

	else {
		//Canon R
		if (PointToLineDistance(worldCoordStart, worldCoordEnd, object2D[2].pos) < object2D[2].GetWidth()) {
			RandomAirCanon(Vector3(3.2, 0, 1), 1, 9, Vector3(0, 1, 0));
			LOGE("HIHI6");
		}
		//Canon L
		if (PointToLineDistance(worldCoordStart, worldCoordEnd, object2D[3].pos) < object2D[3].GetWidth()) {
			RandomAirCanon(Vector3(-3.2, 0, 1), 1, 9, Vector3(0, 1, 0));
			LOGE("HIHI7");
		}
		//Pause		
		if (PointToLineDistance(worldCoordStart, worldCoordEnd, object2D[4].pos) < object2D[4].GetWidth() / 1.5  && levelID != 0) {
			if (!Menu::getInstance()->displayLose && !Menu::getInstance()->displayWin){
				if (state == 1){
					object2D[4].textureID = ResourceManager::getInstance()->m_vTextureID.at(10);
					isActive = false;
					Menu::getInstance()->displayPause = true;
				}				
			}
		}
		//Resume
		Menu::getInstance()->pauseObjects[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(3);
		if (PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->pauseObjects[1].pos) < Menu::getInstance()->pauseObjects[1].GetHeight() && levelID != 0) {
			if (!Menu::getInstance()->displayLose || !Menu::getInstance()->displayWin){
				if (state == 1) {
					Menu::getInstance()->pauseObjects[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(3);
					isActive = true;
					Menu::getInstance()->displayPause = false;
					object2D[4].textureID = ResourceManager::getInstance()->m_vTextureID.at(52);
				}
				else
					Menu::getInstance()->pauseObjects[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(4);
			}
		}
		//Sound
		/*if (PointToLineDistance(worldCoordStart, worldCoordEnd, object2D[5].pos) < object2D[5].GetWidth() / 2 && levelID != 0 && !Menu::getInstance()->displayPause) {
			if (object2D[5].isOn){
				object2D[5].textureID = ResourceManager::getInstance()->m_vTextureID.at(70);
				object2D[5].isOn = false;
			}
			else{
				object2D[5].textureID = ResourceManager::getInstance()->m_vTextureID.at(71);
				object2D[5].isOn = true;
			}
		}*/

		//Next
		Menu::getInstance()->winObjects[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(53);
		if (PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->winObjects[1].pos) < Menu::getInstance()->winObjects[1].GetHeight() && Menu::getInstance()->displayWin){
			if (state == 1) {
				Menu::getInstance()->winObjects[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(53);
				NextLevel();
			}
			else
				Menu::getInstance()->winObjects[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(54);
		}
		
		//restart
		Menu::getInstance()->pauseObjects[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(1);
		if ((PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->pauseObjects[2].pos) < Menu::getInstance()->pauseObjects[2].GetHeight() && Menu::getInstance()->displayPause) && levelID != 0){
			if (state == 1) {
				Menu::getInstance()->pauseObjects[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(1);
				ResetScene();
				ReadScene();
			}
			else
				Menu::getInstance()->pauseObjects[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(2);
		}

		Menu::getInstance()->loseObjects[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(1);
		if ((PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->loseObjects[1].pos) < Menu::getInstance()->loseObjects[1].GetHeight() && Menu::getInstance()->displayLose) && levelID != 0){
			if (state == 1) {
				Menu::getInstance()->loseObjects[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(1);
				ResetScene();
				ReadScene();
			}
			else
				Menu::getInstance()->loseObjects[1].textureID = ResourceManager::getInstance()->m_vTextureID.at(2);
		}

		Menu::getInstance()->winObjects[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(55);
		if (((PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->winObjects[2].pos) < Menu::getInstance()->winObjects[2].GetHeight() && Menu::getInstance()->displayWin )) && levelID != 0) {
			if (state == 1) {
				Menu::getInstance()->winObjects[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(55);
				ResetScene();
				ReadScene();
			}
			else
				Menu::getInstance()->winObjects[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(56);
		}

		//pause menu
		Menu::getInstance()->pauseObjects[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(7);
		if (PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->pauseObjects[3].pos) < Menu::getInstance()->pauseObjects[3].GetHeight() && levelID != 0){
			if (state == 1) {
				Menu::getInstance()->pauseObjects[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(7);
				levelID = 0;
				ResetScene();
				ReadScene();
				//Menu::getInstance()->save.Loaded();
			}
			else
				Menu::getInstance()->pauseObjects[3].textureID = ResourceManager::getInstance()->m_vTextureID.at(8);
		}

		Menu::getInstance()->loseObjects[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(7);
		if ((PointToLineDistance(worldCoordStart, worldCoordEnd, Menu::getInstance()->loseObjects[2].pos) < Menu::getInstance()->loseObjects[2].GetHeight()) && levelID != 0) {
			if (state == 1) {
				Menu::getInstance()->loseObjects[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(7);
				levelID = 0;
				ResetScene();
				ReadScene();				
			}
			else
				Menu::getInstance()->loseObjects[2].textureID = ResourceManager::getInstance()->m_vTextureID.at(8);
		}
	}
}

Vector3 SceneManager::UnProject(Vector3 winCoord) {
	
	Matrix maUnProject; 
	maUnProject = maView * maProjection;
	maUnProject.Inverse();

	int viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);
	Vector4 windowCoord;

	windowCoord.x = (winCoord.x - (float)viewport[0]) / (float)viewport[2] * 2.0 - 1.0;
	windowCoord.y = -((winCoord.y - (float)viewport[1]) / (float)viewport[3] * 2.0 - 1.0);
	windowCoord.z = 2.0 * winCoord.z - 1.0;
	windowCoord.w = 1.0;

	Vector4 worldCoord;

	worldCoord = maUnProject * windowCoord;
	worldCoord.x = worldCoord.x / worldCoord.w;
	worldCoord.y = worldCoord.y / worldCoord.w;
	worldCoord.z = worldCoord.z / worldCoord.w;

	return Vector3(worldCoord.x, worldCoord.y, worldCoord.z);

}