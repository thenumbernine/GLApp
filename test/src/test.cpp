#include "GLApp/GLApp.h"
#include "GLApp/ViewBehavior.h"
#include "GLCxx/Program.h"
#include "GLCxx/Attribute.h"
#include "GLCxx/VertexArray.h"
#include "GLCxx/Buffer.h"
#include "GLCxx/gl.h"
#include "Tensor/Tensor.h"
#include "Common/File.h"
#include <chrono>
#include <iostream>
#include "SDL.h"

struct Test : public ::GLApp::ViewBehavior<::GLApp::GLApp> {
	using Super = ::GLApp::ViewBehavior<::GLApp::GLApp>;

	using Clock = std::chrono::high_resolution_clock;
	std::chrono::time_point<Clock> startTime = std::chrono::high_resolution_clock::now();

	GLCxx::Program shaderProgram;
	GLCxx::VertexArray vao;

	virtual std::string getTitle() const { return "Spinning Triangle"; }

	virtual void init(Init const & args) {
		Super::init(args);

		SDL_version version;
		SDL_GetVersion(&version);
		std::cout << "SDL_GetVersion:" << std::endl;
		std::cout << (int)version.major << "." << (int)version.minor << "." << (int)version.patch << std::endl;

		//std::string version = "#version 460\n";
		//osx is dumb.
		// TODO version=latest like in the lua framework
		std::string glslVersion = "#version 410\n";
		std::string shaderCode = Common::File::read("test.shader");
		shaderProgram = GLCxx::Program(
			// vertex code
			std::vector<std::string>{
				glslVersion,	//first
				"#define VERTEX_SHADER\n",
				shaderCode,
			},
			// fragment code
			std::vector<std::string>{
				glslVersion,	//first
				"#define FRAGMENT_SHADER\n",
				shaderCode,
			}
		);

		vao = GLCxx::VertexArray(std::vector<GLCxx::Attribute>{
				//infer attribute properties from the shader program's attribute info
				GLCxx::Attribute(shaderProgram, "pos", GLCxx::ArrayBuffer(Tensor::float3x3{
					{0, 1.25, 0},
					{-1, -.75, 0},
					{1, -.75, 0}
				})),
				GLCxx::Attribute(shaderProgram, "color", GLCxx::ArrayBuffer(Tensor::float3x3{
					{1,0,0},
					{0,1,0},
					{0,0,1}
				}))
			},
			GLCxx::ElementArrayBuffer(Tensor::uint3{0,1,2})
		);

	}

	virtual void onUpdate() {
		Super::onUpdate();

		shaderProgram.use();

		// SDL's version, get # milliseconds since SDL was initialized:
		// float t = SDL_GetTicks64() / 1000;
		//
		// C++'s version.
		// This is how you get the # of milliseconds since some epoch.
		// Welcome to the future, where everything is retarded.
		auto t = 1e-3 * std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - startTime).count();
		view->mvMat = view->mvMat * Tensor::rotate<float>(t * 30., Tensor::float3(0, 1, 0));
		glUniformMatrix4fv(shaderProgram.getUniformLocation("projMat"), 1, GL_TRUE, &view->projMat.x.x);
		glUniformMatrix4fv(shaderProgram.getUniformLocation("mvMat"), 1, GL_TRUE, &view->mvMat.x.x);

		vao.bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		vao.unbind();
		shaderProgram.done();
	}
};

GLAPP_MAIN(Test)
