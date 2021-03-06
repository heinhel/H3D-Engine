#include <cassert>
#include <sstream>
#include <stdlib.h>

#include "../../H3D/System/Utilities.hpp"
#include "../../H3D/System/Window.hpp"
#include "../../H3D/System/FileDataStructures.hpp"
#include "../../H3D/System/FileSystem.hpp"

#include "../../H3D/System/Config.hpp"
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
/////////////////////////////////////////////////////////////////
const std::string h3d::Log::getCurrentTime()
{
	std::string currTime;
	const time_t now = time(0);
	const int bufSize = 50;
	char timeStr[bufSize];
	ctime_s(&timeStr[0], bufSize, &now);
	for (int i = 0; i < bufSize; i++)
		if (timeStr[i] == '\n')
			timeStr[i] = ' '; 
	currTime.assign(timeStr);
	return currTime;
}
/////////////////////////////////////////////////////////////////
// Assertion 
void AssertFailed(const char* file, const char* line, const char* expr)
{
	std::string str("accured at: " + std::string(line) +
					" in file '" + std::string(file) + 
					"' with the expression: " + std::string(expr));
	h3d::Log::costum("H3D-ASSERT", str.c_str());
}
// Verify
void VerifyFailed(const char* file, const char* line, const char* expr)
{
	std::string str("accured at: " + std::string(line) +
					" in file '" + std::string(file) +
					"' with the expression: " + std::string(expr));
	h3d::Log::costum("H3D-VERIFY", str.c_str());
}
/////////////////////////////////////////////////////////////////
// Implementation of Logger
/////////////////////////////////////////////////////////////////
bool h3d::DebugMode = false;

std::mutex h3d::Log::m_fileMutex;
FILE* h3d::Log:: m_logFile = nullptr;
h3d::LogType h3d::Log::m_currentLogType = h3d::LogType::CONSOLE;
/////////////////////////////////////////////////////////////////
void h3d::Log::setLogType(h3d::LogType type) {
	m_currentLogType = type;
}
/////////////////////////////////////////////////////////////////
// costum tag log
void h3d::Log::costum(const char* tag, const char* str)
{
	std::string logString(getCurrentTime());
	logString.append(" [" + std::string(tag) + "]: ");
	logString.append(str);
	logString.append("\n");
	if (m_currentLogType == LogType::CONSOLE)
	{
		printf(logString.c_str());
	}
	else if (m_currentLogType == LogType::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str());
	}
}
/////////////////////////////////////////////////////////////////
// Lua implementation of log functions
/////////////////////////////////////////////////////////////////
extern "C" {
	void luaLog_error(lua_State *lua){
		h3d::Log::error(lua_tostring(lua, 1));
	}
	void luaLog_debug(lua_State *lua){
		h3d::Log::debug(lua_tostring(lua, 1));
	}
	void luaLog_info(lua_State *lua){
		h3d::Log::info(lua_tostring(lua, 1));
	}
	void luaLog_alarm(lua_State *lua){
		h3d::Log::alarm(lua_tostring(lua, 1));
	}
}
/////////////////////////////////////////////////////////////////
// Take Screenshot
void h3d::Log::screenshot(char folder[], h3d::Window& win) 
{
	std::string item_name = "shot " + std::string(h3d::Log::getCurrentTime().c_str()) + ".bmp";
	std::replace(item_name.begin(), item_name.end(), ':', '_');
	std::string path = std::string(folder) + item_name;
	if (h3d::DebugMode)
		h3d::Log::info("Saving Screenshot '%s'", path.c_str());

	const h3d::Vec2<int> size = win.getSize();
	h3d::FileType::BMP::Header t_header = { 0 };
	h3d::FileType::BMP::Body t_body = { 0 };

	uint8_t * pixels = new uint8_t[size.x*size.y*3];
	glReadPixels(0, 0, size.x, size.y, GL_BGR, GL_UNSIGNED_BYTE, pixels);

	t_header.bfType = 19778;
	t_header.bfReserved = 0;
	t_header.bfOffBits = sizeof(t_header) + sizeof(t_body);
	t_header.bfsize = size.x*size.y * 3 + sizeof(t_header) + sizeof(t_body);

	t_body.biWidth = size.x;
	t_body.biHeight = size.y;
	t_body.biPlanes = 1;
	t_body.biBitCount = 24;
	t_body.biCompression = 0;
	t_body.biSizeImage = 0;
	t_body.biSize = sizeof(t_body);
	t_body.biXPelsPerMeter = 72;
	t_body.biYPelsPerMeter = 72;

	h3d::FileHandle fh;
	if (fh.open(path) == false) {
		h3d::Log::error("Unable to save screenshot to %s", path.c_str());
		return;
	}
	
	fh.write((char*)&t_header, sizeof(t_header));
	fh.write((char*)&t_body, sizeof(t_body));
	fh.write((char*)pixels, size.x*size.y * 3);
	
	delete[] pixels;
	fh.close();
}
/////////////////////////////////////////////////////////////////
