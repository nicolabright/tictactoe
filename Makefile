all:    tictactoe.c
	gcc tictactoe.c -o tictactoe.exe
	@ tictactoe.exe

clean:
	del tictactoe.exe 2> nul
