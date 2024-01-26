#include "../win/Painter.h"
#include <stdexcept>


namespace win
{

	Painter::Painter(HWND hWnd)
		: hWnd_{ hWnd }
		, hDc_{ ::BeginPaint(hWnd_, &ps_) }
	{
		if (nullptr == hDc_)
		{
			throw std::runtime_error("BeginPaint");
		}
	}

	Painter::~Painter()
	{
		const BOOL ok = ::EndPaint(hWnd_, &ps_);
	}

}
