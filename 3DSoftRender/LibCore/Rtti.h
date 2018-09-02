#pragma once
namespace Hikari
{
	class Rtti
	{
	public:
		Rtti(const char* _name, const Rtti* _baseType);
		~Rtti();

		inline const char* GetName() const;
		inline bool IsExactly(const Rtti& _type) const;
		bool IsDerived(const Rtti& _type) const;
	private:
		const char* name;
		const Rtti* Basetype;
	};


	inline const char* Rtti::GetName() const
	{
		return name;
	}

	inline bool Rtti::IsExactly(const Rtti& _type) const
	{
		return (&_type == this);
	}
}

#define DECLARE_RTTI \
	public: \
	static const Rtti TYPE; \
	\
	virtual const Rtti& GetRttiType()const \
{ \
	return TYPE; \
}

#define IMPLEMENT_RTTI(nsname,baseclassname,classname) \
	const Rtti classname::TYPE(#nsname"."#classname, &baseclassname::TYPE)
