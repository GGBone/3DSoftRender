#include "Tuple.h"

template <int Dimension, typename Type>
Tuple<Dimension, Type>::Tuple()
{
}

template <int Dimension, typename Type>
Tuple<Dimension, Type>::Tuple(const Tuple& tuple)
{
	for (int i = 0; i < Dimension; ++i)
	{
		mTuple[i] = tuple.mTuple[i];
	}
}

template <int Dimension, typename Type>
Tuple<Dimension, Type>::operator const Type*() const
{
	return mTuple;
}

template <int Dimension, typename Type>
Tuple<Dimension, Type>::operator Type*()
{
	return mTuple;
}

template <int Dimension, typename Type>
const Type& Tuple<Dimension, Type>::operator[](int i) const
{
	return mTuple[i];
}

template <int Dimension, typename Type>
Type& Tuple<Dimension, Type>::operator[](int i)
{
	return mTuple[i];
}

template <int Dimension, typename Type>
Tuple<Dimension, Type>& Tuple<Dimension, Type>::operator=(const Tuple& tuple)
{
	for (int i = 0; i < Dimension; ++i)
	{
		mTuple[i] = tuple.mTuple[i];
	}
	return *this;
}

template <int Dimension, typename Type>
bool Tuple<Dimension, Type>::operator==(const Tuple& tuple) const
{
	return false;
}

template <int Dimension, typename Type>
bool Tuple<Dimension, Type>::operator!=(const Tuple& tuple) const
{
	return false;
}

template <int Dimension, typename Type>
bool Tuple<Dimension, Type>::operator<(const Tuple& tuple) const
{
	return false;
}

template <int Dimension, typename Type>
bool Tuple<Dimension, Type>::operator>(const Tuple& tuple) const
{
	return false;
}
