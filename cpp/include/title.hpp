# ifndef TITLE
# define TITLE

class Title {

	private:
		int fontSize = 64;
		int fontThick = 16;
		static const int nStr = 3;
		const char* str[nStr] = {
			"Fly",
			"Config",
			"Exit",
		};
		const char* arrow = "> ";
		
		int select;
		int fontHandle;
		int strPos[nStr][2];
		int arrowPosX;
		unsigned int white;

		void Init();
		void SetStringInformation();
		bool Select();
		void Draw();
		void End();

	public:
		int TitleMode();
};

# endif
