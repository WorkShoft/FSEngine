#include "pch.h"
#include "../npc.h"
#include "dataregister.h"

namespace FSEngine {
std::map<char, Sprite> DataRegister::m_Sprites;
std::map<std::string, NPC*> DataRegister::m_NPCs;


void DataRegister::AddNPC(const std::string &id, NPC *npc)
{
	m_NPCs.emplace(id, npc);
}

void DataRegister::AddTile(const char &id, const Sprite &tile)
{
	m_Sprites.emplace(id, tile);
}

NPC *DataRegister::GetNPC(const std::string &id)
{
	NPC *npc = nullptr;

	auto it = m_NPCs.find(id);
	if(it == m_NPCs.end()) {
		FSE_ERROR("NPC {0} not in register.", id);
	} else {
		npc = it->second->clone();
		npc->onInit();
	}
	return npc;
}

Sprite DataRegister::GetTile(const char &symbol)
{
	Sprite spr(nullptr, 0, 0);
	auto it = m_Sprites.find(symbol);
	if(it == m_Sprites.end()) {
		FSE_ERROR("Sprite {0} not in register.", symbol);
	} else {
		spr = Sprite(it->second);
	}
	return spr;
}

}