#pragma once

#include "GLApp/View.h"
#include "Tensor/Vector.h"
#include "Tensor/Quat.h"
#include <memory>

namespace GLApp {
struct GLApp;

struct ViewFrustum : public View {
	using Super = View;

public:	//protected:
	Tensor::float3 pos = {0,0,10};
	Tensor::Quat<float> angle;
	Tensor::float3 orbit;

	float fovY = 90;	//in degrees
	float zFar = 100;
	float zNear = .01f;

public:
	using Super::Super;

	virtual void setupProjection();
	virtual void setupModelview();
	virtual void mousePan(int dx, int dy);
	virtual void mouseZoom(int dx, int dy);
	virtual void mouseRotate(int dx, int dy);
};

}
