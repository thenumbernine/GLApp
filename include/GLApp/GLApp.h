#pragma once

#include <stdlib.h>	//NULL
#include <SDL/SDL.h>

class GLApp {
private:
	bool done;
public:
	
	//the final link: have the external program subclassing GLApp implement this to return an instance of itself
	// (using the GLAPP_MAIN macro)
	static GLApp *mainApp();

	virtual int main(int argc = 0, char **argv = NULL);

	virtual void requestExit();	//request exit
	
	virtual void init();
	virtual void resize(int width, int height);
	virtual void sdlEvent(SDL_Event &event);
	virtual void update();
	virtual void shutdown();
};

#define GLAPP_MAIN(classname)	\
	GLApp *GLApp::mainApp() {	\
		static classname glapp_main;	\
		return &glapp_main;	\
	}

