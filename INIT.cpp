#include "includesVoids.h"
void INIT(){
	BUTTONS_INIT();
	if(INIT_==true){
		WINDOW_INIT();//window: winW, winH, aspect and fullscreen are dynamic.
		BOARD_INIT();//BOARD: 
		TEXT_INIT();//TEXTINPUT: 
		if(WINDOW.checkedFilesOnce==false){
/*				BOARD.controlsMoveLeft=GLUT_KEY_LEFT;
				BOARD.controlsMoveRight=GLUT_KEY_RIGHT;
				BOARD.controlsRotate=GLUT_KEY_UP;
				BOARD.controlsSwitchRotation='g';
				BOARD.controlsSoftDrop=GLUT_KEY_DOWN;
				BOARD.controlsHardDrop=' ';//space
				BOARD.controlsHoldSwitchHold='h';
				BOARD.controlsPause=27;
				BOARD.controlsFullscreen=GLUT_KEY_F1;*/
			for(int n=0;n<5;n++){//initialize the highscores: 
				BOARD.highScoresName[n]="-";
				BOARD.highScoresScore[n]=0;
				BOARD.highScoresLevel[n]=0;
				BOARD.highScoresLinesClearedthisLevel[n]=0;
				BOARD.highScoresTime[n]="0:0.0";
				BOARD.highScoresBestCombo[n]=0;
			}
			CHECK_FILE_CREATE_IF_NONEXISTENT("_HighScores.txt");
			//CHECK_FILE_CREATE_IF_NONEXISTENT("_Controls.txt");
		}WINDOW.checkedFilesOnce=true;
		LISTS();//lists: 
		INIT_=false;//set init_ to false: 
	}
}/*END INIT*/
