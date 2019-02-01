#include "pch.h"
#include "mapparser.h"
#include "../../util/fileutil.h"
#include "dataregister.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace FSEngine {

/*******************************
*             Map              *
*******************************/

Map::Map(const std::vector<NPC*> &npcs, const std::vector<Sprite> &tiles, SpriteRenderer &renderer) : 
	m_npcs(npcs), m_tiles(tiles), m_sprRenderer(renderer) {

	for(const auto &it : m_tiles) {
		m_sprRenderer.addStaticSprite(it);
	}
}

Map::~Map()
{
	for(auto &it : m_npcs) {
		delete it;
	}
}

void Map::update()
{
	for(const auto &it : m_npcs) {
		it->onUpdate();
	}
}

void Map::render()
{
	for(const auto &it : m_npcs) {
		it->onRender();
		m_sprRenderer.addSprite(it->sprite);
	}
	m_sprRenderer.draw();
}

void Map::enter()
{
	for(const auto &it : m_npcs) {
		it->onEnter();
	}
}

void Map::exit()
{
	for(const auto &it : m_npcs) {
		it->onExit();
	}
}

/*******************************
*           MapParser          *
*******************************/

Map MapParser::LoadMap(const std::string &mapDir, SpriteRenderer &renderer)
{
	//Commence funky node traversal	
	using namespace pugi;

	xml_document doc;
	xml_parse_result result = doc.load_file(mapDir.c_str());
	if(!result) {
		FSE_ERROR("Failed to load map file {0}", mapDir);
	}

	xml_node root = doc.child("map");
	xml_node tileRoot = root.child("tiles");
	xml_node npcRoot = root.child("npcs");
	
	std::vector<NPC*> npcList = LoadNPCs(npcRoot);
	std::vector<Sprite> tileList = GetTiles(tileRoot);

	Map map(npcList, tileList, renderer);
	return map;
}

std::vector<Sprite> MapParser::GetTiles(const pugi::xml_node &tileNode)
{
	std::vector<Sprite> sprites;
	for(const pugi::xml_node &layer : tileNode.children("layer")) {
		const float depth = layer.attribute("depth").as_float();

		std::vector<std::string> layers;
		const char *values = layer.child_value();
		boost::split(layers, values, boost::is_any_of("\n"));
		layers.erase(layers.begin());
		layers.erase(layers.begin() + layers.size());

		int y = (layers.size() - 1);
		for(const std::string &tiles : layers) {
			int x = -1;
			for(const char tile : tiles) {
				x++;
				if(tile == ' ') 
					continue;

				Sprite spr = DataRegister::GetTile(tile);
				if(spr.getTexture() == nullptr) 
					continue;
				
				spr.setDepth(depth);
				spr.setPosition(x * 64, y * 64);
				sprites.push_back(spr);
			}
			y--;
		}
	}
	
	return sprites;
}

std::vector<NPC*> MapParser::LoadNPCs(const pugi::xml_node &npcNode)
{
	std::vector<NPC*> npcs;
	for(const pugi::xml_node &npc : npcNode.children("npc")) {
		const std::string id = npc.attribute("id").as_string();
		Sprite npcSpr = DataRegister::GetTile(*npc.child_value("texture"));
		npcSpr.setPosition(atof(npc.child_value("x")), atof(npc.child_value("y")));
		npcSpr.setDepth(atof(npc.child_value("depth")));

		NPC *clone = DataRegister::GetNPC(id);
		if(!clone)
			continue;

		clone->sprite = npcSpr;

		for(const pugi::xml_node &addInfoNode : npc.children("addInfo")) {
			const std::string name = addInfoNode.attribute("name").as_string();
			void *value = (void*)addInfoNode.child_value();
			clone->setInfo(name, value);
		}

		npcs.push_back(clone);
	}

	return npcs;
}

}