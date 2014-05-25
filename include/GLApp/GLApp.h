#pragma once

#include <stdlib.h>	//NULL
#include <SDL2/SDL.h>

class GLApp {
protected:
	bool done;
	SDL_Window *window;
	SDL_GLContext context;

public:

	/*
	the external program's subclass of GLApp will implement this to return an instance of itself
	 (using the GLAPP_MAIN macro)
	*/
	static GLApp *mainApp();

	GLApp();

	virtual int main(int argc = 0, char **argv = NULL);

	virtual void requestExit();	//request exit
	
	virtual void init();
	virtual void resize(int width, int height);
	virtual void sdlEvent(SDL_Event &event);
	virtual void update();
	virtual void shutdown();
	
	//used for window construction during init()
	virtual const char *getTitle();
	virtual int getSDLInitFlags();

	//used for access
	SDL_Window *getWindow() { return window; }
	SDL_GLContext getContext() { return context; }
};

#define GLAPP_MAIN(classname)	\
	GLApp *GLApp::mainApp() {	\
		static classname glapp_main;	\
		return &glapp_main;	\
	}

