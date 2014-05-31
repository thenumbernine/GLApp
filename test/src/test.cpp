#include <GLApp/GLApp.h>
#include <OpenGL/gl.h>
struct Test : public GLApp::GLApp {
	float angle;
	Test() : GLApp(), angle(0.) {}
	virtual void init() {
		GLApp::init();
		glClearColor(.5, .75, .75, 1.);
	}
	virtual void resize(int width, int height) {
		GLApp::resize(width, height);
		float aspectRatio = (float)width / (float)height;
		float zNear = .1f;
		float zFar = 100.f;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-aspectRatio * zNear, aspectRatio * zNear, -zNear, zNear, zNear, zFar);
	}
	virtual void update() {
		GLApp::update();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -2.f);
		glRotatef(angle,0.f,1.f,0.f);
		glBegin(GL_TRIANGLES);
		glColor3f(1.f,0.f,0.f);
		glVertex3f(0.f, 1.25f,0.f);
		glColor3f(0.f,1.f,0.f);
		glVertex3f(-1.f,-.75f,0.f);
		glColor3f(0.f,0.f,1.f);
		glVertex3f(1.f,-.75f,0.f);
		glEnd();
		++angle;
	}
};

GLAPP_MAIN(Test)

