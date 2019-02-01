#pragma once

namespace FSEngine {

class FSDLL Sprite {
public:
	Sprite(const Texture *texture, float x, float y);
	Sprite(const Texture *texture, const glm::vec2 &position, const glm::vec2 &rotation, const glm::vec2 &scale);

	void move(float dx, float dy);
	void rotate(float dx, float dy);

	inline void setDepth(float depth) { m_depth = depth; }
	inline void setScale(float sx, float sy) { m_scale = glm::vec2(sx, sy); }
	inline void setPosition(float x, float y) { m_position = glm::vec2(x, y); }
	inline void setRotation(float rx, float ry) { m_rotation = glm::vec2(rx, ry); }

	inline float getDepth() const { return m_depth; }
	inline float getX() const { return m_position.x; }
	inline float getY() const { return m_position.y; }
	inline glm::vec2 getScale() const { return m_scale; }
	inline AABB getCollision() const { return m_collision; }
	inline glm::vec2 getPosition() const { return m_position; }
	inline glm::vec2 getRotation() const { return m_rotation; }
	inline const Texture *getTexture() const { return m_texture; }
private:
	AABB m_collision;
	float m_depth = 0;
	const Texture *m_texture;
	glm::vec2 m_position, m_rotation, m_scale;
};


class FSDLL SpriteRenderer {
public:
	SpriteRenderer(const Camera *cam, const Window *window);
	SpriteRenderer(const Camera *cam, const Window *window, const std::string &vShaderDir, const std::string &fShaderDir);
	~SpriteRenderer();

	void draw();
	void addSprite(const Sprite &spr);
	void addStaticSprite(const Sprite &spr);
private:
	void createVAO();
	void drawSprite(const Texture *tex, const std::vector<Sprite> &sprs, const glm::mat4 &oMat);

	ShaderProgram m_shader;
	const Camera *m_camera;
	const Window *m_window;
	VertexArray m_spriteVAO;
	UniformBuffer m_uniformBuffer;
	std::map<const Texture*, std::vector<Sprite>> m_staticSprites;
	std::map<const Texture*, std::vector<Sprite>> m_dynamicSprites;

};

}