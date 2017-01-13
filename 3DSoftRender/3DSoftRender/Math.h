#pragma once
#include "Global.h"
#include "Object.h"

using namespace DirectX;
#define MIN(a, b)  (((a) < (b)) ? (a) : (b)) 
#define MAX(a, b)  (((a) > (b)) ? (a) : (b)) 
using namespace CORE;
extern float Fast_Sin(float theta);
extern float Fast_Cos(float theta);
const float PI = 3.141592654f;
const float PI2 = 6.283185307f;
const float PI_DIV_2 = 1.570796327f;
const float PI_DIV_4 = 0.785398163f;
const float EPSILON_E4 = (float)(1E-4);
const float EPSILON_E5 = (float)(1E-5);
const float EPSILON_E6 = (float)(1E-6);

const int PARM_LINE_NO_INTERSECT = 0;
const int PARM_LINE_INTERSECT_IN_SEGMENT = 1;
const int PARM_LINE_INTERSECT_OUT_SEGMENT = 2;
const int PARM_LINE_INTERSECT_EVERYWHERE = 3;
class Vector2D;
class Point2D
{
private:
	float M[2];
	float color[4];
public:
	Point2D();
	Point2D(const float x, const float y);

	Point2D(const Point2D& v);
	Point2D& operator=(const Point2D& v);
	Point2D operator+(const Point2D& v);
	Vector2D operator-(const Point2D& v);
	float& operator[](const int i);
	static Point2D AffineCSum(int N, float d[], Point2D Q[]);
	static Vector2D AffineDSum(int N, float d[], Point2D Q[]);
};
class Vector3D;
class Point4D;
class Point3D
{
private:
	float M[3];
	float color[4];
	float normal[3];
public:
	Point3D();
	Point3D(float x, float y, float z);
	float operator*(const Point3D& v);
	Vector3D operator-(const Point3D& v) const;
	float operator[](int i)const
	{
		return M[i];
	}
	Point3D(const Point3D& v);
	Point3D& operator=(const Point3D& v);
	Point3D& operator=(const Point4D& v);
	Point3D operator+(const Vector3D& v)const;
	inline float Normal()
	{
		float n = M[0] * M[0] + M[1] * M[1] + M[2] * M[2];
		return sqrtf(n);
	}
	static float Normal(Point3D& v);
	friend class Matrix4X4;
	friend class Line3D;
};

class Vector4D;
class Point4D
{
private:
	float M[4];
	float normal[3];
	float color[4];
public:
	Point4D()
	{
		M[0] = { 0 };
		normal[0] = { 0 };
		color[0] = { 0 };
	}
	Point4D(float* m)
	{
		M[0] = m[0];
		M[1] = m[1];
		M[2] = m[2];
		M[3] = m[3];
	}
	Point4D(float x, float y, float z, float w);
	Point4D(Point4D& v)
	{
		M[0] = v[0];
		M[1] = v[1];
		M[2] = v[2];
		M[3] = v[3];
	}
	float& operator[](int index)
	{
		return M[index];
	}
	Point4D& operator=(Vector4D& v);
	Point4D(const Point3D& v)
	{
		M[0] = v[0];
		M[1] = v[1];
		M[2] = v[2];
	}
	Point4D& operator=(Point4D&);
	Point4D operator=(const float[4]);
	Point4D operator+(Point4D& pos);
	Point4D operator+(Point3D& pos);
	Vector3D operator-(const Point3D& point);
	Vector3D operator-(const Point4D& point);
	friend class Matrix4X4;
	friend class Vector3D;
	friend class Point3D;
};

class Vector2D
{
private:
	float M[2];
public:
	Vector2D();
	Vector2D(float x, float y);
	float operator*(const Vector2D& v);
	Vector2D& cross(const Vector2D& v);
	float& operator[](int i);
	Vector2D(const Vector2D& v);
	Vector2D& operator=(const Vector2D& v);
	inline float Normal()
	{
		float n = M[0] * M[0] + M[1] * M[1];
		return ::sqrtf(n);
	}
	static float Normal(Vector2D& v);
};
class Vector4D;
class Vector3D
{
private:
	float M[3];
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	float operator*(const Vector3D&);
	Vector3D operator*(float c)const;
	friend Vector3D operator*(float c, Vector3D v);
	Vector3D cross(const Vector3D&);

	Vector3D(const Vector3D& v);
	Vector3D& operator = (Vector3D&);

	Vector3D& operator = (const Vector4D&);

	Vector3D operator+(const Vector3D& v)const;
	Vector3D operator-(Vector3D& v)const;
	float& operator[](int i)
	{
		return M[i];
	}

	Vector3D Normal()
	{
		float mod = sqrtf(M[0] * M[0] + M[1] * M[1] + M[2] * M[2]);
		if (mod != 0)
			return Vector3D(M[0] / mod, M[1] / mod, M[2] / mod);
		return Vector3D(0.0f, 0.0f, 0.0f);
	}
	bool operator==(float a)
	{
		if (abs(a - M[0]) < 0.0001f)
		{
			return true;
		}
		return false;
	}
	static Vector3D Normal(Vector3D& v);
	friend class Matrix3X3;
	friend class Matrix4X4;
	static Vector3D UP;
	static Vector3D RIGHT;
	static Vector3D FORWARD;
};

class Vector4D
{
private:
	float M[4];
public:
	Vector4D(){}
	Vector4D(float x, float y, float z, float w);
	Vector4D(Vector4D& v);

	float operator*(const Vector4D& v);
	Vector4D cross(const Vector4D& v);
	float& operator[](int index)
	{
		return M[index];
	}
	Vector4D& operator=(const Vector4D&);
	float Normal();
	static float Normal(Vector4D& v);
	friend class Matrix4X4;
	friend class Vector3D;
	static Vector4D UP;
	static Vector4D RIGHT;
	static Vector4D FORWARD;
};

class Matrix3X3
{
public:
	float M[3][3];
public:
	Matrix3X3();

	Matrix3X3(float* m);

	Matrix3X3(const Matrix3X3& m);

	Matrix3X3& operator=(const Matrix3X3& m);
	Matrix3X3& operator=(float m[]);

	Matrix3X3 operator*(const Matrix3X3& m)const;

	void operator*(Point2D&) const;
	void operator*(Point3D&) const;

	void operator*(Vector2D&) const;
	void operator*(Vector3D&) const;

	inline float& operator[](int i)
	{

	}

	void Tranvers();
	void Reflection(Vector3D N);
	inline float det()
	{
		return M[0][0] * M[1][1] * M[2][2] + M[0][1] * M[1][2] * M[2][0] + M[0][2] * M[2][1] * M[1][0]
			- M[0][2] * M[1][1] * M[2][0] - M[0][1] * M[1][0] * M[2][2] - M[0][0] * M[2][1] * M[1][2];
	}
	inline void setIdentity()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				M[i][j] = (i == j);
			}
		}
	}
};
class Matrix4X4
{
private:
	float M[4][4];
public:
	Matrix4X4();
	Matrix4X4(float* m);

	Matrix4X4(const Matrix4X4& m);

	Matrix4X4& operator=(const Matrix4X4& m);
	Matrix4X4& operator=(const Matrix3X3& m);

	Matrix4X4 operator*(const Matrix4X4& m)const;

	Point4D operator*(Point3D&) const;
	Point4D operator*(Point4D&) const;

	void operator*(Vector3D&) const;
	void operator*(Vector4D&) const;

	float& operator[](int i)
	{
		return M[i][i];
	}
	Matrix4X4 Inverse(Matrix4X4& matrix)const;


	//求出代数余子试
	inline float MStar(const Matrix4X4& m, int a, int b)const
	{
		Matrix3X3 temp;
		for (int i = 0, k = i; i < 3; i++, k++)
		{
			for (int j = 0, p = j; j < 3; j++, p++)
			{
				temp.M[i][j] = m.M[k][p];
				if (a == k)
					temp.M[i][j] = m.M[++k][p];
				if (b == p)
					temp.M[i][j] = m.M[k][++p];

			}
		}
		float det = temp.det();
		return det;
	}
	Matrix4X4& Tranvers();

	inline void setIdentity()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				M[i][j] = (i == j);
			}
		}
	}
};

class Line2D
{
public:
	Point2D p0;
	Point2D p1;
	Vector2D v;
public:
	Line2D(Point2D& _p0, Point2D& _p1) : p0(_p0), p1(_p1), v(p1 - p0)
	{
	}
	Line2D()
	{
	}
};


class Line3D
{
public:
	Point3D p0;
	Point3D p1;
	Vector3D v;
public:
	Line3D(Point3D& _p0, Point3D& _p1) :p0(_p0), p1(_p1), v(_p1 - _p0)
	{
	}
	Line3D(){}
	//Line Projection
private:
	void LineProjection(float dmin)
	{
		float s;//s在0-1之间
		Point3D line(p0.M[0] + s * (p1.M[0] - p0.M[0]), p0.M[1] + s * (p1.M[1] - p0.M[0]), (p0.M[2] + s * p1.M[2] - p0.M[2]));
		//line是一条点的集合，当s从0-1变化，line即一条线

		float w0 = p0.M[2] / dmin;
		float w1 = p1.M[2] / dmin;
		float _s = (w1*s) / (w0 + (w1 - w0)*s);	//_s为投影之后的缩放因子
		Point3D line_projection = p0 + _s*(p1 - p0);
	}
};

class Plane3D
{
public:
	Point3D p;
	Vector3D n;
public:
	Plane3D(const Point3D& _p, Vector3D& _n) :p(_p), n(_n.Normal())
	{}
	Plane3D(){}
	inline float Compute_Point_In_Plane3D(Point3D& p)
	{

	}
	inline Point3D Intersect_Parm_Line3D_Plane3D(Line3D& pline, Plane3D& plane, float* t)
	{
		Point3D pt;
		float plane_dot_line = pline.v * plane.n;
		if (plane_dot_line <= EPSILON_E5)
		{
			if (fabs(plane.Compute_Point_In_Plane3D(pline.p0)) <= EPSILON_E5)
			{
				//Paraller and just on the Plane
				return pt;
			}
			else
			{
				//Paraller and just over the Plane
				return pt;
			}
		}
	}
};

class Quaternation
{
private:
	float q;
	Vector3D qv;
	float w, x, y, z;
public:
	Quaternation operator+(Quaternation& q1);
	Quaternation operator-(Quaternation& q1);
	Quaternation operator*(Quaternation& q1);
	Quaternation conjugate(Quaternation& q1);
	void Normalize(Quaternation& q);
	void Normalize();
	void SetIdentity()
	{
		q = 0.0f;
		qv = Vector3D(0, 0, 0);
		w = 0;
		x = 0;
		y = 0;
		z = 0;
	}
	void Quat_Unit_Inverse();
	void Quat_Inverse();
	Quaternation Vector3D_To_Quat(Vector3D& vector);
	Quaternation Vector4D_To_Quat(Vector4D& vector);

};
class Polar2D
{
public:
	float r;
	float theta;
};
class Dicar2D
{
private:
	Point2D E;
	Vector2D x, y;
};
class Dicar3D
{
private:
	Point3D E;
	Vector3D x, y, z;
};

class Cylindrical
{
public:
	Cylindrical();
	~Cylindrical();

private:
	float r;
	float theta;
	float z;
};
class Spherical3D
{
public:
	Spherical3D();
	~Spherical3D();

private:
	float p;
	float theta;
	float phi;
};

//class Vector;
//class Point
//{
//private:
//	float tup[4];
//public:
//	Point operator+(Vector v);
//	Point operator-(Vector v);
//	Vector operator-(Point Q);
//	static Point AffineCSum(int N, float c[], Point Q[]);
//	//sum of c is 1
//	static Vector AffineDSum(int N, float d[], Point Q[]);
//	//sum of d is 0
//};
//
//class Vector
//{
//private:
//	float tup[4];
//public:
//	Vector operator+(Vector v)const;
//	Vector operator-(Vector v)const;
//	Vector operator*(float c)const;
//	friend Vector operator*(float c, Vector v);
//	float operator[](Vector v)const;
//
//};
//
////定义一个球体
//class Sphere
//{
//private:
//	//笛卡尔
//	float a;
//	float b;
//	float c;
//	float r;
//	//极坐标
//	float r;
//	float theta;
//	float fai;
//};

extern void Polar2D_To_Point2D();
extern void Polar2D_To_RectXY();
extern void Point2D_To_Polar2D();
extern void Point2D_To_PolarRth();

extern void Cylindrical3D_To_Point3D();
extern void Cylindrical3D_To_RectXYZ();
extern void Point3D_To_Cylindrical3D();
extern void Point3D_To_CylindricalRthz();

extern void Spherical3D_To_Point3D();
extern void Spherical3D_To_RectXYZ();
extern void Point3D_To_Spherical3D();
extern void Point3D_To_SphericalPThph();

extern void Init_Param_Line2D(Point2D& p_init, Point2D& p_term, Line2D& p);
extern void Compute_Parm_Line2D(Line2D& p, float t, Point2D& pt);
extern int Intersect_Parm_Line2D(Line2D& p1, Line2D& p2, float* t1, float* t2);

extern void Compute_Parm_Line3D(Line3D* p, float t, Point3D* pt);
extern void Init_Parm_Line3D(Point3D* p_init, Point3D* p_term, Line3D* p);
extern char* Get_Line_PLG(char* buffer, int maxLength, FILE* fp);

extern float Compute_Object4DV1_Radius(Object* obj);

extern void Build_Sin_Cos_Tables(void);


