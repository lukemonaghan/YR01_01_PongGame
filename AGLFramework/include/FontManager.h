//////////////////////////////////////////////////////////////////////////
//	Author:	Jamie Stewart
//	Date:	12/11/2012
//	Brief:	Basic Font class for drawing screen-space text
//////////////////////////////////////////////////////////////////////////
#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_
//////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include <GL/wglew.h>
#include <Gl/glfw.h>

#include <list>
#include "MathHelper.h"

namespace AIE
{

class Font; 
struct CharacterBillboard;
struct FontVertex;

//////////////////////////////////////////////////////////////////////////
class FontManager 
{
public:

	static FontManager* CreateInstance();
	static FontManager* GetInstance();
	static void			DestroyInstance();

protected:

    FontManager();
    ~FontManager();

	static FontManager*     m_pInstance;

public:

    void                Update(float fTimeStep);
	void				Draw( unsigned int a_uiProgramID );
	void				DrawString( vec4 v4Position, vec4 v4Color, const char* pBuffer);
    Font*               GetDebugFont();
    Font*               GetCurrentFont();
    
    void                AddFont( Font* pFont );
    Font*               AddFont( const char* pFontName );
    
    void                SetFont( Font* pFont );
    Font*               SetFont( const char* pFontName );
    
    void                RemoveFont( Font* pFont );
    void                RemoveFont( const char* pFontName );
        
private:
    
    Font*                   m_pDebugFont;
    Font*                   m_pCurrentFont;
    std::list<Font*>        m_pFontList;
    
	GLuint				m_uiVAO;
	GLuint				m_uiVBO;
	GLuint				m_uiIBO;
	mat4				m_m4ModelView;
	CharacterBillboard* m_pCharacterBillboards;
	unsigned int		m_uiCharactersToDraw;
};

}//Namespace AIE

//////////////////////////////////////////////////////////////////////////
#endif //_FONT_MANAGER_H_
//////////////////////////////////////////////////////////////////////////
