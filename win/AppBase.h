#pragma once

#include <Windows.h>
#include "../d3d/context.h"
#include <string>
#include <optional>


namespace win
{

	// forward references
	struct Event;

	class AppBase
	{
	public:
		AppBase(const std::wstring& name, d3d::Context& context);
		virtual ~AppBase();		
		virtual std::optional<LRESULT> passEvent(const Event& ev) = 0;
		const std::wstring& getName() const;

	protected:
		std::wstring name_;
		d3d::Context context_;
	};

}
