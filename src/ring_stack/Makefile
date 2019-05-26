INCLUDE = ../../include
LIB = ../../lib/state_util
LIB_OBJ = $(LIB)/ring_stack.o

ring_stack: ring_stack.c $(INCLUDE)/ring_stack.h
	gcc -ansi -g3 -D STATIC ring_stack.c -o ring_stack.out -I$(INCLUDE)
$(LIB_OBJ): ring_stack.c $(INCLUDE)/ring_stack.h
	gcc -ansi -c ring_stack.c -o $(LIB_OBJ) -I$(INCLUDE)
clean:
	rm -f ring_stack.out
