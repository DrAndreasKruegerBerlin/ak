#include "../win/Timer.h"
#include <stdexcept>

namespace win
{

	Timer::~Timer()
	{
		kill();
	}

	/*
	void Timer::set(HWND hWnd, const UINT ms)
	{
		if (nullptr == hWnd_)
		{
			hWnd_ = hWnd;
		}
		else if (hWnd != hWnd_)
		{
			throw std::runtime_error("set timer (wnd)");
		}
		UINT_PTR ret = ::SetTimer(hWnd_, int(hWnd_), ms, nullptr);
		if (0 == ret)
		{
			throw std::runtime_error("set timer (api)");
		}
	}

	void Timer::kill()
	{
		if (nullptr != hWnd_)
		{
			const BOOL ok = ::KillTimer(hWnd_, int(hWnd_));
			hWnd_ = nullptr;
		}
	}
	*/

	void Timer::set(HWND hWnd, const UINT ms)
	{
		WAITORTIMERCALLBACK callback = [](PVOID pParameter, BOOLEAN isTimerOrWaitFired) -> void
		{
			HWND* phWnd = (HWND*) pParameter;
			if (nullptr != phWnd && nullptr != *phWnd)
			{
				//::PostMessage(*phWnd, WM_TIMER, WPARAM(* phWnd), 0);
				const BOOL ok = ::InvalidateRect(*phWnd, NULL, TRUE);
			}
		};

		if (nullptr != hTimerQueue_ || nullptr != hTimer_ || nullptr != hWnd_)
		{
			throw std::runtime_error("already used");
		}
		hTimerQueue_ = ::CreateTimerQueue();
		if (nullptr == hTimerQueue_)
		{
			throw std::runtime_error("bad CreateTimerQueue");
		}
		hWnd_ = hWnd;
		if (!::CreateTimerQueueTimer(&hTimer_, hTimerQueue_, callback, &hWnd_, ms, ms, 0))
		{
			kill();
			throw std::runtime_error("bad CreateTimerQueueTimer");
		}
	}

	void Timer::kill()
	{
		if (nullptr != hTimer_)
		{
			const BOOL ok = ::DeleteTimerQueueTimer(hTimerQueue_, hTimer_, NULL);
		}
		if (nullptr != hTimerQueue_)
		{
			const BOOL ok = ::DeleteTimerQueue(hTimerQueue_);
		}
		hWnd_ = nullptr;
		hTimer_ = nullptr;
		hTimerQueue_ = nullptr;
	}

	HWND Timer::getHWnd() const
	{
		return hWnd_;
	}

}
