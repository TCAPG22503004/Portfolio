# ifndef OBJECT
# define OBJECT

class Object {
	private:
		void MakeObject();

	public:
		// pos: array[10][16][3] -> [num of object][num of vertex][(x, y, z)]
		void UpdateObjectList(int n, float *pos);
		void Draw(int n, float *pos, float rot[4]);
};

# endif
