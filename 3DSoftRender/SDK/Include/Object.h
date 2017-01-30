#pragma once
#include "CoreLib.h"
#include "Rtti.h"
#include "Names.h"

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
	public:
		void SetName(const std::string& _name);
		const std::string& GetName()const;
		virtual Object* GetObjectByName(const std::string& name);
		virtual void GetAllObjectsByName(const std::string& name, std::vector<Object*>& objects);
	private:
		std::string name;


		//Streaming
	public:
		//	typedef Object* (*FactoryFunction)(InStream& stream);



		//Abstract base class,Construction and deconstruction
	protected:
		Object() {};
		virtual ~Object() {};
	};
#include "Object.inl"
}