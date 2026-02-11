# include <fstream>

# ifndef WRITE
# define WRITE


// this is only write file class
// because config.cpp cannot write file (reason is unknown)

class Write {

	public:
		void write(int v, int t[3]) {
			std::ofstream ofs("../etc/config");
			ofs << v << std::endl;
			ofs << t[0] << std::endl;
			ofs << t[1] << std::endl;
			ofs << t[2] << std::endl;

			return;
		};
};

# endif
