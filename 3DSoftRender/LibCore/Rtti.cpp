#include "CorePCH.h"
#include "Rtti.h"
using namespace Hikari;

Rtti::Rtti(const char* _name, const Rtti* _baseType)
{
	name = _name;
	Basetype = _baseType;
}

Rtti::~Rtti()
{

}

bool Rtti::IsDerived(const Rtti& type)const
{
	const Rtti* search = this;
	while (search)
	{
		if (search == &type)
		{
			return true;
		}
		search = search->Basetype;
	}
	return false;
}