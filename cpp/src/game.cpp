# include "DxLib.h"
# include "game.hpp"
# include "object.hpp"
# include "perspective.hpp"
# include "player.hpp"


/* ----------------
	public
------------------- */
int Game::GameMode() {

	// initialize
	Init();

	// create at first
	CreateObjectInit();

	Player p;
	bool isLoop = true;
	while (isLoop) {
	
		// player movement
		p.Rotate(playerRot);

		// convert screen coordinate
		RotateObject();
		Projection();

		// update object


		// draw
		Draw();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) isLoop = false;

		WaitTimer(1000 / fps);
		if (ProcessMessage() == -1) break;
	}

	return 0;
}


/* ----------------
	private
------------------- */
void Game::Init() {

	GetScreenState(&sx, &sy, NULL);
	white = GetColor(255, 255, 255);
	playerRot[0] = 1;
	playerRot[1] = 0;
	playerRot[2] = 0;
	playerRot[3] = 0;

	Object o;
	mergin = o.GetMergin();

	return;
}


void Game::CreateObjectInit() {

	// create forward
	int createDirection[3] = {0, 0, 1};

	Object o;
	for (int i = 0; i < nObj; i++) {
		o.UpdateObjectList(objectPos[i], playerRot, createDirection);
	}

	return;
}


void Game::RotateObject() {

	Object o;
	for (int i = 0; i < nObj; i++) {
		o.Rotate(objectPos[i], playerRot, objectPosRotated[i]);
	}

	return;
}


void Game::Projection() {

	Perspective p;

	for (int i = 0; i < nObj; i++) {
	
		drawRangeMin[0] = 65535;
		drawRangeMin[1] = 65535;
		drawRangeMax[0] = -1;
		drawRangeMax[1] = -1;
		isInside = false;
		isBehind = false;

		for (int j = 0; j < 16; j++) {
			// convert screen coordinate
			isBehind = p.SetXY(objectPosRotated[i][j], drawPos[i][j]);


			// is behind from camera?
			if (isBehind) {
				isInside = false;
				break;
			}

			// is inside of screen?
			if (isInside == false) {

				float x = drawPos[i][j][0];
				float y = drawPos[i][j][1];
				int xMin = 0 - mergin;
				int xMax = sx + mergin;
				int yMin = 0 - mergin;
				int yMax = sy + mergin;

				if (
					x > xMin &&
					x < xMax &&
					y > yMin &&
					y < yMax
				) {
					isInside = true;
				}

				// save minimize & maximize position
				else {
					if (drawRangeMin[0] > x) drawRangeMin[0] = x;
					if (drawRangeMin[1] > y) drawRangeMin[1] = y;
					if (drawRangeMax[0] < x) drawRangeMax[0] = x;
					if (drawRangeMax[1] < y) drawRangeMax[1] = y;
				}
			}
		}

		// create object if one is out of screen
		UpdateObject(i);
	}

	return;
}



void Game::UpdateObject(int i) {

	if (isInside) return;

	// save direction creating new object
	int newObjectDirection[3] = {0, 0, 0};

	// create foward
	if (isBehind) {
		newObjectDirection[2] = 1;
	}

	// create out of screen
	else {
		// create right
		if (drawRangeMax[0] < 0) {
			newObjectDirection[0] = -1;
		}

		// create left
		else if (drawRangeMin[0] > sx) {
			newObjectDirection[0] = 1;
		}

		// create top
		if (drawRangeMin[1] > sy) {
			newObjectDirection[1] = 1;
		}

		// create bottom
		else if (drawRangeMax[1] < 0) {
			newObjectDirection[1] = -1;
		}
	}

	Object o;
	o.UpdateObjectList(objectPos[i], playerRot, newObjectDirection);

	return;
}



void Game::Draw() {

	// clear
	ClearDrawScreen();

	// draw line
	for (int i = 0; i < nObj; i++) {
		for (int j = 0; j < 16 - 1; j++) {
			int x1 = drawPos[i][j][0];
			int y1 = drawPos[i][j][1];
			int x2 = drawPos[i][j+1][0];
			int y2 = drawPos[i][j+1][1];
			DrawLine(x1, y1, x2, y2, white);
		}
	}

	for (int i = 0; i < 4; i++) {
		DrawFormatString(i*100, 700, white, "%f", playerRot[i]);
	}

	// display
	ScreenFlip();

	return;
}
