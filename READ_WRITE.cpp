#include "includesVoids.h"
void CHECK_FILE_CREATE_IF_NONEXISTENT(string file){
	WINDOW.readFile_.open(file);
	string lineData="\0";
	getline(WINDOW.readFile_,lineData);
		if(!WINDOW.readFile_||lineData=="\0"||lineData=="\0"){
			WINDOW.readFile_.close();
			WRITE_FILE(file);
			if(file=="_HighScores.txt")WINDOW.filesReadInitiallyScoreData=true;
		}
		else{//check if file is modified: make separate void?
			WINDOW.readFile_.close();
			READ_FILE(file);
			/*if(1){//check if file was modified: 
				cout<<"File is modified!";
			}
			else{
				cout<<"File is not modified!";
			}*/
			//WINDOW.readFile_.close();
		}
}
void WRITE_FILE(string file){
	WINDOW.writeFile_.open(file);//renew file: 
	WINDOW.writeFile_.close();
	WINDOW.writeFile_.open(file);//write to renewed file: 
		if(file=="_HighScores.txt"){
			for(int n=0;n<5;n++){
				WINDOW.writeFile_<<"NAME: "<<BOARD.highScoresName[n]<<";";
				WINDOW.writeFile_<<"SCORE: "<<BOARD.highScoresScore[n]<<";";
				WINDOW.writeFile_<<"LEVEL REACHED: "<<BOARD.highScoresLevel[n]<<";";
				WINDOW.writeFile_<<"LINES CLEARED THIS LEVEL: "<<BOARD.highScoresLinesClearedthisLevel[n]<<";";
				WINDOW.writeFile_<<"TIME: "<<BOARD.highScoresTime[n]<<";";
				WINDOW.writeFile_<<"BEST COMBO: "<<BOARD.highScoresBestCombo[n]<<";";
				WINDOW.writeFile_<<"\n";
			}
		}
	WINDOW.writeFile_.close();
}
void READ_FILE(string file){
	WINDOW.readFile_.open(file);
	string lineData="\0";
	WINDOW.fileLineNumber=0;
	while(!WINDOW.readFile_.eof()){
		getline(WINDOW.readFile_,lineData);
		if(file=="_HighScores.txt"&&WINDOW.fileLineNumber<5)	GET_SET_HIGH_SCORE(WINDOW.fileLineNumber,file,lineData);
		//if(file=="_Controls.txt"&&WINDOW.fileLineNumber<9)		GET_SET_CONTROLS(WINDOW.fileLineNumber,file,lineData);
		WINDOW.fileLineNumber+=1;
	}
	WINDOW.readFile_.close();
}
void GET_SET_HIGH_SCORE(int n,string file,string lineData){//n here is the position of the array;
	stringstream convNumToStr;convNumToStr.str("\0");//num to string: 
	if(WINDOW.filesReadInitiallyScoreData==false){//set score data from file: 
		int countSemiColon=0;//separates data parts in the file line;
		BOARD.highScoresName[n]="\0";//reset the highscore name;
		string getCurrentLineData="\0";//the data of the current line;
		bool getData=false;//once a section of the data based on ':' and ';' is reached, stop retrieving data and set that data to the variables;
		for(int m=0;m<lineData.length();m++){//check after the ':' and set the data in the line to that; reset after every ;
			if(lineData[m-1]==':'&&lineData[m]==' '){	getData=true;}
			else if(getData==true&&lineData[m]!=';'){	string temp;temp=lineData[m];getCurrentLineData.insert(getCurrentLineData.length(),temp);}
			else if(lineData[m]==';'){
				switch(countSemiColon){
					case 0: 							BOARD.highScoresName[n]=getCurrentLineData;break;
					case 1: 							istringstream(getCurrentLineData)>>BOARD.highScoresScore[n];break;
					case 2: 							istringstream(getCurrentLineData)>>BOARD.highScoresLevel[n];break;
					case 3: 							istringstream(getCurrentLineData)>>BOARD.highScoresLinesClearedthisLevel[n];break;
					case 4: 							istringstream(getCurrentLineData)>>BOARD.highScoresTime[n];break;
					case 5: 							istringstream(getCurrentLineData)>>BOARD.highScoresBestCombo[n];break;
				}getData=false;getCurrentLineData="\0";countSemiColon+=1;
			}
		}
		if(n==4)WINDOW.filesReadInitiallyScoreData=true;
	}
	else{//set score: 
		for(int m=4;m>=n;m--){
			if(m!=n){
				BOARD.highScoresName[m]=BOARD.highScoresName[m-1];
				BOARD.highScoresScore[m]=BOARD.highScoresScore[m-1];
				BOARD.highScoresLevel[m]=BOARD.highScoresLevel[m-1];
				BOARD.highScoresLinesClearedthisLevel[m]=BOARD.highScoresLinesClearedthisLevel[m-1];
				BOARD.highScoresTime[m]=BOARD.highScoresTime[m-1];
				BOARD.highScoresBestCombo[m]=BOARD.highScoresBestCombo[m-1];
			}
			else{
				BOARD.highScoresName[m]=BOARD.nameEnterHighScore;
				BOARD.highScoresScore[m]=BOARD.gameScore;
				BOARD.highScoresLevel[m]=BOARD.levelCurrentlyOn;
				BOARD.highScoresLinesClearedthisLevel[m]=BOARD.linesClearedForThisLevel;
				convNumToStr<<BOARD.gameTimeMinutes;BOARD.highScoresTime[m]=convNumToStr.str();convNumToStr.str("\0");BOARD.highScoresTime[m]+=":";
					convNumToStr<<BOARD.gameTimeSeconds;BOARD.highScoresTime[m]+=convNumToStr.str();convNumToStr.str("\0");BOARD.highScoresTime[m]+=".";
					convNumToStr<<BOARD.gameTimeMilliseconds;BOARD.highScoresTime[m]+=convNumToStr.str();convNumToStr.str("\0");
				BOARD.highScoresBestCombo[m]=BOARD.longestComboStreak;
			}
		}
	}
}
void GET_SET_CONTROLS(int n,string file,string lineData){
	if(WINDOW.filesReadInitiallyControls==false){//set controls from file: 
/*		switch(n){//controls:
			case 0:BOARD.controlsMoveLeft=0;break;//int controlsMoveLeft;
			case 1:BOARD.controlsMoveRight=0;break;//int controlsMoveRight;
			case 2:BOARD.controlsRotate=0;break;//int controlsRotate;
			case 3:BOARD.controlsSwitchRotation=0;break;//int controlsSwitchRotation;
			case 4:BOARD.controlsSoftDrop=0;break;//int controlsSoftDrop;
			case 5:BOARD.controlsHardDrop=0;break;//int controlsHardDrop;
			case 6:BOARD.controlsHoldSwitchHold=0;break;//int controlsHoldSwitchHold;
			case 7:BOARD.controlsPause=0;break;//int controlsPause;
			case 8:BOARD.controlsFullscreen=0;break;//int controlsFullscreen;
		}//check if any controls are the same?*/
		if(n==8)WINDOW.filesReadInitiallyControls=true;
	}
	else{//set controls: 
		;
	}
}
