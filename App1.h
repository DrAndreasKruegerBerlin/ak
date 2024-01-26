#pragma once


#include "win/AppBase.h"
#include "d3d/Device.h"
#include "d3d/VertexBuffer.h"
#include "win/Timer.h"
#include <string>
#include <chrono>

// forward references
namespace d3d { class Context; }

namespace win { class Painter;  }

class App1 : public win::AppBase
{
public:
	using Clock = std::chrono::steady_clock;
	using TimePoint = std::chrono::time_point<Clock>;

public: 
	App1(const std::wstring& name, d3d::Context& context);
	virtual ~App1();
	virtual std::optional<LRESULT> passEvent(const win::Event& ev);

private:
	std::optional<LRESULT> doCreate(const win::Event& ev);
	std::optional<LRESULT> doTimer(const win::Event& ev);
	std::optional<LRESULT> doPaint(const win::Event& ev);

private:
	void render(const win::Painter& painter, const win::Event& ev);

private:
	d3d::Device       device_;
	d3d::VertexBuffer buffer_;
	win::Timer        timer_;
	TimePoint         last_{};
	TimePoint         start_{};
};
