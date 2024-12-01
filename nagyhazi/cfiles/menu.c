#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "econio.h"
#include <stdbool.h>
#include "draw.h"
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
	#include <windows.h>
	#include <mmsystem.h>
#endif

///menu logic
int menu(){
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
	SMALL_RECT WinSize = {0, 0, 135, 35};
	SMALL_RECT* WinWin = &WinSize;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinWin);
	//plays in a loop music.wav file in windows, just do not have music.wav yet
	//PlaySound(TEXT("../sound/music.wav"),NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
#endif
	econio_clrscr();
	//draws menu items
	printSI(1,3,COL_WHITE, COL_BLACK);
	pstart(6, 11, COL_BLACK, COL_WHITE, COL_BLACK);
	//pset(5,16,COL_WHITE, COL_BLACK, COL_WHITE); was good idea
	pquit(6, 16, COL_WHITE, COL_BLACK, COL_WHITE);

	int last = 0;
	int before = 0;	
   while(true){
		econio_rawmode();
		while(true){
				//reads key and do state magic, save previous state and update current state
				int ch = econio_getch();
				if(ch == KEY_UP && last != 0){before = last; last--;}
				else if(ch == KEY_DOWN && last != 1){before = last; last++;}
				else if(ch == KEY_ENTER) break;
				//draws new state of menu items or state machine
				switch(last){
					case 0:
						//start text is shiney, settings not shiney anymore
						pstart(6, 11, COL_BLACK, COL_WHITE, COL_BLACK);
						pquit(6,16,COL_WHITE, COL_BLACK, COL_WHITE);
						break;
						/*
						 * was a good idea, just not in c, devistated am i, said Yoda as
						 * possible upgrade if client wants to get a new feture in like a settings button in production
						 * gonna leave it here as nobody gonna touch it and there is space for it
						 *
					case 1:
						if(before == 0){
							//start not shiney, settings shiney
							pstart(6, 11, COL_WHITE, COL_BLACK, COL_WHITE);
							pset(5,16,COL_BLACK, COL_WHITE, COL_BLACK);
						}
						else {
							//quit not shiney, settings shiney
							pset(5,16,COL_BLACK, COL_WHITE, COL_BLACK);
							pquit(6, 21, COL_WHITE, COL_BLACK, COL_WHITE);
						}
						break;
						*/
					case 1:
						//settings not shiney, quit shiney
						pstart(6,11,COL_WHITE, COL_BLACK, COL_WHITE);
						pquit(6, 16, COL_BLACK, COL_WHITE, COL_BLACK);
						break;
				}
			}
				econio_normalmode();
				//choice is quit, do exit with screen to default
				if(last == 1){
					econio_textbackground(COL_BLACK);
					econio_clrscr();
					econio_textcolor(COL_WHITE);
					exit(0);
				}
				else {
					//choice is start, do clear screen, draw dificulty elements
					econio_textbackground(COL_BLACK);
					econio_clrscr();
					econio_textcolor(COL_WHITE);
					peasy(6, 7, COL_BLACK, COL_WHITE, COL_BLACK);
					pmed(6, 13, COL_WHITE, COL_BLACK, COL_WHITE);
					phard(6, 19, COL_WHITE, COL_BLACK, COL_WHITE);
					
					last = 0;

					econio_rawmode();
					while(true){
						//read keys and save previous state, and update now state
						int ch = econio_getch();
						if(ch == KEY_UP && last != 0){before = last; last--;}
						else if(ch == KEY_DOWN && last != 2){before = last; last++;}
						else if(ch == KEY_ENTER) break;
						
						//state machine goes brrrrrrrr
						switch(last){
							case 0:
								//easy text is shiney, medium is not
								peasy(6, 7, COL_BLACK, COL_WHITE, COL_BLACK);
								pmed(6,13,COL_WHITE, COL_BLACK, COL_WHITE);
								break;
							case 1:
								if(before == 0){
									//easy was shiney, not now anymore, medium shiney
									peasy(6, 7, COL_WHITE, COL_BLACK, COL_WHITE);
									pmed(6,13,COL_BLACK, COL_WHITE, COL_BLACK);
								}
								else {
									//hard not shiney anymore, meium is shiney
									pmed(6,13,COL_BLACK, COL_WHITE, COL_BLACK);
									phard(6, 19, COL_WHITE, COL_BLACK, COL_WHITE);
								}
								break;	
							case 2:
								//medium not shiney, hard is shiney
								pmed(6,13,COL_WHITE, COL_BLACK, COL_WHITE);
								phard(6, 19, COL_BLACK, COL_WHITE, COL_BLACK);
								break;
						}
		         }
		                  
					econio_normalmode();
		         //before exit to who knows where, clean screen
					econio_textbackground(COL_BLACK);
		         econio_clrscr();
		         econio_textcolor(COL_WHITE);

	            return last;
	         }
		}
}
