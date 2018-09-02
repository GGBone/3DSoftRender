#pragma once
namespace Hikari
{
	template <int Dimension, typename Type>
	class Tuple
	{
	public:
		Tuple();
		Tuple(const Tuple& tup);

		operator const Type*() const;
		operator Type*();
		const Type& operator[](int i) const;
		Type& operator[](int i);

		Tuple& operator=(const Tuple& tuple);

		bool operator==(const Tuple& tuple) const;
		bool operator!=(const Tuple& tuple) const;
		bool operator<(const Tuple& tuple) const;
		bool operator>(const Tuple& tuple) const;
	protected:
		Type mTuple[Dimension];
	};

#include "Tuple.inl"
}
