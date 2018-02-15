#ifndef SENG_C
#define SENG_C
#include <stdlib.h>
#include <state_engine.h>
#include <ring_stack.h>
#include <state.h>
#include <stdio.h>

r_stack* rs;

State resolve(seng engine, char* str){
	push(rs, engine->start);
	while( rs->capacity ){
		State temp = pop(rs);
		if(temp && temp->V > *str && *str >= 0 ){
			switch(temp->opt){
				case FINAL:
					return temp;
				break;
				case OPTIONAL:
					if(temp->states[*str])
						push(rs, temp->states[*str++]);
					else
						push(rs, temp->aux);
				break;
				default:
					push(rs, temp->states[*str++]);
			}
		}
	}
	return NULL;
}

#ifdef STATIC
int main(){
	init((void**)&rs, 0x80);
	State s1;
	State s2;
	State s3;
	State s4;
	alloc_state(&s1, 4);
	alloc_state(&s2, 10);
	alloc_state(&s3, 4);
	alloc_state(&s4, 1);
	act(s1, 2, s2, 0);
	act(s2, 9, s3, OPTIONAL);
	act(s3, 3, s4, 0);
	act(s4, 0, NULL, FINAL);

	seng engine;
	alloc_seng(&engine);
	if(!engine) fprintf(stderr, "Failed to allocate engine.\n"),exit(2);
	use_states(engine, s1);

	char test[] = {2, 9, 3};
	State res = resolve(engine, test);
	if(!res) fprintf(stderr, "result: failed machine\n");
	else printf("result: %d\n", res->opt);
	free_state(s1);
	free_state(s2);
	free_state(s3);
	free_state(s4);
	free_stack(rs);
	free_seng(engine);
	return 0;
}
#endif
#endif
