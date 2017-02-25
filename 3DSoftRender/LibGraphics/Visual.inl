#include "Visual.h"

inline const VertexBuffer * Hikari::Visual::GetVertexBuffer() const
{
	return mvBuffer;
}

inline const IndexBuffer * Hikari::Visual::GetIndexBuffer() const
{
	return miBuffer;
}


inline const VertexFormat* Hikari::Visual::GetVertexFormat() const
{
	return mvFormat;
}

inline const Visual::PrimitiveType Hikari::Visual::GetPrimitiveType() const
{
	return mType;
}

