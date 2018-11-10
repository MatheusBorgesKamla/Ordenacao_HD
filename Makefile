all: compile

compile: Code.o Main.o 
        # O compilador faz a ligação entre os dois objetos
	gcc -o programaTrab Code.o Main.o
#-----> Distancia com o botão TAB ### e não com espaços
teste.o: Code.c
	gcc -o Code.o -c Code.c -W -Wall -ansi -pedantic
main.o: Main.c Code.h
	gcc -o Main.o -c Main.c -W -Wall -ansi -pedantic
clean:
	rm -rf *.o
mrproper: clean
	rm -rf Code