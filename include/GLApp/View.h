#pragma once

/*
superclass of ortho and frustum views
*/

namespace GLApp {
struct GLApp;

struct View {
	::GLApp::GLApp* app = {};

	View(::GLApp::GLApp* app_);
	
	virtual ~View();

	virtual void setup();
	
	virtual void setupProjection();
	virtual void setupModelview();
	virtual void mouseZoom(int dx, int dy);
	virtual void mousePan(int dx, int dy);
	virtual void mouseRotate(int dx, int dy);
};

}
