#include "GLApp/GLApp.h"
#include "Common/Exception.h"
#include <iostream>
#include <SDL/SDL.h>	//main
#include <OpenGL/gl.h>

using namespace std;

//main...
int main(int argc, char *argv[]) {
	return GLApp::mainApp()->main(argc, argv);
}

void GLApp::requestExit() {
	done = true;
}

int GLApp::main(int argc, char **argv) {
	done = false;
	int sdlInitFlags = SDL_INIT_VIDEO;

//SDL init

	try {
		int sdlInitError = SDL_Init(sdlInitFlags);
		if (sdlInitError) throw Exception() << "SDL_Init failed with error code " << sdlInitError;

		try {
			int width = 640;
			int height = 480;

			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			int screenFlags = SDL_OPENGL | SDL_DOUBLEBUF | SDL_RESIZABLE;
			
			/*SDL_Surface *screen = */SDL_SetVideoMode(width, height, 0, screenFlags);
			
			const char *title = "OpenGL App";
			SDL_WM_SetCaption(title, NULL);
			SDL_EnableKeyRepeat(0,0);
			//SDL_GL_SetSwapInterval(1);

			init();
			resize(width, height);

			SDL_Event event;
			do {
				while (SDL_PollEvent(&event) > 0) {
					switch (event.type) {
					case SDL_QUIT:
						done = true;
						break;
					case SDL_VIDEORESIZE:
						width = event.resize.w;
						height = event.resize.h;
						resize(width, height);
					case SDL_KEYDOWN:
#if PLATFORM==WINDOWS
							if (event.key.keysym.sym == SDLK_F4 && (event.key.keysym.mod & KMOD_ALT) != 0) {
								done = true;
							}
#endif
#if PLATFORM==OSX
							if (event.key.keysym.sym == SDLK_q && (event.key.keysym.mod & KMOD_META) != 0) {
								done = true;
							}
#endif
						break;
					}
					sdlEvent(event);
				}

				update();

				SDL_GL_SwapBuffers();
			} while (!done);

		} catch (std::exception &e) {
			cerr << e.what() << endl;
		}

		SDL_Quit();
	
	} catch (std::exception &e) {
		cerr << e.what() << endl;
	}

	shutdown();

	return 0;
}

void GLApp::init() {
}

void GLApp::resize(int width, int height) {
	glViewport(0, 0, width, height);
}

void GLApp::sdlEvent(SDL_Event &event) {
}

void GLApp::update() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLApp::shutdown() {
}
