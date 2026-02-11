# include "DxLib.h"
# include "title.hpp"
# include "config.hpp"
# include "game.hpp"


void BeforeInit() {

	SetGraphMode(1280, 720, 16);
	SetMainWindowText("Fly");
	ChangeWindowMode(TRUE);		// not full screen

	return;
}

void AfterInit() {

	SetDrawScreen(DX_SCREEN_BACK);

	return;
}

void MainLoop() {

	Title title;
	Config config;
	Game game;

	int mode = 0;

	while(mode != -1) {

		switch(mode) {

			case 0:
				mode = title.TitleMode();
				break;

			case 1:
				mode = game.GameMode();
				break;

			case 2:
				mode = config.ConfigTitle();
				break;

			default:
				mode = -1;
				break;
		}

		// break in abnormal end
		if (ProcessMessage() == -1) break;
	}
	return;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

	// initialize
	BeforeInit();
	if (DxLib_Init() == -1) return -1;
	AfterInit();

	// game
	MainLoop();

	// finish
	DxLib_End();
	return 0;
}
