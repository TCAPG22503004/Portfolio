# ifndef TITLE
# define TITLE

class Title {

	private:
		int fontSize = 64;
		int fontThick = 16;
		const char* str[3] = {
			"Fly",
			"Config",
			"Exit",
		};
		const char* arrow = "> ";
		
		int fontHandle;
		int strPos[3][2];	// [number of str (change to need)][x, y (no change)]
		int arrowPosX;
		unsigned int white;

		void Init();
		void SetStringInformation();
		void End();

	public:
		int test();
};

# endif
