#include "pch.h"
#include "logger.h"
#include <ctime>
#include <fstream>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace FSEngine {

std::string Logger::m_LogBuffer;
std::shared_ptr<spdlog::logger> Logger::m_GameLogger;
std::shared_ptr<spdlog::logger> Logger::m_EngineLogger;

void Logger::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	m_EngineLogger = spdlog::stdout_color_st("FSENGINE");
	m_EngineLogger->set_level(spdlog::level::info);

	m_GameLogger = spdlog::stdout_color_st("GAME");
	m_GameLogger->set_level(spdlog::level::info);
}

//Nessecary? Not Really
//Slow? Yes
//Cool? Also yes
void Logger::DumpLogFile()
{
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%d_%m_%Y__%H_%M_%S", timeinfo);
	std::string str(buffer);

	std::ofstream out("logs/FSEngine_" + str + ".txt");
	out << m_LogBuffer;
	out.close();
	m_LogBuffer.clear();
}

#ifndef FSE_RELEASE
void Logger::GLDebugLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
			const GLchar *message, const void *userParam)
{
	switch(severity) {
	case GL_DEBUG_SEVERITY_LOW:
		FSE_INFO("GL (Info): {0}", message);
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		FSE_WARN("GL (Med): {0}", message);
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		FSE_ERROR("GL (High): {0}", message);
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		FSE_INFO("GL (Notif): {0}", message);
		break;
	}
}
#endif

}