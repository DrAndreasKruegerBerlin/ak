#include "../d3d/RuntimeError.h"
#include <d3d9.h>


namespace d3d {

	RuntimeError::Format::Format(const std::string& msg, const unsigned long line, const std::string& path)
	{
		prefix(line, path);
		str_ << msg;
	}

	RuntimeError::Format::Format(const HRESULT hr, const std::string& msg, const unsigned long line, const std::string& path)
	{
		prefix(line, path);
		str_ << msg;
		const auto hrError{ getHrError(hr) };
		if (hrError)
		{
			str_ << ", HR(0x" << std::hex << hr << "):" << *hrError;
		}
		else
		{
			str_ << ", HR(0x" << std::hex << hr << ")";
		}
	}

	RuntimeError::Format::operator std::string() const
	{
		return str_.str();
	}

	void RuntimeError::Format::prefix(const unsigned long line, const std::string& path)
	{
		str_ << "D3D Runtime Error (" << line << ", " << path << "): ";
	}

	std::optional<std::string> RuntimeError::Format::getHrError(const HRESULT hr)
	{
		switch (hr)
		{
		case D3D_OK:								return { "- no error -" };
		case D3DERR_WRONGTEXTUREFORMAT:				return { "wrong texture format" };
		case D3DERR_UNSUPPORTEDCOLOROPERATION:		return { "unsupported color operation" };
		case D3DERR_UNSUPPORTEDCOLORARG:			return { "unsupported color arg" };
		case D3DERR_UNSUPPORTEDALPHAOPERATION:		return { "unsupported alpha operation" };
		case D3DERR_UNSUPPORTEDALPHAARG:			return { "unsupported alpha arg" };
		case D3DERR_TOOMANYOPERATIONS:				return { "too many operations" };
		case D3DERR_CONFLICTINGTEXTUREFILTER:		return { "conflicting texture filter" };
		case D3DERR_UNSUPPORTEDFACTORVALUE:			return { "unsupported factor value" };
		case D3DERR_CONFLICTINGRENDERSTATE:			return { "conflicting render state" };
		case D3DERR_UNSUPPORTEDTEXTUREFILTER:		return { "unsupported texture filter" };
		case D3DERR_CONFLICTINGTEXTUREPALETTE:		return { "conflicting texture palette" };
		case D3DERR_DRIVERINTERNALERROR:			return { "driver internal error" };
		case D3DERR_NOTFOUND:						return { "not found" };
		case D3DERR_MOREDATA:						return { "more data" };
		case D3DERR_DEVICELOST:						return { "device lost" };
		case D3DERR_DEVICENOTRESET:					return { "device not reset" };
		case D3DERR_NOTAVAILABLE:					return { "not available" };
		case D3DERR_OUTOFVIDEOMEMORY:				return { "out of video memory" };
		case D3DERR_INVALIDDEVICE:					return { "invalid device" };
		case D3DERR_INVALIDCALL:					return { "invalid call" };
		case D3DERR_DRIVERINVALIDCALL:				return { "driver invalid call" };
		case D3DERR_WASSTILLDRAWING:				return { "was still drawing" };
		case D3DOK_NOAUTOGEN:						return { "no autogen" };
#if !defined(D3D_DISABLE_9EX)
		case D3DERR_DEVICEREMOVED:					return { "device removed" };
		case S_NOT_RESIDENT:						return { "not resident" };
		case S_RESIDENT_IN_SHARED_MEMORY:			return { "resident in shared memory" };
		case S_PRESENT_MODE_CHANGED:				return { "present mode changed" };
		case S_PRESENT_OCCLUDED:					return { "present occluded" };
		case D3DERR_DEVICEHUNG:						return { "device hung" };
		case D3DERR_UNSUPPORTEDOVERLAY:				return { "unsupported overlay" };
		case D3DERR_UNSUPPORTEDOVERLAYFORMAT:		return { "unsupported overlay format" };
		case D3DERR_CANNOTPROTECTCONTENT:			return { "cannot protect content" };
		case D3DERR_UNSUPPORTEDCRYPTO:				return { "unsupported crypto" };
		case D3DERR_PRESENT_STATISTICS_DISJOINT:	return { "present statistics disjoint" };
#endif
		default:
			break;
		}
		return {};
	}

}
