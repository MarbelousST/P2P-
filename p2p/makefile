all: main

main: control.o interfaz.o cliente.o servidor.o
	gcc control.o interfaz.o cliente.o servidor.o -o main.exe -l pthread

control.o: control.c
	gcc -c control.c -l pthread

interfaz.o: interfaz.c
	gcc -c interfaz.c

cliente.o: cliente.c
	gcc -c cliente.c

servidor.o: servidor.c
	gcc -c servidor.c

clean: 
	rm -rf *.exe *.o

