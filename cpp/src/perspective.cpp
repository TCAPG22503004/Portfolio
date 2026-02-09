# include <cmath>
# include "DxLib.h"
# include "perspective.hpp"


/* ----------------
	public
------------------- */
bool Perspective::SetXY(float pos[3], float result[2]) {

	Init();

	// behind
	if (pos[1] < 0) return true;

	// convert x to x, z to y
	int x = cameraDistance * pos[0] / pos[1] + sx;
	int y = cameraDistance * pos[2] / pos[1] * -1 + sy;

	result[0] = x;
	result[1] = y;

	return false;
}



// use in object.cpp
float Perspective::GetFov() {
	return fov;
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
	cameraDistance = sx / std::tan(fov/2);

	return;
}
