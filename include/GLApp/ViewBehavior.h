#include "GLApp/ViewOrtho.h"
#include "GLApp/ViewFrustum.h"

#include "SDL.h"
#include <memory>

namespace GLApp {

template<typename Parent>
struct ViewBehavior : public Parent {
	using Super = Parent;
	
	std::shared_ptr<::GLApp::ViewFrustum> viewFrustum;
	std::shared_ptr<::GLApp::ViewOrtho> viewOrtho;
	std::shared_ptr<::GLApp::View> view;
	
	//all these flags are used by the mouse input behavior capture below
	//TODO - put them in their own location (in libs.v2 they used to be in a 'Mouse' class)
	//also TODO - make the onSDLEvent toggle-able, or make this a object rather than a behavior
	bool leftButtonDown = false;
	bool leftShiftDown = false;
	bool rightShiftDown = false;
	bool leftGuiDown = false;
	bool rightGuiDown = false;

	ViewBehavior(const typename Super::Init& args)
	: Super(args)
	, viewFrustum(std::make_shared<::GLApp::ViewFrustum>(this))
	, viewOrtho(std::make_shared<::GLApp::ViewOrtho>(this))
	, view(viewFrustum)
	{
	}

	virtual void onUpdate() {
		Super::onUpdate();
		view->setup();
	}

	virtual void onSDLEvent(SDL_Event& event) {
		bool shiftDown = leftShiftDown || rightShiftDown;
		bool guiDown = leftGuiDown || rightGuiDown;
		
		switch (event.type) {
		case SDL_MOUSEMOTION:
			if (leftButtonDown && !guiDown) {
				int dx = event.motion.xrel;
				int dy = event.motion.yrel;
				if (shiftDown) {
					if (dx || dy) {
						view->mouseZoom(dx, dy);
					}
				} else {
					if (dx || dy) {
						view->mousePan(dx, dy);
					}
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				leftButtonDown = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				leftButtonDown = false;
			}
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LSHIFT) {
				leftShiftDown = true;
			} else if (event.key.keysym.sym == SDLK_RSHIFT) {
				rightShiftDown = true;
			} else if (event.key.keysym.sym == SDLK_LGUI) {
				leftGuiDown = true;
			} else if (event.key.keysym.sym == SDLK_RGUI) {
				rightGuiDown = true;
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LSHIFT) {
				leftShiftDown = false;
			} else if (event.key.keysym.sym == SDLK_RSHIFT) {
				rightShiftDown = false;
			} else if (event.key.keysym.sym == SDLK_LGUI) {
				leftGuiDown = false;
			} else if (event.key.keysym.sym == SDLK_RGUI) {
				rightGuiDown = false;
			}
			break;
		}

	}
};

}
