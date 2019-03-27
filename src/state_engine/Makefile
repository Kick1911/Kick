INCLUDE = ../../include
LIB = ../../lib/state_util

keyvalue: keyvalue.c
	gcc -ansi -g3 -D STATIC keyvalue.c -o keyvalue -I$(INCLUDE) $(LIB)/ring_stack.o
sengine: state_engine.c
	gcc -ansi -g3 -D STATIC state_engine.c -o state_engine -I$(INCLUDE) $(LIB)/ring_stack.o
$(LIB)/sengine.o: state_engine.c
	gcc -ansi -fPIC -c $(CFLAGS) state_engine.c -o $(LIB)/sengine.o -I$(INCLUDE)
clean:
	rm -f state_engine keyvalue
