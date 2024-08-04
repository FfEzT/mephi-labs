SORT_ORDER = ASK

ifdef DESK
SORT_ORDER = DESK
endif

a:
	nasm my.asm -f elf64 -g -o lol.o -D SORT_ORDER=$(SORT_ORDER)
	ld lol.o
	./a.out
	echo $?

c:
	g++ a.cpp -g
	./a.out
