# ifndef PERSPECTIVE
# define PERSPECTIVE


# define PI 3.141592653589793

class Perspective {
	private:
		float fov = PI / 4;

		int sx, sy;
		float cameraDistance;

		void Init();

	public:
		bool SetXY(float pos[3], float result[2]);
		float GetFov();
};

# endif
