#pragma once

#include <Windows.h>
#include "../d3d/Device.h"

struct IDirect3D9;

namespace d3d
{

	class Context
	{
	public:
		Context();
		Context(const Context&);
		Context(Context&&) = delete;
		~Context();
		Context& operator=(const Context&);
		Context& operator=(Context&&) = delete;
		Device createDevice(const HWND hwnd);

	private:
		static IDirect3D9* pD3d_;
		static unsigned int ref_;
	};

}
