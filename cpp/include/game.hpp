# ifndef GAME
# define GAME

class Game {

	private:
		int fps = 60;

		int sx, sy;
		unsigned int white;
		float playerPos[3];
		float playerRot[4];
		static const int nObj = 10;
		float objectPos[nObj][16][3];	// [num of object][num of vertex][(x, y, z)]
		float objectPosRotated[nObj][16][3];
		float drawPos[nObj][16][2];

		void Init();
		void CreateObjectInit();
		void RotateObject();
		void Projection();
		void Draw();

	public:
		int GameMode();
};

# endif
