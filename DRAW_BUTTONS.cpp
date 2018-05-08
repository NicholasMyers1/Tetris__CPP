#include "includesVoids.h"
void DRAW_BUTTONS(){
	for(int n=0;n<numberButtonsDraw[WINDOW.currentScreen];n++){
		glLoadIdentity();//load the identity: 
			glTranslatef(BUTTON[WINDOW.currentScreen][n].x,BUTTON[WINDOW.currentScreen][n].y,0);//translate: 
			glScalef(WINDOW.aspect,WINDOW.aspect,1.0f);//scale: 
			glColor3f(1,0,1);//color: 
		//draw buttons: //dynamic buttons, so lengths and widths change when the window resizes: 
			glBegin(GL_LINE_LOOP);//regular button: 
				glVertex2f(BUTTON[WINDOW.currentScreen][n].width,0);
				glVertex2f(BUTTON[WINDOW.currentScreen][n].width,BUTTON[WINDOW.currentScreen][n].height);
				glVertex2f(0,BUTTON[WINDOW.currentScreen][n].height);
				glVertex2f(0,0);
			glEnd(); 
		DRAW_BUTTON_TEXT(n);//draw the button text: 
	}
	UPDATE_BUTTON_TEXT();
}
void UPDATE_BUTTON_TEXT(){
	//set the text for the game screen: 
	stringstream convNumToStr;convNumToStr.str("\0");//num to string: 
	//playing game: 
	BUTTON[4][2].text="\tScore: ";						convNumToStr<<BOARD.gameScore;BUTTON[4][2].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][4].text="\t\tLevel Currently On:\t\t\t";	convNumToStr<<BOARD.levelCurrentlyOn;BUTTON[4][4].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][5].text="\t\tLevel Fall Speed: ";	convNumToStr<<BOARD.currentLineFallSpeed;BUTTON[4][5].text+=convNumToStr.str()+"ms";convNumToStr.str("\0");
	BUTTON[4][6].text="\t\tLines Cleared This Level:";	convNumToStr<<BOARD.linesClearedForThisLevel;BUTTON[4][6].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][8].text= "\t\tOne Line At Once:\t\t\t\t";	convNumToStr<<BOARD.numLinesCleared[0];BUTTON[4][8].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][9].text= "\t\tTwo Lines At Once:\t\t\t ";	convNumToStr<<BOARD.numLinesCleared[1];BUTTON[4][9].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][10].text="\t\tThree Lines At Once:\t\t ";	convNumToStr<<BOARD.numLinesCleared[2];BUTTON[4][10].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][11].text="\t\tFour Lines At Once:\t\t\t";	convNumToStr<<BOARD.numLinesCleared[3];BUTTON[4][11].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][12].text="\t\tLines Cleared Total:\t\t ";	convNumToStr<<BOARD.totalLinesCleared;BUTTON[4][12].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][13].text="\t\tBest Combo:\t\t\t\t\t\t\t";	convNumToStr<<BOARD.longestComboStreak;BUTTON[4][13].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][15].text="\t\tI Block:\t\t ";				convNumToStr<<BOARD.blockDropped[0];BUTTON[4][15].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][16].text="\t\tJ Block:\t\t ";				convNumToStr<<BOARD.blockDropped[1];BUTTON[4][16].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][17].text="\t\tL Block:\t\t ";				convNumToStr<<BOARD.blockDropped[2];BUTTON[4][17].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][18].text="\t\tO Block:\t\t ";				convNumToStr<<BOARD.blockDropped[3];BUTTON[4][18].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][19].text="\t\tS Block:\t\t ";				convNumToStr<<BOARD.blockDropped[4];BUTTON[4][19].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][20].text="\t\tT Block:\t\t ";				convNumToStr<<BOARD.blockDropped[5];BUTTON[4][20].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][21].text="\t\tZ Block:\t\t ";				convNumToStr<<BOARD.blockDropped[6];BUTTON[4][21].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][22].text="\t\tBlocks Held: ";				convNumToStr<<BOARD.blocksHeld;BUTTON[4][22].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[4][23].text="\tTime: "; 
		convNumToStr<<BOARD.gameTimeMinutes;BUTTON[4][23].text+=convNumToStr.str()+":";convNumToStr.str("\0");
		convNumToStr<<BOARD.gameTimeSeconds;BUTTON[4][23].text+=convNumToStr.str()+".";convNumToStr.str("\0");
		convNumToStr<<BOARD.gameTimeMilliseconds;BUTTON[4][23].text+=convNumToStr.str()+";";convNumToStr.str("\0");
	//show score nohighscore: 
	UPDATE_BUTTON_TEXT_SCORING(8);
	BUTTON[8][9].text="You: Score:\t\t\t\t\t\t\t\t\t ";			convNumToStr<<BOARD.gameScore;BUTTON[8][9].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[8][9].text+="\n\t\t Level Reached:\t\t\t\t\t ";		convNumToStr<<BOARD.levelCurrentlyOn;BUTTON[8][9].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[8][9].text+="\n\t\t Lines Cleared This Level:";		convNumToStr<<BOARD.linesClearedForThisLevel;BUTTON[8][9].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[8][9].text+="\n\t\t Time:\t\t\t\t\t\t\t\t\t\t"; 
		convNumToStr<<BOARD.gameTimeMinutes;BUTTON[8][9].text+=convNumToStr.str()+":";convNumToStr.str("\0");
		convNumToStr<<BOARD.gameTimeSeconds;BUTTON[8][9].text+=convNumToStr.str()+".";convNumToStr.str("\0");
		convNumToStr<<BOARD.gameTimeMilliseconds;BUTTON[8][9].text+=convNumToStr.str()+";";convNumToStr.str("\0");
	BUTTON[8][9].text+="\n\t\t Best Combo:\t\t\t\t\t\t\t"; convNumToStr<<BOARD.longestComboStreak;BUTTON[8][9].text+=convNumToStr.str();convNumToStr.str("\0");
	//show score received high score: 
	UPDATE_BUTTON_TEXT_SCORING(3);
	BUTTON[9][4].text="Your Score:\t\t\t\t\t\t\t";		convNumToStr<<BOARD.gameScore;BUTTON[9][4].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[9][5].text="Level Reached:\t\t\t\t\t ";		convNumToStr<<BOARD.levelCurrentlyOn;BUTTON[9][5].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[9][6].text="Lines Cleared This Level:";		convNumToStr<<BOARD.linesClearedForThisLevel;BUTTON[9][6].text+=convNumToStr.str();convNumToStr.str("\0");
	BUTTON[9][7].text="Time:\t\t\t\t\t\t\t\t\t\t"; 
		convNumToStr<<BOARD.gameTimeMinutes;BUTTON[9][7].text+=convNumToStr.str()+":";convNumToStr.str("\0");
		convNumToStr<<BOARD.gameTimeSeconds;BUTTON[9][7].text+=convNumToStr.str()+".";convNumToStr.str("\0");
		convNumToStr<<BOARD.gameTimeMilliseconds;BUTTON[9][7].text+=convNumToStr.str()+";";convNumToStr.str("\0");
	BUTTON[9][8].text="Best Combo:\t\t\t\t\t\t\t";		convNumToStr<<BOARD.longestComboStreak;BUTTON[9][8].text+=convNumToStr.str();convNumToStr.str("\0"); 
}
void UPDATE_BUTTON_TEXT_SCORING(int screenNumber){
	stringstream convNumToStr;convNumToStr.str("\0");//num to string: 
	for(int n=0;n<5;n++){
		BUTTON[screenNumber][n+4].text=(char)(n+49);BUTTON[screenNumber][n+4].text+=":\t Name:\t\t\t\t\t\t\t\t\t\t";//BUTTON[screenNumber][n+4].text="1:\t Name:\t\t\t\t\t\t\t\t\t\t";
			BUTTON[screenNumber][n+4].text+=BOARD.highScoresName[n];
		BUTTON[screenNumber][n+4].text+="\n\t\t Score:\t\t\t\t\t\t\t\t\t ";	convNumToStr<<BOARD.highScoresScore[n];
			BUTTON[screenNumber][n+4].text+=convNumToStr.str();convNumToStr.str("\0");
		BUTTON[screenNumber][n+4].text+="\n\t\t Level Reached:\t\t\t\t\t ";	convNumToStr<<BOARD.highScoresLevel[n];
			BUTTON[screenNumber][n+4].text+=convNumToStr.str();convNumToStr.str("\0");
		BUTTON[screenNumber][n+4].text+="\n\t\t Lines Cleared This Level:";	convNumToStr<<BOARD.highScoresLinesClearedthisLevel[n];
			BUTTON[screenNumber][n+4].text+=convNumToStr.str();convNumToStr.str("\0");
		BUTTON[screenNumber][n+4].text+="\n\t\t Time:\t\t\t\t\t\t\t\t\t\t";	convNumToStr<<BOARD.highScoresTime[n];
			BUTTON[screenNumber][n+4].text+=convNumToStr.str();convNumToStr.str("\0");
		BUTTON[screenNumber][n+4].text+="\n\t\t Best Combo:\t\t\t\t\t\t\t";	convNumToStr<<BOARD.highScoresBestCombo[n];
			BUTTON[screenNumber][n+4].text+=convNumToStr.str();convNumToStr.str("\0");
	}
}
void DRAW_BUTTON_TEXT(int n){
	//set values for text: x,y are location of text: tx and ty are the increments of the text so it does not show in one spot.
	for(int m=0;m<BUTTON[WINDOW.currentScreen][n].text.length();m++){
		if(BUTTON[WINDOW.currentScreen][n].text[0]==' '&&m==0||BUTTON[WINDOW.currentScreen][n].text[0]==' '&&m==0)BUTTON[WINDOW.currentScreen][n].text.erase(m,1);
		if(	BUTTON[WINDOW.currentScreen][n].text[m]==' '&&BUTTON[WINDOW.currentScreen][n].text[m+1]==' '||
			BUTTON[WINDOW.currentScreen][n].text[m]==' '&&BUTTON[WINDOW.currentScreen][n].text[m+1]==' '
		){
			while(BUTTON[WINDOW.currentScreen][n].text[m]==' '||BUTTON[WINDOW.currentScreen][n].text[m]==' ')BUTTON[WINDOW.currentScreen][n].text.erase(m,1);
		}
	}
	int endLineCount[40]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//40 \n's allowed per button?;
	int tabCount=0;
	int countEndLine=0;//determine if the number of lines of text based on \n is odd or even. split text to half a line if odd. 
	for(int m=0;m<BUTTON[WINDOW.currentScreen][n].text.length();m++){
		if(BUTTON[WINDOW.currentScreen][n].text[m]!='\n')endLineCount[countEndLine]+=1;
		else if(BUTTON[WINDOW.currentScreen][n].text[m]=='\n')countEndLine+=1;
		if(BUTTON[WINDOW.currentScreen][n].text[m]=='\t')tabCount+=1;
	}
	double tempX=BUTTON[WINDOW.currentScreen][n].x;
	double tempY=BUTTON[WINDOW.currentScreen][n].y;
	double tempTX=(BUTTON[WINDOW.currentScreen][n].width*.5)-(((endLineCount[0]+tabCount)*.5)*15);
	double tempTY=-(BUTTON[WINDOW.currentScreen][n].height*.5)+(((countEndLine-1)*.5)*(18));
	countEndLine=0;
	//special conditions for the text on specific buttons on specific screens: 
	if(WINDOW.currentScreen==1||WINDOW.currentScreen==6){	if(n==1)tempTX=0;}
	else if(WINDOW.currentScreen==3){						if(n==4||n==5||n==6||n==7||n==8)tempTX=0;}
	else if(WINDOW.currentScreen==4){						if(n>=2&&n<24)tempTX=-15;}
	else if(WINDOW.currentScreen==8){						if(n==4||n==5||n==6||n==7||n==8||n==9)tempTX=0;}
	else if(WINDOW.currentScreen==9){						if(n==4||n==5||n==6||n==7||n==8)tempTX=0;}
	int colorTextSpecificLineInButton=0;
	bool hadColonYet=false;
	int lineLength=0;
	for(int m=0;m<BUTTON[WINDOW.currentScreen][n].text.length();m++){
		if(m>0&&BUTTON[WINDOW.currentScreen][n].text[m-1]==':')hadColonYet=true;
		//load the identity: 
		glLoadIdentity();
		//special conditions: 
		lineLength+=1;
		if(BUTTON[WINDOW.currentScreen][n].text[m]=='\n'){
			lineLength=0;
			hadColonYet=false;
			countEndLine+=1;
			if(WINDOW.currentScreen==1||WINDOW.currentScreen==6){	if(n==1)tempTX=-15;}
			else if(WINDOW.currentScreen==3){						if(n==4||n==5||n==6||n==7||n==8)tempTX=-15;}
			else if(WINDOW.currentScreen==8){						if(n==4||n==5||n==6||n==7||n==8||n==9)tempTX=-15;}
			else{ 													tempTX=(BUTTON[WINDOW.currentScreen][n].width*.5)-((endLineCount[countEndLine]*.5)*15)-15;}//0;
			tempTY-=18;
			colorTextSpecificLineInButton+=1;
		}
		if(BUTTON[WINDOW.currentScreen][n].text[m]=='\t')tempTX+=15;
		glTranslatef(tempX,tempY,0);//initial translation: 
		glRotatef(180,1,0,0);//rotate for the text: 
		glTranslatef(tempTX*WINDOW.aspect,tempTY*WINDOW.aspect,0);//translate each text character: 
		glScalef(0.15*WINDOW.aspect,0.15*WINDOW.aspect,1);//scale for the text: 
		tempTX+=15;//increment value: 
		//color: 
		if(WINDOW.currentScreen==0){											glColor3f(.7,.9,.7);}//main screen;
		else if(WINDOW.currentScreen==1){//rules screen; 
			if(n==1){
				if(	colorTextSpecificLineInButton==0||colorTextSpecificLineInButton==7||colorTextSpecificLineInButton==12||
					colorTextSpecificLineInButton==19||colorTextSpecificLineInButton==30
				){																glColor3f(1,0,0);}//main point: 
				else if(m>=2&&BUTTON[WINDOW.currentScreen][n].text[m-2]=='\n'&&
						BUTTON[WINDOW.currentScreen][n].text[m-1]=='\t'&&
						BUTTON[WINDOW.currentScreen][n].text[m]=='*'
				){																glColor3f(1,1,0);}//point *
				else if(m==0&&BUTTON[WINDOW.currentScreen][n].text[m]=='*'){	glColor3f(1,1,0);}//point *
				else{ 															glColor3f(.7,.9,.7);}//regular text: 
			}
			else if(n==4){														glColor3f(.25,.75,.25);}//title: 
			else{ 																glColor3f(.7,.9,.7);}//regular text: 
		}
		else if(WINDOW.currentScreen==2){//controls screen: 
			if(n==3||n==5||n==7||n==9||n==11||n==13||n==15||n==17||n==19){		glColor3f(1,0,0);}//main point:
			else if(n==21){														glColor3f(.25,.75,.25);}//title: 
			else{ 																glColor3f(.7,.9,.7);}
		}
		else if(WINDOW.currentScreen==3){//high score table screen: 
			if(n==4||n==5||n==6||n==7||n==8){									glColor3f(1,0,0);//main point:
				if(hadColonYet==true){											glColor3f(.7,.9,.7);}
				if(countEndLine>0){												glColor3f(.7,.9,.7);}//override;
			}
			else if(n==3){														glColor3f(.25,.75,.25);}//title: 
			else{ 																glColor3f(.7,.9,.7);}
		}
		else if(WINDOW.currentScreen==4){//ingame screen: 
			if(n==3||n==7||n==14){if(colorTextSpecificLineInButton==0)			glColor3f(1,0,0);}//main point:
			else if(n==1){														glColor3f(.25,.75,.25);}//title: 
			else{ 																glColor3f(.7,.9,.7);}
		}
		else if(WINDOW.currentScreen==5){										glColor3f(.7,.9,.7);}//pause screen:
		else if(WINDOW.currentScreen==6){//pause rules screen; 
			if(n==1){
				if(	colorTextSpecificLineInButton==0||colorTextSpecificLineInButton==7||colorTextSpecificLineInButton==12||
					colorTextSpecificLineInButton==19||colorTextSpecificLineInButton==30
				){																glColor3f(1,0,0);}//main point: 
				else if(m>=2&&BUTTON[WINDOW.currentScreen][n].text[m-2]=='\n'&&
						BUTTON[WINDOW.currentScreen][n].text[m-1]=='\t'&&
						BUTTON[WINDOW.currentScreen][n].text[m]=='*'
				){																glColor3f(1,1,0);}//point *
				else if(m==0&&BUTTON[WINDOW.currentScreen][n].text[m]=='*'){	glColor3f(1,1,0);}//point *
				else{ 															glColor3f(.7,.9,.7);}//regular text: 
			}
			else if(n==4){														glColor3f(.25,.75,.25);}//title: 
			else{																glColor3f(.7,.9,.7);}//regular text: 
		}
		else if(WINDOW.currentScreen==7){//pause controls screen: 
			if(n==3||n==5||n==7||n==9||n==11||n==13||n==15||n==17||n==19){		glColor3f(1,0,0);}//main point:
			else if(n==21){														glColor3f(.25,.75,.25);}//title: 
			else{																glColor3f(.7,.9,.7);}
		}
		else if(WINDOW.currentScreen==8){//high score table screen: 
			if(n==4||n==5||n==6||n==7||n==8||n==9){								glColor3f(1,0,0);//main point:
				if(hadColonYet==true){											glColor3f(.7,.9,.7);}
				if(countEndLine>0){												glColor3f(.7,.9,.7);}//override;
			}
			else if(n==3){														glColor3f(.25,.75,.25);}//title: 
			else{																glColor3f(.7,.9,.7);}
		}
		else if(WINDOW.currentScreen==9){//enter high score: 
			if(n==2||n==4||n==5||n==6||n==7||n==8){								glColor3f(1,0,0);//main point:
				if(hadColonYet==true||n==2&&countEndLine==2){					glColor3f(.7,.9,.7);}//had : yet?
			}
			else if(n==1){														glColor3f(.25,.75,.25);}//title: 
			else{																glColor3f(.7,.9,.7);}
			if(n==3&&BOARD.nameEnterHighScore.length()==0){						glColor3f(1,0,0);}
			else if(n==3&&BOARD.nameEnterHighScore.length()>0){					glColor3f(0,1,0);}
		}
			if(n==0){															glColor4f(1,0.06274509803*m,0,1);}
		//draw text: 
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,BUTTON[WINDOW.currentScreen][n].text[m]);
		//draw pointer:
		if(WINDOW.currentScreen==9){//draw the pointer: 
			if(n==2&&countEndLine==2&&lineLength==TEXTINPUT.pointerPosition){
				if((GetTickCount()-TEXTINPUT.blinkertimer)>TEXTINPUT.pointerBlinkingRate){//color alpha: 
					if(TEXTINPUT.pointerBlinkAlphaOn==false)	TEXTINPUT.pointerBlinkAlphaOn=true;
					else if(TEXTINPUT.pointerBlinkAlphaOn==true)TEXTINPUT.pointerBlinkAlphaOn=false;
					TEXTINPUT.blinkertimer=GetTickCount();
				}
				glLoadIdentity();
				glColor4f(1,1,1,(int)TEXTINPUT.pointerBlinkAlphaOn);
				glTranslatef(tempX,tempY,0);
				glRotatef(180,1,0,0);
				double trText=7.5+(TEXTINPUT.pointerPosition*15);
				glTranslatef((tempTX*WINDOW.aspect)-(7.5*WINDOW.aspect),tempTY*WINDOW.aspect,0);
				glScalef(0.15*WINDOW.aspect,0.15*WINDOW.aspect,1);
				glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,TEXTINPUT.pointer[0]);
			}
		}
	}
}
