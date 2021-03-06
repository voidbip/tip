CC = gcc
CCFLAGS = -Wall -Werror -pedantic-errors

debug: CCFLAGS += -g
debug: libtip.a libtip.so 

release: CCFLAGS += -O3
release: libtip.a libtip.so

all: release docs


tip.o: tip.c tip.h
	$(CC) $(CCFLAGS) -c -fPIC tip.c -o tip.o

libtip.so: tip.o
	$(CC) $(CCFLAGS )-shared -o libtip.so tip.o

libtip.a: tip.o
	ar rcs libtip.a tip.o

main: main.c libtip.so
	$(CC) $(CCFLAGS) -static -L. -o main main.c -ltip

docs: tip.o doxygen.config mainpage.dox 
	doxygen doxygen.config	

clean:
	rm -rf tip.o libtip.so libtip.a main main.o ./docs/*
