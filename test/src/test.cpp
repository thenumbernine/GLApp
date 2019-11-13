#include "GLApp/gl.h"
#include "GLApp/GLApp.h"
#include "GLApp/ViewBehavior.h"
#include <chrono>

struct Test : public ::GLApp::ViewBehavior<::GLApp::GLApp> {
	using Super = ::GLApp::ViewBehavior<::GLApp::GLApp>;

	using Clock = std::chrono::high_resolution_clock;
	std::chrono::time_point<Clock> lastTime = Clock::now();

	float angle = 0;

	Test(const Init& args) : Super(args) {
		glClearColor(.5, .75, .75, 1.);
		viewFrustum->dist = 3.;
	}
	
	virtual void onUpdate() {
		std::chrono::time_point<Clock> thisTime = Clock::now();
		float deltaTime = 1e-9 * (double)std::chrono::duration_cast<std::chrono::nanoseconds>(thisTime - lastTime).count();
		lastTime = thisTime;
		
		Super::onUpdate();
		glMatrixMode(GL_MODELVIEW);
		glRotatef(angle,0.f,1.f,0.f);
		glBegin(GL_TRIANGLES);
		glColor3f(1.f,0.f,0.f);
		glVertex3f(0.f, 1.25f,0.f);
		glColor3f(0.f,1.f,0.f);
		glVertex3f(-1.f,-.75f,0.f);
		glColor3f(0.f,0.f,1.f);
		glVertex3f(1.f,-.75f,0.f);
		glEnd();
		angle += deltaTime * 360 * 10;	//10 revolutions per second
	}
};

GLAPP_MAIN(Test)
