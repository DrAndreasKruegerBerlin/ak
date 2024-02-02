#include "../d3d/Device.h"
#include "../d3d/VertexBuffer.h"
#include "../d3d/RuntimeError.h"

#include <algorithm>

#include <d3d9.h>
#include <d3dx9math.h>


namespace d3d
{

	Device::Device(IDirect3DDevice9* pDev)
		: pDev_{ pDev }
	{
		if (nullptr == pDev_)
		{
			throw D3D_RUNTIME_ERROR("nullptr");
		}
	}

	Device::Device(Device&& dev) noexcept
		: pDev_{nullptr}
	{
		std::swap(dev.pDev_, this->pDev_);
	}

	Device& Device::operator=(Device&& dev) noexcept
	{
		if (&dev != this)
		{
			if (nullptr != pDev_)
			{
				pDev_->Release();
				pDev_ = nullptr;
			}
			std::swap(dev.pDev_, this->pDev_);
		}
		return *this;
	}

	Device::~Device()
	{
		if (nullptr != pDev_)
		{
			pDev_->Release();
			pDev_ = nullptr;
		}
	}

	void Device::setTransformWorld(const D3DXMATRIX& mat)
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->SetTransform(D3DTS_WORLD, &mat));
	}

	void Device::setTransformProjection(const D3DXMATRIX& mat)
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->SetTransform(D3DTS_PROJECTION, &mat));
	}

	void Device::setTransformView(const D3DXMATRIX& mat)
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->SetTransform(D3DTS_VIEW, &mat));
	}

	void Device::clear()
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));
	}

	void Device::beginScene()
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->BeginScene());
	}

	void Device::endScene()
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->EndScene());
	}

	void Device::present()
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->Present(NULL, NULL, NULL, NULL));
	}

	void Device::setRenderStateLight(const bool on)
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->SetRenderState(D3DRS_LIGHTING, on ? TRUE : FALSE));
	}

	void Device::setRenderStateZEnable(const bool on)
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->SetRenderState(D3DRS_ZENABLE, on ? TRUE : FALSE));
	}

	void Device::setRenderStateCullMode(const CullMode mode)
	{
		DWORD cullmode{};
		switch (mode)
		{
		case CullMode::NONE:
			cullmode = D3DCULL_NONE;
			break;
		case CullMode::CW:
			cullmode = D3DCULL_CW;
			break;
		case CullMode::CCW:
			cullmode = D3DCULL_CCW;
			break;
		default:
			throw D3D_RUNTIME_ERROR("bad cull mode");
		}
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->SetRenderState(D3DRS_CULLMODE, cullmode));
	}

	void Device::SetRenderStateFillmode(const FillMode mode)
	{
		DWORD fillmode{};
		switch (mode)
		{
		case FillMode::POINT:
			fillmode = D3DFILL_POINT;
			break;
		case FillMode::SOLID:
			fillmode = D3DFILL_SOLID;
			break;
		case FillMode::WIREFRAME:
			fillmode = D3DFILL_WIREFRAME;
			break;
		default:
			throw D3D_RUNTIME_ERROR("bad fill mode");
		}
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->SetRenderState(D3DRS_FILLMODE, fillmode));
	}

	void Device::setVertexFormat(const DWORD format)
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->SetFVF(format));
	}

	void Device::drawPrimitive(const UINT count)
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->DrawPrimitive(D3DPT_TRIANGLELIST, 0, count));
	}

	VertexBuffer Device::createVertexBuffer(const size_t size)
	{
		IDirect3DVertexBuffer9* pBuffer{ nullptr };
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->CreateVertexBuffer(
			UINT(size * sizeof(VertexBuffer::Vertex)),
			0,
			VertexBuffer::getVertexFormat(),
			D3DPOOL_MANAGED,
			&pBuffer,
			NULL));
		return pBuffer;
	}

	void Device::setStreamSource(const VertexBuffer& buffer)
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pDev_->SetStreamSource(0, buffer.pBuffer_, 0, sizeof(VertexBuffer::Vertex)));
	}

}
