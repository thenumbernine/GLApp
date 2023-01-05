#include "GLApp/GLApp.h"
#include "GLApp/ViewBehavior.h"
#include "GLCxx/gl.h"
#include <chrono>
#include <iostream>
#include "SDL.h"

struct Test : public ::GLApp::ViewBehavior<::GLApp::GLApp> {
	using Super = ::GLApp::ViewBehavior<::GLApp::GLApp>;

	using Clock = std::chrono::high_resolution_clock;
	std::chrono::time_point<Clock> startTime = std::chrono::high_resolution_clock::now();
	
	virtual std::string getTitle() { return "Spinning Triangle"; }

	virtual void init(Init const & args) {
		Super::init(args);

		SDL_version version;
		SDL_GetVersion(&version);
		std::cout << "SDL_GetVersion:" << std::endl;
		std::cout << (int)version.major << "." << (int)version.minor << "." << (int)version.patch << std::endl;
	}

	virtual void onUpdate() {
		Super::onUpdate();

		// SDL's version, get # milliseconds since SDL was initialized:
		// float t = SDL_GetTicks64() / 1000;
		//
		// C++'s version.
		// This is how you get the # of milliseconds since some epoch.
		// Welcome to the future, where everything is retarded.
		auto t = 1e-3 * std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - startTime).count();
		glRotated(t * 30, 0, 1, 0);
		
		glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex3f(-5, -4, 0);
		glColor3f(0, 1, 0);
		glVertex3f(5, -4, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0, 6, 0);
		glEnd();
	}
};

GLAPP_MAIN(Test)
