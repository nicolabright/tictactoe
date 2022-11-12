all:    tictactoe.c
	gcc tictactoe.c -o tictactoe.exe
	@ cls
	@ tictactoe.exe

clean:
	del tictactoe.exe 2> nul
