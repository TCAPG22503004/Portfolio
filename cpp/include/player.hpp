# ifndef PLAYER
# define PLAYER

class Player {
	private:
		float moveSpeed = 3;
		float deltaRotate = 0.001;

	public:
		void Move(float pos[3], float rot[4]);
		void Rotate(float rot[4]);
};

# endif
