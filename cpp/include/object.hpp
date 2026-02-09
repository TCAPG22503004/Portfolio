# ifndef OBJECT
# define OBJECT

class Object {
	private:
		int newObjDistanceXZ = 5000;
		int newObjDistanceY = 10000;
		int newObjSizeMin = 100;
		int newObjSizeMax = 500;

		float thetaX, thetaZ;
		float center[3];
		float delta[3];

		void SetTheta(int d[3]);
		void SetCenterAndDelta(float rot[4], int d[3]);
		void MakeObject(float result[16][3]);

	public:
		void Rotate(float objList[16][3], float rot[4], float result[16][3]);
		void UpdateObjectList(float objList[16][3], float rot[4], int direction[3]);
};

# endif
