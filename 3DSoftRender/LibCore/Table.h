#pragma once
#include "Core\Tuple.h"

namespace Hikari
{
	template <int NUMROWS,int NUMCOLS,typename TYPE>
	class Table
	{
	public:
		Table();
		~Table();
		Table(const Table& table);

		inline operator const TYPE* ()const;
		inline operator TYPE* ();
		inline const TYPE* operator[](int row)const;
		inline TYPE* operator[](int row);
		inline const TYPE& operator()(int row, int col)const;
		void SetRow(int row, const Tuple<NUMCOLS, TYPE>& Tuple);
		Tuple<NUMROWS, TYPE> GetRow(int row)const;
		void SetColum(int col, const Tuple<NUMROWS, TYPE>& tuple);
		Tuple<NUMROWS, TYPE> GetColum(int col)const;

		Table& operator= (const Table& table);


		bool operator==(const Table& table)const;
		bool operator!=(const Table& table)const;
		bool operator>(const Table& table)const;
		bool operator<(const Table& table)const;
		bool operator>=(const Table& table)const;
		bool operator<=(const Table& table)const;

	protected:
		enum 
		{
			NUMENTRIES = NUMROWS * NUMCOLS
		};
		TYPE mEntry[NUMENTRIES];
	};
#include "Table.inl"
}