all: Baash.o
	 gcc Baash.o -o Baash

ksamp.o: Baash.c
		 gcc -c Baash.c -o Baash.o

clean: 
	  rm Baash.o Baash
