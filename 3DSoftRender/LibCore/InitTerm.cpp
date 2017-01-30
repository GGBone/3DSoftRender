#include "CorePCH.h"
#include "InitTerm.h"
using namespace Hikari;

int InitTerm::msNumInitializers = 0;
InitTerm::Initializer InitTerm::msInitializers[MAX_ELEMENTS];
int InitTerm::msNumTerminators = 0;
InitTerm::Terminator InitTerm::msTerminators[MAX_ELEMENTS];

void Hikari::InitTerm::AddInitialize(Initializer function)
{
	msInitializers[++msNumInitializers] = function;
}

void Hikari::InitTerm::ExecuteInitializers()
{
	for (int i = 0 ; i < msNumInitializers; i++)
	{
		msInitializers[msNumInitializers]();
	}
}

void Hikari::InitTerm::AddTerminator(Terminator function)
{
	msTerminators[++msNumTerminators] = function;
}

void Hikari::InitTerm::ExecuteTerminators()
{
	for (int i = 0; i < msNumTerminators; i++)
	{
		msTerminators[msNumTerminators]();
	}
}
