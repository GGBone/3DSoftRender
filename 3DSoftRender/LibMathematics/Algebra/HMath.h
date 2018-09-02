#ifndef HMATH_H
#define HMATH_H
#include <cmath>
#include <cstdlib>
#include <cfloat>


template <typename T>
class Math
{
public:
	static T ACos(T value);
	static T ASin(T value);
	static T ATan(T value);
	static T ACot(T value);
	static T ATan2(T value);
	static T Ceil(T value);
	static T Cos(T value);
	static T Exp(T value);
	static T FAbs(T value);
	static T Floor(T value);
	static T FMod(T value);
	static T InvSqrt(T value);
	static T Log(T value);
	static T Log2(T value);
	static T Log10(T value);

	static T Pow(T value);
	static T Sin(T value);
	static T Sqrt(T value);
	static T Tan(T value);

	//return -1 if input is negative
	static int Sign(int value);
	static T Sign(T value);

	static T UnitRandom(unsigned int seed = 0);

	static T SymmetricRandom(unsigned int seed = 0);


	static const T PI;
};

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
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


extern void Polar2D_To_Point2D();
extern void Polar2D_To_RectXY();
extern void Point2D_To_Polar2D();
extern void Point2D_To_PolarRth();

extern void Cylindrical3D_To_APoint();
extern void Cylindrical3D_To_RectXYZ();
extern void APoint_To_Cylindrical3D();
extern void APoint_To_CylindricalRthz();

extern void Spherical3D_To_APoint();
extern void Spherical3D_To_RectXYZ();
extern void APoint_To_Spherical3D();
extern void APoint_To_SphericalPThph();
//
//extern void Init_Param_Line2D(Point2D& p_init, Point2D& p_term, Line2D& p);
//extern void Compute_Parm_Line2D(Line2D& p, float t, Point2D& pt);
//extern int Intersect_Parm_Line2D(Line2D& p1, Line2D& p2, float* t1, float* t2);
//
//extern void Compute_Parm_Line3D(Line3D* p, float t, APoint* pt);
//extern void Init_Parm_Line3D(APoint* p_init, APoint* p_term, Line3D* p);
//extern char* Get_Line_PLG(char* buffer, int maxLength, FILE* fp);

//extern float Compute_Object4DV1_Radius(Object* obj);

extern void Build_Sin_Cos_Tables(void);


#endif
