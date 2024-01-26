#pragma once

#include "../d3d/VertexBuffer.h"
#include <Windows.h>

struct IDirect3DDevice9;
struct D3DXMATRIX;

namespace d3d
{

	class Device
	{
	public:
		enum class CullMode { NONE, CW, CCW };

	public:
		Device() noexcept = default;
		Device(const Device&) = delete;
		Device(Device&&) noexcept;
		~Device();
		Device& operator=(const Device&) = delete;
		Device& operator=(Device&&) noexcept;

		void setTransformWorld(const D3DXMATRIX& mat);
		void setTransformProjection(const D3DXMATRIX& mat);
		void setTransformView(const D3DXMATRIX& mat);

		void clear();
		void beginScene();
		void endScene();
		void present();

		void setRenderStateLight(const bool on);
		void setRenderStateZEnable(const bool on);
		void setRenderStateCullMode(const CullMode mode);

		void setVertexFormat(const DWORD format);
		void drawPrimitive(const UINT count);

		VertexBuffer createVertexBuffer(const size_t size);
		void setStreamSource(const VertexBuffer& buffer);

	private:
		Device(IDirect3DDevice9*);

	private:
		IDirect3DDevice9* pDev_ {nullptr};

	friend class Context;
	};
}
