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
	Tensor::Vector<float,3> pos;
	Tensor::Quat<float> angle;
	float dist;

public:
	ViewFrustum(::GLApp::GLApp* app_);

	virtual void setupProjection();
	virtual void setupModelview();
	virtual void mousePan(int dx, int dy);
	virtual void mouseZoom(int dx, int dy);
};

}
