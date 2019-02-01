#include "pch.h"
#include "window.h"
#include "input.h"
#include "../gfx/texture.h"
#include "../gfx/base/glbuffers.h"
#include "../gfx/base/shaderprogram.h"
#include "../gfx/spriterenderer.h"
#include "../entity/camera.h"

namespace FSEngine {

Window::Window(int width, int height, const std::string &title, const windowCreateInfo_t &wci) : 
		m_isFullscreen(wci.startFullscreen), m_width(width), m_height(height), m_startWidth(width), m_startHeight(height)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		FSE_FATAL("Failed to init SDL, {0}", SDL_GetError());
	}

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, getWindowFlags(wci));
	if(!m_window) {
		FSE_FATAL("Failed to create window, {0}", SDL_GetError());
	}

	configureOpenGL(wci);
	m_isOpen = true;
}

Window::~Window()
{
	if(m_isFullscreen)
		setFullscreen(false);

	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Window::update()
{
	Mouse::Update();
	KeyInput::Update();
	SDL_GL_SwapWindow(m_window);

	SDL_Event evnt;
	while(SDL_PollEvent(&evnt)) {
		eventLoop(evnt);
	}
}

void Window::setFullscreen(bool isFullscreen)
{
	m_isFullscreen = isFullscreen;
	SDL_SetWindowFullscreen(m_window, isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
	if(!isFullscreen) {
		m_width = m_startWidth;
		m_height = m_startHeight;
	} else {
		SDL_GetWindowSize(m_window, &m_width, &m_height);
	}
	
	glViewport(0, 0, m_width, m_height);
}

void Window::eventLoop(const SDL_Event &evnt)
{
	switch(evnt.type) {
	case SDL_QUIT:
		m_isOpen = false;
		break;
	case SDL_KEYDOWN:
		KeyInput::m_KeyMap[evnt.key.keysym.sym] = true;
		break;
	case SDL_KEYUP:
		KeyInput::m_KeyMap[evnt.key.keysym.sym] = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		Mouse::m_KeyMap[evnt.button.button] = true;
		break;
	case SDL_MOUSEBUTTONUP:
		Mouse::m_KeyMap[evnt.button.button] = false;
		break;
	case SDL_MOUSEMOTION:
		Mouse::m_MousePos.x = evnt.motion.x;
		Mouse::m_MousePos.y = evnt.motion.y;
		break;
	}
}

void Window::configureOpenGL(const windowCreateInfo_t &wci)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG DEBUG_CALL( | SDL_GL_CONTEXT_DEBUG_FLAG));
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	m_context = SDL_GL_CreateContext(m_window);
	if(!m_context) {
		FSE_FATAL("Failed to create SDL context. {0}", SDL_GetError());
	}

	SDL_GL_MakeCurrent(m_window, m_context);
	SDL_GL_SetSwapInterval(wci.vSync);

	glewExperimental = true;
	GLenum success = glewInit();
	if(success != GLEW_OK) {
		FSE_FATAL("Failed to init GLEW, {0}", glewGetErrorString(success));
	}

	if(!GLEW_VERSION_4_5) {
		FSE_FATAL("System does not support OpenGL 4.5, you can fuck off now.", 0);
	}

	if(!GLEW_ARB_spirv_extensions) {
		FSE_ERROR("System does not support spir-v shaders, defaulting to fallbacks.", 0);
		ShaderProgram::UseFallbacks = true;
	}

#ifndef FSE_RELEASE
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(Logger::GLDebugLog, nullptr);
#endif
}

Uint32 Window::getWindowFlags(const windowCreateInfo_t &wci)
{
	Uint32 flags = SDL_WINDOW_OPENGL;
	if(wci.borderless) flags |= SDL_WINDOW_BORDERLESS;
	if(wci.hidden) flags |= SDL_WINDOW_HIDDEN;
	if(wci.resizeable) flags |= SDL_WINDOW_RESIZABLE;
	if(wci.startFullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	return flags;
}

}
