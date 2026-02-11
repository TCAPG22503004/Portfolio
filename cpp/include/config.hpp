# ifndef CONFIG 
# define CONFIG 

class Config {
	private:
	public:
		void ReadParameter(int *speed, int angular[3]);
		void WriteParameter(int *speed, int angular[3]);
};

# endif
