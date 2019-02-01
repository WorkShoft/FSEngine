#include "pch.h"
#include <fstream>

namespace FSEngine {

void CreateFolder(const std::string &path)
{
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
	if (!CreateDirectory(path.c_str(), NULL) || ERROR_ALREADY_EXISTS != GetLastError()) {
		FSE_WARN("Failed to create directory {0}: {1}", path, GetLastError());	
	}
#else
	const int dir_err = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (-1 == dir_err) {
		FSE_WARN("Failed to create directory {0}", path);
		FSE_WARN("", 0);
	}
#endif
}

std::vector<char> ReadBinaryFile(const std::string &filePath)
{
	std::ifstream file(filePath, std::ios::ate | std::ios::binary);
	if (!file.is_open()) {
		FSE_WARN("Failed to load file, {0}", filePath);
		return {' '};
	}
	
	size_t fileSize = (size_t) file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();
	return buffer;
}

}