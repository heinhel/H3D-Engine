#include "Utilities.hpp"
#include <time.h>
#include <cassert>
#include <stdlib.h>
/////////////////////////////////////////////////////////////////
// Assertion 
void AssertFailed(const char* file, const char* line, const char* expr)
{
	std::string str("accured at: " + std::string(line) + 
					" with the expression: " + std::string(expr));
	Log.costum("H3D-ASSERT", str.c_str());
}
// Verify
void VerifyFailed(const char* file, const char* line, const char* expr)
{
	std::string str("accured at: " + std::string(line) +
					" with the expression: " + std::string(expr));
	Log.costum("H3D-VERIFY", str.c_str());
}
/////////////////////////////////////////////////////////////////
// Implementation of Logger
/////////////////////////////////////////////////////////////////
bool h3d::DebugMode;
/////////////////////////////////////////////////////////////////
h3d::__Logger::__Logger() :m_currentLogType(1) {}
h3d::__Logger::~__Logger() {}
/////////////////////////////////////////////////////////////////
void h3d::__Logger::setLogType(int type) {
	m_currentLogType = type;
}
/////////////////////////////////////////////////////////////////
std::string h3d::__Logger::getCurrentTime()
{
	std::string currTime;
	time_t now = time(0);
	currTime.assign(ctime(&now));
	currTime.erase(std::end(currTime));
	return currTime;
}
/////////////////////////////////////////////////////////////////
// costum tag log
void h3d::__Logger::costum(const char* tag, const char* str)
{
	std::string logString(getCurrentTime());
	logString.erase(std::end(logString) - 1);
	logString.append(" [" + std::string(tag) + "]: ");
	logString.append(str);
	logString.append("\n");
	if (m_currentLogType == LogTypes::CONSOLE)
	{
		printf(logString.c_str());
	}
	else if (m_currentLogType == LogTypes::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, logString.c_str());
	}
}
/////////////////////////////////////////////////////////////////
// Static global Instance
h3d::__Logger& h3d::__Logger::GetInstance()
{
	static __Logger instance;
	return instance;
}
/////////////////////////////////////////////////////////////////
// Lua implementation of log functions
/////////////////////////////////////////////////////////////////
int luaLog_error(lua_State *lua)
{
	h3d::__Logger::GetInstance().error((char*)lua_tostring(lua,1));
	return 0;
}
int luaLog_debug(lua_State *lua)
{
	h3d::__Logger::GetInstance().debug((char*)lua_tostring(lua, 1));
	return 0;
}
int luaLog_info(lua_State *lua)
{
	h3d::__Logger::GetInstance().info((char*)lua_tostring(lua, 1));
	return 0;
}
int luaLog_alarm(lua_State *lua)
{
	h3d::__Logger::GetInstance().alarm((char*)lua_tostring(lua, 1));
	return 0;
}
/////////////////////////////////////////////////////////////////