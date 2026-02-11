# ifndef PLAYER
# define PLAYER

class Player {
	private:
		float moveSpeed;
		float deltaRotate[3];

	public:
		void Move(float pos[3], float rot[4]);
		void Rotate(float rot[4]);
		void SetParameter();
};

# endif
