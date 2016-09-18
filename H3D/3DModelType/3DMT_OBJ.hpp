#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include <gl\glew.h>
#include "..\Vector.hpp"
#include "..\Utilities.hpp"
#include "../ResourceManager.hpp"
#include "../Vertex.hpp"
#include <vector>
#include <string>
/////////////////////////////////////////////////////////////////
// .obj 3D File Format Handling Class
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace ModelType {
		class OBJ
		{
		private:	
			struct Mesh
			{
				// Name of the Mesh
				char m_meshname[40];
				char m_meshContentTags;

				// MaterialID
				std::string m_textureID;
				
				// OpenGL Stuff
				GLuint m_vba_object;
				GLuint m_element_buffer;
				GLuint m_verticesBufferOGL;

				// Buffer Data
				std::vector<h3d::Vec3<GLfloat>> m_vertices;
				std::vector<h3d::Vec3<GLfloat>> m_normals;
				std::vector<h3d::Vec2<GLfloat>> m_texCoords;
				std::vector<GLuint>				m_indicesVertices;
				std::vector<GLuint>				m_indicesNormals;
				std::vector<GLuint>				m_indicesTexCoords;
				
				// final Vertices
				std::vector<h3d::Vertex> m_verticesVec;

				// Tag for content
				enum {
					VERTICES=0,NORMALS=1,TEXCOORDS=2
				};

				// Con-/Destructor
				Mesh();
				~Mesh();
				void clearUp();

				// Rendering
				void correctIndices();
				void prepareRendering();
				void render();
			};
			std::vector<Mesh> m_meshes;

		public:
			H3D_API OBJ();
			H3D_API ~OBJ();

			bool H3D_API loadFromFile(char Path[]);
			void H3D_API render();
		};
	}
}
/////////////////////////////////////////////////////////////////