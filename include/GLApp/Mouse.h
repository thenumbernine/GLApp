#pragma once

#include "Tensor/Vector.h"
#include "GLApp/gl.h"
#include "SDL.h"

namespace GLApp {

struct Mouse {
	Tensor::int2 ipos = {};
	Tensor::float2 pos = {};
	Tensor::float2 lastPos = {};
	Tensor::float2 deltaPos = {};
	bool leftDown = {};
	bool rightDown = {};
	bool lastLeftDown = {};
	bool lastRightDown = {};
	bool leftClick = {};
	bool rightClick = {};
	bool leftPress = {};
	bool leftRelease = {};
	bool rightPress = {};
	bool rightRelease = {};
	bool leftDragging = {};
	bool rightDragging = {};
	bool leftDragged = {};
	bool rightDragged = {};

	void update();
};

}
