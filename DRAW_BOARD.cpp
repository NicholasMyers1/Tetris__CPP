#include "includesVoids.h"
void DRAW_BOARD(){
	if(BOARD.resumeTimer!=-1&&(GetTickCount()-BOARD.resumeTimer)>3000&&BOARD.gamePause==true)		RESUME_FROM_PAUSE();//resume:
	if(BOARD.gamePause==false&&BOARD.gameEnded==false)												DROP_BLOCKS();//fall;
	for(int n=0;n<10;n++){//DRAW EVERYTHING ON THE BOARD: //0-9;
		for(int m=0;m<22/*0*/;m++){//0-19;
			glLoadIdentity();//board: 



//glRotatef(180,0,0,1);


//glRotatef(-45,1,0,0);
//glTranslatef(0,50,0);




			glColor4f(0,1,.05*m,.375);//glColor4f(.25,.5,1,.5);
			glTranslatef(-11,-21,-50);//-15,-100
			glTranslatef((n+1)*2,(m+1)*2,0);
			if(m<20)glCallList(board[1]);
			if(BOARD.gamePause==false&&BOARD.gameEnded==false){
				if(m<21){//20
					if(BOARD.positionsFilledPrev[n][m]==true){//preview: 
						glTranslatef(n-(1*n),m-(1*m),0);
						if(m<20){
							glColor4f(BOARD.positionsFilledColorTempAndPrev[0],BOARD.positionsFilledColorTempAndPrev[1],BOARD.positionsFilledColorTempAndPrev[2],.5);
							glCallList(board[0]);
							glColor4f(0,0,0,1);glCallList(board[2]);
						}
					}
					if(BOARD.positionsFilledTemp[n][m]==true){//temp: 
						glTranslatef(n-(1*n),m-(1*m),0);
						glColor4f(BOARD.positionsFilledColorTempAndPrev[0],BOARD.positionsFilledColorTempAndPrev[1],BOARD.positionsFilledColorTempAndPrev[2],1);
						if(m<20)glCallList(board[1]);
					}
					if(BOARD.positionsFilledPerm[n][m]==true){//perm: 
						if(BOARD.checkGameEnded==true&&m==20){
							BOARD.gameEnded=true;
							BOARD.ShowGameOverScreenTimer=GetTickCount();
						}
						glTranslatef(n-(1*n),m-(1*m),0);
						glColor4f(BOARD.positionsFilledColorPerm[0][n][m],BOARD.positionsFilledColorPerm[1][n][m],BOARD.positionsFilledColorPerm[2][n][m],1);
						if(m<20)glCallList(board[0]);
					}
				}
				if(n>2&&n<7&&m>19){//call netting for next: 
					glLoadIdentity();
					glColor4f(0,0,0,1);
					glTranslatef(-11,-21,-50);//-15,-100
					glTranslatef((n+1)*2,(m+1)*2,0);
					glTranslatef((n-(1*n))+18,(m-(1*m))-6,0);
					glCallList(board[2]);
				}
				if(n>2&&n<7&&m>19){//call netting for holding: 
					glLoadIdentity();
					glColor4f(0,0,0,1);
					glTranslatef(-11,-21,-50);//-15,-100
					glTranslatef((n+1)*2,(m+1)*2,0);
					glTranslatef((n-(1*n))-18,(m-(1*m))-6,0);
					glCallList(board[0]);
				}
				if(BOARD.positionsFilledNextBlockToFall[n][m]==true){//next: 
					glLoadIdentity();
					glColor4f(BOARD.positionsFilledColorNext[0],BOARD.positionsFilledColorNext[1],BOARD.positionsFilledColorNext[2],1);
					glTranslatef(-11,-21,-50);//-15,-100
					glTranslatef((n+1)*2,(m+1)*2,0);
					glTranslatef((n-(1*n))+18,(m-(1*m))-6,0);
					glCallList(board[0]);
				}
				if(BOARD.positionsFilledHolding[n][m]==true){//holding: 
					glLoadIdentity();
					glColor4f(BOARD.positionsFilledColorHold[0],BOARD.positionsFilledColorHold[1],BOARD.positionsFilledColorHold[2],1);
					glTranslatef(-11,-21,-50);//-15,-100
					glTranslatef((n+1)*2,(m+1)*2,0);
					glTranslatef((n-(1*n))-18,(m-(1*m))-6,0);
					glCallList(board[0]);
				}
			}
		}
	}
	if(BOARD.gamePause==false&&BOARD.gameEnded==false){ 											CHECK_FULL_ROW();}//check for full row: 
	COMBO_LOGIC();
	if(BOARD.gamePause==true){																		COUNTDOWN_ON_PAUSE();}//show 3,2,1 but in squares;//draw: COUNTDOWN, 3,2,1: 
	if(BOARD.gameEnded==true){
		if((GetTickCount()-BOARD.ShowGameOverScreenTimer)>=250)numberButtonsDraw[4]=25;
	}
}
