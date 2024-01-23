#include "../win/Manager.h"
#include "../win/Event.h"
#include "../deb/Debug.h"
#include "../deb/WinMsgText.h"
#include <stdexcept>
#include <vector>

namespace win
{
	HINSTANCE        Manager::hInst_{ nullptr };
	Manager::MapType Manager::map_{};
	ATOM             Manager::atomRegister_{ 0 };
	std::wstring     Manager::nameWindowClass_{};

	Manager::Manager(HINSTANCE hInst)
	{
		if (nullptr != hInst_ || 0 != atomRegister_)
		{
			throw std::runtime_error("Manager already instantiated");
		}
		hInst_ = hInst;
		registerWindowClass();
		map_.clear();
	};

	Manager::~Manager()
	{
		/*
		* Destroy not directly by erasing a map element, instaed call the API
		* DestroyWindow that will erase the corresponding map element with the attached
		* application by sending the message WM_NCDESTROY.
		*/
		while (! map_.empty())
		{
			BOOL ret = ::DestroyWindow(map_.begin()->first);
		}
		unregisterWindowClass();
		hInst_ = nullptr;
	}

	void Manager::passApp(AppBasePtrType spApp)
	{
		const HWND hWnd = ::CreateWindowExW(
			0,
			nameWindowClass_.c_str(),
			spApp->getName().c_str(),
			WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			20, 20, 800, 600,
			NULL, NULL,
			hInst_,
			LPVOID(&spApp));
		if (nullptr == hWnd)
		{
			throw std::runtime_error("cannot create window for application");
		}
	}

	void Manager::registerWindowClass()
	{
		nameWindowClass_ = L"AK_BASIC_WINDOW_CLASS_V1.0";
		WNDCLASSEXW wc =
		{
			.cbSize = sizeof(wc),
			.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
			.lpfnWndProc = &Manager::handleMessage,
			.hInstance = hInst_,
			.hCursor = ::LoadCursor(NULL, IDC_ARROW),
			.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
			.lpszClassName = nameWindowClass_.c_str(),
		};
		atomRegister_ = ::RegisterClassExW(&wc);
		if (0 == atomRegister_)
		{
			throw std::runtime_error("bad RegisterClassEx");
		}
	}

	void Manager::unregisterWindowClass()
	{
		if (0 != atomRegister_)
		{
			const BOOL ret = ::UnregisterClassW(nameWindowClass_.c_str(), hInst_);
			if (ret)
			{
				atomRegister_ = 0;
			}
		}
	}

	LRESULT CALLBACK Manager::handleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		const win::Event ev{ hWnd, msg, wParam, lParam };
		LRESULT res{};
		try
		{
			res = handleMessage(ev);
		}
		catch (const std::exception& exc)
		{
			deb::Debug() << "Std. Exception: " << exc.what();
			res = ::DefWindowProc(ev.hWnd_, ev.msg_, ev.wParam_, ev.lParam_);
		}
		catch (...)
		{
			deb::Debug() << "Unknown Exception";
			res = ::DefWindowProc(ev.hWnd_, ev.msg_, ev.wParam_, ev.lParam_);
		}
		return res;
	}

	LRESULT Manager::handleMessage(const win::Event& ev)
	{
		deb::Debug() << "MSG(" << ::GetTickCount64() << "/" << ev.hWnd_ << "): " << deb::getWinMsgText(ev.msg_);
		if (ev.msg_ == WM_NCCREATE)
		{
			createWindow(ev);
		}
		std::optional<LRESULT> res = passEvent(ev);
		if (ev.msg_ == WM_NCDESTROY)
		{
			destroyWindow(ev);
		}
		if (!res)
		{
			return ::DefWindowProc(ev.hWnd_, ev.msg_, ev.wParam_, ev.lParam_);
		}
		return *res;
	}

	void Manager::createWindow(const win::Event& ev)
	{
		CREATESTRUCT* pCs = reinterpret_cast<CREATESTRUCT*>(ev.lParam_);
		if (nullptr == pCs || nullptr == pCs->lpCreateParams)
		{
			throw std::runtime_error("bad create struct");
		}
		AppBasePtrType* ppsApp = reinterpret_cast<AppBasePtrType*>(pCs->lpCreateParams);
		if (!map_.insert({ ev.hWnd_, *ppsApp }).second)
		{
			throw std::runtime_error("bad insert");
		}
	}

	std::optional<LRESULT> Manager::passEvent(const win::Event& ev)
	{
		MapType::iterator it{ map_.find(ev.hWnd_) };
		if (it != map_.end())
		{
			return it->second->passEvent(ev);
		}
		return {};
	}

	void Manager::destroyWindow(const win::Event& ev)
	{
		MapType::iterator it = map_.find(ev.hWnd_);
		if (it != map_.end())
		{
			map_.erase(it);
			if (map_.empty()) // if there is no element anymore, than we can quit it.
			{
				::PostQuitMessage(0);
				deb::Debug() << "map empty -> so quit";
			}
		}
	}

	int Manager::run()
	{
		deb::Debug() << "loop started";
		BOOL ret{ TRUE };
		MSG msg;
		while (TRUE == ret)
		{
			ret = GetMessage(&msg, nullptr, 0, 0);
			switch (ret)
			{
			case TRUE:
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				break;
			case FALSE:
				break;
			default: // yes, there is the possibility to get -1!
				throw std::runtime_error("bad GetMessage");
			}
		}
		deb::Debug() << "loop ended";
		return int(msg.wParam);
	}

}
