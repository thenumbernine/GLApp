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
	Tensor::float3 pos;
	Tensor::Quat<float> angle;
	
	float zFar = 100;
	float zNear = .01f;
	
	//TODO this is really a viewOrbit variable
	float dist = 1.;

public:
	using Super::Super;

	virtual void setupProjection();
	virtual void setupModelview();
	virtual void mousePan(int dx, int dy);
	virtual void mouseZoom(int dx, int dy);
};

}
