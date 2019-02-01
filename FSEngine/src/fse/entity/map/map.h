#pragma once

namespace FSEngine {

class FSDLL Map {
public:
	Map(const std::vector<NPC*> &npcs, const std::vector<Sprite> &tiles, SpriteRenderer &renderer);
	~Map();
	
	void update();
	void render();
	void enter();
	void exit();
private:
	std::vector<NPC*> m_npcs;
	std::vector<Sprite> m_tiles;
	SpriteRenderer &m_sprRenderer;
};

}