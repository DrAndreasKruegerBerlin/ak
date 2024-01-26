#include "../d3d/VertexBuffer.h"
#include "../d3d/RuntimeError.h"

#include <algorithm>
#include <d3d9.h>

namespace d3d
{

	VertexBuffer::LockGuard::LockGuard(IDirect3DVertexBuffer9* pBuffer)
		: pBuffer_{pBuffer}
	{
		D3D_RUNTIME_ERROR_HR_CHECK(pBuffer_->Lock(0, 0, reinterpret_cast<void**>(& pMem_), 0));
	}

	VertexBuffer::LockGuard::~LockGuard()
	{
		pBuffer_->Unlock();
	}

	VertexBuffer::Vertex* VertexBuffer::LockGuard::getMem() const
	{
		return pMem_;
	}

	VertexBuffer::VertexBuffer(IDirect3DVertexBuffer9* pBuffer)
		: pBuffer_{ pBuffer }
	{
		if (nullptr == pBuffer_)
		{
			throw D3D_RUNTIME_ERROR("nullptr");
		}
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& buffer) noexcept
	{
		std::swap(buffer.pBuffer_, this->pBuffer_);
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& buffer) noexcept
	{
		if (this != &buffer)
		{
			if (nullptr != pBuffer_)
			{
				pBuffer_->Release();
				pBuffer_ = nullptr;
			}
			std::swap(buffer.pBuffer_, this->pBuffer_);
		}
		return *this;
	}

	VertexBuffer::~VertexBuffer()
	{
		if (nullptr != pBuffer_)
		{
			pBuffer_->Release();
			pBuffer_ = nullptr;
		}
	}

	size_t VertexBuffer::getSize() const
	{
		D3DVERTEXBUFFER_DESC desc;
		D3D_RUNTIME_ERROR_HR_CHECK(pBuffer_->GetDesc(&desc));
		const size_t size{ desc.Size / sizeof(Vertex) };
		return size;
	}

	void VertexBuffer::checkSize(const size_t size) const
	{
		if (size > getSize())
		{
			throw D3D_RUNTIME_ERROR("bad size");
		}
	}

	DWORD VertexBuffer::getVertexFormat() 
	{
		return format_;
	}

	const DWORD VertexBuffer::format_ = D3DFVF_XYZ | D3DFVF_DIFFUSE;
}
