#pragma once

namespace FSEngine {

class FSDLL NPC {
public:
	NPC(Sprite &spr) : sprite(spr) {}
	virtual ~NPC() {}

	virtual void onInit() = 0;
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;	

	virtual void onEnter() {}
	virtual void onExit() {}

	virtual NPC *clone() const = 0;

	inline void *getValue(const std::string &name) const { return _addInfo.at(name); }
	inline void setInfo(const std::string &name, void *value) { _addInfo.at(name) = value; }
	
	Sprite sprite;
protected:
	inline void addInfo(const std::string &name) { _addInfo.emplace(name, nullptr); }

	std::map<std::string, void*> _addInfo;
};

}