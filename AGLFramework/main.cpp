//include everything
#include "AIE.h"
#include "include\GL\glfw.h"
#include <cmath>
#include <assert.h>
#include <crtdbg.h>
#include <string>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//setup the global vars (not needed but future proof)
int height = 780;
int width = 1280;
int Menu = 1;
int iScore [] = {0,0};
char buffer[60];
int winner = -1;
bool debug = false;
//button checking array
//0 = space, 1 = enter, 2 = backspace, 3 = up, 4 = down
bool bCanCheck[] = {0,0,0,0,0};
bool bQuitGame = false;
float ballx=width/2;
float bally=height/2;

float xspeed = 0;
float yspeed = 0;

bool bPaddle = 0;

float fDeltaTime = 0.0f;
float fLastTime = 0.0f;

void DrawHitline(int x, int y){
		DrawLine(x,  y-28,  x,  y-64,  SColour(0xFF,0x00,0x00,0xAA) );
		DrawLine(x,  y+28,  x,  y-28,  SColour(0x00,0xFF,0x00,0xAA) );
		DrawLine(x,  y+28,  x,  y+64,  SColour(0x00,0x00,0xFF,0xAA) );
}
void DrawInt(int i,int w, int h){
	_itoa_s (i,buffer,10);
	DrawString(buffer, w, h );
}
void BallReset(){
	ballx=width/2;
	bally=height/2;
	srand((unsigned)time(0));
	xspeed = -10 +(rand() % 20);
	yspeed = -5 +(rand() % 10);
	//if the ball is in the up/down area, reset it again
	while (xspeed>-2 && xspeed <2){
		srand((unsigned)time(0));	
		xspeed = -5 +(rand() % 10);	
	}
	while (yspeed>-2 && yspeed <2){
		srand((unsigned)time(0));	
		yspeed = -5 +(rand() % 10);	
	}
	if (xspeed<0){
		bPaddle = 0;}
	else if (xspeed>0){
		bPaddle = 1;
	}
}
int main( int arc, char* argv[] )
{	
	// First we need to create our Game Framework
	Initialise( width, height, false );
// Now load some sprites
	unsigned int BackgroundSprite = CreateSprite( "images/background.png", 1280, 780, false );
	unsigned int PaddleLeftSprite = CreateSprite( "images/Paddle.png", 32, 64, true );
	unsigned int PaddleRightSprite = CreateSprite( "images/Paddle.png", 32, 64, true );
	unsigned int BallSprite = CreateSprite( "images/Ball.png", 32, 32, true );
	unsigned int Header = CreateSprite( "images/Header.png", 444, 128, true );

//setup all the variables
	int paddleleftx = 100;
	int paddlelefty = height/2;
	int paddleleftyvar = 0;

	int paddlerightx = width-100;
	int paddlerighty = height/2;
	int paddlerightyvar = 0;
	
	if (xspeed<0){
		bPaddle = 0;}
	else if (xspeed>0){
		bPaddle = 1;
	}
	int iOption = 1;
	int iOptiony = height/2;

//if the ball is in the up/down area, reset it again
	while (xspeed>-2 && xspeed <2){
		srand((unsigned)time(0));	
		xspeed = -5 +(rand() % 10);	
	}
	while (yspeed>-2 && yspeed <2){
		srand((unsigned)time(0));	
		yspeed = -5 +(rand() % 10);	
	}

	glClearColor(0.0f,0.0f,0.0f,0);
	do{

		fDeltaTime = (clock() - fLastTime)/(float)CLOCKS_PER_SEC;
		fLastTime = clock();

		if (!IsKeyDown(GLFW_KEY_SPACE)){
			bCanCheck[0]=true;
		}
		if (!IsKeyDown(GLFW_KEY_ENTER)){
			bCanCheck[1]=true;
		}
		if (!IsKeyDown(GLFW_KEY_BACKSPACE)){
			bCanCheck[2]=true;
		}
		if (!IsKeyDown(GLFW_KEY_UP)){
			bCanCheck[3]=true;
		}
		if (!IsKeyDown(GLFW_KEY_DOWN)){
			bCanCheck[4]=true;
		}
		switch (Menu){
/////////////////////////////////////////////////////////////////////////////////////////////////////GAME CASE////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case 0:
//make sure the game doesnt "flash" with keypress's on menus by clearing all old objects
		ClearScreen();
//controls & movement
		if ( IsKeyDown('W') && paddlelefty>64)      {paddleleftyvar--;}
		if ( IsKeyDown('S') && paddlelefty<height-64) {paddleleftyvar++;}
		
		if ( IsKeyDown(GLFW_KEY_UP) && paddlerighty>64 )      {paddlerightyvar--;} 
		if ( IsKeyDown(GLFW_KEY_DOWN) && paddlerighty<height-64){paddlerightyvar++;}
//left
		if (paddlelefty>=64 && paddlelefty<=height-64){
			paddlelefty += paddleleftyvar * 10.0f * fDeltaTime;
		}else {
			paddleleftyvar = 0; if (paddlelefty>height/2) {paddlelefty=height-64;}else{paddlelefty=64;}
			}
//right
		if (paddlerighty>=64 && paddlerighty<=height-64){
			paddlerighty += paddlerightyvar * 10.0f * fDeltaTime;
		}else {
			paddlerightyvar=0; if (paddlerighty>height/2) {paddlerighty=height-64;}else{paddlerighty=64;}
		}
		ballx += xspeed * 100.0f * fDeltaTime;
		bally += yspeed * 100.0f * fDeltaTime;

//ball collisions
//outside left/right and top/bottom bounce
//add to score
		if (ballx>=width){iScore[1]++;} 
		if (ballx<=0)    {iScore[0]++;}
//reset room
		if (ballx<=0 || ballx>=width){ 
			BallReset();
		}
		if (bally<=0 || bally>=height){
			yspeed *= -1;
		}
//stop the ball going to fast
		if (xspeed>10) {xspeed=10; }
		if (xspeed<-10){xspeed=-10;}
		if (yspeed>10) {yspeed=10; }
		if (yspeed<-10){yspeed=-10;}
//paddle left
		if (ballx<=paddleleftx+16 && bPaddle == 0){
			if       (bally<paddlelefty-28 && bally>paddlelefty-64){
				xspeed *= -3 * 100.0f * fDeltaTime;
				yspeed *= 2 * 100.0f * fDeltaTime;
			}else if (bally<paddlelefty+28 && bally>paddlelefty-28){
				yspeed *= -1 * 100.0f * fDeltaTime;
				xspeed *= -1 * 100.0f * fDeltaTime;
			}else if (bally<paddlelefty+64 && bally>paddlelefty+28){
				xspeed *= -3 * 100.0f * fDeltaTime;
				yspeed *= -2 * 100.0f * fDeltaTime;
			}
		bPaddle = 1;
		}
//paddle right
		if (ballx>=paddlerightx-16 && bPaddle == 1){
			if       (bally<paddlerighty-28 && bally>paddlerighty-64){
				xspeed *= -3;
				yspeed *= 2;
			}else if (bally<paddlerighty+28 && bally>paddlerighty-28){
				yspeed *= -1;
				xspeed *= -1;
			}else if (bally<paddlerighty+64 && bally>paddlerighty+28){
				xspeed *= -3;
				yspeed *= -2;
			}
		bPaddle = 0;
		}
//draw the instances
		DrawSprite(BackgroundSprite);
		MoveSprite( BackgroundSprite, 0, 0);
		DrawSprite(PaddleLeftSprite);
		DrawSprite(PaddleRightSprite);
		DrawSprite(BallSprite);
//draw the middle
		DrawLine(width/2,  0,  width/2,  height,  SColour(0x00,0x00,0x00,0xAA) );
//move the instances
		MoveSprite( PaddleLeftSprite, paddleleftx, paddlelefty );
		MoveSprite( PaddleRightSprite, paddlerightx, paddlerighty);
		MoveSprite( BallSprite, ballx, bally );
//convert the int's to strings and draw thw score
		DrawInt(iScore[0],(width/4)*3, 32);
		DrawInt(iScore[1],(width/4), 32);
//if someone has won, change the screen to say so.
		for (int i = 0; i<=1; i++){
			if (iScore[i] >= 10){
				winner = i;
				Menu = 2;
			}
		}
//debug information
		if (debug==true){
//hitlines
		DrawHitline(paddleleftx+16,paddlelefty);
		DrawHitline(paddlerightx-16,paddlerighty);
//vars	
		std::cout << "paddlelefty : " << paddlelefty<< std::endl;
		std::cout << "paddleleftyvar : " << paddleleftyvar<< std::endl;
		std::cout << "paddlerighty : " << paddlerighty<< std::endl;
		std::cout << "paddlerightyvar : " << paddlerightyvar<< std::endl;
		std::cout << "ballx : " << ballx<< std::endl;
		std::cout << "bally : " << bally<< std::endl;
		std::cout << "xspeed : " << xspeed<< std::endl;
		std::cout << "yspeed : " << yspeed<< std::endl;
		}
//Checks to set the debug to show or no
		if (IsKeyDown(GLFW_KEY_BACKSPACE) && bCanCheck[2] == true){
			if (debug==true ){
				debug=false;
				bCanCheck[2]=false;
			}else if (debug==false){
				debug=true;
				bCanCheck[2]=false;
			}
		}
		//add to the timer
		break;
///////////////////////////////////////////////////////////////////////////////////////////////////MAIN MENU//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case 1:
			ClearScreen();
			//sets the screen to black
			//draws the information
			DrawSprite(BackgroundSprite);
			MoveSprite( BackgroundSprite, 0, 0);
			DrawSprite(Header);
			MoveSprite( Header, width/2, height/8 );
//fake objects
			MoveSprite( BallSprite, width/2, iOptiony );
			DrawSprite(BallSprite);
			MoveSprite( PaddleLeftSprite, 100, height/2 );
			DrawSprite(PaddleLeftSprite);
			MoveSprite( PaddleRightSprite, width-100, height/2 );
			DrawSprite(PaddleRightSprite);
			DrawString( "Scores", width/2+32, height/2-48 );
			DrawString( "Play Game", width/2+32, height/2-16 );
			DrawString( "Quit",  width/2+32, height/2+16 );
			DrawString( "Controls", (width/2)+32, height/2+48 );

			switch (iOption){
			case 0:
				iOptiony = (height/2)-32;
				break;
			case 1:
				iOptiony = (height/2);
				break;
			case 2:
				iOptiony = (height/2)+32;
				break;
			case 3:
				iOptiony = (height/2)+64;
				break;
			default:
				break;
			}
			if (IsKeyDown(GLFW_KEY_DOWN) && bCanCheck[4] == true){
				bCanCheck[4]=false;
				iOption++;
				if (iOption>3){iOption=0;}
			}
			if (IsKeyDown(GLFW_KEY_UP) && bCanCheck[3] == true){
				bCanCheck[3]=false;
				iOption--;
				if (iOption<0){iOption=3;}
			}
			if (IsKeyDown(GLFW_KEY_ENTER) && bCanCheck[1] == true){
				bCanCheck[1] = false;
				switch (iOption){
				case 0:
					Menu = 2;//goto the highscores
					break;
				case 1:
					//reset the winner and score
					winner=-1;
					iScore[0]=0;
					iScore[1]=0;
					//reset the ball
					BallReset();
					//reset the paddles
					paddlelefty = height/2;
					paddleleftyvar = 0;
					paddlerighty = height/2;
					paddlerightyvar = 0;
					Menu = 0;//goto the game
					break;
				case 2:
					bQuitGame = true;
					break;
				case 3:
					Menu = 3;//goto the Controls Page
					break;
				}
			}			
			//go to game when pressed
		break;
////////////////////////////////////////////////////////////////////////////////////////////////////////WIN SCREEN////////////////////////////////////////////////////////////////////////////////////////////////////////
		case 2:
//draw the win screen
			ClearScreen();
			DrawSprite(BackgroundSprite);
			MoveSprite( BackgroundSprite, 0, 0);
			DrawSprite(Header);
			MoveSprite( Header, width/2, height/8 );
//draw the background pong items
			MoveSprite( BallSprite, width/2, height/2-32 );
			DrawSprite(BallSprite);
			MoveSprite( PaddleLeftSprite, 100, height/2 );
			DrawSprite(PaddleLeftSprite);
			MoveSprite( PaddleRightSprite, width-100, height/2 );
			DrawSprite(PaddleRightSprite);
//draw old menu
			DrawString( "Play Game", width/2+32, height/2-16 );
			DrawString( "Controls", (width/2)+32, height/2+48 );
			DrawString( "Quit", (width/2)+32, height/2+16 );
//draw new items with some indentation
			DrawString( "  Scores", width/2+32, height/2-48 );
			switch (winner){
			case 0:
			DrawString("  Player One Wins", (width/2)+32, height/2-112 );
			break;
			case 1:
			DrawString("  Player Two Wins", (width/2)+32, height/2-112 );
			break;
			}
		DrawString("  Enter to return to the main menu.", (width/2)+32, height/2-80 );
//back to the main menu
		if (IsKeyDown(GLFW_KEY_ENTER) && bCanCheck[1] == true){
				//goto the main menu
				Menu = 1;
				iOptiony = 1;
				bCanCheck[1] = false;
			}
		if (IsKeyDown(GLFW_KEY_DOWN) && bCanCheck[4] == true){
				//goto the main menu
				Menu = 1;
				iOptiony = 1;
				bCanCheck[4] = false;
			}
		break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////CONTROLS//////////////////////////////////////////////////////////////////////////////////////////////////////
		case 3:
		ClearScreen();
//draw the pong background
			DrawSprite(BackgroundSprite);
			MoveSprite( BackgroundSprite, 0, 0);
			DrawSprite(Header);
			MoveSprite( Header, width/2, height/8 );
			
			MoveSprite( BallSprite, width/2, iOptiony );
			DrawSprite(BallSprite);
			MoveSprite( PaddleLeftSprite, 100, height/2 );
			DrawSprite(PaddleLeftSprite);
			MoveSprite( PaddleRightSprite, width-100, height/2 );
			DrawSprite(PaddleRightSprite);
//draw old menu
			DrawString( "Scores", width/2+32, height/2-48 );
			DrawString( "Play Game", width/2+32, height/2-16 );
			DrawString( "Quit", (width/2)+32, height/2+16 );
//draw new items with some indentation
			DrawString( "  Controls", (width/2)+32, height/2+48 );
			DrawString( "  Payer Left, W is up, S is down.", (width/2)+32, height/2+80 );

			DrawString( "  Player Right, Arrow Up is up, Arrow Down is down.",width/2+32, height/2+112 );
			DrawString( "  Enter to return to main menu.", width/2+32, height/2+144 );
//check if up or enter is pressed to go back
		if (IsKeyDown(GLFW_KEY_ENTER) && bCanCheck[1] == true){
				//goto the main menu
				Menu = 1;
				iOptiony = 1;
				bCanCheck[1] = false;
			}
		if (IsKeyDown(GLFW_KEY_UP) && bCanCheck[3] == true){
				//goto the main menu
				Menu = 1;
				iOptiony = 1;
				bCanCheck[3] = false;
			}
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////DESTROY EVERYTHING//////////////////////////////////////////////////////////////////////////////////////////////////
}
	} while ( FrameworkUpdate() == false && !bQuitGame == true);
//destroy all objects clearing them on game exit
	DestroySprite(PaddleLeftSprite);
	DestroySprite(PaddleRightSprite);
	DestroySprite(BallSprite);
	DestroySprite(Header);
	DestroySprite(BackgroundSprite);
	Shutdown();
//programming signature
	std::cout << "So long, and thanks for all the fish!";
	return 0;
}