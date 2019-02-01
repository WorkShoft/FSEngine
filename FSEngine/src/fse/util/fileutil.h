#pragma once

#define FSE_FILE_READ_FAILED(x) (x.size() == 1 && x[0] == ' ')

namespace FSEngine {

extern FSDLL void CreateFolder(const std::string &path);
extern FSDLL std::vector<char> ReadBinaryFile(const std::string &file);

}