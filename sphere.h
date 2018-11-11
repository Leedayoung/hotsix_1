
#include <GL/glew.h>


class Sphere
{
public:
	Sphere();
	~Sphere();
	void init(GLuint vertexPositionID);
	void cleanup();
	void draw();
	void set_longitude(int rad);
	void set_lattitude(int rad);
	void set_radius(int rad);

private:
	int lats, longs;
	bool isInited;
	GLuint m_vao, m_vboVertex, m_vboIndex;
	int numsToDraw;
};

