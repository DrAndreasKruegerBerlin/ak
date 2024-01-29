#include <Windows.h>
#include "win/Manager.h"
#include "d3d/Context.h"
#include "deb/Debug.h"
#include "ak/App.h"
#include "ak/ScenePyramid.h"
#include "ak/SceneCube.h"
#include "ak/View.h"
#include <stdexcept>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int ret{ 0 };
	try
	{
		::d3d::Context context{};
		::win::Manager manager{hInstance};
		manager.passApp(std::make_shared<ak::App>(L"APP1", context, std::make_unique<ak::ScenePyramid>(), std::make_unique<ak::View>()));
		manager.passApp(std::make_shared<ak::App>(L"APP2", context, std::make_unique<ak::ScenePyramid>(), std::make_unique<ak::View>()));
		manager.passApp(std::make_shared<ak::App>(L"APP3", context, std::make_unique<ak::ScenePyramid>(), std::make_unique<ak::View>()));
		manager.passApp(std::make_shared<ak::App>(L"APP4", context, std::make_unique<ak::ScenePyramid>(), std::make_unique<ak::View>()));
		manager.passApp(std::make_shared<ak::App>(L"APP5", context, std::make_unique<ak::ScenePyramid>(), std::make_unique<ak::View>()));
		manager.passApp(std::make_shared<ak::App>(L"APP6", context, std::make_unique<ak::SceneCube>(), std::make_unique<ak::View>()));
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
