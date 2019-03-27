LIB = ../lib
S_UTIL = $(LIB)/state_util

$(LIB)/state_util.so: 
	gcc -ansi -fPIC -c -o $(S_UTIL)/ring_stack.o -I$(INCLUDE) hash_table.c
	gcc -ansi -shared -o $(LIB)/libhash.so.1 hash_table.o
make_obj: 
	cd ring_stack && $(MAKE) object
	cd state_engine && $(MAKE) object
clean:
	cd ring_stack && $(MAKE) clean
	cd state_engine && $(MAKE) clean
