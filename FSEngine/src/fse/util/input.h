#pragma once

namespace FSEngine {

#define FSKEY(x) FSE_KEY_##x = SDLK_##x,

enum FSDLL FSKeys : int {
	FSKEY(ESCAPE)
	FSKEY(F1)
	FSKEY(F2)
	FSKEY(F3)
	FSKEY(F4)
	FSKEY(F5)
	FSKEY(F6)
	FSKEY(F7)
	FSKEY(F8)
	FSKEY(F9)
	FSKEY(F10)
	FSKEY(F11)
	FSKEY(F12)

	FSKEY(1)
	FSKEY(2)
	FSKEY(3)
	FSKEY(4)
	FSKEY(5)
	FSKEY(6)
	FSKEY(7)
	FSKEY(8)
	FSKEY(9)
	FSKEY(0)
	FSKEY(BACKSPACE)

	FSKEY(q)
	FSKEY(w)
	FSKEY(e)
	FSKEY(r)
	FSKEY(t)
	FSKEY(y)
	FSKEY(u)
	FSKEY(i)
	FSKEY(o)
	FSKEY(p)

	FSKEY(CAPSLOCK)
	FSKEY(a)
	FSKEY(s)
	FSKEY(d)
	FSKEY(f)
	FSKEY(g)
	FSKEY(h)
	FSKEY(j)
	FSKEY(k)
	FSKEY(l)

	FSKEY(z)
	FSKEY(x)
	FSKEY(c)
	FSKEY(v)
	FSKEY(b)
	FSKEY(n)
	FSKEY(m)
	FSKEY(COMMA)

	FSKEY(LCTRL)
	FSKEY(LALT)
	FSKEY(SPACE)
	FSKEY(RCTRL)

	FSKEY(UP)
	FSKEY(LEFT)
	FSKEY(DOWN)
	FSKEY(RIGHT)
};
enum FSDLL FSBtns : int {
	FSE_MOUSE_LEFT = SDL_BUTTON_LEFT,
	FSE_MOUSE_RIGHT = SDL_BUTTON_RIGHT,
	FSE_MOUSE_MIDDLE = SDL_BUTTON_MIDDLE
};

class FSDLL KeyInput {
	friend class Window;
public:
	static void Update();

	static bool IsKeyDown(int key);
	inline static bool IsKeyPressed(int key) { return !WasKeyDown(key) && IsKeyDown(key); }
private:
	static std::map<int, bool> m_KeyMap;
	static std::map<int, bool> m_PrevKeyMap;

	static bool WasKeyDown(int key);
};

class FSDLL Mouse {
	friend class Window;
public:
	static void Update();

	static bool IsBtnDown(int key);
	inline static bool IsBtnPressed(int key) { return !WasKeyDown(key) && IsBtnDown(key); }
	
	inline static float GetX() { return m_MousePos.x; }
	inline static float GetY() { return m_MousePos.y; }
	inline static float GetDX() { return m_MousePos.x - m_PrevMousePos.x; }
	inline static float GetDY() { return  m_PrevMousePos.y - m_MousePos.y; }
private:
	static glm::vec2 m_MousePos;
	static glm::vec2 m_PrevMousePos;
	static std::map<int, bool> m_KeyMap;
	static std::map<int, bool> m_PrevKeyMap;

	static bool WasKeyDown(int key);
};

}
