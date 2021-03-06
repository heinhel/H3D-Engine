#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <GL/glew.h>

#include "Color.hpp"
#include "../../H3D/Math/Vector.hpp"
#include <string>
#include <fstream>
/////////////////////////////////////////////////////////////////
//	class Image
/////////////////////////////////////////////////////////////////
namespace h3d {
template<typename colT>
class Image
{
private:
	h3d::Vec2<int> Size;

	char channels;
	bool has_alpha;
	colT *data;
public:
	// Con/De-structor
	Image();
	Image(char Path[]);
	~Image();
	
	// Handling data of image
	colT* getData();	

	// check for Channels
	bool hasAlpha();
	char getChannelCount();
	
	// load it from a File
	bool loadFromFile(char Path[]);
};
}
/////////////////////////////////////////////////////////////////