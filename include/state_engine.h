#ifndef SENG_H
#define SENG_H
#include <state.h>

struct sengine{
	int** mem_stacks;
	State start;
};

typedef struct sengine* seng;

State resolve(seng,char*);

void alloc_seng(seng* obj){
	*obj = (seng)malloc(sizeof(struct sengine));
	if(*obj == NULL) free(*obj);
}

void free_seng(seng engine){
	free(engine);
}

void use_states(seng engine, State state){
	engine->start = state;
}
#endif
