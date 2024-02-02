#pragma once

#include <Windows.h>
#include "../win/AppBase.h"
#include <map>
#include <memory>
#include <string>
#include <optional>
#include <array>


namespace win
{

	class Manager
	{
	public:
		using AppBasePtrType = std::unique_ptr<win::AppBase>;
		using MapType = std::map<HWND, std::shared_ptr<win::AppBase> >;

	public:
		Manager(HINSTANCE hInst);
		~Manager();
		template<typename ...App>
		void passApps(App&& ... app)
		{
			std::array<AppBasePtrType, sizeof ... (app)> arrApp{{std::move(app) ...}};
			for (auto& a : arrApp)
				passApp(std::move(a));
		}
		void passApp(AppBasePtrType&& pApp);
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
		static ATOM      atomRegister_;
		static MapType   map_;
	};

}
