# include "DxLib.h"
# include "game.hpp"


/* ----------------
	public
------------------- */
int Game::GameMode() {

	ClearDrawScreen();
	ScreenFlip();
	WaitKey();

	return 0;
}


/* ----------------
	private
------------------- */
