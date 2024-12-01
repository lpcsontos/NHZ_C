

///prints highscore board while getting the data from the save file, needs location and max amount to draw
void printboard(FILE* fptr, int db);

///write to file to the specified file based on state to save new data or update old score
void savewrite_score(int state, int score);

///get input to how many elements to write based on state, medium for printboard
void highscore(int state);
