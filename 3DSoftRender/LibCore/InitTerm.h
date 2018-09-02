#pragma once

namespace Hikari
{
	class InitTerm
	{
	public:
		typedef void (*Initializer)(void);
		static void AddInitialize(Initializer function);
		static void ExecuteInitializers();
		typedef void (*Terminator)(void);
		static void AddTerminator(Terminator function);
		static void ExecuteTerminators();

	private:
		enum
		{
			MAX_ELEMENTS = 512
		};

		static int msNumInitializers;
		static Initializer msInitializers[MAX_ELEMENTS];
		static int msNumTerminators;
		static Terminator msTerminators[MAX_ELEMENTS];
	};
}

#define DECLARE_INITIALIZE	\
public:	\
	static bool RegisterInitialize();	\
	static void Initialize();			\
private:	\
	static bool msInitializeRegistered

#define IMPLEMENT_INITIALIZE(classname)	\
bool classname::msInitializeRegistered = false;	\
bool classname::RegisterInitialize()	\
{ \
	if (!msInitializeRegistered)	\
	{ \
		InitTerm::AddInitialize(classname::Initialize); \
		msInitializeRegistered = true;	\
	}\
	return msInitializeRegistered;\
}

#define REGISTER_INITIALIZE(classname)	\
	static bool gsInitializeRegistered_##classname = \
	classname::RegisterInitialize()

#define DECLEAR_TERMINATE	\
public:	\
	static bool RegisterTerminate();	\
	static void Terminate();			\
private: \
	static bool msTerminateRegistered

#define IMPLEMENT_TERMINATE(classname)	\
bool classname::msTerminateRegistered = false;	\
bool classname::RegisterTerminate() \
{\
	if (!msTerminateRegistered)\
	{\
		InitTerm::AddTerminator(classname::Terminate);	\
		msTerminateRegistered = true;	\
	}\
	return msTerminateRegistered;	\
}

#define REGISTER_TERMINATE(classname)	\
	static bool gsTerminateRegistered_##classname = \
classname::RegisterTerminate();
