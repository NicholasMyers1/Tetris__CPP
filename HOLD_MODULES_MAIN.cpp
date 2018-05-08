#include "includesVoids.h"
//include some subvoids;
void RESTART_GAME(){
	INIT_=true;INIT();
	BOARD.started=true;
	orientationOfCurrentBlockTypeFalling();
	BOARD.fallingTimer=GetTickCount();
	WINDOW.currentScreen=4;
	BOARD.resumeTimer=GetTickCount();
	BOARD.timePassed=0;
		BOARD.gameTimeMilliseconds=0;
		BOARD.gameTimeSeconds=0;
		BOARD.gameTimeMinutes=0;
}
void RESUME_FROM_PAUSE(){
	BOARD.gamePause=false;
	if(BOARD.fallingTimer!=-1){
			BOARD.fallingTimer=BOARD.fallingTimerPause;
			BOARD.rotateFallTimer=BOARD.rotateFallTimerPause;
			BOARD.clearLineTimer=BOARD.clearLineTimerPause;
	}
	else	BOARD.fallingTimer=GetTickCount();
	BOARD.timePassed=GetTickCount();
}
void CHECK_FULL_ROW(){
	int rowFull[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//0-19;
	BOARD.linesClearedThisTime=0;
	for(int n=0;n<20;n++){//0-19;
		for(int m=0;m<10;m++){//0-9;
			if(BOARD.positionsFilledPerm[m][n]==true)rowFull[n]+=1;
		}
		if(rowFull[n]==10){
			BOARD.currenStreakAddOne=true;//for combos:
			if((GetTickCount()-BOARD.clearLineTimer)>250){
				breakDownRow(n);
				BOARD.permPlaceWithSpaceKey=false;
				for(int o=0;o<20;o++){//reset the rowFull to false for all;//not <21,<20;
					rowFull[o]=0;
				}
				//lines cleared: increase level and score: 
				BOARD.linesClearedForThisLevel+=1;
				if(BOARD.linesClearedForThisLevel==10){
					BOARD.levelCurrentlyOn+=1;
					BOARD.linesClearedForThisLevel=0;
					if(BOARD.levelCurrentlyOn<10)BOARD.currentLineFallSpeed=(BOARD.currentLineFallSpeed*.75);
					else if(BOARD.levelCurrentlyOn<13)BOARD.currentLineFallSpeed=60.0677490234;//80;
					else if(BOARD.levelCurrentlyOn<16)BOARD.currentLineFallSpeed=45.0508117675;//70;
					else if(BOARD.levelCurrentlyOn<19)BOARD.currentLineFallSpeed=30.0338745116;//50;
					else if(BOARD.levelCurrentlyOn<29)BOARD.currentLineFallSpeed=15.0169372557;//30;
					else BOARD.currentLineFallSpeed=0;//20;//if(BOARD.levelCurrentlyOn>=29)BOARD.currentLineFallSpeed=0;
					//BOARD.currentLineFallSpeed-=34.4827586207;*///https://gaming.stackexchange.com/questions/13057/tetris-difficulty
					//https://www.reddit.com/r/Tetris/comments/6o6tvv/what_is_the_block_algorithm_for_classic_tetris/	
				}
			}
			n=-1;continue;
		}
	}
	if(BOARD.linesClearedThisTime==1){BOARD.gameScore+=(40*(BOARD.levelCurrentlyOn+1));BOARD.numLinesCleared[0]+=1;}
	if(BOARD.linesClearedThisTime==2){BOARD.gameScore+=(100*(BOARD.levelCurrentlyOn+1));BOARD.numLinesCleared[1]+=1;}
	if(BOARD.linesClearedThisTime==3){BOARD.gameScore+=(300*(BOARD.levelCurrentlyOn+1));BOARD.numLinesCleared[2]+=1;}
	if(BOARD.linesClearedThisTime==4){BOARD.gameScore+=(1200*(BOARD.levelCurrentlyOn+1));BOARD.numLinesCleared[3]+=1;}
	BOARD.totalLinesCleared+=BOARD.linesClearedThisTime;
	if((GetTickCount()-BOARD.clearLineTimer)>250){//check for endgame;
		for(int m=0;m<10;m++){//0-9;//check endgame: 
			if(BOARD.positionsFilledPerm[m][20]==true){BOARD.checkGameEnded=true;break;}
			else if(m==9)BOARD.checkGameEnded=false;
		}
	}
}
void COMBO_LOGIC(){//for scoring: best combos:
	if(BOARD.increaseEachDrop==0){
		if(BOARD.currenStreakAddOne==true){
			BOARD.currentComboStreak+=1;
			if(BOARD.longestComboStreak<BOARD.currentComboStreak)BOARD.longestComboStreak=BOARD.currentComboStreak;
			BOARD.increaseEachDrop=-1;
		}
	}
	if(BOARD.increaseEachDrop==-1){
		if(BOARD.currenStreakAddOne==false){
			BOARD.currentComboStreak=0;
			BOARD.increaseEachDrop=-1;
		}
	}
}
void DROP_BLOCKS(){
	BOARD.gameTimeMilliseconds+=(GetTickCount()-BOARD.timePassed);//update game timer: 
	if(BOARD.gameTimeMilliseconds>=1000){
		BOARD.gameTimeMilliseconds=BOARD.gameTimeMilliseconds-1000;
		BOARD.gameTimeSeconds+=1;
		if(BOARD.gameTimeSeconds>=60){
			BOARD.gameTimeMinutes+=1;
			BOARD.gameTimeSeconds=BOARD.gameTimeSeconds-60;
		}
	}
	BOARD.timePassed=GetTickCount();
	if((GetTickCount()-BOARD.fallingTimer)>BOARD.currentLineFallSpeed&&BOARD.falling==true&&(GetTickCount()-BOARD.clearLineTimer)>250){//set some values: 
		BOARD.newPossiblePosition[0][1]=-1;BOARD.newPossiblePosition[1][1]=-1;
		BOARD.newPossiblePosition[2][1]=-1;BOARD.newPossiblePosition[3][1]=-1;
		BOARD.moveFour[0]=false;BOARD.moveFour[1]=false;
		BOARD.moveFour[2]=false;BOARD.moveFour[3]=false;
		for(int n=0;n<4;n++){
			if(BOARD.yPosFilledDownMost>0&&BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]-1]==false)BOARD.moveFour[n]=true;
		}
		if(BOARD.moveFour[0]==true&&BOARD.moveFour[1]==true&&BOARD.moveFour[2]==true&&BOARD.moveFour[3]==true){//set the positions;
			for(int n=0;n<4;n++){
				BOARD.positionsFilledTemp[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]=false;
				BOARD.currPosFilled[n][1]-=1;
				BOARD.newPossiblePosition[n][1]=BOARD.currPosFilled[n][1];
			}
			for(int n=0;n<4;n++){
				BOARD.positionsFilledTemp[BOARD.currPosFilled[n][0]][BOARD.newPossiblePosition[n][1]]=true;
				if(n==3){	BOARD.yPosFilledUpMost-=1;BOARD.yPosFilledDownMost-=1;}
				if(BOARD.currPosFilled[n][1]==0||BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]-1]==true){
							BOARD.falling=false;BOARD.rotateFallTimer=GetTickCount();}
			}
		}
		else{
			for(int n=0;n<4;n++){
				if(BOARD.moveFour[n]==false){
					BOARD.falling=false;BOARD.rotateFallTimer=GetTickCount();
				}
			}
		}	
		BOARD.fallingTimer=GetTickCount();
		BOARD.increaseEachDrop=-1;//for combos:
	}
	if((GetTickCount()-BOARD.rotateFallTimer)>500&&BOARD.falling==false||BOARD.moveCount>15&&BOARD.falling==false){//place;
		BOARD.increaseEachDrop=0;//for combos:
		BOARD.currenStreakAddOne=false;//for combos:
		for(int n=0;n<4;n++){		BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]=true;
			for(int m=0;m<3;m++){	BOARD.positionsFilledColorPerm[m][BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]=BOARD.positionsFilledColorTempAndPrev[m];}
			BOARD.positionsFilledTemp[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]=false;
		}
		orientationOfCurrentBlockTypeFalling();
		BOARD.held=false;
		BOARD.moveCount=0;
		BOARD.clearLineTimer=GetTickCount();
	}
	//figure out the preview position: 
	for(int n=0;n<10;n++){
		for(int m=23;m>-1;m--)BOARD.positionsFilledPrev[n][m]=false;}//reset to false: 
	//get the y position minus the lowest y position in that set to keep the same orientation: 
	int orientationOfYBlocks[4]={
		BOARD.currPosFilled[0][1]-BOARD.yPosFilledDownMost,BOARD.currPosFilled[1][1]-BOARD.yPosFilledDownMost,
		BOARD.currPosFilled[2][1]-BOARD.yPosFilledDownMost,BOARD.currPosFilled[3][1]-BOARD.yPosFilledDownMost
	};
	//get the highest permanent block in the x range of the falling blocks: 
	int highestPermBlock=0;
	int permBlocksY[4]={0,0,0,0};
	for(int n=0;n<4;n++){
		for(int m=0;m<20;m++){
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][m]==true&&m<BOARD.currPosFilled[n][1])permBlocksY[n]=m+1;
		}
	}
	for(int n=0;n<4;n++){if(highestPermBlock<permBlocksY[n])highestPermBlock=permBlocksY[n];}
	//set the tempView: 
	int countFalse=0;
	do{
		if(countFalse==4)countFalse=0;
		for(int n=0;n<4;n++){
			BOARD.positionsFilledPrev[BOARD.currPosFilled[n][0]][orientationOfYBlocks[n]+highestPermBlock]=true;
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][orientationOfYBlocks[n]+highestPermBlock-1]==false&&highestPermBlock>0){countFalse+=1;}
			if(n==3&&countFalse==4){//lower by one: 
				for(int m=0;m<4;m++){BOARD.positionsFilledPrev[BOARD.currPosFilled[m][0]][orientationOfYBlocks[m]+highestPermBlock]=false;}
				highestPermBlock-=1;
			}
		}
	}while(countFalse==4);
}
void BUTTONS_INIT(){//BUTTONS
		numberButtonsDraw[0]=6;		numberButtonsDraw[1]=5;		numberButtonsDraw[2]=22;	numberButtonsDraw[3]=9;		numberButtonsDraw[4]=24;
		numberButtonsDraw[5]=7;		numberButtonsDraw[6]=5;		numberButtonsDraw[7]=22;	numberButtonsDraw[8]=10;	numberButtonsDraw[9]=9;
		int B,sub;//current button number to initialize;subButton; 0 is center point. ++ is bottom left. opposites. 
		B=0;sub=0;//main screen: 
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(200*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="T\t\tE\t\tT\t\tR\t\tI\t\tS";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(450*WINDOW.aspect);			BUTTON[B][sub].width=900;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(150*WINDOW.aspect);	BUTTON[B][sub].height=100;
				BUTTON[B][sub].text="Start Tetris";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(450*WINDOW.aspect);			BUTTON[B][sub].width=450;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(50*WINDOW.aspect);		BUTTON[B][sub].height=100;
				BUTTON[B][sub].text="General Rules";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=450;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(50*WINDOW.aspect);		BUTTON[B][sub].height=100;
				BUTTON[B][sub].text="Controls";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(450*WINDOW.aspect);			BUTTON[B][sub].width=900;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-50*WINDOW.aspect);	BUTTON[B][sub].height=100;
				BUTTON[B][sub].text="High Scores";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(450*WINDOW.aspect);			BUTTON[B][sub].width=900;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-150*WINDOW.aspect);	BUTTON[B][sub].height=100;
				BUTTON[B][sub].text="Exit Tetris";//sub+=1;
		B=1;sub=0;//clicked on rules: 
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(200*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="T\t\tE\t\tT\t\tR\t\tI\t\tS";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=1500;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(115*WINDOW.aspect);	BUTTON[B][sub].height=630;
				BUTTON[B][sub].text="Board:\n";
				BUTTON[B][sub].text+="\t*The size of the board contains 10x20 possible spots for permanent blocks and falling blocks.\n";
				BUTTON[B][sub].text+="\t*Falling blocks contain a ghost piece which shows the bottom most spot that the block can fall to.\n";
				BUTTON[B][sub].text+="\t*The block to fall next is shown in the right pane.\n";
				BUTTON[B][sub].text+="\t*A block can be put into holding mode on the left pane of the board until needed.\n";
				BUTTON[B][sub].text+="\t*Once a block is in holding, it cannot be used again\n\t\tuntil the next falling block permanently places.\n";
				BUTTON[B][sub].text+="Objectives:\n";
				BUTTON[B][sub].text+="\t*Clear as many rows as possible by strategically placing the seven block types to fill a row.\n";
				BUTTON[B][sub].text+="\t*Once a row is full, that row will dissapear,\n\t\tand every block above that row will fall down one column.\n";
				BUTTON[B][sub].text+="\t*The score will be increased appropriately.\n";
				BUTTON[B][sub].text+="User Interaction:\n";
				BUTTON[B][sub].text+="\t*Blocks can be rotated by the player and be moved left and right.\n";
				BUTTON[B][sub].text+="\t*Blocks can be held by the player to be used at a later time.\n";
				BUTTON[B][sub].text+="\t*Blocks can be soft dropped or hard dropped by the player.\n";
				BUTTON[B][sub].text+="\t*Soft dropping is moving the block type down by one column.\n";
				BUTTON[B][sub].text+="\t*Hard dropping is moving the block type to the ghost piece permanently placing in an instant.\n";
				BUTTON[B][sub].text+="\t*Once a block is permanently placed, the next block type will start to fall.\n";
				BUTTON[B][sub].text+="Scoring:\n";
				BUTTON[B][sub].text+="\t*Soft and hard dropping adds 1 point to the score per column fallen.\n";
				BUTTON[B][sub].text+="\t*Up to four rows can be filled at once. Four rows filled at once is called a Tetris.\n";
				BUTTON[B][sub].text+="\t*One row points added:\t\t\t\t\t\t[ 40\t * (LevelCurrentlyOn + 1) ]\n";
				BUTTON[B][sub].text+="\t*Two rows points added:\t\t\t\t\t [ 100\t* (LevelCurrentlyOn + 1) ]\n";
				BUTTON[B][sub].text+="\t*Three rows points added:\t\t\t\t [ 300\t* (LevelCurrentlyOn + 1) ]\n";
				BUTTON[B][sub].text+="\t*Four(Tetris) rows points added:\t[ 1200 * (LevelCurrentlyOn + 1) ]\n";
				BUTTON[B][sub].text+="\t*Every ten rows cleared, a new level is entered,\n\t\tand the falling speed may increase depending on the level until level 29.\n";
				BUTTON[B][sub].text+="\t*Included with the score is the time, level reached, lines cleared that level and the best combo.\n";
				BUTTON[B][sub].text+="\t*A combo is consecutively clearing one or more lines with a placed block.\n";
				BUTTON[B][sub].text+="Game End/Pausing:\n";
				BUTTON[B][sub].text+="\t*The game ends once permanantly placed blocks reach above the top row.\n";
				BUTTON[B][sub].text+="\t*The game can be paused by pressing the ESC (escape) key.\n";
				BUTTON[B][sub].text+="\t*Once the game unpauses, the game will resume in three seconds.\n";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(185*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Start Tetris";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(185*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Back To Main Screen";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=1500;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(150*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="General Rules";sub+=1;
		B=2;sub=0;//clicked on controls: 
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(200*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="T\t\tE\t\tT\t\tR\t\tI\t\tS";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(185*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Start Tetris";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(185*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Back To Main Screen";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(115*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Move Left:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(115*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Left Arrow";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(65*WINDOW.aspect);		BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Move Right:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(65*WINDOW.aspect);		BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Right Arrow";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(15*WINDOW.aspect);		BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Rotate:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(15*WINDOW.aspect);		BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Up Arrow";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-35*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Switch Rotation:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-35*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="'G' Or 'g' Key";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-85*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Soft Drop:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-85*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Down Arrow";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-135*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Hard Drop:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-135*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Space Key";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-185*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Hold/Switch Hold:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-185*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="'H' Or 'h' Key";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-235*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Pause Game:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-235*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="'ESC' Key";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-285*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Fullscreen:";sub+=1;//toggle
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-285*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="'F1' Key";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=1500;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(150*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Controls";//sub+=1;
		B=3;sub=0;//clicked on high scores: 
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(200*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="T\t\tE\t\tT\t\tR\t\tI\t\tS";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(185*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Start Tetris";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(185*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Back To Main Screen";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=1500;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(150*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="High Score Table";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(115*WINDOW.aspect);	BUTTON[B][sub].height=120;
				BUTTON[B][sub].text="1:\t Name:\t\t\t\t\t\t\t\t\t\t\n\t\t Score:\t\t\t\t\t\t\t\t\t \n\t\t Level Reached:\t\t\t\t\t \n\t\t Lines Cleared This Level:\n\t\t Time:\t\t\t\t\t\t\t\t\t\t\n\t\t Best Combo:\t\t\t\t\t\t\t";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-5*WINDOW.aspect);		BUTTON[B][sub].height=120;
				BUTTON[B][sub].text="2:\t Name:\t\t\t\t\t\t\t\t\t\t\n\t\t Score:\t\t\t\t\t\t\t\t\t \n\t\t Level Reached:\t\t\t\t\t \n\t\t Lines Cleared This Level:\n\t\t Time:\t\t\t\t\t\t\t\t\t\t\n\t\t Best Combo:\t\t\t\t\t\t\t";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-125*WINDOW.aspect);	BUTTON[B][sub].height=120;
				BUTTON[B][sub].text="3:\t Name:\t\t\t\t\t\t\t\t\t\t\n\t\t Score:\t\t\t\t\t\t\t\t\t \n\t\t Level Reached:\t\t\t\t\t \n\t\t Lines Cleared This Level:\n\t\t Time:\t\t\t\t\t\t\t\t\t\t\n\t\t Best Combo:\t\t\t\t\t\t\t";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-245*WINDOW.aspect);	BUTTON[B][sub].height=120;
				BUTTON[B][sub].text="4:\t Name:\t\t\t\t\t\t\t\t\t\t\n\t\t Score:\t\t\t\t\t\t\t\t\t \n\t\t Level Reached:\t\t\t\t\t \n\t\t Lines Cleared This Level:\n\t\t Time:\t\t\t\t\t\t\t\t\t\t\n\t\t Best Combo:\t\t\t\t\t\t\t";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-365*WINDOW.aspect);	BUTTON[B][sub].height=120;
				BUTTON[B][sub].text="5:\t Name:\t\t\t\t\t\t\t\t\t\t\n\t\t Score:\t\t\t\t\t\t\t\t\t \n\t\t Level Reached:\t\t\t\t\t \n\t\t Lines Cleared This Level:\n\t\t Time:\t\t\t\t\t\t\t\t\t\t\n\t\t Best Combo:\t\t\t\t\t\t\t";sub+=1;
		B=4;sub=0;//Started Game: 
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(500*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(200*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="T\t\tE\t\tT\t\tR\t\tI\t\tS";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(500*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(160*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="Scoring Table And Statistics:\n";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(140*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\tScore: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(120*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\tLevel Statistics: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(100*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tLevel Currently On: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(80*WINDOW.aspect);		BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tLevel Fall Speed: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(60*WINDOW.aspect);		BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tLines Cleared This Level: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(40*WINDOW.aspect);		BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\tLines Cleared/Statistics: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(20*WINDOW.aspect);		BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tOne Line At Once: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(0*WINDOW.aspect);		BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tTwo Lines At Once: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-20*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tThree Lines At Once: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-40*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tFour Lines At Once: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-60*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tLines Cleared Total: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-80*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tBest Combo: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-100*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\tBlocks Dropped/Held: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-120*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tI Block: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-140*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tJ Block: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-160*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tL Block: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-180*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tO Block: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-200*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tS Block: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-220*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tT Block: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-240*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tZ Block: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-260*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\t\tBlocks Held: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(730*WINDOW.aspect);			BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-280*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="\tTime: ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(250*WINDOW.aspect);			BUTTON[B][sub].width=500;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(0*WINDOW.aspect)-(75*WINDOW.aspect);		BUTTON[B][sub].height=150;
				BUTTON[B][sub].text="G A M E\tO V E R\n\nContinue To Scoring Sheet";//sub+=1;
		B=5;sub=0;//Pause Game: 
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(200*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="T\t\tE\t\tT\t\tR\t\tI\t\tS";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(450*WINDOW.aspect);			BUTTON[B][sub].width=900;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(150*WINDOW.aspect);	BUTTON[B][sub].height=100;
				BUTTON[B][sub].text="Continue Tetris";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(450*WINDOW.aspect);			BUTTON[B][sub].width=450;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(50*WINDOW.aspect);		BUTTON[B][sub].height=100;
				BUTTON[B][sub].text="General Rules";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=450;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(50*WINDOW.aspect);		BUTTON[B][sub].height=100;
				BUTTON[B][sub].text="Controls";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(450*WINDOW.aspect);			BUTTON[B][sub].width=900;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-50*WINDOW.aspect);	BUTTON[B][sub].height=100;
				BUTTON[B][sub].text="Restart Tetris";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(450*WINDOW.aspect);			BUTTON[B][sub].width=450;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-150*WINDOW.aspect);	BUTTON[B][sub].height=100;
				BUTTON[B][sub].text="Exit To Welcome Screen";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=450;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-150*WINDOW.aspect);	BUTTON[B][sub].height=100;
				BUTTON[B][sub].text="Exit Tetris";//sub+=1;
		B=6;sub=0;//clicked on rules: 
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(200*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="T\t\tE\t\tT\t\tR\t\tI\t\tS";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=1500;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(115*WINDOW.aspect);	BUTTON[B][sub].height=630;
				BUTTON[B][sub].text="Board:\n";
				BUTTON[B][sub].text+="\t*The size of the board contains 10x20 possible spots for permanent blocks and falling blocks.\n";
				BUTTON[B][sub].text+="\t*Falling blocks contain a ghost piece which shows the bottom most spot that the block can fall to.\n";
				BUTTON[B][sub].text+="\t*The block to fall next is shown in the right pane.\n";
				BUTTON[B][sub].text+="\t*A block can be put into holding mode on the left pane of the board until needed.\n";
				BUTTON[B][sub].text+="\t*Once a block is in holding, it cannot be used again\n\t\tuntil the next falling block permanently places.\n";
				BUTTON[B][sub].text+="Objectives:\n";
				BUTTON[B][sub].text+="\t*Clear as many rows as possible by strategically placing the seven block types to fill a row.\n";
				BUTTON[B][sub].text+="\t*Once a row is full, that row will dissapear,\n\t\tand every block above that row will fall down one column.\n";
				BUTTON[B][sub].text+="\t*The score will be increased appropriately.\n";
				BUTTON[B][sub].text+="User Interaction:\n";
				BUTTON[B][sub].text+="\t*Blocks can be rotated by the player and be moved left and right.\n";
				BUTTON[B][sub].text+="\t*Blocks can be held by the player to be used at a later time.\n";
				BUTTON[B][sub].text+="\t*Blocks can be soft dropped or hard dropped by the player.\n";
				BUTTON[B][sub].text+="\t*Soft dropping is moving the block type down by one column.\n";
				BUTTON[B][sub].text+="\t*Hard dropping is moving the block type to the ghost piece permanently placing in an instant.\n";
				BUTTON[B][sub].text+="\t*Once a block is permanently placed, the next block type will start to fall.\n";
				BUTTON[B][sub].text+="Scoring:\n";
				BUTTON[B][sub].text+="\t*Soft and hard dropping adds 1 point to the score per column fallen.\n";
				BUTTON[B][sub].text+="\t*Up to four rows can be filled at once. Four rows filled at once is called a Tetris.\n";
				BUTTON[B][sub].text+="\t*One row points added:\t\t\t\t\t\t[ 40\t * (LevelCurrentlyOn + 1) ]\n";
				BUTTON[B][sub].text+="\t*Two rows points added:\t\t\t\t\t [ 100\t* (LevelCurrentlyOn + 1) ]\n";
				BUTTON[B][sub].text+="\t*Three rows points added:\t\t\t\t [ 300\t* (LevelCurrentlyOn + 1) ]\n";
				BUTTON[B][sub].text+="\t*Four(Tetris) rows points added:\t[ 1200 * (LevelCurrentlyOn + 1) ]\n";
				BUTTON[B][sub].text+="\t*Every ten rows cleared, a new level is entered,\n\t\tand the falling speed may increase depending on the level until level 29.\n";
				BUTTON[B][sub].text+="\t*Included with the score is the time, level reached, lines cleared that level and the best combo.\n";
				BUTTON[B][sub].text+="\t*A combo is consecutively clearing one or more lines with a placed block.\n";
				BUTTON[B][sub].text+="Game End/Pausing:\n";
				BUTTON[B][sub].text+="\t*The game ends once permanantly placed blocks reach above the top row.\n";
				BUTTON[B][sub].text+="\t*The game can be paused by pressing the ESC (escape) key.\n";
				BUTTON[B][sub].text+="\t*Once the game unpauses, the game will resume in three seconds.\n";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(185*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Continue Tetris";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(185*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Back To Pause Screen";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=1500;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(150*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="General Rules";//sub+=1;
		B=7;sub=0;//clicked on controls: 
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(200*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="T\t\tE\t\tT\t\tR\t\tI\t\tS";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(185*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Continue Tetris";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(185*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Back To Pause Screen";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(115*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Move Left:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(115*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Left Arrow";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(65*WINDOW.aspect);		BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Move Right:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(65*WINDOW.aspect);		BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Right Arrow";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(15*WINDOW.aspect);		BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Rotate:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(15*WINDOW.aspect);		BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Up Arrow";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-35*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Switch Rotation:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-35*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="'G' Or 'g' Key";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-85*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Soft Drop:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-85*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Down Arrow";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-135*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Hard Drop:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-135*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Space Key";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-185*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Hold/Switch Hold:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-185*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="'H' Or 'h' Key";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-235*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Pause Game:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-235*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="'ESC' Key";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(300*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-285*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="Fullscreen:";sub+=1;//toggle
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(-40*WINDOW.aspect);			BUTTON[B][sub].width=260;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-285*WINDOW.aspect);	BUTTON[B][sub].height=50;
				BUTTON[B][sub].text="'F1' Key";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=1500;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(150*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Controls";//sub+=1;
		B=8;sub=0;//show high scores: 
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(200*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="T\t\tE\t\tT\t\tR\t\tI\t\tS";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(185*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Start Tetris";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(185*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Back To Main Screen";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=1500;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(150*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="High Score Table";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(115*WINDOW.aspect);	BUTTON[B][sub].height=120;
				BUTTON[B][sub].text="1:\t Name:\t\t\t\t\t\t\t\t\t\t\n\t\t Score:\t\t\t\t\t\t\t\t\t \n\t\t Level Reached:\t\t\t\t\t \n\t\t Lines Cleared This Level:\n\t\t Time:\t\t\t\t\t\t\t\t\t\t\n\t\t Best Combo:\t\t\t\t\t\t\t";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-5*WINDOW.aspect);		BUTTON[B][sub].height=120;
				BUTTON[B][sub].text="2:\t Name:\t\t\t\t\t\t\t\t\t\t\n\t\t Score:\t\t\t\t\t\t\t\t\t \n\t\t Level Reached:\t\t\t\t\t \n\t\t Lines Cleared This Level:\n\t\t Time:\t\t\t\t\t\t\t\t\t\t\n\t\t Best Combo:\t\t\t\t\t\t\t";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-125*WINDOW.aspect);	BUTTON[B][sub].height=120;
				BUTTON[B][sub].text="3:\t Name:\t\t\t\t\t\t\t\t\t\t\n\t\t Score:\t\t\t\t\t\t\t\t\t \n\t\t Level Reached:\t\t\t\t\t \n\t\t Lines Cleared This Level:\n\t\t Time:\t\t\t\t\t\t\t\t\t\t\n\t\t Best Combo:\t\t\t\t\t\t\t";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-245*WINDOW.aspect);	BUTTON[B][sub].height=120;
				BUTTON[B][sub].text="4:\t Name:\t\t\t\t\t\t\t\t\t\t\n\t\t Score:\t\t\t\t\t\t\t\t\t \n\t\t Level Reached:\t\t\t\t\t \n\t\t Lines Cleared This Level:\n\t\t Time:\t\t\t\t\t\t\t\t\t\t\n\t\t Best Combo:\t\t\t\t\t\t\t";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-365*WINDOW.aspect);	BUTTON[B][sub].height=120;
				BUTTON[B][sub].text="5:\t Name:\t\t\t\t\t\t\t\t\t\t\n\t\t Score:\t\t\t\t\t\t\t\t\t \n\t\t Level Reached:\t\t\t\t\t \n\t\t Lines Cleared This Level:\n\t\t Time:\t\t\t\t\t\t\t\t\t\t\n\t\t Best Combo:\t\t\t\t\t\t\t";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-485*WINDOW.aspect);	BUTTON[B][sub].height=105;
				BUTTON[B][sub].text="You: Score:\n";//sub+=1;
		B=9;sub=0;//enter high score: 
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(0*WINDOW.aspect);				BUTTON[B][sub].width=0;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(200*WINDOW.aspect);	BUTTON[B][sub].height=0;
				BUTTON[B][sub].text="T\t\tE\t\tT\t\tR\t\tI\t\tS";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(750*WINDOW.aspect);			BUTTON[B][sub].width=1500;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(150*WINDOW.aspect);	BUTTON[B][sub].height=35;
				BUTTON[B][sub].text="Scoring Sheet";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(115*WINDOW.aspect);	BUTTON[B][sub].height=85;
				BUTTON[B][sub].text="Enter Name:\n\n";sub+=1;//have the pointer for the text to be equal to 0 +half a character width;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(30*WINDOW.aspect);		BUTTON[B][sub].height=30;
				BUTTON[B][sub].text="Confirm Name";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(0*WINDOW.aspect);		BUTTON[B][sub].height=85;
				BUTTON[B][sub].text="Your Score:\t\t\t\t\t\t\t";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-85*WINDOW.aspect);	BUTTON[B][sub].height=85;
				BUTTON[B][sub].text="Level Reached:\t\t\t\t\t ";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-170*WINDOW.aspect);	BUTTON[B][sub].height=85;
				BUTTON[B][sub].text="Lines Cleared This Level:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-255*WINDOW.aspect);	BUTTON[B][sub].height=85;
				BUTTON[B][sub].text="Time:";sub+=1;
			BUTTON[B][sub].x=WINDOW.winW-(WINDOW.winW/2)-(375*WINDOW.aspect);			BUTTON[B][sub].width=750;
			BUTTON[B][sub].y=(WINDOW.winH/2)-(50*WINDOW.aspect)-(-340*WINDOW.aspect);	BUTTON[B][sub].height=85;
				BUTTON[B][sub].text="Best Combo:";//sub+=1;
}
void WINDOW_INIT(){
	for(int n=0;n<2;n++){
		WINDOW.clicked[n]=-1;
		WINDOW.released[n]=-1;
	}
	WINDOW.currentScreen=0;
	WINDOW.buttonCurrentlyClicked=-1;
	WINDOW.buttonCurrentlySelected=-1;
	WINDOW.allowHardDrop=true;
	WINDOW.allowRotation=true;
	for(int n=0;n<128;n++){
		WINDOW.keysCurrentlyPressedSpecial[n]=false;
	}
}
void BOARD_INIT(){
	for(int o=0;o<3;o++){//board: 
		for(int n=0;n<10;n++){
			for(int m=0;m<24;m++){
				if(o==0){
					BOARD.positionsFilledPerm[n][m]=false;//once fallen to ground layer;
					BOARD.positionsFilledTemp[n][m]=false;//falling to ground layer;
					BOARD.positionsFilledPrev[n][m]=false;//preview;
					BOARD.positionsFilledNextBlockToFall[n][m]=false;
					BOARD.positionsFilledHolding[n][m]=false;
				}
				BOARD.positionsFilledColorPerm[o][n][m]=0;
				if(n<4&&m<2){//current and new possible position: 
					BOARD.currPosFilled[n][m]=-1;
					BOARD.newPossiblePosition[n][m]=-1;
					BOARD.moveFour[n]=false;
				}				
			}
			if(o==0){
				if(n<3){//color: 
					BOARD.positionsFilledColorTempAndPrev[n]=0;
					BOARD.positionsFilledColorHold[n]=0;
					BOARD.positionsFilledColorNext[n]=0;
				}
				if(n<4){//lines cleared statistics: 
					BOARD.numLinesCleared[n]=0;
				}
				if(n<7){//blocks dropped statistics: 
					BOARD.blockDropped[n]=0;
				}
			}
		}
	}
	BOARD.prevBlock=-1;
	BOARD.currentBlockTypeFalling=-1;
	BOARD.currentBlockTypeHolding=-1;
		BOARD.currentBlockTypeCurrentRotation=0;
		BOARD.held=false;
	BOARD.nextBlockFalling=-1;
	BOARD.fallingTimer=-1;
	BOARD.rotateFallTimer=-1;
	BOARD.falling=false;
	BOARD.started=false;
	BOARD.rotation=true;
	BOARD.gamePause=true;
		BOARD.resumeTimer=GetTickCount();
			BOARD.ShowGameOverScreenTimer=0;
		BOARD.fallingTimerPause=-1;
		BOARD.rotateFallTimerPause=-1;
		BOARD.clearLineTimerPause=-1;
			BOARD.gameTimeMilliseconds=0;
			BOARD.gameTimeSeconds=0;
			BOARD.gameTimeMinutes=0;
			BOARD.timePassed=0;
	BOARD.gameEnded=false;
	BOARD.checkGameEnded=false;
		BOARD.xPosFilledLeftMost=10;
		BOARD.xPosFilledRightMost=0;
		BOARD.yPosFilledUpMost=0;
		BOARD.yPosFilledDownMost=20;
	BOARD.permPlaceWithSpaceKey=false;
	BOARD.clearLineTimer=-1;
		BOARD.gameScore=0;
		BOARD.levelCurrentlyOn=0;
		BOARD.linesClearedForThisLevel=0;
		BOARD.linesClearedThisTime=0;
				BOARD.totalLinesCleared=0;
				BOARD.blocksHeld=0;
				BOARD.increaseEachDrop=-1;
					BOARD.currenStreakAddOne=0;
				BOARD.longestComboStreak=0;
				BOARD.currentComboStreak=0;
		BOARD.currentLineFallSpeed=1000/*800*/;//1000;//milliseconds. 
		BOARD.moveCount=0;
	BOARD.nameEnterHighScore="\0";
}
VOID TEXT_INIT(){
	TEXTINPUT.textLength=0;
	TEXTINPUT.pointer="|";
	TEXTINPUT.pointerPosition=0;
	TEXTINPUT.pointerBlinkAlphaOn=true;
	TEXTINPUT.pointerBlinkingRate=500;//every (n)ms, the color of alpha changes from 1 to 0 and 0 to 1;
	TEXTINPUT.blinkertimer=GetTickCount();
}
