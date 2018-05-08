#include "includesVoids.h"
void mousemoveunpressed(int x, int y){
	;
}//end void;
void mousemotion(int x, int y){
	;
}
void mouseclick(int button, int state, int x, int y){
	if(state==GLUT_DOWN){//to know where the player clicked;
		WINDOW.clicked[0]=x;
		WINDOW.clicked[1]=y;
	}
	if(state==GLUT_UP){//MOUSE RELEASE FROM BUTTON AND READ IF IT IS WITHIN THE RANGE OF A BUTTON: 
		WINDOW.released[0]=x;
		WINDOW.released[1]=y;
		if(WINDOW.clicked[0]==WINDOW.released[0]&&WINDOW.clicked[1]==WINDOW.released[1]){
			for(int n=0;n<numberButtonsDraw[WINDOW.currentScreen];n++){//button collision: 
				if(	x>(BUTTON[WINDOW.currentScreen][n].x)&&
					x<(BUTTON[WINDOW.currentScreen][n].x)+(BUTTON[WINDOW.currentScreen][n].width*WINDOW.aspect)&&
					y>(BUTTON[WINDOW.currentScreen][n].y)&&
					y<(BUTTON[WINDOW.currentScreen][n].y)+(BUTTON[WINDOW.currentScreen][n].height*WINDOW.aspect)
				){
					BUTTON_LOGIC(n);
				}
			}
		}
	}
}//end void;
void keyUnpressedSpecial(int key, int x, int y){
	if(WINDOW.currentScreen==4){
		WINDOW.keysCurrentlyPressedSpecial[key]=false;
		if(key==GLUT_KEY_UP)WINDOW.allowRotation=true;
	}
}
void keyPressedSpecial(int key, int x, int y){
	if(WINDOW.currentScreen==4){
		if(key!=GLUT_KEY_F1)WINDOW.keysCurrentlyPressedSpecial[key]=true;
	}
	if(key==GLUT_KEY_F1&&WINDOW.fullScreen==true){
		WINDOW.fullScreen=false;
	}
	else if(key==GLUT_KEY_F1&&WINDOW.fullScreen==false){
		WINDOW.fullScreen=true;
	}
	SPECIAL_TEXT_INPUT(key);//enter text: 
	if(BOARD.started==true&&BOARD.gameEnded==false&&BOARD.gamePause==false){
		if(BOARD.permPlaceWithSpaceKey==false){
			//reset values: 
				BOARD.newPossiblePosition[0][0]=-1;BOARD.newPossiblePosition[1][0]=-1;
				BOARD.newPossiblePosition[2][0]=-1;BOARD.newPossiblePosition[3][0]=-1;
				BOARD.newPossiblePosition[0][1]=-1;BOARD.newPossiblePosition[1][1]=-1;
				BOARD.newPossiblePosition[2][1]=-1;BOARD.newPossiblePosition[3][1]=-1;
				BOARD.moveFour[0]=false;BOARD.moveFour[1]=false;
				BOARD.moveFour[2]=false;BOARD.moveFour[3]=false;
			//rotation: 
			if(key==GLUT_KEY_UP&&BOARD.yPosFilledDownMost<21&&WINDOW.allowRotation==true){
				KEY_UP_ROTATE(key);
			}
			MOVE_LEFT_RIGHT(key);//only if these keys are pressed: 
			if(key==GLUT_KEY_DOWN){SOFT_DROP();}//move down fast: 1 unit at a time: 
		}
		if(key==32){HARD_DROP();}//drop to bottom most free spot as is;
		CHECK_MAKE_FALLING_OR_NOT(key);//check to make falling or not: 
	}
}//end void;
void keyUnpressed(unsigned char key, int x, int y){
	if(key==32)WINDOW.allowHardDrop=true;
}//end void;
void keyPressed(unsigned char key, int x, int y){//glutKeyboardFunc(keyPressed);
	if(BOARD.started==true&&BOARD.gameEnded==false&&BOARD.gamePause==false){
		if(key=='h'||key=='H'){ROTATE();}
		if(BOARD.permPlaceWithSpaceKey==false){
			if(key==32&&WINDOW.allowHardDrop==true){//space
				BOARD.permPlaceWithSpaceKey=true;
				keyPressedSpecial((int)key,x,y);
				WINDOW.allowHardDrop=false;
			}
		}
		if(key=='g'||key=='G'){//switch rotation: 
			if(BOARD.rotation==true)BOARD.rotation=false;
			else if(BOARD.rotation==false)BOARD.rotation=true;
		}
		if(key==27){
			BOARD.gamePause=true;
			WINDOW.currentScreen=5;
			BOARD.resumeTimer=-1;
			BOARD.fallingTimerPause=BOARD.fallingTimer;
			BOARD.rotateFallTimerPause=BOARD.rotateFallTimer;
			BOARD.clearLineTimerPause=BOARD.clearLineTimer;
		}
	}
	if(BOARD.gameEnded==true){
		if(WINDOW.currentScreen==9){
			if(key!=';')REGULAR_TEXT_INPUT(key);
		}//enter highscore:
	}
}//end void;
