//////////////////////////////////////////////////////////////////////////
//	Author:	Jamie Stewart
//	Date:	12/11/2012
//	Brief:	This is a basic textured screen-space quad
//////////////////////////////////////////////////////////////////////////
#ifndef _AIE_BASIC_SPRITE_H_
#define _AIE_BASIC_SPRITE_H_

#include "MathHelper.h"

namespace AIE
{

//////////////////////////////////////////////////////////////////////////
class BasicSprite
{
public:

	BasicSprite( const char* a_pTexture, int a_iWidth, int a_iHeight, bool a_bDrawFromCenter = true );
	BasicSprite( const BasicSprite& pSprite );
	~BasicSprite();

	void	Draw(unsigned int a_uiProgram);

	void	SetRotation( int a_iRotation );
	
	void	SetPosition( int a_iX, int a_iY );
	void	GetPosition( int& a_iX, int& a_iY );

	void	SetSize( int a_iWidth, int a_iHeight );
	void	GetSize( int& a_iWidth, int& a_iHeight );

	void	SetSpriteID( unsigned int a_uiSpriteID );
	void	GetSpriteID( unsigned int& a_uiSpriteID );

	bool	DrawFromCenter() { return m_bDrawFromCenter; }
	unsigned int GetTextureID() { return m_uiTextureID; }

private:

	mat4			m_m4Matrix;
	vec2			m_v2Scale;
	unsigned int	m_uiTextureID;    
    bool            m_bDrawFromCenter;

};

inline void BasicSprite::SetPosition( int a_iX, int a_iY )
{
	m_m4Matrix.row3 = vec4( (float)a_iX, (float)a_iY, -1.f, 1.f );
}

inline void BasicSprite::GetPosition( int& a_iX, int& a_iY )
{
	a_iX = (int)m_m4Matrix.row3.x;
	a_iY = (int)m_m4Matrix.row3.y;
}

inline void BasicSprite::SetSize( int a_iWidth, int a_iHeight )
{
	m_v2Scale = vec2( (float)a_iWidth, (float)a_iHeight );
}

inline void BasicSprite::GetSize( int& a_iWidth, int& a_iHeight )
{
	a_iWidth = (int)m_v2Scale.x;
	a_iHeight = (int)m_v2Scale.y;
}

}//namespace AIE

//////////////////////////////////////////////////////////////////////////
#endif //_AIE_BASIC_SPRITE_H_
//////////////////////////////////////////////////////////////////////////