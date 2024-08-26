#include "GLApp/ViewFrustum.h"
#include "GLApp/GLApp.h"
#include "Tensor/Vector.h"
#ifdef GLAPP_VIEW_USE_GL_MATRIX_MODE
#include "GLCxx/gl.h"
#endif

namespace GLApp {

void ViewFrustum::setupProjection() {
	float tanFovY = tan(fovY * M_PI / 360.f);
#ifndef GLAPP_VIEW_USE_GL_MATRIX_MODE
	projMat = Tensor::frustum<float>(
		-zNear * tanFovY * app->getAspectRatio(),
		 zNear * tanFovY * app->getAspectRatio(),
		-zNear * tanFovY,
		 zNear * tanFovY,
		 zNear,
		 zFar);
#else
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(
		-zNear * tanFovY * app->getAspectRatio(),
		 zNear * tanFovY * app->getAspectRatio(),
		-zNear * tanFovY,
		 zNear * tanFovY,
		 zNear,
		 zFar);
#endif
}

void ViewFrustum::setupModelview() {
	auto aa = angle.conjugate().toAngleAxis();
#ifndef GLAPP_VIEW_USE_GL_MATRIX_MODE
	mvMat = Tensor::rotate<float>(aa.w, aa.axis())
		* Tensor::translate<float>(-pos);
#else
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(aa.w * 180. / M_PI, aa.x, aa.y, aa.z);
	glTranslatef(-pos.x, -pos.y, -pos.z);
#endif
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
