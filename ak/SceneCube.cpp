#include "../ak/SceneCube.h"
#include "../d3d/Device.h"
#include "../deb/Debug.h"
#include <d3dx9math.h>
#include <array>
#include <stdexcept>

namespace ak
{

	void SceneCube::init(d3d::Device& dev)
	{
		constexpr static const std::array vertices
		{
			d3d::VertexBuffer::Vertex{ 3,3,3, D3DCOLOR_XRGB(255, 0, 255)},
			d3d::VertexBuffer::Vertex{ 3,-3,3, D3DCOLOR_XRGB(255, 0, 255)},
			d3d::VertexBuffer::Vertex{ -3,-3,3, D3DCOLOR_XRGB(255, 0, 255)},
			d3d::VertexBuffer::Vertex{ 3,3,3, D3DCOLOR_XRGB(255, 0, 255)},
			d3d::VertexBuffer::Vertex{ -3,-3,3, D3DCOLOR_XRGB(255, 0, 255)},
			d3d::VertexBuffer::Vertex{ -3,3,3, D3DCOLOR_XRGB(255, 0, 255)},

			d3d::VertexBuffer::Vertex{ 3,3,3, D3DCOLOR_XRGB(0, 255, 255)},
			d3d::VertexBuffer::Vertex{ 3,-3,-3, D3DCOLOR_XRGB(0, 255, 255)},
			d3d::VertexBuffer::Vertex{ 3,-3,3, D3DCOLOR_XRGB(0, 255, 255)},
			d3d::VertexBuffer::Vertex{ 3,3,3, D3DCOLOR_XRGB(0, 255, 255)},
			d3d::VertexBuffer::Vertex{ 3,3,-3, D3DCOLOR_XRGB(0, 255, 255)},
			d3d::VertexBuffer::Vertex{ 3,-3,-3, D3DCOLOR_XRGB(0, 255, 255)},

			d3d::VertexBuffer::Vertex{ -3,3,3, D3DCOLOR_XRGB(255, 255, 255)},
			d3d::VertexBuffer::Vertex{ -3,-3,3, D3DCOLOR_XRGB(255, 255, 255)},
			d3d::VertexBuffer::Vertex{ -3,-3,-3, D3DCOLOR_XRGB(255, 255, 255)},
			d3d::VertexBuffer::Vertex{ -3,3,3, D3DCOLOR_XRGB(255, 255, 255)},
			d3d::VertexBuffer::Vertex{ -3,-3,-3, D3DCOLOR_XRGB(255, 255, 255)},
			d3d::VertexBuffer::Vertex{ -3,3,-3, D3DCOLOR_XRGB(255, 255, 255)},

			d3d::VertexBuffer::Vertex{ 3,3,-3, D3DCOLOR_XRGB(255, 255, 0)},
			d3d::VertexBuffer::Vertex{ -3,-3,-3, D3DCOLOR_XRGB(255, 255, 0)},
			d3d::VertexBuffer::Vertex{ 3,-3,-3, D3DCOLOR_XRGB(255, 255, 0)},
			d3d::VertexBuffer::Vertex{ 3,3,-3, D3DCOLOR_XRGB(255, 255, 0)},
			d3d::VertexBuffer::Vertex{ -3,3,-3, D3DCOLOR_XRGB(255, 255, 0)},
			d3d::VertexBuffer::Vertex{ -3,-3,-3, D3DCOLOR_XRGB(255, 255, 0)},

			d3d::VertexBuffer::Vertex{ 3,3,3, D3DCOLOR_XRGB(0, 255, 0)},
			d3d::VertexBuffer::Vertex{ -3,3,-3, D3DCOLOR_XRGB(0, 255, 0)},
			d3d::VertexBuffer::Vertex{ 3,3,-3, D3DCOLOR_XRGB(0, 255, 0)},
			d3d::VertexBuffer::Vertex{ 3,3,3, D3DCOLOR_XRGB(0, 255, 0)},
			d3d::VertexBuffer::Vertex{ -3,3,3, D3DCOLOR_XRGB(0, 255, 0)},
			d3d::VertexBuffer::Vertex{ -3,3,-3, D3DCOLOR_XRGB(0, 255, 0)},

			d3d::VertexBuffer::Vertex{ 3,-3,3, D3DCOLOR_XRGB(0, 0, 255)},
			d3d::VertexBuffer::Vertex{ 3,-3,-3, D3DCOLOR_XRGB(0, 0, 255)},
			d3d::VertexBuffer::Vertex{ -3,-3,-3, D3DCOLOR_XRGB(0, 0, 255)},
			d3d::VertexBuffer::Vertex{ 3,-3,3, D3DCOLOR_XRGB(0, 0, 255)},
			d3d::VertexBuffer::Vertex{ -3,-3,-3, D3DCOLOR_XRGB(0, 0, 255)},
			d3d::VertexBuffer::Vertex{ -3,-3,3, D3DCOLOR_XRGB(0, 0, 255)},
		};
		if (buffer_)
		{
			throw std::runtime_error("buffer already used");
		}
		buffer_ = dev.createVertexBuffer(vertices.size());
		buffer_.copy(vertices.begin(), vertices.end());
		dev.setRenderStateLight(false);    // turn off the 3D lighting
		dev.setRenderStateCullMode(d3d::Device::CullMode::CW);
		dev.setRenderStateZEnable(true);    // turn on the z-buffer
	}

	void SceneCube::render(d3d::Device& dev, com::TimePoint tpNow, com::TimePoint tpStart)
	{
		// select which vertex format we are using
		dev.setVertexFormat(d3d::VertexBuffer::getVertexFormat());

		// select the vertex buffer to display
		dev.setStreamSource(buffer_);

		D3DXMATRIX matRotateX;	     // a matrix to store the translation for second pyramid
		D3DXMATRIX matRotateY;       // a matrix to store the Y rotation 
		D3DXMATRIX matRotateZ;

		// calculate angel for rotation: 1 round in 3 second
		const auto durSinceStart = tpNow - tpStart;
		const auto millisecs = durSinceStart.count() / 1'000'000 / 4;
		const FLOAT angelY = (2 * D3DX_PI) * (millisecs % 1'000) / 1'000;
		D3DXMatrixRotationY(&matRotateY, angelY);    
		D3DXMatrixRotationX(&matRotateX, (2 * D3DX_PI / 360) * 45);

		// tell Direct3D about each world transform, and then draw another triangle
		dev.setTransformWorld(matRotateX * matRotateY);
		const std::size_t noVertices = buffer_.getNoOfVertices();
		dev.drawPrimitive(noVertices);

		D3DXMATRIX matTranslateX;
		D3DXMATRIX matScale;
		D3DXMatrixTranslation(&matTranslateX, 6, 0, 0);
		D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.2f);

		D3DXMatrixRotationY(&matRotateY, -angelY);
		dev.setTransformWorld(matScale * matTranslateX * matRotateX * matRotateY);
		dev.drawPrimitive(noVertices);

		D3DXMatrixRotationZ(&matRotateZ, -angelY + D3DX_PI / 2);
		dev.setTransformWorld(matScale * matTranslateX * matRotateX * matRotateZ);
		dev.drawPrimitive(noVertices);

		D3DXMatrixRotationY(&matRotateY, -angelY + D3DX_PI);
		dev.setTransformWorld(matScale *matTranslateX *  matRotateX * matRotateY);
		dev.drawPrimitive(noVertices);

		D3DXMatrixRotationZ(&matRotateZ, -angelY + 3*D3DX_PI/2);
		dev.setTransformWorld(matScale * matTranslateX * matRotateX * matRotateZ);
		dev.drawPrimitive(noVertices);
	}

}