# ifndef QUATERNION
# define QUATERNION

class Quaternion {
	private:
		void CalculateQuaternion(float pos[4], float rot[4]);
	public:
		void RotateObject(float *pos, float rot[4]);
		void RotateWorld(float pos[3], float rot[4]);
		void RotateLocal(float pos[3], float rot[4]);
};

# endif
