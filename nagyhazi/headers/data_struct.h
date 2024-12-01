#ifndef data_struct_h
#define data_struct_h

//definition of space key
#define KEY_SPACE 32
///max length of name
#define MAX_NAME 12
///max length of collectable points
#define MAX_POINT_LENGTH 4
///target length of a board piece without the "|" tags(there are 3 of these tags)
#define TARGETLEN 15

///data structure of highscore system
typedef struct datas{
	char name[MAX_NAME + 1];
	int score;
}Data;

///@brief Bullets data structure
/**
 *	
 * array of bullets, where y will change as it goes up
 * but x wont change
 * x will compare its value if it is greater or equ or smaller or equ than
 * invader x_start and x_end value to see if it hits it, also do this with y as invaders can run into bullets
 *	also the array will be dinamically allocated, as with every bullet shot
 *	the array will grow, and with each shot that go out to space or hits an invader
 *	the array maybe shrink
 *
 */

typedef struct Bullets{
	int x;
	int y;
}Bullets;

///Invaders data structure
/**
 *
 * linked list of invaders, 
 * x_start is an array of x coordinates, invader hitbox x starting coord
 * x_end is an array of the x_start x end coords
 * y is an array where y coords are of invaders
 * (in documentation the star symbol will not show, in the character design there are stars still)
 * 																															
 *	|  *(-_-)*   <- y[0] = 0, x_start[0] = 3, x_end[0] = 9											
 *	|	$._$_.$   <- y[1] = 1, x_start[1] = 3, x_end[1] = 9
 *
 * the related coords are in the same place in the arrays
 *
 * head and body are 7 character long
 *
 */


typedef struct Invaders{
	int* x_start;
	int* x_end;
	int* y;
	struct Invaders* next;
}Invaders;


///Player data structure
/**
 *
 * will store it in a struct cause why not, easier data storage for me to implement
 * same way of thinking as with the Invaders, just dont need the full hitbox, as Invaders only kill
 * the player if they reach its level(y coord)
 *	new design:
 *
 *-.I.   (- is not part of the player design)																													
 *(_U_)
 *
 */

typedef struct Player{
	int* x_start;
	int shoot_pos_x;
	int shoot_pos_y;
	int* y;
}Player;

#endif
