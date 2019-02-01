#pragma once

namespace FSEngine {

class FSDLL AABB {
public:
	inline AABB(float x, float y, float width, float height)
	{
		m_minX = x;
		m_minY = y;
		m_width = width;
		m_height = height;
		update();
	}

	inline AABB(float minX, float minY, float maxX, float maxY, float w, float h)
	{
		m_minX = minX;
		m_minY = minY;
		m_maxX = maxX;
		m_maxY = maxY;
		m_width = w;
		m_height = h;
	}

	inline void move(float x, float y)
	{
		m_minX += x;
		m_minY += y;
		update();
	}

	inline void mutate(float minX, float minY, float maxX, float maxY) 
	{ 
		m_minX = minX; 
		m_minY = minY; 
		m_maxX = maxX;
		m_maxY = maxY;
	 }

	inline bool isWithin(const AABB &other)
	{
		return (m_minX < other.getX() && m_minY < other.getY()) && (m_maxX > other.getMX() && m_maxY > other.getMY());
	}

	inline float getX() const { return m_minX; }
	inline float getY() const { return m_minY; }
	inline float getMX() const { return m_maxX; }
	inline float getMY() const { return m_maxY; }
	inline float getWidth() const { return m_width; }
	inline float getHeight() const { return m_height; }
private:
	inline void update() 
	{
		m_maxX = m_minX + m_width;
		m_maxY = m_minY + m_height;
	}

	float m_width, m_height;
	float m_minX, m_minY, m_maxX, m_maxY;
};

}