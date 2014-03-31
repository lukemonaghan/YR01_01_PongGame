//////////////////////////////////////////////////////////////////////////
#ifndef __AIEFRAMEWORK_H_
#define __AIEFRAMEWORK_H_
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include "MathHelper.h"

//////////////////////////////////////////////////////////////////////////
struct Vertex
{
	union
	{
		struct  
		{
			vec4 position;
			vec2 uv;
		};
		struct
		{
			float x, y, z, w;
			float u, v;
		};
	};

	bool operator == (const Vertex& rhs)
	{
		return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w && u == rhs.u && v == rhs.v);
	}
};

// loads a texture of various formats
unsigned int LoadTexture(const char* a_szTexture, unsigned int a_uiFormat = GL_RGB, unsigned int a_uiInternalFormat = GL_RGB);

// creates a simple shader using a vertex shader and pixel shader
// Note: vertex shader has 2 inputs, a vec4 for position and a vec2 for a UV
unsigned int LoadEffect(const char* a_szVertexShader, const char* a_szPixelShader);

// helper function for loading shader code into memory
char* FileToBuffer(const char* a_szPath);

// builds a textured plane out of 2 triangles and fills in the vertex array, vertex buffer, and index buffer
void Build3DPlane(float a_fSize, unsigned int& a_ruiVAO, unsigned int& a_ruiVBO, unsigned int& a_ruiIBO);

//////////////////////////////////////////////////////////////////////////
#endif // __AIEFRAMEWORK_H_
//////////////////////////////////////////////////////////////////////////