#include "Visual.h"
inline const VertexBuffer * Hikari::Visual::GetVertexBuffer() const
{
	return mvBuffer;
}

inline const VisualPass * Hikari::Visual::GetVisualPass() const
{
	return mPass;
}

inline const VertexFormat* Hikari::Visual::GetVertexFormat() const
{
	return vFormat;
}

inline const Visual::PrimitiveType Hikari::Visual::GetPrimitiveType() const
{
	return mType;
}

