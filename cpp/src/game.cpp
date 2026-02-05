# include "DxLib.h"
# include "game.hpp"
# include "object.hpp"
# include "perspective.hpp"
# include "player.hpp"


/* ----------------
	public
------------------- */
int Game::GameMode() {

	ClearDrawScreen();
	// initialize
	Init();

	// create at first
	CreateObjectInit();

	// convert screen coordinate
	Projection();

	// draw
	Draw();

	ScreenFlip();

	WaitKey();

	return 0;
}


/* ----------------
	private
------------------- */
void Game::Init() {

	GetScreenState(&sx, &sy, NULL);
	white = GetColor(255, 255, 255);

	return;
}


void Game::CreateObjectInit() {

	// create forward
	int createDirection[3] = {0, 1, 0};

	Object o;
	for (int i = 0; i < nObj; i++) {
		o.UpdateObjectList(objectPos[i], objectRot, createDirection);
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
			p.SetXY(objectPos[i][j], drawPos[i][j]);

			if (isInside == false) {
				// is inside of screen?
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
//	ClearDrawScreen();

	// draw line
	for (int i = 0; i < nObj; i++) {
		for (int j = 0; j < 16 - 1; j++) {
			float x1 = drawPos[i][j][0];
			int y1 = drawPos[i][j][1];
			int x2 = drawPos[i][j+1][0];
			int y2 = drawPos[i][j+1][1];
		//	DrawFormatString(j*100, i*20, white, "%f", x1);
		// 	DrawLine(x1, y1, x2, y2, white);
		}
	}

	// display
//	ScreenFlip();

	return;
}
