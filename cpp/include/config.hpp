# ifndef CONFIG 
# define CONFIG 

class Config {
	private:
		int fontSize = 64;
		int fontThick = 16;
		const char* str[3] = {
			"AA",
			"BB",
			"Exit",
		};
		const char* arrow = "> ";
		
		int select;
		int fontHandle;
		int strPos[3][2];
		int arrowPosX;
		unsigned int white;

		void Init();
		void SetStringInformation();
		bool Select();
		void Draw();
		void End();

	public:
		void ReadParameter(int *speed, int angular[3]);
		void WriteParameter(int *speed, int angular[3]);
		int ConfigTitle();
		int ConfigGame();
};

# endif
