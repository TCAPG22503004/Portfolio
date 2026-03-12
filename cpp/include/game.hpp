# ifndef GAME
# define GAME

# include "constant.hpp"

class Game {

	private:
		int fps = 60;
		int margin = 250;

		int sx, sy;
		unsigned int white;
		float playerPos[3];
		float playerRot[4];
		static const int nObj = 10;
		float objectPos[nObj][N_VERTEX][3];	// [num of object][num of vertex][(x, y, z)]
		float objectPosRelative[nObj][N_VERTEX][3];
		float drawPos[nObj][N_VERTEX][2];
		bool isInside;
		int x, y, xMin, xMax, yMin, yMax;

		void Init();
		void CreateObjectInit();
		void TransformObject();
		void Projection();
		void UpdateObject(int i);
		void Draw();
		bool ConfigOrTitle();

	public:
		int GameMode();
};

# endif
