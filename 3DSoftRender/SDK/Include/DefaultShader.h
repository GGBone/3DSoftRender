#pragma once
#include "GraphicsLib.h"
#include "HMatrix.h"
#include "HMath.h"
#include "HPoint.h"
#include "Float4.h"
namespace Hikari
{
	struct VInput
	{
		HPoint position; //:POSITION
		Float4 color;
		//Normal
		//Coord
	};
	struct PInput
	{
		HPoint position;
		Float4 color;
	};
	struct ConstantBuffer //c0
	{
		HMatrix model;
		HMatrix view;
		HMatrix projection;
	};
	class Cell
	{
	public:
		PInput VS_Main(VInput PIN);
		Float4 PS_Main(PInput PInput); //:SV_Target
		void UpdateConstantBuffer(ConstantBuffer* buffer);
	private:
		//default 8
		ConstantBuffer c0;
		ConstantBuffer c1;
	};

}