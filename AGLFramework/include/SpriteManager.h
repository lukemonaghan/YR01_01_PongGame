//////////////////////////////////////////////////////////////////////////
//	Author:	Jamie Stewart
//	Date:	12/11/2012
//	Brief:	Class to manage sprites
//////////////////////////////////////////////////////////////////////////
#ifndef _SPRITEMANAGER_H_
#define _SPRITEMANAGER_H_
//////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include <GL/wglew.h>
#include <Gl/glfw.h>

#include <vector>
#include <stack>
#include "BasicSprite.h"
#include "Utilities.h"

namespace AIE
{

//////////////////////////////////////////////////////////////////////////
class SpriteManager
{
public:

	static SpriteManager* CreateInstance();
	static SpriteManager* GetInstance();
	static void DestroyInstance();

	void Draw( unsigned int a_uiShaderID );

	unsigned int	AddSprite( const char* a_pTexture, int a_iWidth, int a_iHeight, bool a_bDrawFromCenter );
	void			MoveSprite( unsigned int a_uiSpriteID, int a_iXPos, int a_iYPos );
	void			RotateSprite( unsigned int a_uiSpriteID, int a_iRotation );
	void			RemoveSprite( unsigned int a_uiSpriteID );

	void			MarkSpriteForDraw( unsigned int a_uiSpriteID );

protected:

	SpriteManager();
	~SpriteManager();

private:

	std::vector<BasicSprite*>				m_Sprites;
	std::stack<BasicSprite*>				m_pSpritesToDrawThisFrame;
	static SpriteManager*					m_pInstance;

	GLuint m_uiVAO;
	GLuint m_uiVBO;
	GLuint m_uiIBO;

	AIE::Vertex aoVertices[4];
	AIE::Vertex aoUpperLeftVertices[4];

};

}//end namespace AIE

//////////////////////////////////////////////////////////////////////////
#endif //_SPRITEMANAGER_H_
//////////////////////////////////////////////////////////////////////////