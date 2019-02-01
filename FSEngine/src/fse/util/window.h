#pragma once

namespace FSEngine {

class Camera;

struct FSDLL windowCreateInfo_t {
	bool borderless = false, 
		vSync = true, 
		resizeable = false, 
		hidden = false, 
		startFullscreen = false;
};

class FSDLL Window {
public:
	Window(int width, int height, const std::string &title, const windowCreateInfo_t &wci = {});
	~Window();

	void update();
	void setFullscreen(bool isFullscreen);

	inline void close() { m_isOpen = false; }
	inline bool isOpen() const { return m_isOpen; }
	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
	inline bool isFullscreen() const { return m_isFullscreen; }

	inline operator SDL_Window*() const { return m_window; }
	inline SDL_GLContext getGLContext() const { return m_context; }
private:
	int m_width, m_height, m_startWidth, m_startHeight;
	bool m_isOpen, m_isFullscreen;
	SDL_Window *m_window;
	SDL_GLContext m_context; //held on to for the sake of it really

	void eventLoop(const SDL_Event &evnt);
	void configureOpenGL(const windowCreateInfo_t &wci);
	Uint32 getWindowFlags(const windowCreateInfo_t &wci);
};

}
