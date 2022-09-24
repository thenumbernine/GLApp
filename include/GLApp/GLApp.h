#pragma once

#include "Tensor/Vector.h"

#include "SDL.h"
#include <vector>
#include <string>
#include <memory>

namespace GLApp {

struct GLApp {
protected:
	bool done = {};
	Tensor::Vector<int,2> screenSize = {640, 480};
	float aspectRatio = (float)screenSize(0) / (float)screenSize(1);
	SDL_Window *window = {};
	SDL_GLContext context = {};
	int exitCode = {};
public:
	bool swap = true;

public:
	//init args
	using Init = std::vector<std::string>;

	/*
	the external program's subclass of GLApp will implement this to return an instance of itself
	 (using the GLAPP_MAIN macro)
	*/
	static std::shared_ptr<::GLApp::GLApp> createMainApp();

	//vtable isn't set up yet so don't pass args into GLApp via ctor
	virtual void init(const Init& args);
	virtual ~GLApp();

	virtual void loop();

	virtual void requestExit();	//request exit
	virtual void requestExit(int code);

	virtual int getExitCode() const;

	virtual void onResize();
	virtual void onSDLEvent(SDL_Event &event);
	virtual void onUpdate();
	
	//used for window construction during init()
	virtual const char *getTitle();
	virtual int getSDLInitFlags();
	
	virtual Tensor::Vector<int,2> getScreenSize() const;
	virtual float getAspectRatio() const;

	//used for access
	SDL_Window *getWindow() { return window; }
	SDL_GLContext getGLContext() { return context; }
};

}

/*
Define this somewhere to provide the function which GLApp.cpp expects in its main() for building the App object

When declaring type names, when the namespace matches the class name that this is a static method within, I often have to use :: prefix to deonate the namespace is found in global scope and the class name is found in the namespace.
However I cannot use the :: prefix on the function name, or else it will give me an error "error: ‘GLApp’ in ‘class std::shared_ptr<GLApp::GLAppASDF>’ does not name a type" (even if I keep the namespace and class names distinct, i.e. struct GLApp -> struct GLAppASDF).
*/
#define GLAPP_MAIN(classname)\
namespace GLApp {\
	std::shared_ptr<::GLApp::GLApp> GLApp::GLApp::createMainApp() {\
		return std::dynamic_pointer_cast<::GLApp::GLApp>(std::make_shared<classname>());\
	}\
}
