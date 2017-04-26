#pragma once
#include "CoreLib.h"
namespace Hikari
{
	template<int Dimension,typename Type>
	class Tuple
	{
	public:
		Tuple();
		Tuple(const Tuple& tup);

		inline operator const Type*() const;
		inline operator Type*();
		inline const Type& operator[](int i)const;
		inline Type& operator[](int i);

		Tuple& operator=(const Tuple& tuple);

		bool operator==(const Tuple& tuple)const;
		bool operator!=(const Tuple& tuple)const;
		bool operator<(const Tuple& tuple)const;
		bool operator>(const Tuple& tuple) const;

	protected:
		Type mTuple[Dimension];
	};
	
#include "Tuple.inl"
}