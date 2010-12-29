compile:
	nasm -f bin loader.asm -o loader
	nasm -f bin kernel.asm -o kernel

image:
	cat loader kernel > image

install:

	dd if=image of=/dev/fd0

clean:

	rm -f kernel
	rm -f loader
	rm -f image

all: compile image install