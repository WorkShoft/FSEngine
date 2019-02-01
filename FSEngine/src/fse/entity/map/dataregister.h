#pragma once

namespace FSEngine {

class FSDLL DataRegister {
public:
	static void AddNPC(const std::string &id, NPC *npc);
	static void AddTile(const char &tile, const Sprite &sprite);

	static NPC *GetNPC(const std::string &id);
	static Sprite GetTile(const char &symbol);
private:
	static std::map<char, Sprite> m_Sprites;
	static std::map<std::string, NPC*> m_NPCs;
};

}