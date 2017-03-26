#pragma once
#include "Object.h"

struct SwimingFishing {
	Object head, body, tail;
	Vector3 scale, pos, moveAngle, angle, sign,rot;
	float maxAngle, dist, moveAngleStride, velocity;
	float range;
};

struct JellyFishStruct{
	Object head, tail;
	Vector3 pos;
	float rotZ, scale, range;
	int vRigidBodyID;
};