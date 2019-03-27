#ifndef STATE_H
#define STATE_H

#define FINAL (0b1)
#define OPTIONAL (0b10)
#define ANY (0b11)

typedef struct state{
	void* data;
	unsigned char opt;
	struct state* aux;
	unsigned int V;
	unsigned int offset;
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

void alloc_state(State* s, size_t V, unsigned int offset){
	*s = malloc(sizeof(state_t));
	(*s)->V = V;
	(*s)->offset = offset;
	(*s)->states = calloc(sizeof(State), V);	
}

void free_state(State s){
	free(s->states);
	free(s);
}
#endif
