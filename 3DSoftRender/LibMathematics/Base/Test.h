#pragma once
struct Test3
{
	float X,
		Y, Z;

	Test3()
	{

	}
	Test3(float x, float y, float z)
	{
		this->X = x;
		this->Y = y;
		this->Z = z;

	}
};

struct Test4
{
	float X,
		Y, Z, W;
	Test4()
	{

	}
	Test4(float x, float y, float z, float w)
	{
		this->X = x;
		this->Y = y;
		this->Z = z;
		W = w;
	}
	Test4 operator=(const Test4& test)
	{
		return Test4(test.X, test.Y,test.Z, test.W);
	}
};