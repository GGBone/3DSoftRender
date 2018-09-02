#pragma once
#include "Rtti.h"
#include "Names.h"

namespace Hikari
{
	class Object
	{
	public:
		//Run-Time type info
		virtual const Rtti& GetRttiType() const;
		bool IsExactly(const Rtti& _type) const;
		bool IsDerived(const Rtti& _type) const;
		bool IsExactlyTypeOf(const Object* _object) const;
		bool IsDerivedOf(const Object* _object) const;
		static const Rtti TYPE;

		//Names for Object
		virtual bool operator==(const Object& rhs)
		{
			return false;
		}

	public:
		void SetName(const std::string& _name);
		const std::string& GetName() const;
		virtual Object* GetObjectByName(const std::string& name);
		virtual void GetAllObjectsByName(const std::string& name, std::vector<Object*>& objects);
	private:
		std::string name;

	protected:
		Object() = default;
		virtual ~Object() = default;;

		enum ConstructorType
		{
			NoUUID
		};

		Object(ConstructorType type);

	private:
		Object(const Object& copy);
		Object(Object&& copy);
		Object& operator=(const Object& other);
	};

#include "Object.inl"
}
