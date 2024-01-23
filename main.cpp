#include <Windows.h>
#include "win/Manager.h"
#include "d3d/Context.h"
#include "deb/Debug.h"
#include "App1.h"
#include <stdexcept>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int ret{ 0 };
	try
	{
		::d3d::Context context{};
		::win::Manager manager{hInstance};
		manager.passApp(std::make_shared<App1>(L"APP1", context));
		manager.passApp(std::make_shared<App1>(L"APP2", context));
		manager.passApp(std::make_shared<App1>(L"APP3", context));
		ret = manager.run();
	}
	catch (const std::exception& exc)
	{
		deb::Debug() << "Std. Exception: " << exc.what();
		ret = 1;
	}
	catch (...)
	{
		deb::Debug() << "Unknown Exception";
		ret = 2;
	}
	return ret;
}
