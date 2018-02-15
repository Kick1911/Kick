INCLUDE = include
LIB = lib
ARCH = $(LIB)/{state_util}.so

main: sobj main.c
	gcc -ansi main.c -o prekick -I$(INCLUDE)
lib: $(ARCH)
	cd src; $(MAKE) lib
test:
	cd src/state_engine; $(MAKE) test
clean:
	cd src && $(MAKE) clean
	cd lib && $(MAKE) clean
