#include "Object.h"
using namespace CORE;
//������Objectû�и��࣬�����������������
const Rtti Object::TYPE("Object", NULL);

const Rtti& Object::GetRttiType() const
{
	return TYPE;
}
bool Object::IsExactly(const Rtti& type)const
{
	return GetRttiType().IsExactly(type);
}
bool Object::IsDerived(const Rtti& type)const
{
	return GetRttiType().IsDerived(type);
}
bool Object::IsExactlyTypeOf(const Object* Object)const
{
	return Object && GetRttiType().IsExactly(Object->GetRttiType());
}
bool Object::IsDerivedOf(const Object* object)const
{
	return object && GetRttiType().IsDerived(object->GetRttiType());
}

void Object::SetName(const std::string& _name)
{
	name = _name;
}

const std::string& Object::GetName()const
{
	return name;
}

Object* Object::GetObjectByName(const std::string& _name)
{
	return name == _name ? this : 0;
}

void Object::GetAllObjectsByName(const std::string& _name, std::vector<Object*>& objects)
{
	if (name == _name)
	{
		objects.push_back(this);
	}
}



//streaming