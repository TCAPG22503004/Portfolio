# include <cmath>
# include "DxLib.h"
# include "perspective.hpp"

# define PI 3.141592653589793

/* ----------------
	public
------------------- */
bool Perspective::SetXY(float pos[3], float result[2]) {

	// behind
	if (pos[2] < 0) return false;

	int x = cameraDistance * pos[0] / pos[2] + sx;
	int y = cameraDistance * pos[1] / pos[2] * -1 + sy;

	result[0] = x;
	result[1] = y;

	return true;
}


/* -----------------
	private
-------------------- */
void Perspective::Init() {
	
	// screen size
	GetScreenState(&sx, &sy, NULL);
	sx /= 2;
	sy /= 2;

	// camera position
	float fov = PI / 4;	// field of view
	cameraDistance = sx / std::tan(fov/2);

	return;
}
