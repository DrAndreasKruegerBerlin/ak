#pragma once

#include <Windows.h>

namespace win
{

	class Timer
	{
	public:
		Timer() = default;
		~Timer();
		void set(HWND hWnd, const UINT ms);
		void kill();
		HWND getHWnd() const;

	private:
		HWND hWnd_{nullptr};
	};

}
