#pragma once

namespace FSEngine {

class FSDLL Camera {
public:
	Camera(float x, float y, float width, float height);

	void update(float width, float height);
	void move(float dx, float dy);

	inline void setPosition(const glm::vec2 &pos) { m_position = pos; }
	inline void setPosition(float x, float y) { m_position.x = x; m_position.y = y; }
	inline AABB getViewport() const { return m_viewport; }
	inline glm::vec2 getPosition() const { return m_position; }
private:
	AABB m_viewport;
	glm::vec2 m_position;
};

}