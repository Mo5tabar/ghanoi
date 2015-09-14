# File: Makefile
# Author: Sami Metoui 
# Description: ghanoi Makefile
# License: GPL 3 (http://www.gnu.org/licenses/gpl.html)

all: ghanoi
	
ghanoi: ghanoi.o
	gcc -o ghanoi ghanoi.o `allegro-config --libs`

ghanoi.o: main.c 
	gcc -o ghanoi.o -c main.c 
	
clean:
	rm -rf *.o

mrproper: clean
	rm -rf ghanoi