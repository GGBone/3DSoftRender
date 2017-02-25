#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H
#include "WindowApplication3.h"

namespace Hikari
{

	class ControlPoint
	{
	private:
		XMFLOAT3 position;
		XMFLOAT3 color;
		XMFLOAT3 tangent;
	public:
		ControlPoint() {}
		ControlPoint(XMFLOAT3 pos, XMFLOAT3 col) :position(pos), color(col) {}
		XMFLOAT3 GetPosition() { return position; }
		XMFLOAT3 GetColor() { return color; }
		XMFLOAT3 GetTangent() { return tangent; }
		void SetPosition(XMFLOAT3 pos) { position = pos; }
		void SetColor(XMFLOAT3 col) { color = col; }
		void SetTangent(XMFLOAT3 tan) { tangent = tan; }
	};
}

#endif