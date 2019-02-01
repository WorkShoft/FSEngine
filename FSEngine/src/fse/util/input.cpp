#include "pch.h"
#include "input.h"

namespace FSEngine {

std::map<int, bool> KeyInput::m_KeyMap;
std::map<int, bool> KeyInput::m_PrevKeyMap;

void KeyInput::Update()
{
	for (auto& it : m_KeyMap) {
		m_PrevKeyMap[it.first] = it.second;
	}
}

bool KeyInput::IsKeyDown(int key)
{
	auto it = m_KeyMap.find(key);
	if (it != m_KeyMap.end()) {
		return it->second;
	}
	return false;
}

bool KeyInput::WasKeyDown(int key)
{
	auto it = m_PrevKeyMap.find(key);
	if (it != m_PrevKeyMap.end()) {
		return it->second;
	}
	return false;
}

//Mouse Input
glm::vec2 Mouse::m_MousePos;
glm::vec2 Mouse::m_PrevMousePos;
std::map<int, bool> Mouse::m_KeyMap;
std::map<int, bool> Mouse::m_PrevKeyMap;

void Mouse::Update()
{
	for (auto& it : m_KeyMap) {
		m_PrevKeyMap[it.first] = it.second;
	}

	m_PrevMousePos = m_MousePos;
}

bool Mouse::IsBtnDown(int key)
{
	auto it = m_KeyMap.find(key);
	if (it != m_KeyMap.end()) {
		return it->second;
	}
	return false;
}

bool Mouse::WasKeyDown(int key)
{
	auto it = m_PrevKeyMap.find(key);
	if (it != m_PrevKeyMap.end()) {
		return it->second;
	}
	return false;
}

}
