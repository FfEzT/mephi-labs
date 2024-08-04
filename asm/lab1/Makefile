all:
	nasm my.asm -f elf64 -g -o lol.o
	ld lol.o
	./a.out
	echo $?

# AS = /usr/bin/nasm
# LD = /usr/bin/ld
#
# ASFLAGS = -g -f elf64
# LDFLAGS = -static
#
# SRCS = my.asm
# OBJS = $(SRCS:.s=.o)
#
# EXE = lab1
#
# all: $(SRCS) $(EXE)
#
# clean:
# 	rm -rf $(EXE) $(OBJS)
#
# $(EXE): $(OBJS)
# 	$(LD) $(LDFLAGS) $(OBJS) -o $@
#
# .s.o:
# 	$(AS) $(ASFLAGS) $< -o $@
