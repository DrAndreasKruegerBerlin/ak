#include "../ak/View.h"
#include "../d3d/Device.h"
#include <d3dx9math.h>

namespace ak
{
	class ViewImpl
	{
	public:
		ViewImpl() = default;
		~ViewImpl() = default;
		void init(int width, int height)
		{ 
			// set the view transform to matView
			D3DXVECTOR3 out(0.0f, 0.0f, 15.0f), eye(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f);
			D3DXMatrixLookAtLH(&matView_,
				&out,   // the camera position
				&eye,   // the look-at position
				&up);   // the up direction

			// set the projection transform
			D3DXMatrixPerspectiveFovLH(&matProjection_,
				D3DXToRadian(45),    // the horizontal field of view
				FLOAT(width) / FLOAT(height), // aspect ratio
				1.0f,    // the near view-plane
				100.0f);    // the far view-plane
			height_ = height;
			width_ = width;
		}

		void render(d3d::Device& dev, int width, int height)
		{
			if (height_ != height || width_ != width)
			{
				init(width, height);
			}
			dev.setTransformView(matView_);   
			dev.setTransformProjection(matProjection_);
		}

	private:
		D3DXMATRIX matView_{};
		D3DXMATRIX matProjection_{};
		int height_{}, width_{};
	};

	View::View()
	{
		// must exist, because of pImpl idiom
	}

	View::~View()
	{
		// must exist, because of pImpl idiom
	}

	void View::init(int width, int height)
	{
		pImpl_->init(width, height);
	}

	void View::render(d3d::Device& dev, int width, int height)
	{
		pImpl_->render(dev, width, height);
	}

}
