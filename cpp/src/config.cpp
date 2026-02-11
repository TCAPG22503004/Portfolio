# include <string.h>
# include <fstream>
# include "DxLib.h"
# include "config.hpp"
# include "player.hpp"
# include "write.cpp"

/* ----------------
	public
------------------- */

// --- read & write file ---

void Config::ReadParameter(int *speed, int angular[3]) {

	try{
		std::ifstream ifs(path);
		int n;

		// move speed
		ifs >> *speed;

		// rotate speed
		for (int i = 0; i < 3; i++) {
			ifs >> angular[i];
		}
	}
	catch (char* s) {

		// default value
		*speed = 3;
		angular[0] = 5;
		angular[1] = 5;
		angular[2] = 5;
	}

	return;
}


void Config::WriteParameter(int speed, int angular[3]) {

		// the reason why cannot write file is unknown,
		// anyway use other class
		Write w;
		w.write(speed, angular);
		return;
/*
	try {
		// write file
		std::ofstream ofs("testaaaa");
		if (ofs) return false;
		
	
		ofs << "AAAAA" << std::endl;
		return;

		ofs << speed << std::endl;
		ofs << angular[0] << std::endl;
		ofs << angular[1] << std::endl;
		ofs << angular[2] << std::endl;
	}
	catch (char* s) {

		// default value
		speed = 3;
		angular[0] = 5;
		angular[1] = 5;
		angular[2] = 5;
	}
*/
	return;
}




// --- config UI ---

int Config::ConfigTitle() {

	int n = 1;

	Init();
	SetStringInformation();
	SetStringInformationAppend(n);

	Draw(n);

	bool isLoop = true;
	while (isLoop) {
		isLoop = Select(n);

		// break in abnormal end
		if (ProcessMessage() == -1) break;
	}

	End();

	// back to title
	return 0;
}

int Config::ConfigGame() {

	int n = 2;

	Init();
	SetStringInformation();
	SetStringInformationAppend(n);

	Draw(n);

	bool isLoop = true;
	while (isLoop) {
		isLoop = Select(n);

		// break in abnormal end
		if (ProcessMessage() == -1) break;
	}

	End();

	// back game
	if (selectAppend == 0) return 1;

	// back title
	return 0;
}




/* ------------------
	private
--------------------- */
void Config::Init() {

	fontHandle = CreateFontToHandle(NULL, fontSize, fontThick);
	white = GetColor(255, 255, 255);

	// read file
	ReadParameter(&v, theta);

	return;
}


void Config::SetStringInformation() {

	int sx, sy;
	GetScreenState(&sx, &sy, NULL);

	// set strPos
	// all strings have same length in Config (in contrast Title)
	int w = GetDrawStringWidthToHandle(str[0], strlen(str[0]), fontHandle);
	for (int i = 0; i < nStr; i++) {

		int x;
		x = (sx - w) / 2;
		strPos[i][0] = x;

		int y;
		y = sy / (nStr + 1) * (i+1) - fontSize / 2;
		strPos[i][1] = y;
	}

	// set parameter position
	parameterPosX = (sx + w) / 2;
	
	// set arrowPosX
	int x;
	w = GetDrawStringWidthToHandle(arrow, strlen(arrow), fontHandle);
	x = strPos[0][0] - w;
	arrowPosX = x;

	return;
}


bool Config::Select(int nButton) {

	int key = WaitKey();

	// change scene
	// when button is selected
	if (key == KEY_INPUT_SPACE || key == KEY_INPUT_RETURN) {
		if (select == nStr - 1) {
			return false;
		}
	}

	// up - down: move arrow
	else if (key == KEY_INPUT_UP) {
		if (select > 0) {
			select--;
		}
	}

	else if (key == KEY_INPUT_DOWN) {
		if (select < nStr - 1) {
			select++;
		}
	}

	// right - left: change value or button
	else if (key == KEY_INPUT_RIGHT) {
		
		// change value
		if (select == 0) {
			v += 1;
		}

		else if (select < nStr - 1) {
			theta[select - 1] += 1;
		}

		// button change
		else if (selectAppend < nButton - 1) {
			selectAppend += 1;
		}

	}

	else if (key == KEY_INPUT_LEFT) {

		// change value
		if (select == 0) {
			v -= 1;
		}

		else if (select < nStr - 1) {
			theta[select - 1] -= 1;
		}

		// button change
		else if (selectAppend > 0) {
			selectAppend -= 1;
		}
	}

	// update screen
	Draw(nButton);


	return true;
}


void Config::Draw(int nButton) {

	// clear
	ClearDrawScreen();

	// string
	for (int i = 0; i < nStr; i++) {
		DrawStringToHandle(strPos[i][0], strPos[i][1], str[i], white, fontHandle);
	}

	// arrow
	if (select != nStr - 1) {
		DrawStringToHandle(arrowPosX, strPos[select][1], arrow, white, fontHandle);
	}
	else {
		DrawStringToHandle(arrowPosXAppend[selectAppend], strPos[select][1], arrow, white, fontHandle);
	}


	// parameter
	DrawFormatStringToHandle(parameterPosX, strPos[0][1], white, fontHandle, "%d", v);
	for (int i = 0; i < 3; i++) {
		DrawFormatStringToHandle(parameterPosX, strPos[i+1][1], white, fontHandle, "%d", theta[i]);
	}

	// button
	for (int i = 0; i < nButton; i++) {
		DrawStringToHandle(strPosAppend[i], strPos[nStr - 1][1], strAppend[i], white, fontHandle);
	}

	//display
	ScreenFlip();

	return;
}


void Config::End() {

	DeleteFontToHandle(fontHandle);

	// write file
	WriteParameter(v, theta);

	return;
}



// back (& title) information
void Config::SetStringInformationAppend(int nButton) {

	int sx, sy;
	GetScreenState(&sx, &sy, NULL);

	for (int i = 0; i < nButton; i++) {

		// set strPos
		int x;
		int w = GetDrawStringWidthToHandle(strAppend[i], strlen(strAppend[i]), fontHandle);
		x = (sx - w) / (nButton + 1) * (i + 1);
		strPosAppend[i] = x;

		// set arrowPosX
		w = GetDrawStringWidthToHandle(arrow, strlen(arrow), fontHandle);
		x = strPosAppend[i] - w;
		arrowPosXAppend[i] = x;
	}

	return;
}
