#pragma once

#include <Windows.h>

namespace win
{

	struct Event
	{
		HWND hWnd_;
		UINT msg_;
		WPARAM wParam_;
		LPARAM lParam_;
	};
}
