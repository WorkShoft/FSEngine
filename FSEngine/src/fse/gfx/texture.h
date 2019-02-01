#pragma once

namespace FSEngine {

struct FSDLL textureData_t {
	unsigned char *data = nullptr;
	int components, width, height;
};

class FSDLL Texture {
public:
	Texture(int width, int height, int levels);
	Texture(const textureData_t &data, int levels);
	~Texture();

	void makeActive(int bank) const;
	void subImage(int level, int offsetX, int offsetY, const textureData_t &data);

	inline GLuint getID() const { return m_id; }
	inline textureData_t getData() const { return m_data; }
	
	static textureData_t LoadTextureData(const std::string &path);
	static void DestroyTextureData(const textureData_t &data);
private:
	void createTexture(int width, int height, int l);

	GLuint m_id;
	textureData_t m_data;
};

}