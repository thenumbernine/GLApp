#pragma once

#include "GLApp/ViewOrtho.h"
#include "GLApp/ViewFrustum.h"
#include "GLApp/Mouse.h"
#include "Tensor/Vector.h"

#include "SDL.h"
#include <memory>

namespace GLApp {

template<typename Super_>
struct ViewBehavior : public Super_ {
	using Super = Super_;
	
	std::shared_ptr<::GLApp::ViewFrustum> viewFrustum;
	std::shared_ptr<::GLApp::ViewOrtho> viewOrtho;
	std::shared_ptr<::GLApp::View> view;
	
	bool leftShiftDown = false;
	bool rightShiftDown = false;
	bool leftGuiDown = false;
	bool rightGuiDown = false;
	bool leftAltDown = false;
	bool rightAltDown = false;
	
	Mouse mouse;

	ViewBehavior() {
		viewFrustum = std::make_shared<::GLApp::ViewFrustum>(this);
		viewOrtho = std::make_shared<::GLApp::ViewOrtho>(this);
		view = viewFrustum;
	}

	virtual ~ViewBehavior() {}

	virtual void onUpdate() {
		mouse.update();
		Super::onUpdate();
		view->setup();
	}

	virtual void onSDLEvent(SDL_Event& event) {
		Super::onSDLEvent(event);
		
		bool shiftDown = leftShiftDown || rightShiftDown;
		bool guiDown = leftGuiDown || rightGuiDown;
		bool altDown = leftAltDown || rightAltDown;
		
		switch (event.type) {
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			{
				Tensor::int2 d;
				if (event.type == SDL_MOUSEMOTION) {
					d = {event.motion.xrel, event.motion.yrel};
				} else {
					d = Tensor::int2(event.wheel.x, event.wheel.y) * 10;
				}
				if (mouse.leftDown && !guiDown) {
					if (shiftDown) {
						if (d != Tensor::int2()) {
							view->mouseZoom(d.x, d.y);
						}
					} else if (altDown) {
						if (d != Tensor::int2()) {
							view->mousePan(d.x, d.y);
						}
					} else {
						if (d != Tensor::int2()) {
							view->mouseRotate(d.x, d.y);
						}
					}
				}
			}
			break;
#if 0 //moved into mouse.update where it polls the buttons
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			{
				bool down = event.type == SDL_MOUSEBUTTONDOWN;
				if (event.button.button == SDL_BUTTON_LEFT) {
					mouse.leftDown = down;
				} else if (event.button.button == SDL_BUTTON_RIGHT) {
					mouse.rightDown = down;
				}
			}
			break;
#endif		
		case SDL_KEYUP:
		case SDL_KEYDOWN:
			{
				bool down = event.type == SDL_KEYDOWN;
				if (event.key.keysym.sym == SDLK_LSHIFT) {
					leftShiftDown = down;
				} else if (event.key.keysym.sym == SDLK_RSHIFT) {
					rightShiftDown = down;
				} else if (event.key.keysym.sym == SDLK_LGUI) {
					leftGuiDown = down;
				} else if (event.key.keysym.sym == SDLK_RGUI) {
					rightGuiDown = down;
				} else if (event.key.keysym.sym == SDLK_LALT) {
					leftAltDown = down;
				} else if (event.key.keysym.sym == SDLK_RALT) {
					rightAltDown = down;
				}
			}
			break;
		}
	}
};

}
