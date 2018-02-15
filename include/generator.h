#ifndef GEN_H
#define GEN_H
#include <state.h>
#include <malloc.h>

typedef struct generator{
	char** rules;
	State root;
}gen;

typedef gen* Gen;

alloc_gen(Gen* g){
	*g = malloc(sizeof(gen));
}

#endif
