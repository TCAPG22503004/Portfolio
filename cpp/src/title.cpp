# include <string.h>
# include "DxLib.h"
# include "title.hpp"

/* ----------------
	public
------------------- */
int Title::test() {

	Init();
	SetStringInformation();

	for (int i = 0; i < 3; i++) {
		DrawStringToHandle(strPos[i][0], strPos[i][1], str[i], white, fontHandle);
	}

	ScreenFlip();
	WaitKey();

	End();
	return -1;
}


/* -----------------
	private
-------------------- */
void Title::Init() {

	fontHandle = CreateFontToHandle(NULL, fontSize, fontThick);
	white = GetColor(255, 255, 255);

	return;
}


void Title::SetStringInformation() {

	int sx, sy;
	GetScreenState(&sx, &sy, NULL);

	// set strPos
	for (int i = 0; i < 3; i++) {
		int x;
		int w = GetDrawStringWidthToHandle(str[i], strlen(str[i]), fontHandle);
		x = (sx - w) / 2;
		strPos[i][0] = x;

		int y;
		y = sy / 4 * (i+1) - fontSize / 2;
		strPos[i][1] = y;
	}

	return;
}


void Title::End() {

	DeleteFontToHandle(fontHandle);

	return;
}
