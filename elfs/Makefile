all: elfdump

elfdump: elfdump.c
	gcc -Wall -o $@ $<

install: elfdump
	install -m 0755 $< ~/bin

clean:
	elfdump
