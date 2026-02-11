# ifndef CONFIG 
# define CONFIG 

class Config {
	private:
		// file path
		const char* path = "../etc/config";

		int fontSize = 64;
		int fontThick = 16;
		static const int nStr = 5;
		const char* str[nStr] = {
			"    speed     : ",
			"x-axis / pitch: ",
			"y-axis / roll : ",
			"z-axis / yaw  : ",
			"",
		};
		const char* arrow = "> ";
		
		int select = 0;
		int fontHandle;
		int strPos[nStr][2];
		int arrowPosX;
		unsigned int white;
		// add from title
		int v;
		int theta[3];
		int parameterPosX;
		static const int nStrAppend = 2;
		const char* strAppend[nStrAppend] = {
			"Back",
			"Title",
		};
		int strPosAppend[nStrAppend];
		int arrowPosXAppend[nStrAppend];
		int selectAppend = 0;


		void Init();
		void SetStringInformation();
		bool Select(int nButton);
		void Draw(int nButton);
		void End();
		// add from title
		void SetStringInformationAppend(int nButton);

	public:
		void ReadParameter(int *speed, int angular[3]);
		void WriteParameter(int speed, int angular[3]);
		int ConfigTitle();
		int ConfigGame();
};

# endif
