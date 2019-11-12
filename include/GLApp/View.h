/*
superclass of ortho and frustum views
*/

#pragma once

namespace GLApp {
struct GLApp;

struct View {
	::GLApp::GLApp* app;

	View(::GLApp::GLApp* app_) 
	: app(app_)
	{}
	
	virtual void setupProjection() {}
	virtual void setupModelview() {}
	virtual void mousePan(int dx, int dy) {}
	virtual void mouseZoom(int dx, int dy) {}
};

}
