#include "GLApp/GLApp.h"

#include "Common/Exception.h"
#include "Common/Finally.h"

#include <iostream>
#include <SDL2/SDL.h>	//main
#include <OpenGL/gl.h>
#include <string>
#include <vector>
#include <algorithm>

#ifdef PLATFORM_osx
#include <unistd.h>
#endif

//main...
int main(int argc, char *argv[]) {
	std::vector<std::string> args;
	std::copy(argv, argv+argc, std::back_inserter<std::vector<std::string>>(args));
#ifdef PLATFORM_osx
	if (args.size() == 0) throw Common::Exception() << "expected arg for the exe path";
	std::string exe = args[0];
	exe = exe.substr(0, exe.find_last_of('/'));
	exe = exe.substr(0, exe.find_last_of('/')) + "/Resources";
	chdir(exe.c_str());
#endif
	return ::GLApp::GLApp::mainApp()->main(args);
}

namespace GLApp {

GLApp::GLApp()
: window(nullptr)
, context(SDL_GLContext())
, swap(true)
{}

int GLApp::main(const std::vector<std::string>& args) {
	done = false;

//SDL init

	int sdlInitError = SDL_Init(getSDLInitFlags());
	if (sdlInitError) throw Common::Exception() << "SDL_Init failed with error code " << sdlInitError;

	Common::Finally sdlFinally([&](){ SDL_Quit(); });
		
	int width = 640;
	int height = 480;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(getTitle(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	if (!window) throw Common::Exception() << "failed to create window";
	Common::Finally sdlWindowFinally([&](){ SDL_DestroyWindow(window); });

	context = SDL_GL_CreateContext(window);
	if (!context) throw Common::Exception() << "failed to create GL context";

	SDL_GL_SetSwapInterval(0);

	init();
	resize(width, height);

	SDL_Event event;
	do {
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
			case SDL_QUIT:
				done = true;
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
				case SDL_WINDOWEVENT_RESIZED:
					width = event.window.data1;
					height = event.window.data2;
					resize(width, height);
					break;
				}
				break;
			case SDL_KEYDOWN:
#if PLATFORM_windows
					if (event.key.keysym.sym == SDLK_F4 && (event.key.keysym.mod & KMOD_ALT) != 0) {
						done = true;
					}
#endif
#if PLATFORM_osx
					if (event.key.keysym.sym == SDLK_q && (event.key.keysym.mod & KMOD_GUI) != 0) {
						done = true;
					}
#endif
				break;
			}
			sdlEvent(event);
		}

		update();

		if (swap) SDL_GL_SwapWindow(window);
	} while (!done);

	shutdown();

	return 0;
}

void GLApp::requestExit() {
	done = true;
}

const char *GLApp::getTitle() {
	return "OpenGL App";
}

int GLApp::getSDLInitFlags() {
	return SDL_INIT_VIDEO;
}

void GLApp::init() {
}

void GLApp::resize(int width, int height) {
	SDL_SetWindowSize(window, width, height);
	glViewport(0, 0, width, height);
}

void GLApp::sdlEvent(SDL_Event& event) {
}

void GLApp::update() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLApp::shutdown() {
}

};

