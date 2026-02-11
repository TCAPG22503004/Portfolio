# include <cmath>
# include "quaternion.hpp"

/* ----------------
	public
------------------- */
void Quaternion::RotateObject(float pos[3], float rot[4], float result[3]) {
	
		// make matrix
		float left[3][3];
		left[0][0] = rot[0]*rot[0] + rot[1]*rot[1] - rot[2]*rot[2] - rot[3]*rot[3];
		left[0][1] = 2 * (rot[1]*rot[2] - rot[0]*rot[3]);
		left[0][2] = 2 * (rot[1]*rot[3] + rot[0]*rot[2]);
		left[1][0] = 2 * (rot[1]*rot[2] + rot[0]*rot[3]);
		left[1][1] = rot[0]*rot[0] - rot[1]*rot[1] + rot[2]*rot[2] - rot[3]*rot[3];
		left[1][2] = 2 * (rot[2]*rot[3] - rot[0]*rot[1]);
		left[2][0] = 2 * (rot[1]*rot[3] - rot[0]*rot[2]);
		left[2][1] = 2 * (rot[2]*rot[3] + rot[0]*rot[1]);
		left[2][2] = rot[0]*rot[0] - rot[1]*rot[1] - rot[2]*rot[2] + rot[3]*rot[3];

		// protect to change value
		float right[3] = {pos[0], pos[1], pos[2]};


		// product
		for (int i = 0; i < 3; i++) {
			float add = 0;

			for (int j = 0; j < 3; j++) {
				add += left[i][j] * right[j];
			}

			result[i] = add;
		}

		return;
}


void Quaternion::RotateCoordinate(float pos[3], float rot[4], float result[3]) {

		// make matrix
		float left[3][3];
		left[0][0] = rot[0]*rot[0] + rot[1]*rot[1] - rot[2]*rot[2] - rot[3]*rot[3];
		left[0][1] = 2 * (rot[1]*rot[2] + rot[0]*rot[3]);
		left[0][2] = 2 * (rot[1]*rot[3] - rot[0]*rot[2]);
		left[1][0] = 2 * (rot[1]*rot[2] - rot[0]*rot[3]);
		left[1][1] = rot[0]*rot[0] - rot[1]*rot[1] + rot[2]*rot[2] - rot[3]*rot[3];
		left[1][2] = 2 * (rot[2]*rot[3] + rot[0]*rot[1]);
		left[2][0] = 2 * (rot[1]*rot[3] + rot[0]*rot[2]);
		left[2][1] = 2 * (rot[2]*rot[3] - rot[0]*rot[1]);
		left[2][2] = rot[0]*rot[0] - rot[1]*rot[1] - rot[2]*rot[2] + rot[3]*rot[3];

		// protect to change value
		float right[3] = {pos[0], pos[1], pos[2]};


		// product
		for (int i = 0; i < 3; i++) {
			float add = 0;

			for (int j = 0; j < 3; j++) {
				add += left[i][j] * right[j];
			}

			result[i] = add;
		}

		return;
}


void Quaternion::ProductWorld(float rot[4], float delta, int n, float result[4]) {

	// make rotate quaternion
	float d[4] = {std::cos(delta), 0, 0, 0};
	d[n] = std::sin(delta);

	// product
	ProductQuaternion(d, rot, result);

	return;
}


void Quaternion::ProductLocal(float rot[4], float delta, int n, float result[4]) {

	// make rotate quaternion
	float d[4] = {std::cos(delta), 0, 0, 0};
	d[n] = std::sin(delta);

	// product
	ProductQuaternion(rot, d, result);

	return;
}


/* -----------------
	private
-------------------- */
void Quaternion::ProductQuaternion(float left[4], float right[4], float result[4]) {

	// make matrix
	float newLeft[4][4] = {
		{left[0], -left[1], -left[2], -left[3]},
		{left[1],  left[0], -left[3],  left[2]},
		{left[2],  left[3],  left[0], -left[1]},
		{left[3], -left[2],  left[1],  left[0]}
	};

	// avoid changing value
	float newRight[4];
	for (int i = 0; i < 4; i++) {
		newRight[i] = right[i];
	}

	// calculate
	for (int i = 0; i < 4; i++) {
		result[i] = 0;
		for (int j = 0; j < 4; j++) {
			result[i] += newLeft[i][j] * newRight[j];
		}
	}

	return;
}
