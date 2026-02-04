# ifndef QUATERNION
# define QUATERNION

class Quaternion {
	private:
		void ProductQuaternion(float left[4], float right[4], float result[4]);
	public:
		void RotateObject(float pos[3], float rot[4], float result[3]);
		void RotateCoordinate(float pos[3], float rot[4], float result[3]);
		void ProductWorld(float rot[4], float delta, int n, float result[4]);
		void ProductLocal(float rot[4], float delta, int n, float result[4]);
};

# endif
