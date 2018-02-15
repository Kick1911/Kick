#ifndef STATE_H
#define STATE_H

#define FINAL (0b1)
#define OPTIONAL (0b10)
#define ANY (0b11)

typedef struct state{
	unsigned char opt;
	struct state* aux;
	unsigned int V;
	struct state** states;
}state_t;

typedef struct state* State;

void act(State s, unsigned int in, State next, unsigned char opt){
	switch(opt){
		case OPTIONAL:
			s->aux = next;
		default:
			s->states[in] = next;
			s->opt = opt;
	}
}

void alloc_state(State* s, size_t size){
	*s = malloc(sizeof(state_t));
	(*s)->V = size;
	(*s)->states = calloc(sizeof(State), size);	
}

void free_state(State s){
	free(s->states);
	free(s);
}
#endif
