#include "Tuple.h"
template<int Dimension, typename Type>
Hikari::Tuple<Dimension, Type>::Tuple()
{

}

template<int Dimension, typename Type>
Hikari::Tuple<Dimension, Type>::Tuple(const Tuple& tuple)
{
	for (int i = 0; i < Dimension; ++i)
	{
		mTuple[i] = tuple.mTuple[i];
	}
}

template<int Dimension, typename Type>
inline Hikari::Tuple<Dimension, Type>::operator const Type*() const
{
	return mTuple;
}

template<int Dimension, typename Type>
inline Hikari::Tuple<Dimension, Type>::operator Type*()
{
	return mTuple;
}

template<int Dimension, typename Type>
inline const Type& Hikari::Tuple<Dimension, Type>::operator[](int i) const
{
	return mTuple[i];
}

template<int Dimension, typename Type>
inline Type& Hikari::Tuple<Dimension, Type>::operator[](int i)
{
	return mTuple[i];
}

template<int Dimension, typename Type>
inline Tuple<Dimension, Type>& Hikari::Tuple<Dimension, Type>::operator=(const Tuple& tuple)
{
	for (int i = 0; i < Dimension; ++i)
	{
		mTuple[i] = tuple.mTuple[i];
	}
	return *this;
}

template<int Dimension, typename Type>
inline bool Hikari::Tuple<Dimension, Type>::operator==(const Tuple & tuple) const
{
	return false;
}

template<int Dimension, typename Type>
inline bool Hikari::Tuple<Dimension, Type>::operator!=(const Tuple & tuple) const
{
	return false;
}

template<int Dimension, typename Type>
inline bool Hikari::Tuple<Dimension, Type>::operator<(const Tuple & tuple) const
{
	return false;
}

template<int Dimension, typename Type>
inline bool Hikari::Tuple<Dimension, Type>::operator>(const Tuple & tuple) const
{
	return false;
}
