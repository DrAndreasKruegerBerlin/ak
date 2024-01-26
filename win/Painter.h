#pragma once


#include <Windows.h>

namespace win
{

	class Painter
	{
	public:
		Painter(HWND hWnd);
		~Painter();

		operator HDC ()
		{
			return hDc_;
		}

		const PAINTSTRUCT& getPs() const
		{
			return ps_;
		}

	private:
		HWND hWnd_;
		HDC  hDc_;
		PAINTSTRUCT ps_;
	};

}
