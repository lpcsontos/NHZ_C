#if linux
#include "data_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "econio.h"
#include "draw.h"
#include "debugmalloc.h"
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <termios.h>
struct termios orig_termios;

//wrote some time ago for nonblocking input
/**
 * resets terminal mode */

void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

/**
 * set terminal mode*/
void set_conio_terminal_mode()
{
    struct termios new_termios;

    // take two copies - one for now, one for later
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    // register cleanup handler, and set the new terminal mode
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

///check if a button is pressed(basically but a little bit complicated)
int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

///gets the pressed button code
int getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

/**
 * sets up the Player data structure*/

Player* Setup_Player(){
	Player* p = (Player*)malloc(sizeof(Player));
	
	p->x_start=(int*)malloc(2*sizeof(int));
	p->x_start[0] = 1;
	p->x_start[1] = 0;
	
	//where the bullet will start from
	p->shoot_pos_x = 2;
	p->shoot_pos_y = 27;

	//playing field will be 120*40, 120 width, 40 height
	p->y=(int*)malloc(2*sizeof(int));
	p->y[0] = 29;
	p->y[1] = 30;

	return p;
}

/** Sets up the Invaders, makes the linked list, allocates memory to the linked list member
 * and also allocates memory to the sub arrays and fills it up with data */

Invaders* Setup_Inv(int mode){
	//0 easy, 1 is medium and 2 is hard
	//in easy half of the rows invaders will be, and it will move in medium speed
	//in medium there will be six in a row and it will move at medium speed
	//in hard there vill be more rows: not 7 but 11, they will move much faster
	int S_Width = 6;//number of white characters between 2 invader
	int row_length[3] = {6,7,8};
	int numb_row[3] = {4,5,7};
	//linked list setup
	Invaders* list = NULL;
	for(int j = 0; j < numb_row[mode]; j++){
		for(int i = 0; i < row_length[mode]; i++){
			//create one element
			Invaders* mov;
			mov =(Invaders*)malloc(sizeof(Invaders));
			mov->next = list;//connect to previous
			//allocate space to the arrays
			mov->x_start = (int*)malloc(2*sizeof(int));
			mov->x_end = (int*)malloc(2*sizeof(int));
			mov->y = (int*)malloc(2*sizeof(int));
			//first element of rows and the very first element restarts the x coords
			if(mov->next == NULL || i == 0){
				//starting coord
				mov->x_start[0] = 0;
				mov->x_start[1] = 0;
				//end of hitbox coords 
				mov->x_end[0] = (mov->x_start[0]) + S_Width;
				mov->x_end[1] = (mov->x_start[1]) + S_Width;
			}
			else{
				//same just if its not the first element
				mov->x_start[0] = (list->x_end[0]) +2;
				mov->x_start[1] = (list->x_end[1]) +2;
				mov->x_end[0] = (mov->x_start[0]) + S_Width;
				mov->x_end[1] = (mov->x_start[1]) + S_Width;
			}
			//set y coords
			mov->y[0] = 3*j+1;
			mov->y[1] = 3*j+2;
			//next element
			list = mov;
		}
	}
	return list;
}

/**
 * This function will free up the memory allocated to the Invaders and its sub allocated space*/

void freeInvaders(Invaders* i){
	///will get current linked list member, free its sub arrays, got to next member and free previous member
	while(i != NULL){
		Invaders* buff = i;
		free(i->x_start);
		free(i->x_end);
		free(i->y);
		i = i->next;
		free(buff);
	}
}

/**
 * counts how many invaders are there*/
int numb_inv(Invaders* first){
	Invaders* mov = first;
	int count = 0;
	while(mov!=NULL){
		count++;
		mov=mov->next;
	}
	return count;
}

/**
 * This function checks if the bullet hit an invader, if yes, then delete from the linked list*/

int check_bullet(Invaders* first, Bullets* b,int* score,int db){
	Invaders* mov = first;
	Invaders* mov2 = mov;
	while(mov != NULL){
		for(int i = 0; i < db; i++){
			if(mov->y[0] == b[i].y || mov->y[1] == b[i].y){
				if(b[i].x >= mov->x_start[0] && b[i].x <= mov->x_end[0]){
					if(numb_inv(first) == 1){
						*score += 5;
						return 0;
					}
					if(mov == first){
						d_invader(COL_BLACK,COL_BLACK,COL_BLACK,COL_BLACK,mov->x_start[0],mov->y[0],mov->x_start[1],mov->y[1]);
						b[i].y = 0;
						*score += 5;
						return 2;
					}
					else if(mov->next == NULL){
						*score += 5;
						d_invader(COL_BLACK,COL_BLACK,COL_BLACK,COL_BLACK,mov->x_start[0],mov->y[0],mov->x_start[1],mov->y[1]);
						mov2->next=NULL;
						free(mov);
						return 1;
					}
					else{
						*score += 5;
						d_invader(COL_BLACK,COL_BLACK,COL_BLACK,COL_BLACK,mov->x_start[0],mov->y[0],mov->x_start[1],mov->y[1]);
						Invaders* mov3 = mov;
						mov=mov->next;
						mov2->next = mov;
						free(mov3);
						mov=mov2;
						b[i].y = 0;
					}
				}
			}
		}
		mov2=mov;
		mov=mov->next;
	}
	return 1;
}

/** 
 * Main game logic function which will be accesed from main.c*/

int game(int mode){
	econio_clrscr();
	//setup phase
	int score = 0; // the score which to export
	int b_db = 0;
	int sdb_b = 0;
	bool run = true;
	Player* p = Setup_Player();//strange, but it is what it is
	Invaders* first = Setup_Inv(mode);
	int row_length[3] = {6,7,8};
	int cycle = 0;
	int way = 1;
	int test = 1;
	int x_ref = first->x_start[0];
	Bullets* b =(Bullets*)malloc(50*sizeof(Bullets)); //setup for future 
	
	//first draw
	d_init(first, p);
	//game logic
	set_conio_terminal_mode();
	while(run){
		econio_rawmode();
		while(!kbhit()){
			//check if bullet has collision with invader
			if(b_db > 0)test = check_bullet(first,b,&score,b_db);
			if(test == 0){
				econio_normalmode();
				reset_terminal_mode();
				//before exit free the bullets :)
				free(b);
				free(p);
				freeInvaders(first);//yeah free the slaves!!!
				debugmalloc_dump();
				return score;
			}
			else if(test == 2){
				Invaders* mov = first;
				first = first->next;
				free(mov);
			}
			//checks if invader is in line with player
			if(first->y[0] == 28 || first->y[0] == 29){
				econio_normalmode();
				reset_terminal_mode();
				//before exit free the bullets :)
				free(b);
				free(p);
				freeInvaders(first);//yeah free the slaves!!!
				debugmalloc_dump();
				return score;
			}
			//check collisions
			//bullets draw and such
			if(cycle%3==0){
				for(int i = 0; i < b_db; i++){
					if(b[i].y != 0){
						d_bullet(b[i], 0);
						b[i].y--;
						d_bullet(b[i], 1);
						econio_gotoxy(0, 30);
						printf("%d",b[0].y);
						econio_flush();
					}
					else {d_bullet(b[i], 0);}
				}
			}
			if(cycle%(1+numb_inv(first)) == 0 || cycle%20 == 0){
				//move invaders
				if(x_ref < 70 && way){
					mov_invx(first, way);
					x_ref++;
				}
				else{
					if(way){mov_invy(first);}
					way = 0;
					if(x_ref >= 7*row_length[mode]){
						mov_invx(first, way);
						x_ref--;
					}
					else{
						way = 1;
						mov_invy(first);
					}
				}
			}
			if(cycle%100 == 0){sdb_b = 0;}
			d_score(score);
			d_bullets(sdb_b);
			
			usleep(23000);
			cycle++;
			if(cycle == 101)cycle = 0;
		}
		econio_normalmode();
		//did it with switch too, but who cares
		//check keyboard press
		int key = getch();
		//move player to left
		if(key== 'a'){
			if(p->x_start[1] > 0){
				d_player(COL_BLACK,COL_BLACK,COL_BLACK,COL_BLACK,p->x_start[0],p->y[0],p->x_start[1],p->y[1]);
				p->x_start[0]-=2;
				p->shoot_pos_x-=2;
				p->x_start[1]-=2;
				d_player(COL_WHITE,COL_BLACK,COL_BLACK,COL_BLACK,p->x_start[0],p->y[0],p->x_start[1],p->y[1]);
			}
		}
			//move player to right
		else if(key == 'd'){
			if(p->x_start[1] < 70){
				d_player(COL_BLACK,COL_BLACK,COL_BLACK,COL_BLACK,p->x_start[0],p->y[0],p->x_start[1],p->y[1]);
				p->x_start[0]+=2;
				p->shoot_pos_x+=2;
				p->x_start[1]+=2;
				d_player(COL_WHITE,COL_BLACK,COL_BLACK,COL_BLACK,p->x_start[0],p->y[0],p->x_start[1],p->y[1]);
			}
		}
			//shoot bullet
		else if(key == KEY_SPACE && sdb_b < 7){
			sdb_b++;
			b[b_db].x=p->shoot_pos_x;
			b[b_db].y=p->shoot_pos_y;
			b_db++;
			if(b_db%49 == 0)b =(Bullets*)realloc(b,(b_db + 51)*sizeof(Bullets));
			d_bullet(b[b_db-1], 1);
		}
	}
	debugmalloc_dump();
	return score;
}
#endif
