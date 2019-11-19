#include "GLApp/gl.h"
#include "GLApp/GLApp.h"

#include "Common/Exception.h"

#include "SDL.h"	//main

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#if !defined(PLATFORM_msvc) && !defined(PLATFORM_clang_win)
#include <unistd.h>
#endif

//all just for the chdir ...
#if defined(PLATFORM_linux)
#include <linux/limits.h>	//PATH_MAX
#endif

//SDL_main...
int main(int argc, char *argv[]) {
	std::vector<std::string> args;
	std::copy(argv, argv+argc, std::back_inserter<std::vector<std::string>>(args));

//fix the fact that osx doesn't know where it is being run from
#ifdef PLATFORM_osx
	if (args.size() == 0) throw Common::Exception() << "expected arg for the exe path";
	std::string exe = args[0];
	exe = exe.substr(0, exe.find_last_of('/'));
	exe = exe.substr(0, exe.find_last_of('/')) + "/Resources";
	if (chdir(exe.c_str())) {
		throw Common::Exception() << "chdir failed with error " << errno;
	}
#endif
	
//you know, no guarantees for Linux either
//https://stackoverflow.com/questions/4025370/can-an-executable-discover-its-own-path-linux
#ifdef PLATFORM_linux
	pid_t pid = getpid();
	std::string path = "/proc/" + std::to_string(pid) + "/exe";

	std::vector<char> dest(PATH_MAX+1, 0);// readlink does not null terminate!
	if (readlink(path.c_str(), dest.data(), PATH_MAX) == -1) {
		throw Common::Exception() << "readlink failed to find the current path"; 
	}
	std::string deststr(dest.begin(), dest.end());
	deststr = deststr.substr(0, deststr.find_last_of('/'));
	if (chdir(deststr.c_str())) {
		throw Common::Exception() << "chdir failed with error " << errno;
	}
#endif
	
	std::shared_ptr<::GLApp::GLApp> app = ::GLApp::GLApp::createMainApp();
	app->init(args);
	app->loop();
	return app->getExitCode();
}

namespace GLApp {

void GLApp::init(const Init& args) {
//SDL init

	int sdlInitError = SDL_Init(getSDLInitFlags());
	if (sdlInitError) throw Common::Exception() << "SDL_Init failed with error code " << sdlInitError;
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(getTitle(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenSize(0), screenSize(1), SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	if (!window) throw Common::Exception() << "failed to create window";

	context = SDL_GL_CreateContext(window);
	if (!context) throw Common::Exception() << "failed to create GL context";

#if defined(PLATFORM_msvc)
	{
		GLenum err = glewInit();
		if (err != GLEW_OK) throw Common::Exception() << "GLEW failed to initialize with error " << glewGetErrorString(err); 
	}
#endif

	SDL_GL_SetSwapInterval(0);

	onResize();
}

GLApp::~GLApp() {
	if (context) SDL_GL_DeleteContext(context);
	if (window) SDL_DestroyWindow(window);
	SDL_Quit();
}

void GLApp::loop() {
	SDL_Event event;
	while (!done) {
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
			case SDL_QUIT:
				done = true;
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
				case SDL_WINDOWEVENT_RESIZED:
					screenSize(0) = event.window.data1;
					screenSize(1) = event.window.data2;
					aspectRatio = (float)screenSize(0) / (float)screenSize(1);
					onResize();
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
			onSDLEvent(event);
		}

		onUpdate();

		if (swap) SDL_GL_SwapWindow(window);
	}
}

void GLApp::requestExit() {
	done = true;
}

void GLApp::requestExit(int code) {
	exitCode = code;
	requestExit();
}

const char *GLApp::getTitle() {
	return "OpenGL App";
}

int GLApp::getSDLInitFlags() {
	return SDL_INIT_VIDEO;
}

void GLApp::onResize() {
	SDL_SetWindowSize(window, screenSize(0), screenSize(1));
	glViewport(0, 0, screenSize(0), screenSize(1));
}

void GLApp::onSDLEvent(SDL_Event& event) {
}

void GLApp::onUpdate() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}
