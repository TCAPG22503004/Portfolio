# include <string.h>
# include "DxLib.h"
# include "title.hpp"

/* ----------------
	public
------------------- */
int Title::TitleMode() {

	Init();
	SetStringInformation();

	Draw();

	bool isLoop = true;
	while (isLoop) {
		isLoop = Select();

		// break in abnormal end
		if (ProcessMessage() == -1) break;
	}

	End();

	// start game
	if (select == 0) return 1;

	//config
	else if (select == 1) return 2;

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
	for (int i = 0; i < nStr; i++) {

		// set strPos
		int x;
		int w = GetDrawStringWidthToHandle(str[i], strlen(str[i]), fontHandle);
		x = (sx - w) / 2;
		strPos[i][0] = x;

		int y;
		y = sy / (nStr + 1) * (i+1) - fontSize / 2;
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


bool Title::Select() {

	int key = WaitKey();

	// change scene
	if (key == KEY_INPUT_SPACE || key == KEY_INPUT_RETURN) {
		return false;
	}

	// move arrow & update screen
	else if (key == KEY_INPUT_UP) {
		if (select > 0) {
			select--;
			Draw();
		}
	}

	else if (key == KEY_INPUT_DOWN) {
		if (select < nStr - 1) {
			select++;
			Draw();
		}
	}

	return true;
}


void Title::Draw() {

	ClearDrawScreen();

	// string
	for (int i = 0; i < nStr; i++) {
		DrawStringToHandle(strPos[i][0], strPos[i][1], str[i], white, fontHandle);
	}

	// arrow
	DrawStringToHandle(arrowPosX, strPos[select][1], arrow, white, fontHandle);

	ScreenFlip();

	return;
}


void Title::End() {

	DeleteFontToHandle(fontHandle);

	return;
}
