#include "Core\Table.h"
#pragma once
template<int NUMROWS, int NUMCOLS, typename TYPE>
inline Hikari::Table<NUMROWS, NUMCOLS, TYPE>::Table()
{
}

template<int NUMROWS, int NUMCOLS, typename TYPE>
inline Hikari::Table<NUMROWS, NUMCOLS, TYPE>::~Table()
{
}

template<int NUMROWS, int NUMCOLS, typename TYPE>
inline Hikari::Table<NUMROWS, NUMCOLS, TYPE>::Table(const Table & table)
{
	for (int i = 0; i < NUMENTRIES; ++i)
	{
		mEntry = table.mEntry[i];
	}
}

template<int NUMROWS, int NUMCOLS, typename TYPE>
inline Hikari::Table<NUMROWS, NUMCOLS, TYPE>::operator const TYPE*() const
{
	return mEntry;
}

template<int NUMROWS, int NUMCOLS, typename TYPE>
inline Hikari::Table<NUMROWS, NUMCOLS, TYPE>::operator TYPE*()
{
	return mEntry;
}

template<int NUMROWS, int NUMCOLS, typename TYPE>
inline const TYPE * Hikari::Table<NUMROWS, NUMCOLS, TYPE>::operator[](int row) const
{
	return &mEntry[NUMCOLS * row];
}

template<int NUMROWS, int NUMCOLS, typename TYPE>
inline TYPE * Hikari::Table<NUMROWS, NUMCOLS, TYPE>::operator[](int row)
{
	return &mEntry[NUMCOLS * row];
}

template<int NUMROWS, int NUMCOLS, typename TYPE>
inline const TYPE & Hikari::Table<NUMROWS, NUMCOLS, TYPE>::operator()(int row, int col) const
{
	return mEntry[col + NUMCOLS * row];
}

template<int NUMROWS, int NUMCOLS, typename TYPE>
inline void Hikari::Table<NUMROWS, NUMCOLS, TYPE>::SetRow(int row, const Tuple<NUMCOLS, TYPE>& tuple)
{
	for (int c = 0, i = NUMCOLS * row; c < NUMCOLS; ++c, ++i)
	{
		mEntry[i] = tuple[c];
	}
}



template<int NUMROWS, int NUMCOLS, typename TYPE>
inline Tuple<NUMROWS, TYPE> Hikari::Table<NUMROWS, NUMCOLS, TYPE>::GetRow(int row) const
{
	Tuple<NUMROWS, TYPE> result;
	for (int c = 0, i = NUMCOLS * row; c < NUMCOLS; ++c, ++i)
	{
		result[c] = mEntry[i];
	}
	return result;
}

template<int NUMROWS, int NUMCOLS, typename TYPE>
inline void Hikari::Table<NUMROWS, NUMCOLS, TYPE>::SetColum(int col, const Tuple<NUMROWS, TYPE>& tuple)
{
	for (int r = 0, i = col; r < NUMROWS; ++r, i+= NUMCOLS)
	{
		mEntry[i] = tuple[r];
	}
}



template<int NUMROWS, int NUMCOLS, typename TYPE>
inline Tuple<NUMROWS, TYPE> Hikari::Table<NUMROWS, NUMCOLS, TYPE>::GetColum(int col) const
{
	Tuple<NUMROWS, TYPE> result;
	for (int r = 0, i = col; r < NUMROWS; ++r, i += NUMCOLS)
	{
		result[i] = tuple[r];
	}
	return result;
}

template<int NUMROWS, int NUMCOLS, typename TYPE>
inline Table<NUMROWS,NUMCOLS,TYPE>& Hikari::Table<NUMROWS, NUMCOLS, TYPE>::operator=(const Table & table)
{
	for (int i = 0; i < NUMENTRIES; i++)
	{
		mEntry[i] = table.mEntry[i];
	}
	return *this;
}


