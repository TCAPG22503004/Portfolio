# include <random>
# include "DxLib.h"
# include "object.hpp"
# include "perspective.hpp"
# include "quaternion.hpp"

/* ----------------
	public
------------------- */
void Object::MoveAndRotate(float objList[16][3], float pos[3], float rot[4], float result[16][3]) {

	Quaternion q;
	for (int i = 0; i < 16; i++) {
	
		// move origin
		for (int j = 0; j < 3; j++) {
			result[i][j] = objList[i][j] - pos[j];
		}

		// rotate
		q.RotateObject(result[i], rot, result[i]);
	}

	return;
}


void Object::UpdateObjectList(float pos[3], float rot[4], int direction[3], float result[16][3]) {

	// set create angle
	SetTheta(direction);
	
	// set rotation quaternion
	float rotObj[4] = {rot[0], -rot[1], -rot[2], -rot[3]};
	Quaternion q;
	q.ProductLocal(rotObj, thetaX, 1, rotObj);
	q.ProductLocal(rotObj, thetaZ, 3, rotObj);
	

	// create object
	SetCenterAndDelta(pos, rotObj);
	MakeObject(result);


	return;
}



/* -----------------
	private
-------------------- */
void Object::SetTheta(int d[2]) {

	// init <random>
	std::random_device seed_gen;
	std::uint32_t seed = seed_gen();
	std::mt19937 engine(seed);
	std::uniform_real_distribution<float> dist(-1, 1);

	// thetaX -> rotate based x axis (look like moving z direction)
	// thetaZ -> rotate based z axis (look like moving x direction)

	// z =   fov / 2 (-> change view from \/ to \|) / 2 (-> quaternion uses half anguler)
	Perspective p;
	float fov = p.GetFov();

	thetaZ = fov / 2 / 2;

	// x: z * aspect
	int sx, sy;
	GetScreenState(&sx, &sy, NULL);

	thetaX = thetaZ * sy / sx;


	// set theta

	// create left or right
	// (+1 or -1) * 1.2 (-> create outside of screen with consider object's size)
	if (d[0] != 0) {
		thetaZ *= d[0] * 1.2;
	}

	// (else) random direction
	else {
		thetaZ *= dist(engine);
	}

	// create up or down
	// (+1 or -1) * 1.3 (-> create outside of screen with consider object's size)
	if (d[1] != 0) {
		thetaX *= d[1] * 1.3;
	}

	// (else) random direction
	else {
		thetaX *= dist(engine);
	}

	return;
}



void Object::SetCenterAndDelta(float pos[3], float rot[4]) {

	// init <random>
	std::random_device seed_gen;
	std::uint32_t seed = seed_gen();
	std::mt19937 engine(seed);
	std::uniform_real_distribution<float> dist0(newObjDistanceMin, newObjDistanceMax);
	std::uniform_real_distribution<float> dist1(newObjSizeMin, newObjSizeMax);


	// set center
	center[0] = 0;
	center[1] = dist0(engine);
	center[2] = 0;

	Quaternion q;
	q.RotateObject(center, rot, center);

	for (int i = 0; i < 3; i++) {
		center[i] += pos[i];
	}


	// set delta
	for (int i = 0; i < 3; i++) {
		delta[i] = dist1(engine);
	}


	return;
}



void Object::MakeObject(float result[16][3]) {

	// + or - list
	int sign[16][3] = {
		{-1, +1, -1},
		{-1, -1, -1},
		{+1, -1, -1},
		{+1, -1, +1},
		{+1, +1, +1},
		{-1, +1, +1},
		{-1, +1, -1},
		{+1, +1, -1},
		{+1, +1, +1},
		{+1, +1, -1},
		{+1, -1, -1},
		{+1, -1, +1},
		{-1, -1, +1},
		{-1, -1, -1},
		{-1, -1, +1},
		{-1, +1, +1},
	};

	
	// make vertex list
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = center[j] + delta[j] * sign[i][j];	
		}
	}

	return;
}
