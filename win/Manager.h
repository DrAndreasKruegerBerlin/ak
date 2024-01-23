#pragma once

#include <Windows.h>
#include "../win/AppBase.h"
#include <map>
#include <memory>
#include <string>
#include <optional>


namespace win
{

	class Manager
	{
	public:
		using AppBasePtrType = std::shared_ptr<win::AppBase>;
		using MapType = std::map<HWND, AppBasePtrType >;

	public:
		Manager(HINSTANCE hInst);
		~Manager();
		void passApp(AppBasePtrType spApp);
		int run();

	private:
		static void registerWindowClass();
		static void unregisterWindowClass();
		static LRESULT CALLBACK handleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT handleMessage(const win::Event& ev);
		static void createWindow(const Event& ev);
		static std::optional<LRESULT> passEvent(const win::Event& ev);
		static void destroyWindow(const win::Event& ev);

	private:
		static HINSTANCE hInst_;
		static MapType map_;
		static ATOM atomRegister_;
		static std::wstring nameWindowClass_;
	};

}
