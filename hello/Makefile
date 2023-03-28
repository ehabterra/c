# create object files
.PHONY	: asm
asm:
	gcc -c main.c

# link object files
.PHONY	: lnk
lnk:
	gcc main.o -o main

# link directly the source file
.PHONY	: link
link:
	gcc main.c -o main

.PHONY : build
build:
	gcc -o main main.c test.c