# ifndef OBJECT
# define OBJECT

class Object {
	private:
		int newObjDistanceXZ = 5000;
		int newObjDistanceY = 10000;
		int newObjSize = 100;
		float posRandomRatio = 0.2;
		float sizRandomRatio = 0.5;

		int center[3];
		int delta[3];

		void SetInitCenter(float rot[3], int Y);
		void MakeObject(int o[3], int d[3], int result[16][3]);

	public:
		void UpdateObjectList(int objList[16][3], float rot[3], int direction);
};

# endif
