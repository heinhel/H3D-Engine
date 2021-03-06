#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
// Includes
#include <list>
#include "../../H3D/Math/Vector.hpp"
#include "../../H3D/Math/Matrix.hpp"
#include <cstdint>

namespace h3d {
	/////////////////////////////////////////////////////////////
	// Class for Node
	/////////////////////////////////////////////////////////////
	class ScenegraphNodeBase
	{
	private:	
		// Children Node Handling
		std::list<ScenegraphNodeBase> m_children;
		void					  m_updateChildren();
	public:
		// Con-/Destructor
		H3D_API          ScenegraphNodeBase();
		H3D_API virtual ~ScenegraphNodeBase();

		// Release from Memory
		void H3D_API release();

		// If Node is last in Chain
		bool H3D_API isBranch();

		// Virtual Update
		virtual void H3D_API update();
		
		// Add Child
		void H3D_API addChild(const h3d::ScenegraphNodeBase &child);

		// Destroy this Node with Children
		void H3D_API destroy();
	};
	/////////////////////////////////////////////////////////////
	// Class Scenegraph
	/////////////////////////////////////////////////////////////
	class Scenegraph
	{
	private:

	public:
		// Con-/Destructor
		Scenegraph();
		~Scenegraph();

		// File Operations
		bool H3D_API saveToFile();
		bool H3D_API loadFromFile();
	};
}
/////////////////////////////////////////////////////////////////