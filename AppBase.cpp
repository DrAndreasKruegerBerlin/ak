#include "../win/AppBase.h"
#include "../deb/Debug.h"

namespace win
{

	AppBase::AppBase(const std::wstring& name, d3d::Context& context)
		: name_{ name }
		, context_{context}
	{
		deb::Debug() << "Application " << name_ << " started...";
	}

	AppBase::~AppBase()
	{
		deb::Debug() << "Application " << name_ << " ended";
	}

	const std::wstring& AppBase::getName() const
	{
		return name_;
	}

}
