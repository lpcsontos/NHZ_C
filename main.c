#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "score.h"
#include "game.h"

int main(){
	//it is looped to be played again 
	while(1){
		int state = menu();
		highscore(state);
		int score = game(state);
		savewrite_score(state, score);
	}
}



