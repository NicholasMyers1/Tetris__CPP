#include "includesVoids.h"
void SPECIAL_TEXT_INPUT(int key){
	if(WINDOW.currentScreen==9){//left and right: 
		if(key==GLUT_KEY_LEFT){
			if(TEXTINPUT.pointerPosition>0){
				TEXTINPUT.pointerPosition-=1;
			}
		}
		if(key==GLUT_KEY_RIGHT){
			if(TEXTINPUT.pointerPosition<BOARD.nameEnterHighScore.length()){
				TEXTINPUT.pointerPosition+=1;
			}
		}
	}
}
void REGULAR_TEXT_INPUT(int key){
	bool spaceNotAllowed=false;
	if(key==' '){
		if(	TEXTINPUT.pointerPosition==0||
			TEXTINPUT.pointerPosition==BOARD.nameEnterHighScore.length()&&BOARD.nameEnterHighScore[BOARD.nameEnterHighScore.length()-1]==' '||
			TEXTINPUT.pointerPosition==39||
			TEXTINPUT.pointerPosition==BOARD.nameEnterHighScore.length()-1&&BOARD.nameEnterHighScore[BOARD.nameEnterHighScore.length()-1]==' '||
			BOARD.nameEnterHighScore[TEXTINPUT.pointerPosition]==' '||BOARD.nameEnterHighScore[TEXTINPUT.pointerPosition-1]==' '
		){
			spaceNotAllowed=true;
		}
	}
	if(BOARD.nameEnterHighScore.length()<15){//text input: 
		if(	key==' '&&spaceNotAllowed==false||key!=' '&&spaceNotAllowed==false){
			if(key>(int)31&&key<(int)127){//input regular ascii text: 
				string input="\0";input=key;
				BOARD.nameEnterHighScore.insert(TEXTINPUT.pointerPosition,input);//+=key;
				BUTTON[9][2].text="Enter Name:\n\n"+BOARD.nameEnterHighScore;
				TEXTINPUT.pointerPosition+=1;
			}
		}
	}
	if(key==8){//erase backspace
		if(TEXTINPUT.pointerPosition>0){
			if(BOARD.nameEnterHighScore[TEXTINPUT.pointerPosition]==' '&&BOARD.nameEnterHighScore[TEXTINPUT.pointerPosition-2]==' '){
				BOARD.nameEnterHighScore.erase(TEXTINPUT.pointerPosition-2,2);
				TEXTINPUT.pointerPosition-=2;
			}
			else if(BOARD.nameEnterHighScore[TEXTINPUT.pointerPosition]==' '&&TEXTINPUT.pointerPosition==1){
				BOARD.nameEnterHighScore.erase(TEXTINPUT.pointerPosition-1,1);
				TEXTINPUT.pointerPosition-=1;
				BOARD.nameEnterHighScore.erase(TEXTINPUT.pointerPosition,1);
			}
			else{
				BOARD.nameEnterHighScore.erase(TEXTINPUT.pointerPosition-1,1);
				TEXTINPUT.pointerPosition-=1;
			}
			BUTTON[9][2].text="Enter Name:\n\n"+BOARD.nameEnterHighScore;
		}
	}
	else if(key==(int)127){//erase delete key
		if(TEXTINPUT.pointerPosition<BOARD.nameEnterHighScore.length()){
			if(	BOARD.nameEnterHighScore[TEXTINPUT.pointerPosition-1]==' '&&
				BOARD.nameEnterHighScore[TEXTINPUT.pointerPosition]!=' '&&
				BOARD.nameEnterHighScore[TEXTINPUT.pointerPosition+1]==' '){
				BOARD.nameEnterHighScore.erase(TEXTINPUT.pointerPosition,2);
			}
			else{
				BOARD.nameEnterHighScore.erase(TEXTINPUT.pointerPosition,1);
			}
			BUTTON[9][2].text="Enter Name:\n\n"+BOARD.nameEnterHighScore;
		}
	}
}
void KEY_UP_ROTATE(int key){
	WINDOW.allowRotation=false;
	if(BOARD.rotation==true){
		BOARD.currentBlockTypeCurrentRotation+=1;
		if(BOARD.currentBlockTypeCurrentRotation>3){
			BOARD.currentBlockTypeCurrentRotation=0;
		}
		//get the previos positions incase the rotation is not allowed: 
		for(int n=0;n<4;n++){
			BOARD.newPossiblePosition[n][0]=BOARD.currPosFilled[n][0];
			BOARD.newPossiblePosition[n][1]=BOARD.currPosFilled[n][1];
		}
		//goto rotation void;
		rotateThePiecesVoid();
	}
	else if(BOARD.rotation==false){
		for(int n=0;n<3;n++){
			BOARD.currentBlockTypeCurrentRotation+=1;
			if(BOARD.currentBlockTypeCurrentRotation>3){
				BOARD.currentBlockTypeCurrentRotation=0;
			}
			//get the previos positions incase the rotation is not allowed: 
			for(int n=0;n<4;n++){
				BOARD.newPossiblePosition[n][0]=BOARD.currPosFilled[n][0];
				BOARD.newPossiblePosition[n][1]=BOARD.currPosFilled[n][1];
			}
			//goto rotation void;
			rotateThePiecesVoid();
		}
	}
	short int translateType=-1;
	//find out if the block is colliding with any permanantly placed objects: 		
	for(int n=0;n<4;n++){
		if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
			BOARD.moveFour[n]=true;
		}
		else{
			BOARD.moveFour[n]=false;
		}
	}
	//find out what block in the new rotated piece is touching what wall or perm block: 
	if(BOARD.moveFour[0]==true||BOARD.moveFour[1]==true||BOARD.moveFour[2]==true||BOARD.moveFour[3]==true){
		for(int n=0;n<4;n++){
			if(translateType==-1){
				if(BOARD.xPosFilledLeftMost==0&&BOARD.positionsFilledPerm[BOARD.xPosFilledRightMost][BOARD.currPosFilled[n][1]]==true){
					translateType=0;//touching left wall: 
				}
				else if(BOARD.xPosFilledRightMost==9&&BOARD.positionsFilledPerm[BOARD.xPosFilledLeftMost][BOARD.currPosFilled[n][1]]==true){
					translateType=1;
				}
			}
			if(n==3&&translateType==-1){//touching right wall: 
				translateType=2;
			}
		}
	}
	//do the rotations: by default: -1 means it is an allowed rotation. there are no collisions;
	if(translateType==0){//touching left wall and perm block: move up, right, down, down, left, up reset. 
		for(int n=0;n<4;n++){//move up: 
			BOARD.positionsFilledTemp[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]=false;
			BOARD.currPosFilled[n][1]+=1;
			if(n==3){
				for(int m=0;m<4;m++)BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=true;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move right: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][0]+=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move down: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][1]-=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move down (again): 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][1]-=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move left: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][0]-=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move up and reset: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][0]=BOARD.newPossiblePosition[m][0];
					BOARD.currPosFilled[m][1]=BOARD.newPossiblePosition[m][1];//+=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
						BOARD.currentBlockTypeCurrentRotation-=1;
						if(BOARD.currentBlockTypeCurrentRotation<0){
							BOARD.currentBlockTypeCurrentRotation=3;
						}
					}
				}
				break;
			}
		}
	}
	else if(translateType==1){//touching right wall and perm block: move up, left, down, down, right, up reset. 
		for(int n=0;n<4;n++){//move up: 
			BOARD.positionsFilledTemp[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]=false;
			BOARD.currPosFilled[n][1]+=1;
			if(n==3){
				for(int m=0;m<4;m++)BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=true;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move left: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][0]-=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move down: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][1]-=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move down (again): 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][1]-=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move right: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][0]+=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move up and reset: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][0]=BOARD.newPossiblePosition[m][0];
					BOARD.currPosFilled[m][1]=BOARD.newPossiblePosition[m][1];//+=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
						BOARD.currentBlockTypeCurrentRotation-=1;
						if(BOARD.currentBlockTypeCurrentRotation<0){
							BOARD.currentBlockTypeCurrentRotation=3;
						}
					}
				}
				break;
			}
		}
	}
	else if(translateType==2){//any block touching perm piece: move up, right, down, down, left, left, up, up, center reset. 
		for(int n=0;n<4;n++){//move up: 
			BOARD.positionsFilledTemp[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]=false;
			BOARD.currPosFilled[n][1]+=1;
			if(n==3){
				for(int m=0;m<4;m++)BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=true;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move right: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][0]+=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move down: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][1]-=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move down (again): 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][1]-=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move left: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][0]-=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move left (again): 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][0]-=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move up: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][1]+=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//move up (again): 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][1]+=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
					}
				}
				break;
			}
		}
		for(int n=0;n<4;n++){//check for any collisions: 
			if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]==true){
				for(int m=0;m<4;m++){//reset: 
					BOARD.positionsFilledTemp[BOARD.currPosFilled[m][0]][BOARD.currPosFilled[m][1]]=false;
					BOARD.currPosFilled[m][0]=BOARD.newPossiblePosition[m][0];
					BOARD.currPosFilled[m][1]=BOARD.newPossiblePosition[m][1];//+=1;
					if(m==3){
						for(int o=0;o<4;o++)BOARD.positionsFilledTemp[BOARD.currPosFilled[o][0]][BOARD.currPosFilled[o][1]]=true;
						BOARD.currentBlockTypeCurrentRotation-=1;
						if(BOARD.currentBlockTypeCurrentRotation<0){
							BOARD.currentBlockTypeCurrentRotation=3;
						}
					}
				}
				break;
			}
		}
	}
	FIND_BOUNDS();
	//reset the values: 
	BOARD.newPossiblePosition[0][0]=-1;BOARD.newPossiblePosition[1][0]=-1;
	BOARD.newPossiblePosition[2][0]=-1;BOARD.newPossiblePosition[3][0]=-1;
	BOARD.newPossiblePosition[0][1]=-1;BOARD.newPossiblePosition[1][1]=-1;
	BOARD.newPossiblePosition[2][1]=-1;BOARD.newPossiblePosition[3][1]=-1;
	BOARD.moveFour[0]=false;BOARD.moveFour[1]=false;
	BOARD.moveFour[2]=false;BOARD.moveFour[3]=false;
}
void ROTATE(){
	if(BOARD.started==true&&BOARD.held==false){
		BOARD.blocksHeld+=1;
		BOARD.held=true;
		//set block type for holding: 
		short int tempFallToHold=-1;
		if(BOARD.currentBlockTypeHolding==-1){
			//set the color of the hold:
			for(int n=0;n<3;n++){
				BOARD.positionsFilledColorHold[n]=BOARD.positionsFilledColorTempAndPrev[n];
			}
			BOARD.currentBlockTypeHolding=BOARD.currentBlockTypeFalling;
			orientationOfCurrentBlockTypeFalling();//color auto set for temp and prew in this void;
		}
		else{
			//set the color of the temp and prev:
			float getColorTemp[3]={0,0,0};
			for(int n=0;n<3;n++){
				getColorTemp[n]=BOARD.positionsFilledColorHold[n];
				BOARD.positionsFilledColorHold[n]=BOARD.positionsFilledColorTempAndPrev[n];
				BOARD.positionsFilledColorTempAndPrev[n]=getColorTemp[n];
			}
			tempFallToHold=BOARD.currentBlockTypeFalling;
			BOARD.currentBlockTypeFalling=BOARD.currentBlockTypeHolding;
			BOARD.currentBlockTypeHolding=tempFallToHold;
			BOARD.prevBlock=BOARD.currentBlockTypeFalling;
			//reset tempBlocks: 
			for(int n=0;n<10;n++){
				for(int m=0;m<24;m++){
					BOARD.positionsFilledTemp[n][m]=false;//falling to ground layer;
					BOARD.positionsFilledPrev[n][m]=false;
				}
			}
			BOARD.currentBlockTypeCurrentRotation=0;
			BOARD.permPlaceWithSpaceKey=false;
			BOARD.falling=true;
			//set the block: 
			if(BOARD.currentBlockTypeFalling==0){
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
			}
		}
		//reset the tempHoldingBlocks: 
		for(int n=0;n<10;n++){
			for(int m=0;m<24;m++){
				BOARD.positionsFilledHolding[n][m]=false;
			}
		}
		//set block type holding positions and boolean pieces to true: 
		if(BOARD.currentBlockTypeHolding==0){
			BOARD.positionsFilledHolding[6][20]=true;BOARD.positionsFilledHolding[5][20]=true;
			BOARD.positionsFilledHolding[4][20]=true;BOARD.positionsFilledHolding[3][20]=true;
		}
		if(BOARD.currentBlockTypeHolding==1){
			BOARD.positionsFilledHolding[3][21]=true;BOARD.positionsFilledHolding[3][20]=true;
			BOARD.positionsFilledHolding[4][20]=true;BOARD.positionsFilledHolding[5][20]=true;
		}
		if(BOARD.currentBlockTypeHolding==2){
			BOARD.positionsFilledHolding[5][21]=true;BOARD.positionsFilledHolding[5][20]=true;
			BOARD.positionsFilledHolding[4][20]=true;BOARD.positionsFilledHolding[3][20]=true;
		}
		if(BOARD.currentBlockTypeHolding==3){
			BOARD.positionsFilledHolding[5][21]=true;BOARD.positionsFilledHolding[4][21]=true;
			BOARD.positionsFilledHolding[5][20]=true;BOARD.positionsFilledHolding[4][20]=true;
		}
		if(BOARD.currentBlockTypeHolding==4){
			BOARD.positionsFilledHolding[5][21]=true;BOARD.positionsFilledHolding[4][21]=true;
			BOARD.positionsFilledHolding[4][20]=true;BOARD.positionsFilledHolding[3][20]=true;
		}
		if(BOARD.currentBlockTypeHolding==5){
			BOARD.positionsFilledHolding[4][21]=true;BOARD.positionsFilledHolding[3][20]=true;
			BOARD.positionsFilledHolding[4][20]=true;BOARD.positionsFilledHolding[5][20]=true;
		}
		if(BOARD.currentBlockTypeHolding==6){
			BOARD.positionsFilledHolding[3][21]=true;BOARD.positionsFilledHolding[4][21]=true;
			BOARD.positionsFilledHolding[4][20]=true;BOARD.positionsFilledHolding[5][20]=true;
		}
		FIND_BOUNDS();
		BOARD.fallingTimer=GetTickCount();
	}
}
void SOFT_DROP(){
	for(int n=0;n<4;n++){
		if(BOARD.yPosFilledDownMost>0&&BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]-1]==false){
			BOARD.moveFour[n]=true;
		}
	}
	if(BOARD.moveFour[0]==true&&BOARD.moveFour[1]==true&&BOARD.moveFour[2]==true&&BOARD.moveFour[3]==true){//set the positions;
		for(int n=0;n<4;n++){
			BOARD.positionsFilledTemp[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]=false;
			BOARD.currPosFilled[n][1]-=1;
			BOARD.newPossiblePosition[n][1]=BOARD.currPosFilled[n][1];
		}
		for(int n=0;n<4;n++){
			BOARD.positionsFilledTemp[BOARD.currPosFilled[n][0]][BOARD.newPossiblePosition[n][1]]=true;
			if(n==3){
				BOARD.yPosFilledUpMost-=1;BOARD.yPosFilledDownMost-=1;
			}
			if(BOARD.currPosFilled[n][1]==0||BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]-1]==true){
				BOARD.falling=false;
			}
		}
		BOARD.gameScore+=1;
	}
	else{
		for(int n=0;n<4;n++){
			if(BOARD.moveFour[n]==false){
				BOARD.falling=false;
			}
		}
	}
	BOARD.rotateFallTimer=GetTickCount();
}
void HARD_DROP(){
	short unsigned int spacesFallen=0;
	bool allowHardDrop=true;
	for(int n=0;n<4;n++){
		if(BOARD.yPosFilledDownMost>0&&BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]-1]==false){
			BOARD.moveFour[n]=true;
		}
		if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]-1]==true){
			allowHardDrop=false;
			BOARD.permPlaceWithSpaceKey=false;
		}
	}
	if(BOARD.moveFour[0]==true&&BOARD.moveFour[1]==true&&BOARD.moveFour[2]==true&&BOARD.moveFour[3]==true&&allowHardDrop==true){//set the positions;
		while(BOARD.falling==true){
			spacesFallen+=1;
			for(int n=0;n<4;n++){
				BOARD.positionsFilledTemp[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]=false;
				BOARD.currPosFilled[n][1]-=1;
				BOARD.newPossiblePosition[n][1]=BOARD.currPosFilled[n][1];
			}
			for(int n=0;n<4;n++){
				BOARD.positionsFilledTemp[BOARD.currPosFilled[n][0]][BOARD.newPossiblePosition[n][1]]=true;
				if(n==3){
					BOARD.yPosFilledUpMost-=1;BOARD.yPosFilledDownMost-=1;
				}
				if(BOARD.currPosFilled[n][1]==0||BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]-1]==true){
					BOARD.falling=false;
					BOARD.rotateFallTimer=GetTickCount()+100;
				}
			}
		}
	}
	BOARD.gameScore+=(spacesFallen*2);
}
void MOVE_LEFT_RIGHT(int key){
	if(	key==GLUT_KEY_LEFT||
		WINDOW.keysCurrentlyPressedSpecial[GLUT_KEY_LEFT]==true&&key==GLUT_KEY_UP||
		WINDOW.keysCurrentlyPressedSpecial[GLUT_KEY_LEFT]==true&&key==GLUT_KEY_DOWN
	){
		for(int n=0;n<4;n++){
			if(BOARD.xPosFilledLeftMost>0&&BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]-1][BOARD.currPosFilled[n][1]]==false){
				BOARD.moveFour[n]=true;
			}
		}
		if(BOARD.moveFour[0]==true&&BOARD.moveFour[1]==true&&BOARD.moveFour[2]==true&&BOARD.moveFour[3]==true){//set the positions;
			for(int n=0;n<4;n++){
				BOARD.positionsFilledTemp[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]=false;
				BOARD.currPosFilled[n][0]-=1;
				BOARD.newPossiblePosition[n][0]=BOARD.currPosFilled[n][0];
			}
			for(int n=0;n<4;n++){
				BOARD.positionsFilledTemp[BOARD.newPossiblePosition[n][0]][BOARD.currPosFilled[n][1]]=true;
				if(n==3){
					BOARD.xPosFilledRightMost-=1;BOARD.xPosFilledLeftMost-=1;
				}
			}
		}
	}
	if(	key==GLUT_KEY_RIGHT||
		WINDOW.keysCurrentlyPressedSpecial[GLUT_KEY_RIGHT]==true&&key==GLUT_KEY_UP||
		WINDOW.keysCurrentlyPressedSpecial[GLUT_KEY_RIGHT]==true&&key==GLUT_KEY_DOWN
	){
		for(int n=0;n<4;n++){
			if(BOARD.xPosFilledRightMost<9&&BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]+1][BOARD.currPosFilled[n][1]]==false){
				BOARD.moveFour[n]=true;
			}
		}
		if(BOARD.moveFour[0]==true&&BOARD.moveFour[1]==true&&BOARD.moveFour[2]==true&&BOARD.moveFour[3]==true){//set the positions;
			for(int n=0;n<4;n++){
				BOARD.positionsFilledTemp[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]]=false;
				BOARD.currPosFilled[n][0]+=1;
				BOARD.newPossiblePosition[0][n]=BOARD.currPosFilled[n][0];
			}
			for(int n=0;n<4;n++){
				BOARD.positionsFilledTemp[BOARD.newPossiblePosition[0][n]][BOARD.currPosFilled[n][1]]=true;
				if(n==3){
					BOARD.xPosFilledRightMost+=1;BOARD.xPosFilledLeftMost+=1;
				}
			}
		}
	}
}
void CHECK_MAKE_FALLING_OR_NOT(int key){
	if(BOARD.permPlaceWithSpaceKey==false){
		if(key==GLUT_KEY_LEFT||key==GLUT_KEY_RIGHT||key==GLUT_KEY_UP||key==GLUT_KEY_DOWN){
			//reset values: 
			BOARD.moveFour[0]=false;BOARD.moveFour[1]=false;
			BOARD.moveFour[2]=false;BOARD.moveFour[3]=false;
			//make falling true if the conditions persist: 
			for(int n=0;n<4;n++){
				if(BOARD.positionsFilledPerm[BOARD.currPosFilled[n][0]][BOARD.currPosFilled[n][1]-1]==false&&BOARD.currPosFilled[n][1]>0){
					BOARD.moveFour[n]=true;
				}
			}
			if(BOARD.moveFour[0]==true&&BOARD.moveFour[1]==true&&BOARD.moveFour[2]==true&&BOARD.moveFour[3]==true&&BOARD.falling==false){
				BOARD.falling=true;
				BOARD.fallingTimer=GetTickCount();
			}
			for(int n=0;n<4;n++){
				if(BOARD.falling==false||BOARD.moveCount==0||BOARD.moveFour[n]==false){
					BOARD.moveCount+=1;
					break;
				}
			}
			BOARD.rotateFallTimer=GetTickCount();
		}
	}
}
