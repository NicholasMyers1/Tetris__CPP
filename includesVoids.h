#ifndef INCLUDESVOIDS_H
#define INCLUDESVOIDS_H
		#include <future>
		#include <math.h>
		#include <ctime>
		#ifdef WIN32
			#define WIN32_LEAN_AND_MEAN
				#define _WIN32_WINNT 0x501
			#include <windows.h>
		#endif
			#include <winsock2.h>
			#include <ws2tcpip.h>
			#include <future>
			#include <math.h>
		#include <iostream>
		#include <stdlib.h>
		#include <stdio.h>
		#include <stdarg.h>
		#include <cstring>
		#include <fstream>
	#define GLEW_STATIC
		#include <GL/glew.h>
		#include <gl\gl.h>
		#include <gl\glext.h>
		#include <gl\glaux.h>
		#include <gl\glu.h>
		#include <GL\glut.h>
		#include <assert.h>
		#include <sstream>
		#include <iomanip>
		#include <ctime>
		#include <cstring>
		#include <cmath>
		#include <limits.h>
		#include <random>
		#include <fstream>
		#include <time.h>
		#include <string.h>
		#include <string>
		#include <cstdlib>
		#include <cstdio>
		#include <gl\glfw.h>
		#include <vector>
		#include <conio.h>
		#include <new>
			#include <pthread.h>
	using namespace std;
/*
-lWs2_32
-lMswsock
-lAdvApi32
//
-lglew32s
-lglut32
-lglu32
-lwinmm
-lgdi32
-lmingw32
-lopengl32
-pthread
*/
	//VOIDS: 
		void INIT();
			void BUTTONS_INIT();
			void WINDOW_INIT();
			void BOARD_INIT();
			void TEXT_INIT();
			void CHECK_FILE_CREATE_IF_NONEXISTENT(string file);
				void READ_FILE(string file);
				void WRITE_FILE(string file);
					void GET_SET_HIGH_SCORE(int n,string file,string lineData);
					void GET_SET_CONTROLS(int n,string file,string lineData);
			void LISTS();
			void CHECK_OUT_OF_RANGE();
			void FIND_BOUNDS();
			void COUNTDOWN_ON_PAUSE();
		int main(int argc,char **argv);
			void mousemoveunpressed(int x, int y);
			void mousemotion(int x, int y);
			void mouseclick(int button,int state,int x,int y);
			void BUTTON_LOGIC(int buttonNumber);
			void RESTART_GAME();
			void RESUME_FROM_PAUSE();
			void DROP_BLOCKS();
			void CHECK_FULL_ROW();
				void breakDownRow(int n);
			void COMBO_LOGIC();
				void orientationOfCurrentBlockTypeFalling();
			void keyPressedSpecial(int key,int x,int y);
				void SPECIAL_TEXT_INPUT(int key);
				void KEY_UP_ROTATE(int key);
				void REGULAR_TEXT_INPUT(int key);
				void ROTATE();
				void SOFT_DROP();
				void HARD_DROP();
				void MOVE_LEFT_RIGHT(int key);
				void CHECK_MAKE_FALLING_OR_NOT(int key);
				void rotateThePiecesVoid();
			void keyUnpressedSpecial(int key, int x, int y);
			void keyPressed(unsigned char key,int x,int y);
			void keyUnpressed(unsigned char key, int x, int y);
		void reshape(int w,int h);
		void display();
			void DRAW2D();
				void DRAW_BOARD();
			void DRAW3D();
				void DRAW_BUTTONS();
					void UPDATE_BUTTON_TEXT();
					void UPDATE_BUTTON_TEXT_SCORING(int screenNumber);
					void DRAW_BUTTON_TEXT(int n);
			//void drawText();
	//LISTS: 
		extern GLuint board[3];
	//STRUCTURES:
		//buttons; 
		struct _BUTTONS{
			double x,y;
			double width,height;
			string text;
		};extern _BUTTONS BUTTON[10][30];//[SERVERCONNECT.playerStatus][buttonCurrentlyClicked];
			extern int numberButtonsDraw[10];//[WINDOW.currentScreen]max number of buttons to draw for this screen;
//
		struct _WINDOW{
			bool allowHardDrop;
			bool allowRotation;
			bool keysCurrentlyPressedSpecial[128];
			double winW,winH;//dynamic; not initialized in init;
			double aspect;//dynamic;not valued in init;
			bool fullScreen;//starts as false; not implemented yet;
			unsigned int clicked[2],released[2];//x and y press and release;
			unsigned int currentScreen;
			unsigned int buttonCurrentlyClicked;//which button is currently clicked on the current screen?
			unsigned int buttonCurrentlySelected;
			ifstream readFile_;
			ofstream writeFile_;
				bool filesReadInitiallyScoreData;
				bool filesReadInitiallyControls;
				int fileLineNumber;
				bool checkedFilesOnce;
			_WINDOW(){
				fullScreen=true;
				filesReadInitiallyScoreData=false;
				filesReadInitiallyControls=false;
				checkedFilesOnce=false;
			}
		};extern _WINDOW WINDOW;
//
		struct _TEXT_INPUT{
			//bool typing;
			int textLength;
			string pointer;
			int pointerPosition;
			bool pointerBlinkAlphaOn;
			int pointerBlinkingRate;
			DWORD blinkertimer;
		};extern _TEXT_INPUT TEXTINPUT;
//
		struct _BOARD{
			bool positionsFilledPerm[10][24];//once fallen to ground layer;
			bool positionsFilledTemp[10][24];//falling to ground layer block;
			bool positionsFilledPrev[10][24];//falling to ground layer preview;
			bool positionsFilledNextBlockToFall[10][24];//next one to fall;
			bool positionsFilledHolding[10][24];//hold this until further use. 
				short int currentBlockTypeHolding;
				bool held;
			short int currentBlockTypeFalling;//0,1,2,3,4,5,6;/*+1;*///random number between -1 and 7; so 0-6;//same list to call;
			short int nextBlockFalling;
			int prevBlock;//don't select previous block when selecting the next random block: 
			bool falling;
			int currentBlockTypeCurrentRotation;//0,90,180,270;
				DWORD fallingTimer;//=GetTickCount;//GetTickCount()>n;
				DWORD rotateFallTimer;//timer after rotating before perm placing
				DWORD clearLineTimer;
			int currPosFilled[4][2];//the current position used to access the positionsFilledTemp: x,y;
				float positionsFilledColorPerm[3][10][24];
				float positionsFilledColorTempAndPrev[3];//[4][2];
				float positionsFilledColorHold[3];//[4][2];
				float positionsFilledColorNext[3];//[4][2];
			int newPossiblePosition[4][2];//when rotating, or moving, use this to check if the position is valid, as well as make sure pieces don't disappear. 
			bool moveFour[4];//if all true, then that move is valid, can move temp blocks to position player chose;
				int xPosFilledLeftMost;//x and y positions left most piece. 0-9 and 0-19;
				int xPosFilledRightMost;//x and y positions right most piece. 0-9 and 0-19;
				int yPosFilledUpMost;//x and y positions up most piece. 0-9 and 0-19;
				int yPosFilledDownMost;//x and y positions down most piece. 0-9 and 0-19;
				unsigned long long int gameScore;
					string highScoresName[5];//scoring: 
					unsigned long long int highScoresScore[5];
					unsigned long long int highScoresLevel[5];
					unsigned long long int highScoresLinesClearedthisLevel[5];
					string highScoresTime[5];
					unsigned long long int highScoresBestCombo[5];
				unsigned long long int levelCurrentlyOn;//total number of lines cleared: (levelCurrentlyOn*10)+linesClearedForThisLevel;
				unsigned long long int linesClearedForThisLevel;
				short unsigned int linesClearedThisTime;
					unsigned long long int numLinesCleared[4];
					unsigned long long int totalLinesCleared;
					unsigned long long int blockDropped[7];
					unsigned long long int blocksHeld;
				short int increaseEachDrop;//-1,0,1; -1=do not loop again. 0=loop and reset combo to 0. 1 means loop again and add one to combo;
				bool currenStreakAddOne;
					long long int longestComboStreak;
					long long int currentComboStreak;
				double currentLineFallSpeed;
				unsigned long long int moveCount;
			bool permPlaceWithSpaceKey;
			bool started;
			bool rotation;
			bool gamePause;
				DWORD resumeTimer;
					DWORD ShowGameOverScreenTimer;
				DWORD fallingTimerPause;
				DWORD rotateFallTimerPause;
				DWORD clearLineTimerPause;
			long long int gameTimeMilliseconds;
			long long int gameTimeSeconds;
			long long int gameTimeMinutes;
/*				bool controlIsSpecial[9];
				int controlsMoveLeft;//controls:
				int controlsMoveRight;
				int controlsRotate;
				int controlsSwitchRotation;
				int controlsSoftDrop;
				int controlsHardDrop;
				int controlsHoldSwitchHold;
				int controlsPause;
				int controlsFullscreen;*/
			DWORD timePassed;//the time interval between the last update and the current one;
			bool gameEnded;
			bool checkGameEnded;
			string nameEnterHighScore;
		};extern _BOARD BOARD;
	//GLOBALS: 
		extern bool INIT_;
#endif
