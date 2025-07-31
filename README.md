This mini game is the copy of the retro game Space Invaders. The player controls a small spaceship to shoot down the aliens.
As more and more of them gets shot down the faster they are coming down to Earth. The player gets points after every enemy.
With its score you can get on the highscore list. The different difficulties have different highscore lists.



<img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/89be23f6-fe59-401b-879d-dba2177f7b33" />












This project uses econio!! Its licnese and readme file is located in the license folder, the header file is in the headers folder.

Sound folder is empty, as windows version do not work, which use the sounds.

Build description:

    -linux build:

        build command: gcc -Wall -Werror -Iheaders cfiles/*.c main.c -o build/a
        necessary steps for the build:
            -step 1: if build directory is included, then skip step 2
            -step 2: create build directory in the same directory as the main.c file
            -step 3: run the build command in the same directory as the main.c file


    -windows build(not working right now):

        build command: 
            x86_64-w64-mingw32-gcc -Wall -Werror -Iheaders cfiles/*.c main.c -o build/main64.exe -lwinmm
        necessary steps for the build:
            -step 1: if build directory is included, then skip step 2
            -step 2: create build directory in the same directory as the main.c file
            -step 3: run the build command in the same directory as the main.c file
