CC = cc


pong: net.o pong.o
	mkdir bin/
	$(CC) -o bin/pong pong.o net.o -lSDL2

net.o:
	$(CC) -o net.o net.c -c

pong.o:
	$(CC) -o pong.o pong.c -c

clean: 
	rm -rf bin/
	rm pong.o net.o
