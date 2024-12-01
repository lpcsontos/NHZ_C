#include "data_struct.h"
#include <stdio.h>
#include "econio.h"
#include <stdbool.h>
#include <stdlib.h>



//prints SPACE INVADERS, shifted with n tabs
void printSI(int tabcounter, int y, int tcolor, int bcolor){
	econio_textbackground(bcolor);
	econio_textcolor(tcolor);
	econio_gotoxy(8*tabcounter, y);
	printf("#######\\######\\  #####\\  ######\\#######\\    ##\\###\\   ##\\##\\   ##\\#######\\######\\ #######\\#####\\  #######\\\n");
	econio_gotoxy(8*tabcounter, y+1);
	printf("##-----/##/--##\\##/--##\\##/----/##/----/    ##|####\\  ##|##|   ##|##/--##|##/--##|##/----/##/-##\\ ##/----/\n");
	econio_gotoxy(8*tabcounter, y+2);
	printf("#######\\#######/#######|##|     #####\\      ##|##/##\\ ##|##|   ##|#######|##|  ##|#####\\  ######/ #######\\\n");
	econio_gotoxy(8*tabcounter, y+3);
	printf("\\----##|##/---/ ##/--##|##|     ##/--/      ##|##|\\##\\##|\\##\\ ##/ ##/--##|##|  ##|##/--/  ##/-##\\ \\----##|\n");
	econio_gotoxy(8*tabcounter, y+4);
	printf("#######|##|     ##|  ##|\\######\\#######\\    ##|##| \\####| \\####/  ##|  ##|######/ #######\\##| ##| #######|\n");
	econio_gotoxy(8*tabcounter, y+5);
	printf("\\______/\\_/     \\_/  \\_/ \\_____/\\______/    \\_/\\_/  \\___/  \\___/  \\_/  \\_/\\_____/ \\______/\\_/ \\_/ \\______/\n");
}

//prints start, shifted with n tabs, choice text,background color 
void pstart(int tabcount, int y,int tcolor, int bcolor, int b2color){
	econio_textbackground(b2color);econio_gotoxy(8*tabcount, y);econio_textbackground(bcolor);
	econio_textcolor(tcolor);printf(" __  ___  __  __  ___");
	econio_textbackground(b2color);
	econio_gotoxy(8*tabcount, y+1);econio_textbackground(bcolor);printf("(__   |  [__][__)  | ");
	econio_textbackground(b2color);
	econio_gotoxy(8*tabcount, y+2);econio_textbackground(bcolor);printf(".__)  |  |  ||  \\  | ");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount, y+3);
	econio_textbackground(bcolor);printf("                     ");
	econio_textbackground(b2color);
}

//prints quit, shifted with n tabs, choice text,background color 
void pquit(int tabcount, int y, int tcolor, int bcolor, int b2color){
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 2, y);
	econio_textbackground(bcolor);econio_textcolor(tcolor);printf(" __       ___ ___");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 2, y+1);
	econio_textbackground(bcolor);printf("|  | |  |  |   | ");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 2, y+2);
	econio_textbackground(bcolor);printf("|__\\ |__| _|_  | ");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 2, y+3);
	econio_textbackground(bcolor);printf("                 ");econio_textbackground(b2color);
	econio_textcolor(COL_BLACK);
}

//prints settings, shifted with n tabs, choice text,background color 
void pset(int tabcount, int y, int tcolor, int bcolor, int b2color){
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 6, y);
	econio_textbackground(bcolor);
	econio_textcolor(tcolor);printf(" __ ___________     __ __");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 6, y+1);
	econio_textbackground(bcolor);printf("(_ |_  |  |  | |\\ |/__(_ ");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 6, y+2);
	econio_textbackground(bcolor);printf("__)|__ |  | _|_| \\|\\_|__)");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 6, y+3);
	econio_textbackground(bcolor);printf("                         ");
	econio_textbackground(b2color);
}


//prints easy, shifted with n tabs, choice text,background color 
void peasy(int tabcount, int y,int tcolor, int bcolor, int b2color){
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 4, y);econio_textbackground(bcolor);
	econio_textcolor(tcolor);printf("  __  __   ___ .   . ");
	econio_textbackground(b2color);
	econio_gotoxy(8*tabcount + 4, y+1);econio_textbackground(bcolor);printf(" |__ |__| [__   \\_/  ");
	econio_textbackground(b2color);
	econio_gotoxy(8*tabcount + 4, y+2);econio_textbackground(bcolor);printf(" |__ |  | ___]   |   ");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 4, y+3);
	econio_textbackground(bcolor);printf("                     ");
	econio_textbackground(b2color);
}

//prints medium, shifted with 0 tabs, choice text,background color 
void pmed(int tabcount, int y, int tcolor, int bcolor, int b2color){
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 1, y);
	econio_textbackground(bcolor);econio_textcolor(tcolor);printf(" .  .  ___  __  . .  . .  . ");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 1, y+1);
	econio_textbackground(bcolor);printf(" |\\/| |___ |  \\ | |  | |\\/| ");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 1, y+2);
	econio_textbackground(bcolor);printf(" |  | |___ |__/ | |__| |  | ");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 1, y+3);
	econio_textbackground(bcolor);printf("                            ");
	econio_textbackground(b2color);
}

//prints hard, shifted with 0 tabs, choice text,background color 
void phard(int tabcount, int y, int tcolor, int bcolor, int b2color){
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 4, y);
	econio_textbackground(bcolor);
	econio_textcolor(tcolor);printf(" .  .  __  .--.  __  ");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 4, y+1);
	econio_textbackground(bcolor);printf(" |__| |__| |__/ |  \\ ");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 4, y+2);
	econio_textbackground(bcolor);printf(" |  | |  | |  \\ |__/ ");
	econio_textbackground(b2color);econio_gotoxy(8*tabcount + 4, y+3);
	econio_textbackground(bcolor);printf("                       ");
	econio_textbackground(b2color);
	econio_textcolor(COL_BLACK);
}


//draws invader
void d_invader(int tcolor, int bcolor, int tcolor2, int bcolor2, int x, int y, int x2, int y2){
	econio_textcolor(tcolor2);econio_textbackground(bcolor2);
	econio_gotoxy(x,y);econio_textcolor(tcolor);econio_textbackground(bcolor);
	printf("*(-_-)*");econio_textcolor(tcolor2);econio_textbackground(bcolor2);
	econio_gotoxy(x2,y2);econio_textcolor(tcolor);econio_textbackground(bcolor);
	printf("$._$_.$");econio_textcolor(tcolor2);econio_textbackground(bcolor2);
}

//draws player
void d_player(int tcolor, int bcolor, int tcolor2, int bcolor2, int x, int y, int x2, int y2){
	econio_textcolor(tcolor2);econio_textbackground(bcolor2);
	econio_gotoxy(x,y);econio_textcolor(tcolor);econio_textbackground(bcolor);
	printf(".I.");econio_textcolor(tcolor2);econio_textbackground(bcolor2);
	econio_gotoxy(x2,y2);econio_textcolor(tcolor);econio_textbackground(bcolor);
	printf("(_U_)");econio_textcolor(tcolor2);econio_textbackground(bcolor2);
}

//draws map first time
void d_init(Invaders* first, Player* p){
	Invaders* mov = first;
	while(mov != NULL){
		d_invader(COL_WHITE, COL_BLACK, COL_BLACK, COL_BLACK, mov->x_start[0], mov->y[0], mov->x_start[1], mov->y[1]);
		mov=mov->next;
	}
	d_player(COL_WHITE,COL_BLACK,COL_BLACK,COL_BLACK,p->x_start[0],p->y[0],p->x_start[1],p->y[1]);
	econio_flush();
}

void d_score(int score){
	econio_textbackground(COL_BLACK);
	econio_gotoxy(20,32);
	econio_textcolor(COL_WHITE);
	printf("SCORE: %d",score);
	econio_textcolor(COL_BLACK);
}

void d_bullets(int sdb_b){
	econio_textbackground(COL_BLACK);
	econio_gotoxy(35, 32);
	econio_textcolor(COL_WHITE);
	printf("BULLETS: 7/ %d",7-sdb_b);
	econio_textcolor(COL_BLACK);
}


void mov_invx(Invaders* first, int way){
	Invaders* mov = first;
	while(mov != NULL){
		d_invader(COL_BLACK, COL_BLACK, COL_BLACK, COL_BLACK, mov->x_start[0], mov->y[0], mov->x_start[1], mov->y[1]);
		way==1?mov->x_start[0]++:mov->x_start[0]--;
		way==1?mov->x_start[1]++:mov->x_start[1]--;
		way==1?mov->x_end[0]++:mov->x_end[0]--;
		way==1?mov->x_end[1]++:mov->x_end[1]--;
		d_invader(COL_WHITE, COL_BLACK, COL_BLACK, COL_BLACK, mov->x_start[0], mov->y[0], mov->x_start[1], mov->y[1]);
		mov=mov->next;
	}
}


void mov_invy(Invaders* first){
	Invaders* mov = first;
	while(mov != NULL){
		d_invader(COL_BLACK, COL_BLACK, COL_BLACK, COL_BLACK, mov->x_start[0], mov->y[0], mov->x_start[1], mov->y[1]);
		mov->y[0]+=2;
		mov->y[1]+=2;
		d_invader(COL_WHITE, COL_BLACK, COL_BLACK, COL_BLACK, mov->x_start[0], mov->y[0], mov->x_start[1], mov->y[1]);
		mov=mov->next;
	}
}

void d_bullet(Bullets b, int white){
	econio_textcolor(COL_BLACK);econio_textbackground(COL_BLACK);
	econio_gotoxy(b.x,b.y);
	white==1?econio_textcolor(COL_WHITE):econio_textcolor(COL_BLACK);
	econio_textbackground(COL_BLACK);
	printf("|");econio_textcolor(COL_BLACK);econio_textbackground(COL_BLACK);
}
