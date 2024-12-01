#include "data_struct.h"
#include <stdio.h>
#include <stdlib.h>
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
	#include <windows.h>
#endif
#include <string.h>
#include <stdbool.h>
#include "econio.h"
#include "score.h"
#include <errno.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include "debugmalloc.h"



///prints specified highscore board
void printboard(FILE* fptr, int db){
	if(db == 0)return;
	//variables
	Data data[1] = {};
	int index = 0; 
	const char* padding = "                                         ";//soooo long, idk why
	char buff[5] = "";
	//drawing begining
	econio_clrscr();
	econio_gotoxy(30,1);
	printf("++++++++++++++++++");
	econio_gotoxy(30,2);
	printf("|NAME     | SCORE|");
	econio_gotoxy(30,3);
	printf("++++++++++++++++++");

	int tName =0; int tSCR = 0;
	//magic is done here
	while(index < db){
		//checks if data was corrupted 
		if((tName = fscanf(fptr,"%s", data->name)) == -1 || tName == 0||(tSCR = fscanf(fptr, "%d",&data->score)) == -1 || tSCR == 0){
			//checks if its end of file, if first if did not work
			if((tSCR = fscanf(fptr,"%d",&data->score))== -1){break;}
			econio_clrscr();
			printf("\nCorrupted file\n");
			exit(0);
		}
		//checks if earlier break is needed
		if((tName == EOF && tSCR == EOF) || (tName == 0 && tSCR == 0)){break;}

		sprintf(buff, "%d", data->score);//transform int to string aka char array
		
		//get padding
		int pad1Len = (TARGETLEN*3/5) - strlen(data->name); 
		int pad2Len =(TARGETLEN*2/5)- strlen(buff);
		
		//draw board
		econio_gotoxy(30, 4+(2*index));
		printf("|%s%*.*s|%*.*s%d|", data->name, pad1Len, pad1Len, padding,pad2Len,pad2Len,padding,data->score);
		econio_gotoxy(30, 4+(2*index+1));
		printf("++++++++++++++++++");
		
		index++;//magic number
	}
	printf("\n");
	printf("\n\nPress ENTER to start the game\n");
	econio_rawmode();
	while(1){
		int key = econio_getch();
		if(key == KEY_ENTER){break;}
	}
	econio_normalmode();
}

///save score to related file if score the is higher than stored in the file connected to the name given by the player
void savewrite_score(int state,int score){
	econio_clrscr();
	econio_textcolor(COL_WHITE);
	//set file path with state
	FILE* fptr;
	char paths[][50] = {"../highscores/l1.txt","../highscores/l2.txt","../highscores/l3.txt"};
	fptr = fopen(paths[state], "r");
	if(fptr == NULL){perror("Scoresave: file opening error");}
	else{
		/*
		 * for legacy code to just exist here or to return to something in case of shit
		switch(state){
			case 0:
				fptr = fopen("../highscores/l1.txt", "r+");
				break;
			case 1:
				fptr = fopen("../highscores/l1.txt", "r+");
				break;
			case 2:
				fptr = fopen("../highscores/l1.txt", "r+");
				break;
		}
		*/

		//set up variables to work with
		char name[MAX_NAME + 2] = {};
		int index = 0;
		Data *p = calloc(3, sizeof(*p));//for safety and to pass new data allocate 3 times the space
		Data temp;
		bool in = false;
		int i_new;

		//checks if highscores directory exist and openable
		DIR* dir;
		dir = opendir("../highscores");
		if(dir){closedir(dir);}
		//checks if directory do not exist
		else if(ENOENT == errno){
			closedir(dir);
			mkdir("../highscores", 0700);
			dir = opendir("../highscores");
			if(dir){closedir(dir);}
			//checks if directory still not exist
			else if(ENOENT == errno){
				closedir(dir);
				free(p);
				debugmalloc_dump();
				perror("Could not create highscores directory, please create it manually to the same directory as main.c");
				exit(0);
			}
			//other problem
			else{
				closedir(dir);
				free(p);
				debugmalloc_dump();
				perror("Error occured regarding the highscores directory");
				exit(0);
			}
		}
		//other problem
		else {
			closedir(dir);
			free(p);
			debugmalloc_dump();
			perror("Error occured regarding the highscores directory");
			exit(0);
		}

		FILE* n = fopen("../highscores/n.txt", "w");
		if(n == NULL){perror("Scoresave: file opening error, at line 80");}
		else{
			//input name
			printf("!Your name can only be 12 character long!");
			printf("Your name: ");
			int testName = 0;
			while((testName = scanf("%s",name)) == 0 || testName == -1 || strlen(name) > 12){
				printf("!Your name can only be 12 character long!");
				printf("Your correct name: ");
			}
			//load to struct the saved data
			//yeah nested loops, its not good, but it is what it is, who else gonna touch this code except me anyway?
			//while(fscanf(fptr,"%s %d",p[index].name, &p[index].score) != EOF){
			
				
			int testStr = 0; int testINT = 0;
			while((testStr = fscanf(fptr,"%s",p[index].name)) != EOF && (testINT = fscanf(fptr,"%d", &p[index].score)) != EOF){
				//tests if readed data was corrupted
				if(testStr == 0 || testStr == -1 || testINT == 0 || testINT == -1){
					perror("Corrupted file");
					break;
				}
				/// if name is in list and current score is higher than old, change it, than sort current arrays to descending based on scores
				//check if name is in the list
				if(strcmp(name, p[index].name) == 0){
					in = true;//is it in or not?
					//check to update its score
					if(score > p[index].score){
						p[index].score = score;
						if(index != 0){
							//bubble sort
							for(int i = 0; i <= index-1; i++){
								for(int j = i+1; j <= index; j++){
									if(p[j].score >= p[i].score){
										temp = p[i];
										p[i] = p[j];
										p[j] = temp;
									}
								}
							}
						}
					}
				}
				//gets ready for next item, reallocating space
				index++;
				p = (Data*)realloc(p, (index+1)*sizeof(*p));
			}

			//if not in highscorer list then add it to the top of its score group
			bool found = false;
			if(!in){
				for(int i = 0; i < index; i++){
					if(score >= p[i].score && !found){
						i_new = i;
						found = true;
						break;
					}
				}
			}
			//if nobody is in the list put him in
			if(index == 0)fprintf(n, "%s %d",name, score);
			//save list to file
			else {
				for(int i = 0; i < index; i++){
					if(i == i_new) fprintf(n, "%s %d\n",name, score);
					fprintf(n, "%s %d\n",p[i].name, p[i].score);
				}
			}
			//free buff and close file stream
			free(p);
			fclose(n);
			fclose(fptr);
			//check if any problem occured while freeing memory
			debugmalloc_dump();
			//delete old, rename new save file
			//yeah there are better ways to do it, but i dont want to touch this at this point
			remove(paths[state]);
			rename("../highscores/n.txt",paths[state]);
		}
	}
}


///Main highscore logic
//get state from menu
void highscore(int state){
	//set window size for good windows users :), but i like linux better, just not the terminal modifying
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
	SMALL_RECT WinSize = {0, 0, 70, 40};
	SMALL_RECT* WinWin = &WinSize;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinWin);
#endif

	//highscore board setup
	FILE* fptr;
	char paths[][50] = {"../highscores/l1.txt","../highscores/l2.txt","../highscores/l3.txt"};
	int testDB = 0;int db = 0;
	printf("Give how many scores to show from the top, 0 to not show anything");
	printf("\nor negative number as it will be converted to a positive number\n");
	printf("number of players to show from top 1: ");
	testDB = scanf("%d",&db);
	while(testDB < 1 || db < 0 || db > 1000000){
		econio_clrscr();
		printf("number of players to show from top 1: ");
		testDB = scanf("%*c%d%*c",&db);
	}

	//checks if highscores directory exist and openable
	DIR* dir2;
	dir2 = opendir("../highscores");
	if(dir2){closedir(dir2);}
	//directory does not exist
	else if(ENOENT == errno){
		closedir(dir2);
		mkdir("../highscores", 0700);
		dir2 = opendir("../highscores");
		if(dir2){closedir(dir2);}
		//directory does not exist
		else if(ENOENT == errno){
			closedir(dir2);
			perror("Could not create highscores directory, please create it manually to the same directory as main.c");
			exit(0);
		}
		//other problem
		else{
			closedir(dir2);
			perror("Error occured regarding the highscores directory");
			exit(0);
		}
	}
	//other problem
	else {
		closedir(dir2);
		perror("Error occured regarding the highscores directory");
		exit(0);
	}
	//state machine, would be better to put paths into a 2d char array, but who cares
	//its not like anybody gonna expand this sht
	switch(state){
		//show relevant highscore
		//dont wanna make a function to read file and store the data 
		case 0:
			fptr = fopen(paths[state], "r");
			if(fptr == NULL){
				fptr = fopen(paths[state], "w");
				if(fptr == NULL){
					perror("File open error");
					exit(0);
				}
			}
			printboard(fptr, db);		
			break;
		case 1:
			//show highscore in medium diff
			fptr = fopen(paths[state], "r");
			if(fptr == NULL){
				fptr = fopen(paths[state], "w");
				if(fptr == NULL){
					perror("File open error");
					exit(0);
				}
			}
			printboard(fptr, db);
			break;
		case 2:
			//high diff score
			fptr = fopen(paths[state], "r");
			if(fptr == NULL){
				fptr = fopen(paths[state], "w");
				if(fptr == NULL){
					perror("File open error");
					exit(0);
				}
			}
			printboard(fptr, db);
			break;
	}
}
