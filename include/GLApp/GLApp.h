#pragma once

#include "Tensor/Vector.h"
#include "SDLApp/SDLApp.h"
#include "SDL.h"
#include <vector>
#include <string>
#include <memory>

namespace GLApp {

struct GLApp : public ::SDLApp::SDLApp {
	using Super = ::SDLApp::SDLApp;
protected:	
	SDL_GLContext context = {};
public:
	bool swap = true;

	virtual std::string getTitle() const;
protected:
	//used for window construction during init()
	virtual void initWindow();
	virtual Uint32 getSDLCreateWindowFlags();
	//override this to change SDL GL attributes
	virtual void sdlGLSetAttributes();

public:
	virtual ~GLApp();

	virtual void onResize();
	virtual void onUpdate();
	virtual void postUpdate();
	
	//used for access
	SDL_GLContext getGLContext() { return context; }
};

}

// hmm, old compat? just use SDLAPP_MAIN from here on out?
#define GLAPP_MAIN(classname) SDLAPP_MAIN(classname)
