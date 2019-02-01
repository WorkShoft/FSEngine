#pragma once

namespace FSEngine {

class FSDLL ShaderProgram {
	friend class UniformBuffer;
public:
	ShaderProgram(const std::string &vertDir, const std::string &fragDir);
	~ShaderProgram();

	void activate();

	static bool UseFallbacks;

	inline operator GLuint() const { return m_programID; }
private:
	void createFallbackShaders(GLuint &vID, GLuint &fID);
	GLuint m_programID;

	static GLuint CreateShader(const std::string dir, GLuint type);
};

}