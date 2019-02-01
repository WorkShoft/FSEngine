#pragma once

namespace FSEngine {

class FSDLL MapParser {
public:
	static Map LoadMap(const std::string &path, SpriteRenderer &renderer);
private:
	static std::vector<NPC*> LoadNPCs(const pugi::xml_node &npcNode);
	static std::vector<Sprite> GetTiles(const pugi::xml_node &tileNode);
};

}