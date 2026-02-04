# ifndef PERSPECTIVE
# define PERSPECTIVE

class Perspective {
	private:
		int sx, sy;
		float cameraDistance;

		void Init();

	public:
		bool SetXY(float pos[3], float result[2]);
};

# endif
