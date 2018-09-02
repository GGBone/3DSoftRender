#include "CorePCH.h"
#include "InitTerm.h"
using namespace Hikari;

int InitTerm::msNumInitializers = 0;
InitTerm::Initializer InitTerm::msInitializers[MAX_ELEMENTS];
int InitTerm::msNumTerminators = 0;
InitTerm::Terminator InitTerm::msTerminators[MAX_ELEMENTS];

void InitTerm::AddInitialize(Initializer function)
{
	msInitializers[++msNumInitializers] = function;
}

void InitTerm::ExecuteInitializers()
{
	for (int i = 0; i < msNumInitializers; i++)
	{
		msInitializers[msNumInitializers]();
	}
}

void InitTerm::AddTerminator(Terminator function)
{
	msTerminators[++msNumTerminators] = function;
}

void InitTerm::ExecuteTerminators()
{
	for (int i = 0; i < msNumTerminators; i++)
	{
		msTerminators[msNumTerminators]();
	}
}
