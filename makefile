all: rand.o
	gcc -o rand.out rand.o

rand.o: rand.c
	gcc -c rand.c

run: rand.out
	./rand.out

clean:
	make -i cleanH

cleanH:
	rm *~
	rm *.txt
