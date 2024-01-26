#pragma once


#include <Windows.h>
#include <stdexcept>
#include <sstream>
#include <string>
#include <optional>


namespace d3d {


	class RuntimeError : public std::runtime_error
	{
	private:
		class Format
		{
		public:
			Format(const std::string& msg, const unsigned long line, const std::string& path);
			Format(const HRESULT hr, const std::string& msg, const unsigned long line, const std::string& path);
			operator std::string() const;

		private:
			void prefix(const unsigned long line, const std::string& path);
			static std::optional<std::string> getHrError(const HRESULT hr);

		private:
			std::ostringstream str_{};
		};

	public:
		RuntimeError(const std::string& msg, const long line, const std::string& path)
			: std::runtime_error(Format(msg, line, path))
		{
			// do nothing
		}

		RuntimeError(const HRESULT hr, const std::string& msg, const long line, const std::string& path)
			: std::runtime_error(Format(hr, msg, line, path))
		{
			// do nothing
		}

	};

};


#define D3D_RUNTIME_ERROR(msg) ::d3d::RuntimeError(msg, __LINE__, __FILE__)
#define D3D_RUNTIME_ERROR_HR(hr, msg) ::d3d::RuntimeError(hr, msg, __LINE__, __FILE__)
#define D3D_RUNTIME_ERROR_HR_CHECK(statement) \
	do { \
		const HRESULT hr = statement; \
		if (FAILED(hr)) { \
			throw ::d3d::RuntimeError(hr, #statement, __LINE__, __FILE__); \
		} \
	} while(false)
