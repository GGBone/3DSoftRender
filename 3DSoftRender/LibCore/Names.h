#ifndef NAMES_H
#define NAMES_H
#include"Object.h"
#include <string>
#include <vector>
namespace Hikari
{
#define DECLARE_NAMES	\
public:\
	virtual Object* GetObjectByName(const std::string& Name); \
	virtual void GetAllObjectsByName(const std::string& Name, \
	std::vector<Object*>& objects)

#define IMPLEMENT_DEFAULT_NAMES(baseclassname,classname)	\
	Object* classname::GetObjectByName(const std::string& Name) \
	{ \
		return baseclassname::GetObjectByName(Name); \
	} \
	\
	void classname::GetAllObjectsByName(const std::string& name, \
	std::vector<Object*>& objects)	\
	{	\
		return baseclassname::GetAllObjectsByName(name, objects); \
	}

#define GET_OBJECT_BY_NAME(source,name,found)	\
	if (source)	\
	{	\
	found = source - <>GetObjectByName(name);	\
	if (found) \
	{ \
	return found; \
} \
}
#define GET_ALL_OBJECTS_BY_NAME(source,name,objects) \
	if (source) \
	{ \
	source->GetAllObjectsByName(name, object); \
}
}

#endif
