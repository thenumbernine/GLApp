#pragma once

#include "GLApp/View.h"
#include "Tensor/Vector.h"
#include <memory>

namespace GLApp {
struct GLApp;

struct ViewOrtho : public View {
	using Super = View;

public:	//protected:	
	Tensor::Vector<float,2> pos;
	Tensor::Vector<float,2> zoom = {1,1};
	
	float zFar = -1;
	float zNear = 1;

public:
	using Super::Super;

	virtual void setupProjection();
	virtual void setupModelview();
	virtual void mousePan(int dx, int dy);
	virtual void mouseZoom(int dx, int dy);
};

}
