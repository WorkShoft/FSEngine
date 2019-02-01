#include "pch.h"
#include "../util/maths.h"
#include "../entity/camera.h"
#include <glm/gtc/type_ptr.hpp>

namespace FSEngine {

const float spriteVerts[16] = {
	0, 0, 0, 1,
	64, 0, 1, 1,
	64, 64, 1, 0,
	0, 64, 0, 0
};

const short spriteInds[6] = {
	0, 1, 2, 2, 3, 0
};

/*******************************
*           Sprite             *
*******************************/

Sprite::Sprite(const Texture *texture, float x, float y) : m_position(x, y), m_rotation(0, 0), m_scale(1, 1), m_texture(texture), m_collision(x, y, 64, 64)
{}

Sprite::Sprite(const Texture *texture, const glm::vec2 &position, const glm::vec2 &rotation, const glm::vec2 &scale) : 
		m_texture(texture), m_position(position), m_rotation(rotation), m_scale(scale), m_collision(position.x, position.y, 64 * scale.x, 64 * scale.y) {}

void Sprite::move(float dx, float dy)
{
	m_position.x += dx;
	m_position.y += dy;
	m_collision.move(dx, dy);
}
	
void Sprite::rotate(float dx, float dy)
{
	m_rotation.x += dx;
	m_rotation.y += dy;
}

/*******************************
*        SpriteRenderer        *
*******************************/

SpriteRenderer::SpriteRenderer(const Camera *cam, const Window *window) : 
	m_shader("res/shader/vspriteshader.spv", "res/shader/fspriteshader.spv"), m_uniformBuffer(sizeof(glm::mat4) + sizeof(float), m_shader, 1, "VertUniforms"), 
	m_camera(cam), m_window(window)
{
	createVAO();
}

SpriteRenderer::SpriteRenderer(const Camera *cam, const Window *window, const std::string &vShaderDir, const std::string &fShaderDir) :
	m_shader(vShaderDir, fShaderDir), m_uniformBuffer(sizeof(glm::mat4) + sizeof(float), m_shader, 1, "VertUniforms"), 
	m_camera(cam), m_window(window)
{
	createVAO();
}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::draw()
{
	glm::mat4 orthoMat = GenerateOrthoMat(m_camera, *m_window);
	
	glBindVertexArray(m_spriteVAO);
	m_spriteVAO.enableAttrib(0);
	m_spriteVAO.enableAttrib(1);
	m_uniformBuffer.bind();
	
	for(const auto it : m_staticSprites) {
		drawSprite(it.first, it.second, orthoMat);
	}

	for(const auto it : m_dynamicSprites) {
		drawSprite(it.first, it.second, orthoMat);
		m_dynamicSprites.clear();
	}
}

void SpriteRenderer::addSprite(const Sprite &spr)
{
	auto it = m_dynamicSprites.find(spr.getTexture());
	if(it != m_dynamicSprites.end()) {
		m_dynamicSprites.at(spr.getTexture()).push_back(spr);
	} else {
		std::vector<Sprite> sprs;
		sprs.push_back(spr);
		m_dynamicSprites.emplace(spr.getTexture(), sprs);
	}
}

void SpriteRenderer::addStaticSprite(const Sprite &spr)
{
	auto it = m_staticSprites.find(spr.getTexture());
	if(it != m_staticSprites.end()) {
		m_staticSprites.at(spr.getTexture()).push_back(spr);
	} else {
		std::vector<Sprite> sprs;
		sprs.push_back(spr);
		m_staticSprites.emplace(spr.getTexture(), sprs);
	}
}

void SpriteRenderer::createVAO()
{
	VertexBuffer vb(16);
	vb.storeData(spriteVerts, 0, 16);
	vb.lock();

	IndexBuffer ib(6);
	ib.storeData(spriteInds, 0, 6);

	m_spriteVAO.setIndexBuffer(ib);
	m_spriteVAO.addVertexBuffer(0, 0, sizeof(float) * 4, vb);
	m_spriteVAO.formatVertexAttrib(0, 2, 0);
	m_spriteVAO.formatVertexAttrib(1, 2, sizeof(float) * 2);
	m_spriteVAO.linkAttribs(0, 0);
	m_spriteVAO.linkAttribs(1, 0);
}

void SpriteRenderer::drawSprite(const Texture *tex, const std::vector<Sprite> &sprs, const glm::mat4 &orthoMat)
{
	tex->makeActive(0);

	for(Sprite spr : sprs) {
		if(!m_camera->getViewport().isWithin(spr.getCollision())) continue;
		const float depth = spr.getDepth();

		glm::mat4 sprTransform = GenerateTransformationMatrix(spr.getPosition(), spr.getScale(), spr.getRotation());
		glm::mat4 mvp = orthoMat * sprTransform;
		m_uniformBuffer.storeData(glm::value_ptr(mvp), 0, sizeof(mvp));
		m_uniformBuffer.storeData(&depth, sizeof(mvp), sizeof(float));

		m_shader.activate();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
	}
}

}