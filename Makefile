interpretador: interpretador.o
	cc interpretador.o -o interpretador
interpretador.o: interpretador.c
	cc -c interpretador.c -o interpretador.o
clean:
	rm -f interpretador.o interpretador.c interpretador
