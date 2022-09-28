#include "GLApp/ViewFrustum.h"
#include "GLApp/GLApp.h"
#include "GLCxx/gl.h"
#include "Tensor/Vector.h"

namespace GLApp {

void ViewFrustum::setupProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float tanFovY = tan(fovY * M_PI / 360.f);
	glFrustum(
		-zNear * tanFovY * app->getAspectRatio(),
		 zNear * tanFovY * app->getAspectRatio(),
		-zNear * tanFovY,
		 zNear * tanFovY,
		 zNear,
		 zFar);
}

void ViewFrustum::setupModelview() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	auto aa = angle.conjugate().toAngleAxis();
	glRotatef(aa.w * 180. / M_PI, aa.x, aa.y, aa.z);
	glTranslatef(-pos.x, -pos.y, -pos.z);
}

void ViewFrustum::mousePan(int dx, int dy) {
	float dist = (pos - orbit).length();
	orbit += angle.rotate(Tensor::float3(-dx,dy,0) * (dist * .1f));
	pos = angle.zAxis() * dist + orbit;
}

void ViewFrustum::mouseZoom(int dx, int dy) {
	pos = (pos - orbit) * (float)exp(dy * -.03) + orbit;
}

void ViewFrustum::mouseRotate(int dx, int dy) {
	float magn = sqrt(dx * dx + dy * dy);
	magn *= tan(fovY * M_PI / 360.f);
	float fdx = (float)dx / magn;
	float fdy = (float)dy / magn;
	Tensor::quatf rotation = Tensor::quatf(-fdy, -fdx, 0, magn * M_PI / 180.).fromAngleAxis();
	angle = normalize(angle * rotation);
	pos = angle.zAxis() * (pos - orbit).length() + orbit;
}

}
