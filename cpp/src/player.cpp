# include "DxLib.h"
# include "player.hpp"
# include "quaternion.hpp"

/* ----------------
	public
------------------- */
void Player::Move(float pos[3], float rot[4]) {

	Quaternion q;

	// right-handed system: (+x, +y, +z) = (right, front, up)
	float v[3] = {0, moveSpeed, 0};

	// rotate move direction
	q.RotateCoordinate(v, rot, v);

	// update player position
	for (int i = 0; i < 3; i++) {
		pos[i] += v[i];
	}

	return;
}

void Player::Rotate(float rot[4]) {

	Quaternion q;

	if (CheckHitKey(KEY_INPUT_S) == 1) {
		q.ProductWorld(rot, deltaRotate, 1, rot);
	}
	if (CheckHitKey(KEY_INPUT_W) == 1) {
		q.ProductWorld(rot, -deltaRotate, 1, rot);
	}
	if (CheckHitKey(KEY_INPUT_E) == 1) {
		q.ProductWorld(rot, deltaRotate, 2, rot);
	}
	if (CheckHitKey(KEY_INPUT_Q) == 1) {
		q.ProductWorld(rot, -deltaRotate, 2, rot);
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		q.ProductWorld(rot, deltaRotate, 3, rot);
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		q.ProductWorld(rot, -deltaRotate, 3, rot);
	}
	if (CheckHitKey(KEY_INPUT_R) == 1) {
		rot[0] = 1;
		for (int i = 1; i < 4; i++) {
			rot[i] = 0;
		}
	}

	return;
}


/* -----------------
	private
-------------------- */
