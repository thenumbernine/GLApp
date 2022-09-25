#include "GLApp/View.h"
#include "GLApp/GLApp.h"

namespace GLApp {

View::View(::GLApp::GLApp* app_) 
: app(app_) {
}
	
View::~View() {}

void View::setup() {
	setupProjection();
	setupModelview();
}

void View::setupProjection() {}
void View::setupModelview() {}
void View::mousePan(int dx, int dy) {}
void View::mouseZoom(int dx, int dy) {}
void View::mouseRotate(int dx, int dy) {}

};
