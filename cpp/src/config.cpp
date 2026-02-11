# include <string.h>
# include <fstream>
# include "DxLib.h"
# include "config.hpp"
# include "player.hpp"

/* ----------------
	public
------------------- */

// --- read & write file ---

void Config::ReadParameter(int *speed, int angular[3]) {

	try{
		std::ifstream ifs("../etc/config");
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


void Config::WriteParameter(int *speed, int angular[3]) {

	try {
		// write file
		std::ofstream ofs("../erc/config");
		ofs << *speed << std::endl;
		ofs << angular[0] << std::endl;
		ofs << angular[1] << std::endl;
		ofs << angular[2] << std::endl;
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

