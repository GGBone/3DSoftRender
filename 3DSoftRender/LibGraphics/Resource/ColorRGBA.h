#pragma once
namespace Hikari
{
	class ColorRGBA
	{
	public:
		ColorRGBA() = default;

		ColorRGBA(float r, float g, float b, float a) :
			r(r), g(g), b(b), a(a)
		{
		}

		float r, g, b, a;
	};
}
