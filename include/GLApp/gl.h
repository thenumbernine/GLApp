#pragma once

/*
notice that Common doesn't depend on GL
I'm just putting this in one place for all projects to reference
I would've put it in GLApp, but then projects that use GL but not GLApp would still need to reference GLApp
*/

#if PLATFORM_OSX

//for GLhandleARB, etc
#include <OpenGL/OpenGL.h>
#include <OpenGL/glext.h>

#include <OpenGL/gl.h>

#elif PLATFORM_LINUX

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

#elif PLATFORM_MSVC || PLATFORM_MINGW || PLATFORM_CLANG_WIN

#include <windows.h>
//#define GL_GLEXT_PROTOTYPES
#include "GL/glew.h"
#include <GL/gl.h>
//#include "GL/glext.h"

#endif	//PLATFORM_*
