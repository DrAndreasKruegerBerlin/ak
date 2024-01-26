#pragma once


#include <windows.h>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>

namespace deb
{

	class Debug
	{
	public:
		Debug() : str_{} {}
		~Debug()
		{
			try
			{
				const std::wstring s = str_.str() + L'\n';
				::OutputDebugStringW(s.c_str());
			}
			catch (...)
			{
				; // just catch
			}
		}

		Debug& operator<<(const std::string& str)
		{
			return operator<<(str.c_str());
		}

		Debug& operator<<(LPCSTR psz)
		{
			const std::size_t size = std::strlen(psz) + 1U;
			std::vector<wchar_t> wc(size);
			std::size_t converted = 0;
			if (0 == mbstowcs_s(&converted, &wc.front(), wc.size(), psz, size) && size == converted)
				return operator<<(&wc.front());
			else
				return *this;
		}

		Debug& operator<<(LPCWSTR psz)
		{
			str_ << psz;
			return *this;
		}

		template<typename T>
		Debug& operator<<(const T& t)
		{
			str_ << t;
			return *this;
		}

	private:
		std::wstringstream str_;
	};

}
