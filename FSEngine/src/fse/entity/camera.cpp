#include "pch.h"
#include "camera.h"

namespace FSEngine {

Camera::Camera(float x, float y, float w, float h) : m_position(x, y), m_viewport(x, y, w, h) {}

void Camera::update(float w, float h)
{
	m_viewport.mutate(m_position.x - 64, m_position.y - 64, (m_position.x + w) + 64, (m_position.y + h) + 64);
}

void Camera::move(float dx, float dy)
{
	m_position.x += dx;
	m_position.y += dy;
}

}