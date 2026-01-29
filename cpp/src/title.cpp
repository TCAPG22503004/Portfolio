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
	DrawStringToHandle(arrowPosX, strPos[1][1], arrow, white, fontHandle);

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

	int xMin = 9999;
	for (int i = 0; i < 3; i++) {

		// set strPos
		// (change value if number of str is changed)
		int x;
		int w = GetDrawStringWidthToHandle(str[i], strlen(str[i]), fontHandle);
		x = (sx - w) / 2;
		strPos[i][0] = x;

		int y;
		y = sy / 4 * (i+1) - fontSize / 2;
		strPos[i][1] = y;

		// prepare creating arrowPos
		if (xMin > x) xMin = x;
	}
	
	// set arrowPosX
	int x;
	int w = GetDrawStringWidthToHandle(arrow, strlen(arrow), fontHandle);
	x = xMin - w;
	arrowPosX = x;


	return;
}


void Title::End() {

	DeleteFontToHandle(fontHandle);

	return;
}
