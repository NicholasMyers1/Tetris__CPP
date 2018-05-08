#include "includesVoids.h"
void LISTS(){
	for(int n=0;n<3;n++){
		board[n]=n+1;//set the list number;
		//generate the list;
		glGenLists(board[n]);
		glNewList(board[n],GL_COMPILE);
		if(n==0)glBegin(GL_POLYGON);
		if(n==1)glBegin(GL_TRIANGLE_FAN);
		if(n==2)glBegin(GL_LINE_LOOP);
				glVertex2f(1.f, 1.f);
		    	glVertex2f(1.f, -1.f);
		    	glVertex2f(-1.f, -1.f);
		    	glVertex2f(-1.f, 1.f);
			glEnd();
		glEndList();
	}
}
void COUNTDOWN_ON_PAUSE(){
	glColor4f(1,1,1,1);
	if((GetTickCount()-BOARD.resumeTimer)<1000){//3: 
		glLoadIdentity();glTranslatef(-1*2,2*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(0*2,2*2,-50);glCallList(board[0]);
		glLoadIdentity();glTranslatef(1*2,2*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(1*2,1*2,-50);glCallList(board[0]);
		glLoadIdentity();glTranslatef(1*2,0*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(0*2,0*2,-50);glCallList(board[0]);
		glLoadIdentity();glTranslatef(1*2,-1*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(1*2,-2*2,-50);glCallList(board[0]);
		glLoadIdentity();glTranslatef(0*2,-2*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(-1*2,-2*2,-50);glCallList(board[0]);
	}
	else if((GetTickCount()-BOARD.resumeTimer)<2000){//2: 
		glLoadIdentity();glTranslatef(-1*2,2*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(0*2,2*2,-50);glCallList(board[0]);
		glLoadIdentity();glTranslatef(1*2,2*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(1*2,1*2,-50);glCallList(board[0]);
		glLoadIdentity();glTranslatef(1*2,0*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(0*2,0*2,-50);glCallList(board[0]);
		glLoadIdentity();glTranslatef(-1*2,0*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(-1*2,-1*2,-50);glCallList(board[0]);
		glLoadIdentity();glTranslatef(-1*2,-2*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(0*2,-2*2,-50);glCallList(board[0]);
		glLoadIdentity();glTranslatef(1*2,-2*2,-50);glCallList(board[0]);
	}
	else if((GetTickCount()-BOARD.resumeTimer)<3000){//1:   
		glLoadIdentity();glTranslatef(-1*2,2*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(0*2,2*2,-50);glCallList(board[0]);
		glLoadIdentity();glTranslatef(0*2,1*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(0*2,0*2,-50);glCallList(board[0]);
		glLoadIdentity();glTranslatef(0*2,-1*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(-1*2,-2*2,-50);glCallList(board[0]);
		glLoadIdentity();glTranslatef(0*2,-2*2,-50);glCallList(board[0]);	glLoadIdentity();glTranslatef(1*2,-2*2,-50);glCallList(board[0]);
	}
}
void orientationOfCurrentBlockTypeFalling(){
	//set some variables: 
	if(BOARD.nextBlockFalling==-1)BOARD.nextBlockFalling=(rand()%7+1)-1;
	BOARD.currentBlockTypeFalling=BOARD.nextBlockFalling;
	BOARD.prevBlock=BOARD.currentBlockTypeFalling;
	BOARD.nextBlockFalling=(rand()%8+1)-1;
	if(BOARD.nextBlockFalling==BOARD.prevBlock||BOARD.nextBlockFalling==7){
		BOARD.nextBlockFalling=(rand()%7+1)-1;
	}
	BOARD.currentBlockTypeCurrentRotation=0;
	BOARD.permPlaceWithSpaceKey=false;
	BOARD.falling=true;
	for(int n=0;n<10;n++){//reset tempBlocks: 
		for(int m=0;m<24;m++){
			BOARD.positionsFilledTemp[n][m]=false;//falling to ground layer;
			BOARD.positionsFilledPrev[n][m]=false;
			BOARD.positionsFilledNextBlockToFall[n][m]=false;
		}
	}
	BOARD.blockDropped[BOARD.currentBlockTypeFalling]+=1;
	if(BOARD.currentBlockTypeFalling==0){//set the block: 
		BOARD.positionsFilledTemp[6][20]=true;
			BOARD.currPosFilled[0][0]=6;
			BOARD.currPosFilled[0][1]=20;
		BOARD.positionsFilledTemp[5][20]=true;
			BOARD.currPosFilled[1][0]=5;
			BOARD.currPosFilled[1][1]=20;
		BOARD.positionsFilledTemp[4][20]=true;
			BOARD.currPosFilled[2][0]=4;
			BOARD.currPosFilled[2][1]=20;
		BOARD.positionsFilledTemp[3][20]=true;
			BOARD.currPosFilled[3][0]=3;
			BOARD.currPosFilled[3][1]=20;
		BOARD.positionsFilledColorTempAndPrev[0]=0;BOARD.positionsFilledColorTempAndPrev[1]=1;BOARD.positionsFilledColorTempAndPrev[2]=1;
	}
	else if(BOARD.currentBlockTypeFalling==1){
		BOARD.positionsFilledTemp[3][21]=true;
			BOARD.currPosFilled[0][0]=3;
			BOARD.currPosFilled[0][1]=21;
		BOARD.positionsFilledTemp[3][20]=true;
			BOARD.currPosFilled[1][0]=3;
			BOARD.currPosFilled[1][1]=20;
		BOARD.positionsFilledTemp[4][20]=true;
			BOARD.currPosFilled[2][0]=4;
			BOARD.currPosFilled[2][1]=20;
		BOARD.positionsFilledTemp[5][20]=true;
			BOARD.currPosFilled[3][0]=5;
			BOARD.currPosFilled[3][1]=20;
		BOARD.positionsFilledColorTempAndPrev[0]=0;BOARD.positionsFilledColorTempAndPrev[1]=0;BOARD.positionsFilledColorTempAndPrev[2]=1;
	}
	else if(BOARD.currentBlockTypeFalling==2){
		BOARD.positionsFilledTemp[5][21]=true;
			BOARD.currPosFilled[0][0]=5;
			BOARD.currPosFilled[0][1]=21;
		BOARD.positionsFilledTemp[5][20]=true;
			BOARD.currPosFilled[1][0]=5;
			BOARD.currPosFilled[1][1]=20;
		BOARD.positionsFilledTemp[4][20]=true;
			BOARD.currPosFilled[2][0]=4;
			BOARD.currPosFilled[2][1]=20;
		BOARD.positionsFilledTemp[3][20]=true;
			BOARD.currPosFilled[3][0]=3;
			BOARD.currPosFilled[3][1]=20;
		BOARD.positionsFilledColorTempAndPrev[0]=1;BOARD.positionsFilledColorTempAndPrev[1]=0.64705882352;BOARD.positionsFilledColorTempAndPrev[2]=0;
	}
	else if(BOARD.currentBlockTypeFalling==3){
		BOARD.positionsFilledTemp[5][21]=true;
			BOARD.currPosFilled[0][0]=5;
			BOARD.currPosFilled[0][1]=21;
		BOARD.positionsFilledTemp[4][21]=true;
			BOARD.currPosFilled[1][0]=4;
			BOARD.currPosFilled[1][1]=21;
		BOARD.positionsFilledTemp[5][20]=true;
			BOARD.currPosFilled[2][0]=5;
			BOARD.currPosFilled[2][1]=20;
		BOARD.positionsFilledTemp[4][20]=true;
			BOARD.currPosFilled[3][0]=4;
			BOARD.currPosFilled[3][1]=20;
		BOARD.positionsFilledColorTempAndPrev[0]=1;BOARD.positionsFilledColorTempAndPrev[1]=1;BOARD.positionsFilledColorTempAndPrev[2]=0;
	}
	else if(BOARD.currentBlockTypeFalling==4){
		BOARD.positionsFilledTemp[5][21]=true;
			BOARD.currPosFilled[0][0]=5;
			BOARD.currPosFilled[0][1]=21;
		BOARD.positionsFilledTemp[4][21]=true;
			BOARD.currPosFilled[1][0]=4;
			BOARD.currPosFilled[1][1]=21;
		BOARD.positionsFilledTemp[4][20]=true;
			BOARD.currPosFilled[2][0]=4;
			BOARD.currPosFilled[2][1]=20;
		BOARD.positionsFilledTemp[3][20]=true;
			BOARD.currPosFilled[3][0]=3;
			BOARD.currPosFilled[3][1]=20;
		BOARD.positionsFilledColorTempAndPrev[0]=0;BOARD.positionsFilledColorTempAndPrev[1]=1;BOARD.positionsFilledColorTempAndPrev[2]=0;
	}
	else if(BOARD.currentBlockTypeFalling==5){
		BOARD.positionsFilledTemp[4][21]=true;
			BOARD.currPosFilled[0][0]=4;
			BOARD.currPosFilled[0][1]=21;
		BOARD.positionsFilledTemp[3][20]=true;
			BOARD.currPosFilled[1][0]=3;
			BOARD.currPosFilled[1][1]=20;
		BOARD.positionsFilledTemp[4][20]=true;
			BOARD.currPosFilled[2][0]=4;
			BOARD.currPosFilled[2][1]=20;
		BOARD.positionsFilledTemp[5][20]=true;
			BOARD.currPosFilled[3][0]=5;
			BOARD.currPosFilled[3][1]=20;
		BOARD.positionsFilledColorTempAndPrev[0]=0.50196078431;BOARD.positionsFilledColorTempAndPrev[1]=0;BOARD.positionsFilledColorTempAndPrev[2]=0.50196078431;
	}
	else if(BOARD.currentBlockTypeFalling==6){
		BOARD.positionsFilledTemp[3][21]=true;
			BOARD.currPosFilled[0][0]=3;
			BOARD.currPosFilled[0][1]=21;
		BOARD.positionsFilledTemp[4][21]=true;
			BOARD.currPosFilled[1][0]=4;
			BOARD.currPosFilled[1][1]=21;
		BOARD.positionsFilledTemp[4][20]=true;
			BOARD.currPosFilled[2][0]=4;
			BOARD.currPosFilled[2][1]=20;
		BOARD.positionsFilledTemp[5][20]=true;
			BOARD.currPosFilled[3][0]=5;
			BOARD.currPosFilled[3][1]=20;
		BOARD.positionsFilledColorTempAndPrev[0]=1;BOARD.positionsFilledColorTempAndPrev[1]=0;BOARD.positionsFilledColorTempAndPrev[2]=0;
	}
	FIND_BOUNDS();
	//set the next block to fall and its color: 
	if(BOARD.nextBlockFalling==0){
		BOARD.positionsFilledNextBlockToFall[6][20]=true;BOARD.positionsFilledNextBlockToFall[5][20]=true;
		BOARD.positionsFilledNextBlockToFall[4][20]=true;BOARD.positionsFilledNextBlockToFall[3][20]=true;
		BOARD.positionsFilledColorNext[0]=0;BOARD.positionsFilledColorNext[1]=1;BOARD.positionsFilledColorNext[2]=1;
	}
	if(BOARD.nextBlockFalling==1){
		BOARD.positionsFilledNextBlockToFall[3][21]=true;BOARD.positionsFilledNextBlockToFall[3][20]=true;
		BOARD.positionsFilledNextBlockToFall[4][20]=true;BOARD.positionsFilledNextBlockToFall[5][20]=true;
		BOARD.positionsFilledColorNext[0]=0;BOARD.positionsFilledColorNext[1]=0;BOARD.positionsFilledColorNext[2]=1;
	}
	if(BOARD.nextBlockFalling==2){
		BOARD.positionsFilledNextBlockToFall[5][21]=true;BOARD.positionsFilledNextBlockToFall[5][20]=true;
		BOARD.positionsFilledNextBlockToFall[4][20]=true;BOARD.positionsFilledNextBlockToFall[3][20]=true;
		BOARD.positionsFilledColorNext[0]=1;BOARD.positionsFilledColorNext[1]=0.64705882352;BOARD.positionsFilledColorNext[2]=0;
	}
	if(BOARD.nextBlockFalling==3){
		BOARD.positionsFilledNextBlockToFall[5][21]=true;BOARD.positionsFilledNextBlockToFall[4][21]=true;
		BOARD.positionsFilledNextBlockToFall[5][20]=true;BOARD.positionsFilledNextBlockToFall[4][20]=true;
		BOARD.positionsFilledColorNext[0]=1;BOARD.positionsFilledColorNext[1]=1;BOARD.positionsFilledColorNext[2]=0;
	}
	if(BOARD.nextBlockFalling==4){
		BOARD.positionsFilledNextBlockToFall[5][21]=true;BOARD.positionsFilledNextBlockToFall[4][21]=true;
		BOARD.positionsFilledNextBlockToFall[4][20]=true;BOARD.positionsFilledNextBlockToFall[3][20]=true;
		BOARD.positionsFilledColorNext[0]=0;BOARD.positionsFilledColorNext[1]=1;BOARD.positionsFilledColorNext[2]=0;
	}
	if(BOARD.nextBlockFalling==5){
		BOARD.positionsFilledNextBlockToFall[4][21]=true;BOARD.positionsFilledNextBlockToFall[3][20]=true;
		BOARD.positionsFilledNextBlockToFall[4][20]=true;BOARD.positionsFilledNextBlockToFall[5][20]=true;
		BOARD.positionsFilledColorNext[0]=0.50196078431;BOARD.positionsFilledColorNext[1]=0;BOARD.positionsFilledColorNext[2]=0.50196078431;
	}
	if(BOARD.nextBlockFalling==6){
		BOARD.positionsFilledNextBlockToFall[3][21]=true;BOARD.positionsFilledNextBlockToFall[4][21]=true;
		BOARD.positionsFilledNextBlockToFall[4][20]=true;BOARD.positionsFilledNextBlockToFall[5][20]=true;
		BOARD.positionsFilledColorNext[0]=1;BOARD.positionsFilledColorNext[1]=0;BOARD.positionsFilledColorNext[2]=0;
	}
}
void breakDownRow(int nRow){
	BOARD.linesClearedThisTime+=1;
	for(int n=0;n<20;n++){//0-19;
		for(int m=0;m<10;m++){//0-9;
			if(n==nRow){
				BOARD.positionsFilledPerm[m][n]=false;
			}
		}
	}
	for(int n=0;n<21;n++){//0-20; check row 20: set blocks above to one column below;
		for(int m=0;m<10;m++){//0-9;
			if(n>nRow){
				if(BOARD.positionsFilledPerm[m][n]==true){
					BOARD.positionsFilledPerm[m][n-1]=true;
					for(int o=0;o<3;o++){
						BOARD.positionsFilledColorPerm[o][m][n-1]=BOARD.positionsFilledColorPerm[o][m][n];
					}
				}
				BOARD.positionsFilledPerm[m][n]=false;
			}
		}
	}
}
void rotateThePiecesVoid(){
	//set variables to false: 
	BOARD.positionsFilledTemp[BOARD.currPosFilled[0][0]][BOARD.currPosFilled[0][1]]=false;
	BOARD.positionsFilledTemp[BOARD.currPosFilled[1][0]][BOARD.currPosFilled[1][1]]=false;
	BOARD.positionsFilledTemp[BOARD.currPosFilled[2][0]][BOARD.currPosFilled[2][1]]=false;
	BOARD.positionsFilledTemp[BOARD.currPosFilled[3][0]][BOARD.currPosFilled[3][1]]=false;
	//set positions of new rotation for blocks: 
	//there are better methods of rotating the blocks, but this is what i came up with: 
	if(BOARD.currentBlockTypeFalling==0){
		if(BOARD.currentBlockTypeCurrentRotation==1){//looks like: 1 on sheet coming from 0;
			BOARD.currPosFilled[0][0]-=1;	BOARD.currPosFilled[0][1]+=1;//0;
			BOARD.currPosFilled[1][0]+=0;	BOARD.currPosFilled[1][1]+=0;//1;
			BOARD.currPosFilled[2][0]+=1;	BOARD.currPosFilled[2][1]-=1;//2;
			BOARD.currPosFilled[3][0]+=2;	BOARD.currPosFilled[3][1]-=2;//3;
		}
		else if(BOARD.currentBlockTypeCurrentRotation==2){//looks like: 2 on sheet coming from 1;
			BOARD.currPosFilled[0][0]-=2;	BOARD.currPosFilled[0][1]-=2;//0;
			BOARD.currPosFilled[1][0]-=1;	BOARD.currPosFilled[1][1]-=1;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]+=1;	BOARD.currPosFilled[3][1]+=1;//3;
		}
		else if(BOARD.currentBlockTypeCurrentRotation==3){//looks like: 3 on sheet coming from 2;
			BOARD.currPosFilled[0][0]+=1;	BOARD.currPosFilled[0][1]+=2;//0;
			BOARD.currPosFilled[1][0]+=0;	BOARD.currPosFilled[1][1]+=1;//1;
			BOARD.currPosFilled[2][0]-=1;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]-=2;	BOARD.currPosFilled[3][1]-=1;//3;
		}
		else{//looks like: 0 on sheet coming from 3;
			BOARD.currPosFilled[0][0]+=2;	BOARD.currPosFilled[0][1]-=1;//0;
			BOARD.currPosFilled[1][0]+=1;	BOARD.currPosFilled[1][1]+=0;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]+=1;//2;
			BOARD.currPosFilled[3][0]-=1;	BOARD.currPosFilled[3][1]+=2;//3;
		}
	}
	else if(BOARD.currentBlockTypeFalling==1){
		if(BOARD.currentBlockTypeCurrentRotation==1){//looks like: 1 on sheet coming from 0;
			BOARD.currPosFilled[0][0]+=2;	BOARD.currPosFilled[0][1]+=0;//0;
			BOARD.currPosFilled[1][0]+=1;	BOARD.currPosFilled[1][1]+=1;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]-=1;	BOARD.currPosFilled[3][1]-=1;//3;
		}
		else if(BOARD.currentBlockTypeCurrentRotation==2){//looks like: 2 on sheet coming from 1;
			BOARD.currPosFilled[0][0]-=2;	BOARD.currPosFilled[0][1]-=1;//0;
			BOARD.currPosFilled[1][0]+=0;	BOARD.currPosFilled[1][1]-=1;//1;
			BOARD.currPosFilled[2][0]+=1;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]+=1;	BOARD.currPosFilled[3][1]+=0;//3;
		}
		else if(BOARD.currentBlockTypeCurrentRotation==3){//looks like: 3 on sheet coming from 2;
			BOARD.currPosFilled[0][0]+=1;	BOARD.currPosFilled[0][1]+=1;//0;
			BOARD.currPosFilled[1][0]+=0;	BOARD.currPosFilled[1][1]+=0;//1;
			BOARD.currPosFilled[2][0]-=1;	BOARD.currPosFilled[2][1]-=1;//2;
			BOARD.currPosFilled[3][0]-=2;	BOARD.currPosFilled[3][1]+=0;//3;
		}
		else{//looks like: 0 on sheet coming from 3;
			BOARD.currPosFilled[0][0]-=1;	BOARD.currPosFilled[0][1]+=0;//0;
			BOARD.currPosFilled[1][0]-=1;	BOARD.currPosFilled[1][1]+=0;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]+=1;//2;
			BOARD.currPosFilled[3][0]+=2;	BOARD.currPosFilled[3][1]+=1;//3;
		}
	}
	else if(BOARD.currentBlockTypeFalling==2){
		if(BOARD.currentBlockTypeCurrentRotation==1){//looks like: 1 on sheet coming from 0;
			BOARD.currPosFilled[0][0]-=1;	BOARD.currPosFilled[0][1]+=0;//0;
			BOARD.currPosFilled[1][0]-=1;	BOARD.currPosFilled[1][1]+=0;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]-=1;//2;
			BOARD.currPosFilled[3][0]+=2;	BOARD.currPosFilled[3][1]-=1;//3;
		}
		else if(BOARD.currentBlockTypeCurrentRotation==2){//looks like: 2 on sheet coming from 1;
			BOARD.currPosFilled[0][0]+=1;	BOARD.currPosFilled[0][1]-=1;//0;
			BOARD.currPosFilled[1][0]+=0;	BOARD.currPosFilled[1][1]+=0;//1;
			BOARD.currPosFilled[2][0]-=1;	BOARD.currPosFilled[2][1]+=1;//2;
			BOARD.currPosFilled[3][0]-=2;	BOARD.currPosFilled[3][1]+=0;//3;
		}
		else if(BOARD.currentBlockTypeCurrentRotation==3){//looks like: 3 on sheet coming from 2;
			BOARD.currPosFilled[0][0]-=2;	BOARD.currPosFilled[0][1]+=1;//0;
			BOARD.currPosFilled[1][0]+=0;	BOARD.currPosFilled[1][1]+=1;//1;
			BOARD.currPosFilled[2][0]+=1;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]+=1;	BOARD.currPosFilled[3][1]+=0;//3;
		}
		else{//looks like: 0 on sheet coming from 3;
			BOARD.currPosFilled[0][0]+=2;	BOARD.currPosFilled[0][1]+=0;//0;
			BOARD.currPosFilled[1][0]+=1;	BOARD.currPosFilled[1][1]-=1;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]-=1;	BOARD.currPosFilled[3][1]+=1;//3;
		}
	}
	else if(BOARD.currentBlockTypeFalling==3){/*do nothing;*/}
	else if(BOARD.currentBlockTypeFalling==4){
		if(BOARD.currentBlockTypeCurrentRotation==1){//looks like: 1 on sheet coming from 0;
			BOARD.currPosFilled[0][0]-=1;	BOARD.currPosFilled[0][1]+=0;//0;
			BOARD.currPosFilled[1][0]+=0;	BOARD.currPosFilled[1][1]-=1;//1;
			BOARD.currPosFilled[2][0]+=1;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]+=2;	BOARD.currPosFilled[3][1]-=1;//3;
		}
		else if(BOARD.currentBlockTypeCurrentRotation==2){//looks like: 2 on sheet coming from 1;
			BOARD.currPosFilled[0][0]+=1;	BOARD.currPosFilled[0][1]-=1;//0;
			BOARD.currPosFilled[1][0]+=0;	BOARD.currPosFilled[1][1]+=0;//1;
			BOARD.currPosFilled[2][0]-=1;	BOARD.currPosFilled[2][1]-=1;//2;
			BOARD.currPosFilled[3][0]-=2;	BOARD.currPosFilled[3][1]+=0;//3;
		}
		else if(BOARD.currentBlockTypeCurrentRotation==3){//looks like: 3 on sheet coming from 2;
			BOARD.currPosFilled[0][0]-=2;	BOARD.currPosFilled[0][1]+=1;//0;
			BOARD.currPosFilled[1][0]-=1;	BOARD.currPosFilled[1][1]+=0;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]+=1;//2;
			BOARD.currPosFilled[3][0]+=1;	BOARD.currPosFilled[3][1]+=0;//3;
		}
		else{//looks like: 0 on sheet coming from 3;
			BOARD.currPosFilled[0][0]+=2;	BOARD.currPosFilled[0][1]+=0;//0;
			BOARD.currPosFilled[1][0]+=1;	BOARD.currPosFilled[1][1]+=1;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]-=1;	BOARD.currPosFilled[3][1]+=1;//3;
		}
	}
	else if(BOARD.currentBlockTypeFalling==5){
		if(BOARD.currentBlockTypeCurrentRotation==1){//looks like: 1 on sheet coming from 0;
			BOARD.currPosFilled[0][0]+=1;	BOARD.currPosFilled[0][1]-=1;//0;
			BOARD.currPosFilled[1][0]+=1;	BOARD.currPosFilled[1][1]+=1;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]-=1;	BOARD.currPosFilled[3][1]-=1;//3;
		}
		else if(BOARD.currentBlockTypeCurrentRotation==2){//looks like: 2 on sheet coming from 1;
			BOARD.currPosFilled[0][0]-=1;	BOARD.currPosFilled[0][1]-=1;//0;
			BOARD.currPosFilled[1][0]-=1;	BOARD.currPosFilled[1][1]-=1;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]+=1;	BOARD.currPosFilled[3][1]+=1;//3;
		}
		else if(BOARD.currentBlockTypeCurrentRotation==3){//looks like: 3 on sheet coming from 2;
			BOARD.currPosFilled[0][0]-=1;	BOARD.currPosFilled[0][1]+=1;//0;
			BOARD.currPosFilled[1][0]+=1;	BOARD.currPosFilled[1][1]+=1;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]-=1;	BOARD.currPosFilled[3][1]-=1;//3;
		}
		else{//looks like: 0 on sheet coming from 3;
			BOARD.currPosFilled[0][0]+=1;	BOARD.currPosFilled[0][1]+=1;//0;
			BOARD.currPosFilled[1][0]-=1;	BOARD.currPosFilled[1][1]-=1;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]+=1;	BOARD.currPosFilled[3][1]+=1;//3;
		}
	}
	else if(BOARD.currentBlockTypeFalling==6){
		if(BOARD.currentBlockTypeCurrentRotation==1){//looks like: 1 on sheet coming from 0;
			BOARD.currPosFilled[0][0]+=2;	BOARD.currPosFilled[0][1]+=0;//0;
			BOARD.currPosFilled[1][0]+=1;	BOARD.currPosFilled[1][1]-=1;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]-=1;	BOARD.currPosFilled[3][1]-=1;//3;
		}
		else if(BOARD.currentBlockTypeCurrentRotation==2){//looks like: 2 on sheet coming from 1;
			BOARD.currPosFilled[0][0]-=2;	BOARD.currPosFilled[0][1]-=1;//0;
			BOARD.currPosFilled[1][0]-=1;	BOARD.currPosFilled[1][1]+=0;//1;
			BOARD.currPosFilled[2][0]+=0;	BOARD.currPosFilled[2][1]-=1;//2;
			BOARD.currPosFilled[3][0]+=1;	BOARD.currPosFilled[3][1]+=0;//3;
		}
		else if(BOARD.currentBlockTypeCurrentRotation==3){//looks like: 3 on sheet coming from 2;
			BOARD.currPosFilled[0][0]+=1;	BOARD.currPosFilled[0][1]+=1;//0;
			BOARD.currPosFilled[1][0]+=0;	BOARD.currPosFilled[1][1]+=0;//1;
			BOARD.currPosFilled[2][0]-=1;	BOARD.currPosFilled[2][1]+=1;//2;
			BOARD.currPosFilled[3][0]-=2;	BOARD.currPosFilled[3][1]+=0;//3;
		}
		else{//looks like: 0 on sheet coming from 3;
			BOARD.currPosFilled[0][0]-=1;	BOARD.currPosFilled[0][1]+=0;//0;
			BOARD.currPosFilled[1][0]+=0;	BOARD.currPosFilled[1][1]+=1;//1;
			BOARD.currPosFilled[2][0]+=1;	BOARD.currPosFilled[2][1]+=0;//2;
			BOARD.currPosFilled[3][0]+=2;	BOARD.currPosFilled[3][1]+=1;//3;
		}
	}
	CHECK_OUT_OF_RANGE();
}
void CHECK_OUT_OF_RANGE(){
	bool outOfRangeX[4]={false,false,false,false};
	bool outOfRangeY[4]={false,false,false,false};
	for(int n=0;n<4;n++){
		if(BOARD.currPosFilled[n][0]<0||BOARD.currPosFilled[n][0]>9){
			outOfRangeX[n]=true;
		}
		if(BOARD.currPosFilled[n][1]<0){
			outOfRangeY[n]=true;
		}
	}
	while(outOfRangeX[0]==true||outOfRangeX[1]==true||outOfRangeX[2]==true||outOfRangeX[3]==true){
		for(int n=0;n<4;n++){
			if(BOARD.currPosFilled[n][0]<0){
				for(int m=0;m<4;m++){
					BOARD.currPosFilled[m][0]+=1;
					if(BOARD.currPosFilled[m][0]>-1)outOfRangeX[m]=false;
				}
			}
			else if(BOARD.currPosFilled[n][0]>9){
				for(int m=0;m<4;m++){
					BOARD.currPosFilled[m][0]-=1;
					if(BOARD.currPosFilled[m][0]<10)outOfRangeX[m]=false;
				}
			}
		}
	}
	while(outOfRangeY[0]==true||outOfRangeY[1]==true||outOfRangeY[2]==true||outOfRangeY[3]==true){
		for(int n=0;n<4;n++){
			if(BOARD.currPosFilled[n][1]<0){
				for(int m=0;m<4;m++){
					BOARD.currPosFilled[m][1]+=1;
					if(BOARD.currPosFilled[m][1]>-1)outOfRangeY[m]=false;
				}
			}
		}
	}
	BOARD.positionsFilledTemp[BOARD.currPosFilled[0][0]][BOARD.currPosFilled[0][1]]=true;//set variables to true: 
	BOARD.positionsFilledTemp[BOARD.currPosFilled[1][0]][BOARD.currPosFilled[1][1]]=true;
	BOARD.positionsFilledTemp[BOARD.currPosFilled[2][0]][BOARD.currPosFilled[2][1]]=true;
	BOARD.positionsFilledTemp[BOARD.currPosFilled[3][0]][BOARD.currPosFilled[3][1]]=true;
	FIND_BOUNDS();
}
void FIND_BOUNDS(){
	BOARD.xPosFilledLeftMost=10;//set mostleft, mostright, mostup, mostdown;
	BOARD.xPosFilledRightMost=0;
	BOARD.yPosFilledUpMost=0;
	BOARD.yPosFilledDownMost=20;
	for(int n=0;n<4;n++){
		if(BOARD.xPosFilledLeftMost>BOARD.currPosFilled[n][0]){
			BOARD.xPosFilledLeftMost=BOARD.currPosFilled[n][0];
		}
		if(BOARD.xPosFilledRightMost<BOARD.currPosFilled[n][0]){
			BOARD.xPosFilledRightMost=BOARD.currPosFilled[n][0];
		}
		if(BOARD.yPosFilledDownMost>BOARD.currPosFilled[n][1]){
			BOARD.yPosFilledDownMost=BOARD.currPosFilled[n][1];
		}
		if(BOARD.yPosFilledUpMost<BOARD.currPosFilled[n][1]){
			BOARD.yPosFilledUpMost=BOARD.currPosFilled[n][1];
		}
	}
}
