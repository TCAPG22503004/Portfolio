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

	return;
}


void Game::CreateObjectInit() {

	// create forward
	int createDirection[3] = {0, 1, 0};

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
		// flag to check inside of screen
		bool isInside = false;

		for (int j = 0; j < 16; j++) {
			// convert screen coordinate
			p.SetXY(objectPosRotated[i][j], drawPos[i][j]);

			// is inside of screen?
			if (isInside == false) {
				if (
					drawPos[i][j][0] > 0  &&
					drawPos[i][j][0] < sx &&
					drawPos[i][j][1] > 0  &&
					drawPos[i][j][1] < sy
				) {
					isInside = true;
				}
			}
		}
	}

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
