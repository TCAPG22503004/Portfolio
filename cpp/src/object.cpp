# include <random>
# include "object.hpp"
# include "quaternion.hpp"

/* ----------------
	public
------------------- */
void Object::UpdateObjectList(int objList[16][3], float rot[3], int direction) {

	// not create
	if (direction == 0) return;


	// init <random>
	std::random_device seed_gen;
	std::uint32_t seed = seed_gen();
	std::mt19937 engine(seed);
	std::uniform_real_distribution<float> distPos(0, posRandomRatio);
	std::uniform_real_distribution<float> distSiz(0, sizRandomRatio);
	
	// init center
	SetInitCenter(rot, direction);


	// create front
	if (direction == 1) {
		a = 1;
	}

	// create right
	else if (direction == 2) {
		a = 1;
	}

	// create left
	else if (direction == 3) {
		a = 1;
	}

	// create up
	else if (direction == 4) {
		a = 1;
	}

	// create down
	else if (direction == 5) {
		a = 1;
	}

	return;
}



/* -----------------
	private
-------------------- */
void Object::SetInitCenter(float rot[3], int Y) {

	// set length
	if (Y == 1) center[2] = newObjDistanceY;
	else center[2] = newObjDistanceXZ;

	// rotate
	Quaternion q;
	q.RotateCoordinate(center, rot, center);

	return;
}


void Object::MakeObject(int result[16][3]) {

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
