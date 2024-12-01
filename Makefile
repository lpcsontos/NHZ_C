main.out: main.c
	gcc -Wall -Werror -Iheaders cfiles/*.c main.c -o build/a
	#x86_64-w64-mingw32-gcc -Wall -Werror -Iheaders cfiles/*.c main.c -o build/main64.exe -lwinmm -lncursesw -DNCURSES_STATIC
