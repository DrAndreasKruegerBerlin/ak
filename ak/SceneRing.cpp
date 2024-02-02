#include "../ak/SceneRing.h"
#include "../d3d/Device.h"
#include <d3dx9math.h>
#include <math.h>
#include <vector>

namespace ak
{

	void SceneRing::init(d3d::Device& dev)
	{
		if (buffer_)
		{
			throw std::runtime_error("buffer already used");
		}
		struct Point { FLOAT x_; FLOAT y_; FLOAT z_; };
		constexpr static const int noSeg = 50, noRing = 50;
		constexpr static const FLOAT radRing = 1, radTorus = 2;
		std::vector<std::vector<Point>> points{noRing};
		for (int iRing = 0; iRing < noRing; iRing++)
		{
			D3DXMATRIX matRotY;
			::D3DXMatrixRotationY(&matRotY, D3DXToRadian(-(360.0F * iRing) / noRing));
			D3DXMATRIX matTransZ0;
			::D3DXMatrixTranslation(&matTransZ0, 0, 0, -radTorus);
			D3DXMATRIX matRing = matTransZ0 * matRotY;
			points.at(iRing).resize(noSeg);
			for (int iSeg = 0; iSeg < noSeg; iSeg++)
			{
				D3DXMATRIX matRotX;
				::D3DXMatrixRotationX(&matRotX, D3DXToRadian((360.0F * iSeg) / noSeg));
				D3DXMATRIX matTransZ1;
				::D3DXMatrixTranslation(&matTransZ1, 0, 0, -radRing);
				D3DXMATRIX matRes = matTransZ1 * matRotX * matRing;
				points.at(iRing).at(iSeg) = { matRes._41, matRes._42, matRes._43 };
			}
		}
		std::vector<d3d::VertexBuffer::Vertex> vertices{};
		for (int iRing = 0; iRing < noRing; iRing++)
		{
			for (int iSeg = 0; iSeg < noSeg; iSeg++)
			{
				auto wrap = [](int x, int limit)->int {return (x < limit) ? x : 0; };
				Point& d0 = points.at(wrap(iRing, noRing)).at(wrap(iSeg, noSeg));
				Point& d1 = points.at(wrap(iRing, noRing)).at(wrap(iSeg + 1, noSeg));
				Point& u0 = points.at(wrap(iRing + 1, noRing)).at(wrap(iSeg, noSeg));
				Point& u1 = points.at(wrap(iRing + 1, noRing)).at(wrap(iSeg + 1, noSeg));
				const DWORD col = D3DCOLOR_XRGB(int((255.0f * iSeg) / noSeg), 0, int(255.0f * (noSeg-iSeg)/noSeg));
				vertices.push_back({ u1.x_, u1.y_, u1.z_, col });
				vertices.push_back({ d1.x_, d1.y_, d1.z_, col });
				vertices.push_back({ d0.x_, d0.y_, d0.z_, col });
				vertices.push_back({ d0.x_, d0.y_, d0.z_, col });
				vertices.push_back({ u0.x_, u0.y_, u0.z_, col });
				vertices.push_back({ u1.x_, u1.y_, u1.z_, col });
			}
		}
		buffer_ = dev.createVertexBuffer(vertices.size());
		buffer_.copy(vertices.begin(), vertices.end());
		dev.setRenderStateLight(false);    // turn off the 3D lighting
		dev.setRenderStateCullMode(d3d::Device::CullMode::CW);
		dev.setRenderStateZEnable(true);    // turn on the z-buffer
	}

	void SceneRing::render(d3d::Device& dev, com::TimePoint tpNow, com::TimePoint tpStart)
	{
		const bool isWire = 01;
		dev.setVertexFormat(buffer_.getVertexFormat());
		dev.setStreamSource(buffer_);
		dev.SetRenderStateFillmode(isWire ? d3d::Device::FillMode::WIREFRAME : d3d::Device::FillMode::SOLID);
		const std::size_t noVertices = buffer_.getNoOfVertices();
		D3DXMATRIX matRot, matRotx, matScale;
		const auto durSinceStart = tpNow - tpStart;
		const auto millisecs = durSinceStart.count() / 1'000'000 / 10;
		const FLOAT angelY = (2 * D3DX_PI) * (millisecs % 1'000) / 1'000;
		D3DXMatrixRotationY(&matRot, angelY);
		D3DXMatrixRotationX(&matRotx, 2 * D3DX_PI / 360 * 45);
		D3DXMatrixScaling(&matScale, 2, 2, 2);
		dev.setTransformWorld(matScale * matRotx * matRot);
		dev.drawPrimitive(noVertices);
		dev.SetRenderStateFillmode(d3d::Device::FillMode::SOLID);
	}

}
