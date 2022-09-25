#include "GLApp/ViewFrustum.h"
#include "GLApp/GLApp.h"
#include "GLApp/gl.h"

namespace GLApp {

void ViewFrustum::setupProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-app->getAspectRatio() * zNear, app->getAspectRatio() * zNear, -zNear, zNear, zNear, zFar);
}

void ViewFrustum::setupModelview() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-dist);
	Tensor::Quat<float> angleAxis = angle.toAngleAxis();
	glRotatef(angleAxis(3) * 180. / M_PI, angleAxis(0), angleAxis(1), angleAxis(2));
	glTranslatef(-pos(0), -pos(1), -pos(2));
}

void ViewFrustum::mousePan(int dx, int dy) {
	float magn = sqrt(dx * dx + dy * dy);
	float fdx = (float)dx / magn;
	float fdy = (float)dy / magn;
	Tensor::Quat<float> rotation = Tensor::Quat<float>(fdy, fdx, 0, magn * M_PI / 180.).fromAngleAxis();
	angle = (rotation * angle).unit();
}

void ViewFrustum::mouseZoom(int dx, int dy) {
	dist *= (float)exp((float)dy * -.03f);
}

void ViewFrustum::mouseRotate(int dx, int dy) {
	mousePan(dx, dy);
}

}
