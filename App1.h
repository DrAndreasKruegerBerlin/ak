#pragma once


#include "win/AppBase.h"
#include "d3d/Device.h"
#include "win/Timer.h"
#include <string>

// forward references
namespace d3d { class Context; }

class App1 : public win::AppBase
{
public: 
	App1(const std::wstring& name, d3d::Context& context);
	virtual ~App1();
	virtual std::optional<LRESULT> passEvent(const win::Event& ev);

private:
	std::optional<LRESULT> doCreate(const win::Event& ev);
	std::optional<LRESULT> doTimer(const win::Event& ev);

private:
	d3d::Device device_;
	win::Timer timer_;
	unsigned long long lastTimepoint_;
};
