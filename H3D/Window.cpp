#include "Window.hpp"
#include "WindowImpl.hpp"

#include "Utilities.hpp"
#include "Event.hpp"
#include "WglContext.hpp"

// Windows
#ifdef _WIN32 || _WIN64

#include "Win32WindowImpl.hpp"
typedef h3d::intern::Win32WindowImpl WindowImplType;

// Linux
#elif defined _linux_

#include "X11WindowImpl.hpp"
typedef h3d::intern::X11WindowImpl WindowImplType;

#endif 

/////////////////////////////////////////////////////////////////
h3d::Window::Window(h3d::Vec2<int> p_size, 
					std::string			    p_title,
					h3d::WindowStyle		p_style,
					h3d::ContextSettings contextsettings)
{
	m_opened		= true;
	m_Size			= p_size; 
	m_Title			= p_title; 
	m_WindowStyle	= p_style;
	
	m_impl = std::unique_ptr<WindowImplType>(new WindowImplType());
	m_impl.get()->create(p_size, p_title, p_style, contextsettings);

	m_context = std::unique_ptr<h3d::intern::WglContext>(new h3d::intern::WglContext());	
	if (!m_context.get()->createContext(m_impl) && h3d::DebugMode){
		Log.error("Unable to create OpenGL Context");
	}
}
/////////////////////////////////////////////////////////////////
// Message Handling
bool h3d::Window::pollEvent(h3d::Event& event) {
	return m_impl->pollEvent(event);
}
/////////////////////////////////////////////////////////////////
// OpenGL Operations
std::string h3d::Window::getContextVer() {
	return std::string((char*)glGetString(GL_VERSION));
}
void h3d::Window::clear(GLbitfield mask,h3d::Color<GLfloat> col={ 0,0,0,1 })
{
	glClearColor(col.r, col.g, col.b, col.a);
	glClear(mask);
}
/////////////////////////////////////////////////////////////////
// Setting
void h3d::Window::setActive(bool val){}
void h3d::Window::close() {}
void h3d::Window::swapBuffers() {
	m_impl->swapBuffers();
}
h3d::Window::~Window() {}
/////////////////////////////////////////////////////////////////
// Getting
h3d::Vec2<int>          h3d::Window::getSize() { return m_Size; }
std::string				h3d::Window::getTitle() { return m_Title; }
h3d::WindowStyle		h3d::Window::getStyle() { return m_WindowStyle; }
bool					h3d::Window::isOpen() { return m_opened; }
bool					h3d::Window::isFullscreen() { return m_isFullscreen; }
/////////////////////////////////////////////////////////////////