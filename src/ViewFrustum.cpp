#include "GLApp/ViewFrustum.h"
#include "GLApp/GLApp.h"
#include "GLApp/gl.h"
#include "Tensor/Vector.h"

namespace GLApp {

void ViewFrustum::setupProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float tanFovY = tan(fovY * M_PI / 360.f);
	glFrustum(
		tanFovY * -app->getAspectRatio() * zNear,
		tanFovY * app->getAspectRatio() * zNear,
		tanFovY * -zNear,
		tanFovY * zNear,
		zNear,
		zFar);
}

void ViewFrustum::setupModelview() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Tensor::Quat<float> angleAxis = angle.toAngleAxis();
	glRotatef(angleAxis(3) * 180. / M_PI, angleAxis(0), angleAxis(1), angleAxis(2));
	glTranslatef(-pos(0), -pos(1), -pos(2));
}

void ViewFrustum::mousePan(int dx, int dy) {
	float dist = (pos - orbit).length();
	orbit += angle.rotate(Tensor::float3(-dx,dy,0) * (dist * .1f));
	pos = angle.zAxis() * dist + orbit;
}

void ViewFrustum::mouseZoom(int dx, int dy) {
	pos = (pos - orbit) * exp(dy * -.03) + orbit;
}

void ViewFrustum::mouseRotate(int dx, int dy) {
	float magn = sqrt(dx * dx + dy * dy);
	magn *= tan(fovY * M_PI / 360.f);
	float fdx = (float)dx / magn;
	float fdy = (float)dy / magn;
	Tensor::Quat<float> rotation = Tensor::Quat<float>(fdy, fdx, 0, magn * M_PI / 180.).fromAngleAxis();
	angle = (rotation * angle).unit();
	pos = angle.zAxis() * (pos - orbit).length() + orbit;
}

}
