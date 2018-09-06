#pragma once
namespace Hikari
{
	// CPU Access. Used for textures and Buffers
	enum class CPUAccess
	{
		None = 0,
		// No CPU access to this texture is necessary.
		Read = (1 << 0),
		// CPU reads permitted.
		Write = (1 << 1),
		// CPU writes permitted.
		ReadWrite = Read | Write
	};

	enum class GPUAccess
	{
		None = 0,
		Read = 1 << 0,
		Write = 1 << 1,
		ReadWrite = Read | Write
	};

	enum class ViewType
	{
	};
}
