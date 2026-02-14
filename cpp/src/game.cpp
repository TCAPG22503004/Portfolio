# include "DxLib.h"
# include "config.hpp"
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

	// prepare loop
	Player p;
	p.SetParameter();

	while (true) {
	
		// player movement
		p.Rotate(playerRot);
		p.Move(playerPos, playerRot);

		// convert screen coordinate
		TransformObject();
		Projection();

		// draw
		Draw();

		// config & exit loop
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			if (ConfigOrTitle()) break;
			p.SetParameter();
		}

		// loop
		WaitTimer(1000 / fps);
		if (ProcessMessage() == -1) break;
	}

	return 0;
}


/* ----------------
	private
------------------- */
void Game::Init() {

	// dxlib
	GetScreenState(&sx, &sy, NULL);
	white = GetColor(255, 255, 255);

	// player parameter
	playerRot[0] = 1;
	for (int i = 0; i < 3; i++) {
		playerPos[i] = 0;
		playerRot[i+1] = 0;
	}

	// margin of screen
	xMin = 0 - margin;
	xMax = sx + margin;
	yMin = 0 - margin;
	yMax = sy + margin;

	return;
}


void Game::CreateObjectInit() {

	// create forward
	int createDirection[2] = {0, 0};

	Object o;
	for (int i = 0; i < nObj; i++) {
		o.UpdateObjectList(playerPos, playerRot, createDirection, objectPos[i]);
	}

	return;
}


void Game::TransformObject() {

	Object o;
	for (int i = 0; i < nObj; i++) {
		o.MoveAndRotate(objectPos[i], playerPos, playerRot, objectPosRelative[i]);
	}

	return;
}


void Game::Projection() {

	Perspective p;

	for (int i = 0; i < nObj; i++) {
	
		isInside = false;

		for (int j = 0; j < 16; j++) {
			// convert screen coordinate
			p.SetXY(objectPosRelative[i][j], drawPos[i][j]);

			// is inside of screen?
			if (isInside == false) {

				x = drawPos[i][j][0];
				y = drawPos[i][j][1];

				if (
					x > xMin &&
					x < xMax &&
					y > yMin &&
					y < yMax
				) {
					isInside = true;
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

	int newObjectDirection[2] = {0, 0};


	// create right
	if (x < 0) {
		newObjectDirection[0] = -1;
	}

	// create left
	else if (x > sx) {
		newObjectDirection[0] = 1;
	}

	// create top
	if (y > sy) {
		newObjectDirection[1] = 1;
	}

	// create bottom
	else if (y < 0) {
		newObjectDirection[1] = -1;
	}

	// create new object
	Object o;
	o.UpdateObjectList(playerPos, playerRot, newObjectDirection, objectPos[i]);

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

	// display
	ScreenFlip();

	return;
}


bool Game::ConfigOrTitle() {

	// display config
	Config c;
	int n = c.ConfigGame();

	// continue or finish game
	if (n == 1) return false;

	return true;
}
