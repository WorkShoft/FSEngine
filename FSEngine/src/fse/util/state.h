#pragma once

namespace FSEngine {

class FSDLL State {
public:
	State() {}
	virtual ~State() {}

	virtual void onInit(SpriteRenderer *renderer) = 0;
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;

	virtual void onExit() = 0;
	virtual void onEnter() = 0;
protected:
	SpriteRenderer *_renderer = nullptr;
};

class FSDLL StateManager {
public:
	static void Update();
	static void Render();

	static void ChangeState(State *newState);
	inline static State *GetCurrentState() { return m_currentState; }
private:
	static State *m_currentState;
};

}