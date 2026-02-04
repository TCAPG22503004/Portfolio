# ifndef GAME
# define GAME

class Game {

	private:
		int fps = 60;

		float playerPos[3];
		float playerRot[4] = {1, 0, 0, 0};
		static const int nObj = 10;
		float objectPos[nObj][16][3];	// [num of object][num of vertex][(x, y, z)]
		float objectRot[4] = {1, 0, 0, 0};

		void Init();

	public:
		int GameMode();
};

# endif
