#pragma once

namespace FSEngine {

class FSDLL Logger {
public:
	static void Init();
	static void DumpLogFile();

	inline static std::string &GetLogBuffer() { return m_LogBuffer; }
	inline static std::shared_ptr<spdlog::logger> &GetGameLogger() { return m_GameLogger; }
	inline static std::shared_ptr<spdlog::logger> &GetEngineLogger() { return m_EngineLogger; }
	inline static void BufferLog(const std::string &message) { m_LogBuffer.append(message + "\n"); }

#ifndef FSE_RELEASE
	static void GLDebugLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
			const GLchar *message, const void *userParam);
#endif
private:
	static std::string m_LogBuffer;
	static std::shared_ptr<spdlog::logger> m_GameLogger;
	static std::shared_ptr<spdlog::logger> m_EngineLogger;
};

}

// Core log macros
#define FSE_TRACE(x, ...)    FSEngine::Logger::GetEngineLogger()->trace(x, __VA_ARGS__)
#define FSE_INFO(x, ...)     FSEngine::Logger::GetEngineLogger()->info(x, __VA_ARGS__)
#define FSE_WARN(x, ...)     FSEngine::Logger::BufferLog("WARN: " + std::string(x)); FSEngine::Logger::GetEngineLogger()->warn(x, __VA_ARGS__)
#define FSE_ERROR(x, ...)    FSEngine::Logger::BufferLog("ERROR: " + std::string(x)); FSEngine::Logger::GetEngineLogger()->error(x, __VA_ARGS__)
#define FSE_FATAL(x, ...)    FSEngine::Logger::BufferLog("FATAL: " + std::string(x)); FSEngine::Logger::GetEngineLogger()->critical(x, __VA_ARGS__); FSEngine::Logger::DumpLogFile(); exit(-1)

// Client log macros
#define FSGAME_TRACE(x, ...) FSEngine::Logger::GetGameLogger()->trace(x, __VA_ARGS__)
#define FSGAME_INFO(x, ...)  FSEngine::Logger::GetGameLogger()->info(x, __VA_ARGS__)
#define FSGAME_WARN(x, ...)  FSEngine::Logger::GetGameLogger()->warn(x, __VA_ARGS__)
#define FSGAME_ERROR(x, ...) FSEngine::Logger::GetGameLogger()->error(x, __VA_ARGS__)
#define FSGAME_FATAL(x, ...) FSEngine::Logger::GetGameLogger()->critical(x, __VA_ARGS__)
