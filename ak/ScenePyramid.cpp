#include "../ak/ScenePyramid.h"
#include "../d3d/Device.h"
#include "../deb/Debug.h"
#include <d3dx9math.h>
#include <array>
#include <stdexcept>

namespace ak
{

	void ScenePyramid::init(d3d::Device& dev)
	{
		constexpr static const std::array vertices
		{
			d3d::VertexBuffer::Vertex{ 3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255)},
			d3d::VertexBuffer::Vertex{ 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0)},
			d3d::VertexBuffer::Vertex{ -3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},
			d3d::VertexBuffer::Vertex{ -3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255)},
			d3d::VertexBuffer::Vertex{ 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0,255,0)},
			d3d::VertexBuffer::Vertex{ 0.0f, -3.0f, 3, D3DCOLOR_XRGB(255,0,0)},
			d3d::VertexBuffer::Vertex{ 0.0f, -3.0f, 3, D3DCOLOR_XRGB(0,0,255)},
			d3d::VertexBuffer::Vertex{ 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0,255,0)},
			d3d::VertexBuffer::Vertex{ 3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(255,0,0)}
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

	void ScenePyramid::render(d3d::Device& dev, com::TimePoint tpNow, com::TimePoint tpStart)
	{
		// select which vertex format we are using
		dev.setVertexFormat(d3d::VertexBuffer::getVertexFormat());

		// select the vertex buffer to display
		dev.setStreamSource(buffer_);

		D3DXMATRIX matTranslate1;    // a matrix to store the translation for first pyramid
		D3DXMATRIX matTranslate2;    // a matrix to store the translation for second pyramid
		D3DXMATRIX matRotateY;       // a matrix to store the rotation for each pyramid

		// calculate angel for rotation: 1 round in 3 second
		const auto durSinceStart = tpNow - tpStart;
		const auto millisecs     = durSinceStart.count() / 1'000'000 / 3;
		const FLOAT angel        = (2 * D3DX_PI) * (millisecs % 1'000) / 1'000;

		// build MULTIPLE matrices to translate the model and one to rotate
		D3DXMatrixTranslation(&matTranslate1, 0.0f, 0.0f, 2.0f);
		D3DXMatrixTranslation(&matTranslate2, 0.0f, 0.0f, -2.0f);
		D3DXMatrixRotationY(&matRotateY, -angel);    

		const std::size_t noVertices = buffer_.getNoOfVertices();

		// tell Direct3D about each world transform, and then draw another triangle
		dev.setTransformWorld(matTranslate1 * matRotateY);
		dev.drawPrimitive(noVertices);

		dev.setTransformWorld(matTranslate2 * matRotateY);
		dev.drawPrimitive(noVertices);
	}

}
