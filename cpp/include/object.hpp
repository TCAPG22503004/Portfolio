# ifndef OBJECT
# define OBJECT

class Object {
	private:
		int newObjDistanceMin = 5000;
		int newObjDistanceMax = 10000;
		int newObjSizeMin = 50;
		int newObjSizeMax = 300;

		float thetaX, thetaZ;
		float center[3];
		float delta[3];

		void SetTheta(int d[2]);
		void SetCenterAndDelta(float pos[3], float rot[4]);
		void MakeObject(float result[16][3]);

	public:
		void MoveAndRotate(float objList[16][3], float pos[3], float rot[4], float result[16][3]);
		void UpdateObjectList(float pos[3], float rot[4], int direction[2], float result[16][3]);
};

# endif
