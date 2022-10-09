#include "GLApp/Mouse.h"
#include "GLCxx/gl.h"
#include "SDL.h"

namespace GLApp {

void Mouse::update() {
	lastPos = pos;
	int sdlButtons = SDL_GetMouseState(&ipos.x, &ipos.y);

	Tensor::int4 viewport;
	glGetIntegerv(GL_VIEWPORT, viewport.s.data());
	int viewWidth = viewport[2];
	int viewHeight = viewport[3];

	pos.x = (float)ipos.x / (float)viewWidth;
	pos.y = 1.f - (float)ipos.y / (float)viewHeight;

	deltaPos = pos - lastPos;

	lastLeftDown = leftDown;
	lastRightDown = rightDown;
	leftDown = (sdlButtons & (1 << (SDL_BUTTON_LEFT-1)));
	rightDown = (sdlButtons & (1 << (SDL_BUTTON_RIGHT-1)));

	leftClick = false;
	rightClick = false;
	leftPress = false;
	leftRelease = false;
	rightPress = false;
	rightRelease = false;
	leftDragging = false;
	rightDragging = false;

	if (leftDown) {
		if (!lastLeftDown) {
			leftPress = true;
			leftDragged = false;
		} else {
			if (deltaPos != Tensor::float2()) {
				leftDragging = true;
				leftDragged = true;
			}
		}
	} else {		// left up
		if (lastLeftDown && !leftDown) {			// mouse recorded the leftdown ... to make sure we didnt mousedown on gui and) { drag out
			leftRelease = true;
			if (!leftDragged) {						// left click -- TODO - a millisecond test?
				leftClick = true;
			}
			leftDragged = false;
			leftDown = false;
		}
	}

	if (rightDown) {	// right down
		if (!lastRightDown) {	// right press
			rightPress = true;
			rightDown = true;
			rightDragged = false;
		} else {
			if (deltaPos != Tensor::float2()) {
				rightDragging = true;
				rightDragged = true;
			}
		}
	} else {		// right up
		if (lastRightDown && !rightDown) {			// mouse recorded the rightdown ... to make sure we didnt mousedown on gui and) { drag out
			rightRelease = true;
			if (!rightDragged) {	// right click -- TODO - a millisecond test?
				rightClick = true;
			}
			rightDragged = false;
			rightDown = false;
		}
	}
}

}
