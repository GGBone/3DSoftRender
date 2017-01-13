#ifndef SPIRIT2D_H
#define SPIRIT2D_H
#include <iostream>
namespace Spirit2D
{
	class Vertex_2D
	{
	private:
		float x;
		float y;
		float color_RGB[3];
	public:
		Vertex_2D(float _x = 0, float _y = 0);
		~Vertex_2D();
	};
	class Line_2D
	{
	private:
		Vertex_2D v[2];

	public:
		Line_2D(Vertex_2D v1, Vertex_2D v2);
		Line_2D(float v1 = 0, float v2 = 0);
		~Line_2D();
	};
}
#endif