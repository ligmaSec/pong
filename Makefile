pong: pong.c
	gcc pong.c -lSDL2 -o pong


clean: 
	rm pong
