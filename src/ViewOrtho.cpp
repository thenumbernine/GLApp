#include "GLApp/ViewOrtho.h"
#include "GLApp/GLApp.h"
#ifdef GLAPP_VIEW_USE_DEPRECATED_MATRIXMODE
#include "GLCxx/gl.h"
#endif

namespace GLApp {

void ViewOrtho::setupProjection() {
#ifndef GLAPP_VIEW_USE_DEPRECATED_MATRIXMODE
	projMat = Tensor::ortho<float>(
		-.5 / zoom.x * app->getAspectRatio(),
		 .5 / zoom.x * app->getAspectRatio(),
		-.5 / zoom.y,
		 .5 / zoom.y,
		 zNear,
		 zFar);
#else
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		-.5 / zoom.x * app->getAspectRatio(),
		 .5 / zoom.x * app->getAspectRatio(),
		-.5 / zoom.y,
		 .5 / zoom.y,
		 zNear,
		 zFar);
#endif
}

void ViewOrtho::setupModelview() {
#ifndef GLAPP_VIEW_USE_DEPRECATED_MATRIXMODE
	mvMat = Tensor::translate<float>(Tensor::float3(-pos.x, -pos.y, 0));
#else
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-pos.x, -pos.y, 0);
#endif
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
