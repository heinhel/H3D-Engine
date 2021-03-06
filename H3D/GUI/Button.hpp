#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif // DLL_EXPORT

#include <functional>
#include "Stylesheet.hpp"
#include "../../H3D/Math/Vector.hpp"
#include "../../H3D/Graphics/Vertex.hpp"
#include "../../H3D/Graphics/Texture.hpp"
/////////////////////////////////////////////////////////////////
// GUI Button
/////////////////////////////////////////////////////////////////
namespace gui {
	class Button
	{
	private:
		// States and Values of the Element
		int m_state;

		// Positioning (NDC coords)
		h3d::Vec2<GLfloat> m_size;
		h3d::Vec3<GLfloat> m_position;
		
		// OpenGL Stuff for rendering
		h3d::Vertex m_vertices[4];
		h3d::Texture* m_texture = nullptr;

		// Style definition
		StylesheetModule::Button m_style;
	public:
		H3D_API Button();
		H3D_API ~Button();

		void setPosition(h3d::Vec3<float> pos);
		void setSize(h3d::Vec2<float> size);
		void setStyle(const StylesheetModule::Button& module);
		void setCallback(std::function<void> func_ptr(std::unique_ptr<Button> ptr));

		void H3D_API render();
		void H3D_API update();

		struct {
			static const int normal = 1,
							  pressed = 2,
						      hovered = 3,
						      focused = 4,
						      disabled = 5;
		}State;
		int H3D_API getState();
	};
}
/////////////////////////////////////////////////////////////////