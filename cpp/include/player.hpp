# ifndef PLAYER
# define PLAYER

class Player {
	private:
		void Rotate(float rot1[4], float rot2[4]);

	public:
		void Move(float pos[3]);
		bool KeyInput(float rot1[4], float rot2[4]);
};

# endif
