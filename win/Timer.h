#pragma once

#include <Windows.h>
#include "../com/Chrono.h"

namespace win
{

	class Timer
	{
	public:
		Timer() = default;
		~Timer();
		void set(HWND hWnd, const std::chrono::milliseconds period);
		void kill();
		HWND getHWnd() const;

	private:
		HANDLE hTimerQueue_{ nullptr };
		HANDLE hTimer_{ nullptr };
		HWND   hWnd_{ nullptr };
	};
}
