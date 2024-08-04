AS = /usr/bin/nasm
LD = /usr/bin/ld

CCFLAGS = -g -c -Ofast
ASFLAGS = -g -f elf64
LDFLAGS = -static -z noexecstack

LIBPATH = -L /lib/gcc/x86_64-linux-gnu/13 -L /lib
OBJPATH = /usr/lib/x86_64-linux-gnu

LIBS = -lgcc -lgcc_eh -lc -lm

PREOBJ = $(OBJPATH)/crt1.o $(OBJPATH)/crti.o
POSTOBJ = $(OBJPATH)/crtn.o

SRCS = main.c asm.s 
HEAD = stb_image.h stb_image_write.h lab5.h
OBJS = main.o asm.o


EXE = lab_c
PROC_CHOICE = 

ifdef ASM
PROC_CHOICE = -D ASM=$(ASM)
endif

all: $(SRCS) $(EXE)

clean:
	rm -rf $(EXE) $(OBJS)

$(OBJS): $(HEAD)

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) $(LIBPATH) $(PREOBJ) $(OBJS) $(POSTOBJ) -\( $(LIBS) -\) -o $@

.c.o:
	$(CC) $(CCFLAGS) $(PROC_CHOICE)  $< -O $@	

.s.o:
	$(AS) $(ASFLAGS) $< -o $@
