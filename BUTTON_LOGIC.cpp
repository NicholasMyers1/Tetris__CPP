#include "includesVoids.h"
void BUTTON_LOGIC(int buttonNum){
	switch(WINDOW.currentScreen){
		case 0://welcome screen: 
			switch(buttonNum){
				case 1:		RESTART_GAME();break;//start game: 
				case 2: 	WINDOW.currentScreen=1;break;//rules
				case 3: 	WINDOW.currentScreen=2;break;//controls: 
				case 4: 	WINDOW.currentScreen=3;break;//high scores: 
				case 5: 	exit(0);break;//exit:
			}break;
		case 1://rules screen: 
			switch(buttonNum){
				case 2: 	RESTART_GAME();break;//start game: 
				case 3: 	WINDOW.currentScreen=0;break;//return to welcome/main screen: 
			}break;
		case 2://controls screen: 
			switch(buttonNum){
				case 1: 	RESTART_GAME();break;//start game:
				case 2: 	WINDOW.currentScreen=0;break;//return to welcome/main screen:
			}break;
		case 3://high score screen:
			switch(buttonNum){
				case 1: 	RESTART_GAME();break;//start game:
				case 2: 	WINDOW.currentScreen=0;break;//return to welcome/main screen:   ???//read from the file to get the high scores:???
			}break;
		case 4://ingame:
			switch(buttonNum){
				case 24:	bool enterHighScoreMode=false;
							for(int n=0;n<5;n++){
								if(BOARD.gameScore>BOARD.highScoresScore[n]){
									enterHighScoreMode=true;
									break;
								}
							}
							if(enterHighScoreMode==false)WINDOW.currentScreen=8;//=8;//show player score and high scores. 
							else WINDOW.currentScreen=9;//=9;//allow player to enter high score. and then show high scores. 
							break;//find out if the player can enter for the high score: 
			}break;
		case 5://ingame paused: 
			switch(buttonNum){
				case 1:		WINDOW.currentScreen=4;
							BOARD.resumeTimer=GetTickCount();//continue game:
							break;
				case 2: 	WINDOW.currentScreen=6;break;//rules:
				case 3: 	WINDOW.currentScreen=7;break;//controls:
				case 4: 	RESTART_GAME();break;//restart tetris:
				case 5: 	INIT_=true;INIT();break;//return to main screen:
				case 6: 	exit(0);break;//exit: 
			}break;
		case 6://ingame paused rules: 
			switch(buttonNum){
				case 2:		WINDOW.currentScreen=4;
							BOARD.resumeTimer=GetTickCount();
							break;//continue game:
				case 3:		WINDOW.currentScreen=5;break;//go back:
			}break;
		case 7://ingame paused controls: 
			switch(buttonNum){
				case 1: 	WINDOW.currentScreen=4;
							BOARD.resumeTimer=GetTickCount();
							break;//continue game:
				case 2: 	WINDOW.currentScreen=5;break;//go back:
			}break;
		case 8://game ended: show score and scoreSheet: 
			switch(buttonNum){
				case 1:		RESTART_GAME();break;//start game: 
				case 2: 	INIT_=true;INIT();break;//return to welcome/main screen: 
			}break;
		case 9://game ended: user enter highscore name: 
			switch(buttonNum){
				case 3:		if(BOARD.nameEnterHighScore.length()>0){//and a space is not in the beginning of the string: 
								if(BOARD.nameEnterHighScore[BOARD.nameEnterHighScore.length()-1]==' ')BOARD.nameEnterHighScore.erase(BOARD.nameEnterHighScore.length()-1,1);
								for(int n=0;n<5;n++){
									if(BOARD.gameScore>BOARD.highScoresScore[n]){
										GET_SET_HIGH_SCORE(n,"\0","\0");//UPDATE HIGH SCORES; 
										WRITE_FILE("_HighScores.txt");//UPDATE HIGH SCORES FILE;
										break;
									}
								}
								INIT_=true;INIT();
								WINDOW.currentScreen=3;
							}break;//and a space is not in the beginning of the string: 
			}break;
	}
}
