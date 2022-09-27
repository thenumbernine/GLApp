#include "GLApp/ViewOrtho.h"
#include "GLApp/GLApp.h"
#include "GLCxx/gl.h"

namespace GLApp {

void ViewOrtho::setupProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		pos.x - app->getAspectRatio() * .5 / zoom.x, 
		pos.x + app->getAspectRatio() * .5 / zoom.x,
		pos.y - .5 / zoom.y,
		pos.y + .5 / zoom.y, zNear, zFar);
}

void ViewOrtho::setupModelview() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ViewOrtho::mousePan(int dx, int dy) {
	pos += Tensor::float2(
		-(float)dx * app->getAspectRatio() / (float)app->getScreenSize().x,
		(float)dy / (float)app->getScreenSize().y
	) / zoom;
}

void ViewOrtho::mouseZoom(int dx, int dy) {
#if 0	//zoom separate
	zoom.x *= exp(-dx * -.03);
	zoom.y *= exp(dy * -.03);
#else	//zoom together
	zoom *= exp(dy * -.03);
#endif
}

void ViewOrtho::mouseRotate(int dx, int dy) {
	mousePan(dx, dy);
}

}
