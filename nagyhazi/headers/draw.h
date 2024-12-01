//for menu

///draws SPACE INVADERS text starting y coords and tabcounts*8 x coord with tcolor as text color and bcolor as background color
void printSI(int tabcounter, int y, int tcolor, int bcolor);
///draws START text starting y coords and tabcounts*8 x coord with tcolor as text color and bcolor as background color
void pstart(int tabcount, int y, int tcolor, int bcolor, int b2color);
///draws settings text starting y coords and tabcounts*8 + 2 x coord with tcolor as text color and bcolor as background color
void pset(int tabcount, int y, int tcolor, int bcolor, int b2color);
///draws quit text starting y coords and tabcounts*8 + 6 x coord with tcolor as text color and bcolor as background color
void pquit(int tabcount, int y, int tcolor, int bcolor, int b2color);
///draws easy text starting y coords and tabcounts*8 + 4 x coord with tcolor as text color and bcolor as background color
void peasy(int tabcount, int y, int tcolor, int bcolor, int b2color);
///draws medium text starting y coords and tabcounts*8 + 1 x coord with tcolor as text color and bcolor as background color
void pmed(int tabcount, int y, int tcolor, int bcolor, int b2color);
///draws hard text starting y coords and tabcounts*8 + 4 x coord with tcolor as text color and bcolor as background color
void phard(int tabcount, int y, int tcolor, int bcolor, int b2color);

//__________________________________________________________________________________________________________________
//for game

///draws invader starting y coords and x coord with tcolor as text color and bcolor as background color
void d_invader(int tcolor, int bcolor, int tcolor2, int bcolor2, int x, int y, int x2, int y2);
///draws player starting y coords and x coord with tcolor as text color and bcolor as background color
void d_player(int tcolor, int bcolor, int tcolor2, int bcolor2, int x, int y, int x2, int y2);
///draws score
void d_score(int score);
///Invaders data struct
typedef struct Invaders Invaders;
///Player data struct
typedef struct Player Player;
///Bullets data struct
typedef struct Bullets Bullets;
///draws map first time
void d_init(Invaders* first, Player* p);
///draws bullets
void d_bullet(Bullets b, int white);
///move invaders horizontally
void mov_invx(Invaders* first, int way);
///move invaders vertically
void mov_invy(Invaders* first);
///draws bullet count
void d_bullets(int sdb_b);
