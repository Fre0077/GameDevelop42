#ifndef MAT4
	#define MAT4

	#include <string>
	#include <cmath>

class mat4 {
	public:
		float data[16];
		mat4();
		~mat4();
		void	world(std::string ax, float angle);
		void	world(float x, float y, float z);
		void	view(std::string ax, float angle);
		void	view(float x, float y, float z);
		void	project(float fov, float aspect, float near, float far);
		mat4	multiply(const mat4& other) const;
};

#endif
