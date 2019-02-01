#pragma once
#pragma warning(disable:4251)

#ifdef _WIN32

#ifdef FSENGINE_EXPORTS
#define FSDLL __declspec(dllexport)
#else
#define FSDLL __declspec(dllimport)
#endif

#else
#define FSDLL
#endif

#ifndef FSE_RELEASE
#define DEBUG_CALL(x) x
#else
#define DEBUG_CALL(x)
#endif
