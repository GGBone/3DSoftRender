//#include "Global.h"
//#include <iostream>
//#include "HMath.h"
//
//using namespace Memory;
//float cos_look[361];
//float sin_look[361];
//
//const float Identity_4X4[][4] =
//{
//	1, 0, 0, 0,
//	0, 1, 0, 0,
//	0, 0, 1, 0,
//	0, 0, 0, 1,
//};
//const float Identity_3X3[][3] =
//{
//	1, 0, 0,
//	0, 1, 0,
//	0, 0, 1,
//};
//
//Vector2D::Vector2D()
//{
//	M[0] = 0.0f;
//	M[1] = 0.0f;
//}
//Vector2D::Vector2D(float x, float y)
//{
//	M[0] = x;
//	M[1] = y;
//}
//float& Vector2D::operator[](int i)
//{
//	return M[i];
//}
//Vector2D& Vector2D::operator=(const Vector2D& v)
//{
//	this->M[0] = v.M[0];
//	this->M[1] = v.M[1];
//	return *this;
//}
//
//APoint APoint::operator = (const float f[4])
//{
//	for (int i = 0; i < 4; i++)
//	{
//		M[i] = f[i];
//	}
//	return APoint(M);
//}
//APoint& APoint::operator = (APoint& v)
//{
//	M[0] = v[0];
//	M[1] = v[1];
//	M[2] = v[2];
//	M[3] = v[3];
//	return *this;
//}
//
//APoint& APoint::operator= (Vector4D& v)
//{
//	M[0] = v[0];
//	M[1] = v[1];
//	M[2] = v[2];
//	M[3] = v[3];
//	return *this;
//}
//APoint APoint::operator+(APoint& p)
//{
//	return APoint(M[0] + p[0], M[1] + p[1], M[2] + p[2], M[3] + p[3]);
//}
//APoint APoint::operator+(APoint& p)
//{
//	return APoint(M[0] + p[0], M[1] + p[1], M[2] + p[2], M[3] + 0);
//}
//AVector APoint::operator-(const APoint & point)
//{
//	// TODO: �ڴ˴����� return ���
//	APoint pos(point[0],point[1],point[2]);
//	return APoint(M[0],M[1],M[2]) - pos;
//}
//AVector APoint::operator-(const APoint & point)
//{
//	AVector dpos(point.M[0], point.M[1], point.M[2]);
//	AVector opos(M[0], M[1], M[2]);
//	return dpos - opos;
//}
//APoint::APoint(float a, float b, float c, float d)
//{
//	M[0] = a;
//	M[1] = b;
//	M[2] = c;
//	M[3] = d;
//}
//
//AVector::AVector()
//{
//	M[0] = 0;
//	M[1] = 0;
//	M[2] = 0;
//}
//AVector::AVector(float x, float y, float z)
//{
//	M[0] = x;
//	M[1] = y;
//	M[2] = z;
//}
//
//
//float AVector::operator*(const AVector& v)
//{
//	return v.M[0] * M[0] + v.M[1] * M[1] + v.M[2] * M[2];
//}
//AVector AVector::cross(const AVector& v)
//{
//	AVector temp = v;
//	temp = AVector( M[1] * temp[2] - temp[1] * M[2], M[2] * temp[0] - temp[2] * M[0],-( M[0] * temp[1] - temp[0] * M[1]));
//	return temp.Normal();
//}
//
//AVector::AVector(const AVector& v)
//{
//	M[0] = v.M[0];
//	M[1] = v.M[1];
//	M[2] = v.M[2];
//}
//AVector& AVector::operator = (AVector& v)
//{
//	M[0] = v[0];
//	M[1] = v[1];
//	M[2] = v[2];
//	return *this;
//}
//Vector4D::Vector4D(Vector4D& v)
//{
//	M[0] = v[0];
//	M[1] = v[1];
//	M[2] = v[2];
//	M[3] = v[3];
//}
//AVector& AVector::operator = (const Vector4D& v)
//{
//	M[0] = v.M[0];
//	M[1] = v.M[1];
//	M[2] = v.M[2];
//	return *this;
//}
//
//AVector AVector::operator-(AVector & v) const
//{
//	return AVector(v[0] - M[0],v[1] - M[1],v[2] - M[2]);
//}
//
//Vector4D& Vector4D::operator = (const Vector4D& v)
//{
//	M[0] = v.M[0];
//	M[1] = v.M[1];
//	M[2] = v.M[2];
//	M[3] = v.M[3];
//	return *this;
//}
//Vector4D::Vector4D(float x, float y, float z, float w)
//{
//	M[0] = x;
//	M[1] = y;
//	M[2] = z;
//	M[3] = w;
//}
//Matrix3X3::Matrix3X3()
//{
//	{
//		memcpy_s(M, sizeof(M), Identity_3X3, 9 * sizeof(float));
//	}
//}
//Matrix3X3::Matrix3X3(float* m)
//{
//	if (m != NULL)
//	{
//		memcpy_s(M, sizeof(M), m, 9 * sizeof(float));
//	}
//
//}
//
//Matrix3X3::Matrix3X3(const Matrix3X3& m)
//{
//	{
//		if (m.M != NULL)
//		{
//			memcpy_s(M, sizeof(M), m.M, 9 * sizeof(float));
//		}
//	}
//}
//
//
//Matrix3X3& Matrix3X3::operator=(const Matrix3X3& m)
//{
//	if (m.M != NULL)
//	{
//		memcpy_s(M, sizeof(M), m.M, 9 * sizeof(float));
//	}
//	return *this;
//}
//Matrix3X3& Matrix3X3::operator=(float m[])
//{
//	memcpy_s(M, sizeof(M), m, 9 * sizeof(float));
//	return *this;
//}
//Matrix3X3 Matrix3X3::operator*(const Matrix3X3& m) const
//{
//	int row, col;
//	Matrix3X3 matTemp;
//	for (row = 0; row < 3; row++)
//	{
//		for (col = 0; col < 3; col++)
//		{
//			matTemp.M[row][col] = M[row][0] * m.M[0][col]
//				+ M[row][1] * m.M[1][col] +
//				M[row][2] * m.M[2][col];
//		}
//	}
//	return matTemp;
//}
//void Matrix3X3::operator*(AVector& m) const
//{
//	int row;
//	AVector matTemp;
//	for (row = 0; row < 4; row++)
//	{
//
//		matTemp.M[row] = M[row][0] * m.M[0]
//			+ M[row][1] * m.M[1] +
//			M[row][2] * m.M[2] + M[row][3] * m.M[3];
//
//	}
//	m = matTemp;
//	return;
//}
//
//void Matrix3X3::Tranvers()
//{
//	Matrix3X3 temp;
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			temp.M[j][i] = M[i][j];
//		}
//	}
//	*this = temp;
//}
//
//
//HMatrix::HMatrix()
//{
//	memcpy_s(M, sizeof(M), Identity_4X4, 16 * sizeof(float));
//}
//
//HMatrix::HMatrix(float* m)
//{
//	if (m != NULL)
//	{
//		memcpy_s(M, sizeof(M), m, 16 * sizeof(float));
//	}
//}
//
//HMatrix::HMatrix(const HMatrix& m)
//{
//	if (m.M != NULL)
//	{
//		memcpy_s(M, sizeof(M), m.M, 16 * sizeof(float));
//	}
//}
//
//HMatrix& HMatrix::operator = (const Matrix3X3& m)
//{
//	if (m.M != NULL)
//	{
//		for (int i = 0; i < 3; i++)
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				M[i][j] = m.M[i][j];
//			}
//		}
//	}
//	M[3][3] = 1.0f;
//	return *this;
//}
//
//HMatrix& HMatrix::operator = (const HMatrix& m)
//{
//	if (m.M != NULL)
//	{
//		memcpy_s(M, sizeof(M), m.M, 16 * sizeof(float));
//	}
//	return *this;
//}
//
//HMatrix HMatrix::operator*(const HMatrix& m)const
//{
//	int row, col;
//	HMatrix matTemp;
//	for (row = 0; row < 4; row++)
//	{
//		for (col = 0; col < 4; col++)
//		{
//			matTemp.M[row][col] = M[row][0] * m.M[0][col]
//				+ M[row][1] * m.M[1][col] +
//				M[row][2] * m.M[2][col] +
//				M[row][3] * m.M[3][col];
//		}
//	}
//	return matTemp;
//}
//
//void HMatrix::operator*(AVector& m)const
//{
//	int row;
//	Vector4D matTemp;
//	for (row = 0; row < 4; row++)
//	{
//
//		matTemp.M[row] = M[row][0] * m.M[0]
//			+ M[row][1] * m.M[1] +
//			M[row][2] * m.M[2] + M[row][3] * 1;
//
//	}
//	m = matTemp;
//	return;
//}
//APoint HMatrix::operator*(APoint& m) const
//{
//	int row;
//	APoint matTemp;
//	for (row = 0; row < 4; row++)
//	{
//
//		matTemp.M[row] = M[row][0] * m.M[0]
//			+ M[row][1] * m.M[1] +
//			M[row][2] * m.M[2] + M[row][3] * m.M[3];
//
//	}
//	m = matTemp;
//	return matTemp;
//}
//
//APoint HMatrix::operator*(APoint& m)const
//{
//	int row;
//	APoint matTemp;
//	for (row = 0; row < 4; row++)
//	{
//
//		matTemp.M[row] = M[row][0] * m.M[0]
//			+ M[row][1] * m.M[1] +
//			M[row][2] * m.M[2] + M[row][3] * 1;
//
//	}
//	m = matTemp;
//	return matTemp;
//}
//void HMatrix::operator*(Vector4D& m) const
//{
//	int row;
//	Vector4D matTemp;
//	for (row = 0; row < 4; row++)
//	{
//		matTemp.M[row] = M[row][0] * m.M[0]
//			+ M[row][1] * m.M[1] +
//			M[row][2] * m.M[2] +
//			M[row][3] * m.M[3];
//
//	}
//	m = matTemp;
//	return;
//}
//
//HMatrix HMatrix::Inverse(HMatrix& camera)const
//{
//	float det = M[0][0] * MStar(*this, 0, 0) + (-M[0][1] * MStar(*this, 0, 1))
//		+ M[0][2] * MStar(*this, 0, 2) + (-M[0][3] * MStar(*this, 0, 3));
//	if (abs(det) < 0.0000001f)
//	{
//		return *this;
//	}
//
//	float det_inv = 1.0f / det;
//	HMatrix temp;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			if ((i + j) % 2 == 0)
//				temp.M[i][j] = MStar(*this, i, j) * det_inv;
//			else
//				temp.M[i][j] = -MStar(*this, i, j) * det_inv;
//		}
//	}
//	camera = temp;
//	camera.Tranvers();
//	return temp;
//}
//
//HMatrix& HMatrix::Tranvers()
//{
//	HMatrix temp;
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			temp.M[j][i] = M[i][j];
//		}
//	}
//	*this = temp;
//	return *this;
//}
//
//HMatrix OBJECT;
//HMatrix CAMERA;
//HMatrix PROJECTION;
//
//
//Matrix3X3 reflection;
//void Matrix3X3::Reflection(AVector N)
//{
//	//U = (I - 2N * NT)V
//	float reflect[] = { 1 - N.M[0] * N.M[0], -N.M[0] * N.M[1], -N.M[0] * N.M[2],
//		-N.M[0] * N.M[1], 1 - N.M[1] * N.M[1], -N.M[1] * N.M[2],
//		-N.M[0] * N.M[2], N.M[1] * N.M[2], 1 - N.M[2] * N.M[2] };
//
//	reflection = (reflect);
//
//}
//float Fast_Sin(float theta)
//{
//	theta = fmodf(theta, 360.0f);
//	if (theta < 0.0f)
//		theta += 360;
//	int theta_int = (int)theta;
//	float theta_frac = theta - theta_int;
//	return (sin_look[theta_int] + theta_frac*(sin_look[theta_int + 1] - sin_look[theta_int]));
//}
//float Fast_Cos(float theta)
//{
//	theta = fmodf(theta, 360.0f);
//	if (theta < 0.0f)
//		theta += 360.0f;
//	int theta_int = (int)theta;
//	float theta_frac = theta - theta_int;
//	return  (cos_look[theta_int] + theta_frac*(cos_look[theta_int + 1] - cos_look[theta_int]));
//}
//
//void Build_Sin_Cos_Tables(void)
//{
//	for (int angle = 0; angle <= 360; angle++)
//	{
//		float theta = (float)angle * PI / (float)180;
//		cos_look[angle] = cos(theta);
//		sin_look[angle] = sin(theta);
//	}
//}
//
//int Fast_Distance2D(int x, int y)
//{
//	x = abs(x);
//	y = abs(y);
//	int mn = min(x, y);
//	return (x + y - (mn >> 1) - (mn >> 2) + (mn >> 4));
//}
//
//int Fast_Distance3D(int fx, int fy, int fz)
//{
//	/*
//	int temp;
//	int x, y, z;
//	x = fabs(fx) * 1024;
//	y = fabs(fy) * 1024;
//	z = fabs(fz) * 1024;
//	if (y < x) swap(x, y��temp);
//	if (z < y) swap(y, z, temp);
//	if (y < x) swap(x, y, temp);
//	int dist = (z + 11 * (y >> 5) + (x >> 2));
//	return ((float)(dist >> 10));*/
//	return 1;
//}
//
//void Polar2D_To_Point2D(Polar2D* polar, Point2D& rect)
//{
//	/*rect[0] = polar->r * cosf(polar->theta);
//	rect[1] = polar->r * sinf(polar->theta);*/
//}
//
//void  Init_Param_Line2D(Point2D& p_init, Point2D& p_term, Line2D& p)
//{
//	p.p0 = p_init;
//	p.p1 = p_term;
//	p.v = p_term - p_init;
//}
//int Intersect_Parm_Line2D(Line2D& p1, Line2D& p2, float* t1, float* t2)
//{
//	float det_p1p2 = (p1.v[0] * p2.v[1] - p1.v[1] * p2.v[0]);
//	if (abs(det_p1p2) < EPSILON_E6)
//	{
//		return PARM_LINE_NO_INTERSECT;
//	}
//	*t1 = (p2.v[0] * (p1.p0[1] - p2.p0[1]) - p2.v[1] * (p1.p0[0] - p2.p0[0])) / det_p1p2;
//
//	*t2 = (p1.v[0] * (p1.p0[1] - p2.p0[1]) - p1.v[1] * (p1.p0[0] - p2.p0[0])) / det_p1p2;
//
//	if ((*t1 >= 0) && (*t1 <= 1) && (*t2 >= 0) && (*t2 <= 1))
//		return(PARM_LINE_INTERSECT_IN_SEGMENT);
//	else
//		return(PARM_LINE_INTERSECT_OUT_SEGMENT);
//}
//void Compute_Parm_Line2D(Line2D& p, float t, Point2D& pt)
//{
//	pt[0] = p.v[0] * t;
//	pt[1] = p.v[1] * t;
//}
//float Compute_Object4DV1_Radius(Object* obj)
//{
//	if (Object4DV1 *New_pointer = static_cast<Object4DV1*>(obj))
//	if (NULL != New_pointer)
//	{
//		New_pointer->avg_radius = 0;
//		New_pointer->max_ratius = 0;
//		for (int vertex = 0; vertex < New_pointer->num_vertices; vertex++)
//		{
//			float t = sqrt(New_pointer->vlist_local[vertex][0] * New_pointer->vlist_local[vertex][0] +
//				New_pointer->vlist_local[vertex][1] * New_pointer->vlist_local[vertex][0] +
//				New_pointer->vlist_local[vertex][2] * New_pointer->vlist_local[vertex][2]);
//			New_pointer->avg_radius += t;
//
//			if (New_pointer->max_ratius)
//				New_pointer->max_ratius = t;
//		}
//		New_pointer->avg_radius /= New_pointer->num_vertices;
//		return(New_pointer->max_ratius);
//	}
//	else
//	{
//		return 0.0f;
//	}
//}
//
//
//char* Get_Line_PLG(char* buffer, int maxlength, FILE* fp)
//{
//	int length = 0;
//	int index = 0;
//	while (true)
//	{
//		if (!fp)
//			return NULL;
//		if (!fgets(buffer, maxlength, fp))
//			return NULL;
//		for (length = strlen(buffer), index = 0; isspace(buffer[index]); index++);
//
//		if (index >= length || buffer[index] == '#')
//			continue;
//		return (&buffer[index]);
//	}
//}
//
