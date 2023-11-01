pong: net.o pong.o
	gcc -o pong pong.o net.o -lSDL2
net.o:
	gcc -o net.o net.c -c

pong.o:
	gcc -o pong.o pong.c -c

clean: 
	rm pong net.o pong.o
