#include "Spirit2D.h"
using namespace std;
using namespace Spirit2D;
Vertex_2D::Vertex_2D(float _x, float _y) :x(_x), y(_y)
{
}
Vertex_2D::~Vertex_2D()
{

}
Line_2D::Line_2D(Vertex_2D v1, Vertex_2D v2)
{
	v[0] = v1;
	v[1] = v2;
}
Line_2D::Line_2D(float v1, float v2)
{
	
}
Line_2D::~Line_2D()
{

}