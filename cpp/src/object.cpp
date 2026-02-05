# include <random>
# include "DxLib.h"
# include "object.hpp"
# include "perspective.hpp"
# include "quaternion.hpp"

/* ----------------
	public
------------------- */
void Object::UpdateObjectList(float objList[16][3], float rot[4], int direction[3]) {

	// not create
	int zero[3] = {0, 0, 0};
	if (direction == zero) return;


	// set create angle
	SetTheta(direction);
	
	float rotObj[4];
	Quaternion q;
	q.ProductLocal(rot, thetaX, 1, rotObj);
	q.ProductLocal(rotObj, thetaZ, 3, rotObj);


	// create object
	SetCenterAndDelta(rotObj, direction);
	MakeObject(objList);

	return;
}



/* -----------------
	private
-------------------- */
void Object::SetTheta(int d[3]) {

	// init <random>
	std::random_device seed_gen;
	std::uint32_t seed = seed_gen();
	std::mt19937 engine(seed);
	std::uniform_real_distribution<float> dist(-1, 1);

	// x: fov / 2(-> change view from \/ to \|) / 2(-> quaternion uses half anguler)
	Perspective p;
	float fov = p.GetFov();

	thetaX = fov / 2 / 2;

	// z: x * aspect
	int sx, sy;
	GetScreenState(&sx, &sy, NULL);

	thetaZ = thetaX * sy / sx;


	// set theta
	// create front
	if (d[1] != 0) {
		thetaX *= dist(engine);
		thetaZ *= dist(engine);
	}

	else {
		// create outside of left or right
		if (d[0] != 0) {
			thetaX *= d[0];
		}
	
		// (else) create random position
		else {
			thetaX *= dist(engine);
		}
	
		// create outside of up or down
		if (d[2] != 0) {
			thetaZ *= d[2];
		}
	
		// (else) create random position
		else {
			thetaZ *= dist(engine);
		}
	}

	return;
}



void Object::SetCenterAndDelta(float rot[4], int d[3]) {

	// init <random>
	std::random_device seed_gen;
	std::uint32_t seed = seed_gen();
	std::mt19937 engine(seed);
	std::uniform_real_distribution<float> dist(newObjSizeMin, newObjSizeMax);


	// set center
	if (d[1] != 0) {
		center[1] = newObjDistanceY;
	}
	else {
		center[1] = newObjDistanceXZ;
	}

	Quaternion q;
	q.RotateObject(center, rot, center);


	// set delta
	for (int i = 0; i < 3; i++) {
		delta[i] = dist(engine);
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
