#include "App1.h"
#include "win/Event.h"
#include "win/Painter.h"
#include "deb/Debug.h"
#include <d3dx9math.h>
#include <stdexcept>


App1::App1(const std::wstring& name, d3d::Context& context)
	: win::AppBase(name, context)
	, device_{}
    , buffer_{}
	, timer_{}
{
	// do nothing
}

App1::~App1()
{
	// do nothing
}

std::optional<LRESULT> App1::passEvent(const win::Event& ev)
{
	switch (ev.msg_)
	{
	case WM_CREATE:
		return doCreate(ev);
	case WM_TIMER:
		return doTimer(ev);
	case WM_PAINT:
		return doPaint(ev);
	case WM_ERASEBKGND:
		return { 0 };
	default:
		break;
	}
	return {};
}

std::optional<LRESULT> App1::doCreate(const win::Event& ev)
{
	device_ = context_.createDevice(ev.hWnd_);
	std::vector<::d3d::VertexBuffer::Vertex> vertices =
	{
		{ 3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255)},
		{ 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0)},
		{ -3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0)},
		{ -3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255)},
		{ 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0,255,0)},
		{ 0.0f, -3.0f, 3, D3DCOLOR_XRGB(255,0,0)},
		{ 0.0f, -3.0f, 3, D3DCOLOR_XRGB(0,0,255)},
		{ 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0,255,0)},
		{ 3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(255,0,0)},
	};
	buffer_ = device_.createVertexBuffer(vertices.size());
	buffer_.copy(vertices.begin(), vertices.end());
	device_.setRenderStateLight(false);    // turn off the 3D lighting
	device_.setRenderStateCullMode(d3d::Device::CullMode::CW);    // 
	device_.setRenderStateZEnable(true);    // turn on the z-buffer
	last_ = start_ = Clock::now();
	timer_.set(ev.hWnd_, 50);
	return { 0 };
}

std::optional<LRESULT> App1::doTimer(const win::Event& ev)
{
	BOOL ok = 0;
	ok = ::InvalidateRect(ev.hWnd_, nullptr, TRUE);
	return { 0 };
}

std::optional<LRESULT> App1::doPaint(const win::Event& ev)
{
	win::Painter painter(ev.hWnd_);
	render(painter, ev);
	return { 0 };
}

void App1::render(const win::Painter& painter, const win::Event& ev)
{
	TimePoint ts = Clock::now();
	auto diff = (ts - last_).count() / 1'000'000;
	deb::Debug() << "Rendering (diff:" << diff << "ms)................";
	last_ = ts;

    RECT rectClient;
    ::GetClientRect(ev.hWnd_, &rectClient);

    device_.clear();

    device_.beginScene();

    // select which vertex format we are using
    device_.setVertexFormat(d3d::VertexBuffer::getVertexFormat());

    // set the view transform
    D3DXMATRIX matView;    // the view transform matrix
	D3DXVECTOR3 out(0.0f, 0.0f, 15.0f), eye(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f);
    D3DXMatrixLookAtLH(&matView,
        &out,   // the camera position
        &eye,   // the look-at position
        &up);   // the up direction
    device_.setTransformView(matView);    // set the view transform to matView

    // set the projection transform
    D3DXMATRIX matProjection;    // the projection transform matrix
    D3DXMatrixPerspectiveFovLH(&matProjection,
        D3DXToRadian(45),    // the horizontal field of view
        FLOAT(rectClient.right - rectClient.left) / FLOAT(rectClient.bottom - rectClient.top), // aspect ratio
        1.0f,    // the near view-plane
        100.0f);    // the far view-plane
    device_.setTransformProjection(matProjection);     // set the projection

    // select the vertex buffer to display
    device_.setStreamSource(buffer_);

    D3DXMATRIX matTranslateA;    // a matrix to store the translation for triangle A
    D3DXMATRIX matTranslateB;    // a matrix to store the translation for triangle B
    D3DXMATRIX matRotateY;       // a matrix to store the rotation for each triangle

	const auto durSinceStart = ts - start_;
	auto millisecs = durSinceStart.count() / 1'000'000 / 3;
	FLOAT index = (2 * D3DX_PI) * (millisecs % 1'000) / 1'000;

    // build MULTIPLE matrices to translate the model and one to rotate
    D3DXMatrixTranslation(&matTranslateA, 0.0f, 0.0f, 2.0f);
    D3DXMatrixTranslation(&matTranslateB, 0.0f, 0.0f, -2.0f);
    D3DXMatrixRotationY(&matRotateY, index);    // the front side

    // tell Direct3D about each world transform, and then draw another triangle
    device_.setTransformWorld(matTranslateA * matRotateY);
    device_.drawPrimitive(3);

    device_.setTransformWorld(matTranslateB * matRotateY);
    device_.drawPrimitive(3);

    device_.endScene();

    device_.present();
}
