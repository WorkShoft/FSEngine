#include "pch.h"
#include "shaderprogram.h"
#include "fse/util/fileutil.h"

namespace FSEngine {

bool ShaderProgram::UseFallbacks = false;

ShaderProgram::ShaderProgram(const std::string &vertDir, const std::string &fragDir)
{
	GLuint vID = CreateShader(vertDir, GL_VERTEX_SHADER);
	GLuint fID = CreateShader(fragDir, GL_FRAGMENT_SHADER);
	if(UseFallbacks) createFallbackShaders(vID, fID);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vID);
	glAttachShader(m_programID, fID);
	glLinkProgram(m_programID);

	glDetachShader(m_programID, vID);
	glDetachShader(m_programID, fID);
	glDeleteShader(vID);
	glDeleteShader(fID);
}

ShaderProgram::~ShaderProgram()
{
	glUseProgram(0);
	glDeleteProgram(m_programID);
}

void ShaderProgram::activate()
{
	glUseProgram(m_programID);
}

void ShaderProgram::createFallbackShaders(GLuint &vID, GLuint &fID)
{
#include "fallbackshader.h"

	vID = glCreateShader(GL_VERTEX_SHADER);
	fID = glCreateShader(GL_FRAGMENT_SHADER);
	
	FSE_FALLBACK_BASIC_VERT;
	const GLchar *glVData = vertexData.c_str();
	const GLint glVDataLength = vertexData.length();

	FSE_FALLBACK_BASIC_FRAG;
	const GLchar *glFData = fragmentData.c_str();
	const GLint glFDataLength = fragmentData.length();

	glShaderSource(vID, 1, &glVData, &glVDataLength);
	glShaderSource(fID, 1, &glFData, &glFDataLength);
	glCompileShader(vID);
	glCompileShader(fID);

	GLint isCompiled = 0;
	glGetShaderiv(vID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(vID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vID, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(vID);
		FSE_ERROR("Failed to load shader: {0}", infoLog.data());
	}
}


GLuint ShaderProgram::CreateShader(const std::string dir, GLuint type)
{
	if(UseFallbacks) return 0;

	std::vector<char> shaderData = ReadBinaryFile(dir);
	if(FSE_FILE_READ_FAILED(shaderData)) {
		UseFallbacks = true;
		return 0;
	}

	GLuint id = glCreateShader(type);
	glShaderBinary(1, &id, GL_SHADER_BINARY_FORMAT_SPIR_V, shaderData.data(), shaderData.size());
	glSpecializeShader(id, "main", 0, nullptr, nullptr);
	
#ifndef FSE_RELEASE
	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(id);
		FSE_ERROR("Failed to load shader: {0}", infoLog.data());
		return 0;
	}
#endif

	return id;
}
	
}