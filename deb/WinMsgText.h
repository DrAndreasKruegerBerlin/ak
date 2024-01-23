#pragma once

#include <string>
#include <optional>
#include <Windows.h>

namespace deb
{

	std::string getWinMsgText(const UINT msg);

	std::optional<std::string> getOptionalWinMsgText(const UINT msg);

}
