#pragma once

#include <Windows.h>
#include <algorithm>

struct IDirect3DVertexBuffer9;

namespace d3d
{
	class Device;
	class VertexBuffer
	{
	public:
		struct Vertex { FLOAT x_, y_, z_; DWORD color_; };

	private:
		class LockGuard
		{
		public:
			LockGuard() noexcept = default;
			LockGuard(IDirect3DVertexBuffer9*);
			~LockGuard();
			Vertex* getMem() const;
		private:
			IDirect3DVertexBuffer9* pBuffer_{nullptr};
			Vertex* pMem_{nullptr};
		};

	public:
		VertexBuffer() noexcept = default;
		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&&) noexcept;
		~VertexBuffer();
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&&) noexcept;
		static DWORD getVertexFormat();
		template<typename It>void copy(It begin, It end)
		{
			checkSize(std::distance(begin, end));
			LockGuard guard(pBuffer_);
			std::copy(begin, end, guard.getMem());
		};

	private:
		VertexBuffer(IDirect3DVertexBuffer9* pBuffer);
		size_t getSize() const;
		void checkSize(const size_t size) const;

	private:
		IDirect3DVertexBuffer9* pBuffer_ {nullptr};
		static const DWORD format_;

	friend class Device;
	};

}