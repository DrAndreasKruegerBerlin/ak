#include "../d3d/Context.h"
#include "../d3d/RuntimeError.h"
#include "../deb/Debug.h"
#include <d3d9.h>

namespace d3d
{

	IDirect3D9* Context::pD3d_ = nullptr;
	UINT        Context::ref_ = 0;

	Context::Context()
	{
		if (nullptr == pD3d_)
		{
			pD3d_ = ::Direct3DCreate9(D3D_SDK_VERSION);
			if (nullptr == pD3d_)
			{
				throw D3D_RUNTIME_ERROR("bad Direct3DCreate9");
			}
			ref_ = 1;
			deb::Debug() << "Context created";
		}
		else
		{
			ref_++;
		}
	}

	Context::Context(const Context&)
	{
		ref_++;
	}

	Context::~Context()
	{
		if ((nullptr != pD3d_) && (0 != ref_))
		{
			ref_--;
			if (0 == ref_)
			{
				pD3d_->Release();
				pD3d_ = nullptr;
				deb::Debug() << "Context deleted";
			}
		}
	}

	Context& Context::operator=(const Context& context)
	{
		if (this != &context)
		{
			ref_++;
		}
		return *this;
	}

	Device Context::createDevice(const HWND hWnd)
	{
		RECT rectWnd;
		::GetWindowRect(hWnd, &rectWnd);

		D3DPRESENT_PARAMETERS para{ 0 };
		para.Windowed = TRUE;
		para.hDeviceWindow = hWnd;
		para.SwapEffect = D3DSWAPEFFECT_DISCARD;
		para.BackBufferFormat = D3DFMT_X8R8G8B8;
		para.BackBufferWidth = -rectWnd.left + rectWnd.right;
		para.BackBufferHeight = -rectWnd.top + rectWnd.bottom;
		para.EnableAutoDepthStencil = TRUE;
		para.AutoDepthStencilFormat = D3DFMT_D16;

		IDirect3DDevice9* pDev{ nullptr };
		D3D_RUNTIME_ERROR_HR_CHECK(pD3d_->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&para,
			&pDev));
		return pDev;
	}

}
