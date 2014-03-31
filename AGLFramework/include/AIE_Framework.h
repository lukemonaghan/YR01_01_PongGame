//////////////////////////////////////////////////////////////////////////
//	Author:	Jamie Stewart
//	Date:	12/11/2012
//	Brief:	This is the main entry point for access to the functionality provided by the 
//			AIE Static OpenGL Framework. This class needs to be included in your main.cpp
//			in order to get a simple 2d sprite game up and running.
//////////////////////////////////////////////////////////////////////////
#ifndef _AIE_FRAMEWORK_H_
#define _AIE_FRAMEWORK_H_
//////////////////////////////////////////////////////////////////////////

#include "MathHelper.h"

namespace AIE
{

//////////////////////////////////////////////////////////////////////////
class Framework
{
public:

	//////////////////////////////////////////////////////////////////////////
	// The following functions are the public accessors for creating, retrieving and 
	// destroying an instance of the AIE Framework. Only one instance of the framework 
	// can be created.  See: Design Patterns (Singleton)
	//////////////////////////////////////////////////////////////////////////
	static Framework* Create( int a_iWidth, int a_iHeight, bool a_bFullscreen = false );
	static Framework* Get();
	static void Destroy();

	int		Initialise();
	void	Update();
	void	Draw();
	void	ClearScreen();
	void	Shutdown();

	bool	ShouldQuit();

	// Functionality for the loading and unloading of textures
	unsigned int	LoadTexture( const char* a_pTextureName );
	void			FreeTexture( unsigned int a_uiTextureID );

	#pragma region Sprite creation and mainpulation functionality
	//////////////////////////////////////////////////////////////////////////
	// Sprite creation and manipulation functionality
	//////////////////////////////////////////////////////////////////////////
	unsigned int	CreateSprite( const char* a_pTextureName, int a_iWidth, int a_iHeight, bool a_bDrawFromCenter = true );
	void			MoveSprite( unsigned int a_uiSpriteID, int a_iXPos, int a_iYPos );
	void			DrawSprite( unsigned int a_uiSpriteID );
	void			RotateSprite( unsigned int a_uiSpriteID, int a_iRotation );
    #pragma endregion

	#pragma region Font Rendering functionality
	void			DrawString( vec4 a_v4Position, vec4 a_v4Colour, const char* a_pTextToDisplay );
	#pragma endregion
	
	#pragma region Line Drawing functionality
	//////////////////////////////////////////////////////////////////////////
	// Basic Line Drawing Functionality
	//////////////////////////////////////////////////////////////////////////
	void			DrawLine( int a_iStartX, int a_iStartY, int a_iEndX, int a_iEndY );
	void			DrawLine( int a_iStartX, int a_iStartY, int a_iEndX, int a_iEndY, vec4 a_sColour );
	void			DrawLine( int a_iStartX, int a_iStartY, int a_iEndX, int a_iEndY, vec4 a_sStartColour, vec4 a_sEndColour );
	#pragma endregion

	#pragma region Input handling functionality
	//////////////////////////////////////////////////////////////////////////
	// Input handling functionality
	//////////////////////////////////////////////////////////////////////////
	bool			IsKeyDown(unsigned int a_uiKey);
	void			GetMousePos( int& a_uiMousePosX, int& a_uiMousePosY );
	bool			GetMouseButtonDown(int a_iMouseButton );
	#pragma endregion

private:

	static Framework* sm_pInstance;

protected:

	Framework(int a_iWidth, int a_iHeight, bool a_bFullscreen = false );
	~Framework();
};

} //namespace AIE

//////////////////////////////////////////////////////////////////////////
#endif //_AIE_FRAMEWORK_H
//////////////////////////////////////////////////////////////////////////