#include "GLApp/GLApp.h"
#include "GLCxx/gl.h"
#include "Common/Exception.h"
#include "SDL.h"	//SDL_GL_*
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace GLApp {

void GLApp::initWindow() {
	sdlGLSetAttributes();
	Super::initWindow();

	context = SDL_GL_CreateContext(window);
	if (!context) throw Common::Exception() << "failed to create GL context";

#if PLATFORM_MSVC
	{
		GLenum err = glewInit();
		if (err != GLEW_OK) throw Common::Exception() << "GLEW failed to initialize with error " << glewGetErrorString(err);
	}
#endif

	SDL_GL_SetSwapInterval(0);
}

void GLApp::sdlGLSetAttributes() {
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

#ifdef PLATFORM_OSX
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
#endif
}

Uint32 GLApp::getSDLCreateWindowFlags() {
	return Super::getSDLCreateWindowFlags() | SDL_WINDOW_OPENGL;
}

std::string GLApp::getTitle() const {
	return "OpenGL App";
}

GLApp::~GLApp() {
	// hmm TODO pointer wrappers that dtor this function?
	if (context) SDL_GL_DeleteContext(context);
}

void GLApp::onResize() {
	Super::onResize();	// SDL_SetWindowSize
	glViewport(0, 0, screenSize.x, screenSize.y);
}

void GLApp::onUpdate() {
	//Super::onUpdate(); is empty
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLApp::postUpdate() {
	if (swap) SDL_GL_SwapWindow(window);
}

}
