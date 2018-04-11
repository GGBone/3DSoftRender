#pragma once
#include "Core\Rtti.h"
#include "Core\CoreLib.h"
#include "Core\Names.h"
#include <boost\uuid\uuid.hpp>
namespace Hikari
{
	class Object
	{
	public:
		//Run-Time type info
		virtual const Rtti& GetRttiType()const;
		bool IsExactly(const Rtti& _type)const;
		bool IsDerived(const Rtti& _type)const;
		bool IsExactlyTypeOf(const Object* _object)const;
		bool IsDerivedOf(const Object* _object)const;
		static const Rtti TYPE;

		//Names for Object
		virtual bool operator==(const Object& rhs)
		{
			return m_UUID == rhs.m_UUID;
		}
	public:
		void SetName(const std::string& _name);
		const std::string& GetName()const;
		virtual Object* GetObjectByName(const std::string& name);
		virtual void GetAllObjectsByName(const std::string& name, std::vector<Object*>& objects);
	private:
		std::string name;

	protected:
		Object():m_UUID(boost::uuids::random_generator()()) {};
		virtual ~Object() {};
		enum ConstructorType
		{
			NoUUID
		};
		Object(ConstructorType type);

		boost::uuids::uuid GetUUID()const { return m_UUID; }

	private:
		Object(const Object& copy);
		Object(Object&& copy);
		Object& operator=(const Object& other);

		boost::uuids::uuid m_UUID;
	};
#include "Object.inl"
}