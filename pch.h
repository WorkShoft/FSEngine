#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <pugixml/pugixml.hpp>
#include <INIReader.h>
#include <spdlog/spdlog.h>

#include <fse/util/macros.h>
#include <fse/util/logger.h>
#include <fse/entity/aabb.h>

#include <fse/gfx/texture.h>
#include <fse/gfx/base/glbuffers.h>
#include <fse/gfx/base/shaderprogram.h>
#include <fse/util/window.h>
#include <fse/gfx/spriterenderer.h>
#include <fse/entity/npc.h>
#include <fse/entity/map/map.h>