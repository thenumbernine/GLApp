#include "GLApp/ViewOrtho.h"
#include "GLApp/GLApp.h"
#include "GLApp/gl.h"

namespace GLApp {

void ViewOrtho::setupProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		pos(0) - app->getAspectRatio() * .5 / zoom(0), 
		pos(0) + app->getAspectRatio() * .5 / zoom(0),
		pos(1) - .5 / zoom(1),
		pos(1) + .5 / zoom(1), zNear, zFar);
}

void ViewOrtho::setupModelview() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ViewOrtho::mousePan(int dx, int dy) {
	pos += Tensor::float2(
		-(float)dx * app->getAspectRatio() / (float)app->getScreenSize()(0),
		(float)dy / (float)app->getScreenSize()(1)
	) / zoom;
}

void ViewOrtho::mouseZoom(int dx, int dy) {
#if 0	//zoom separate
	zoom(0) *= exp(-dx * -.03);
	zoom(1) *= exp(dy * -.03);
#else	//zoom together
	zoom *= exp(dy * -.03);
#endif
}

}
