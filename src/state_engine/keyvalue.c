#ifndef SENG_C
#define SENG_C
#include <stdlib.h>
#include <string.h>
#include <state_engine.h>
#include <ring_stack.h>
#include <state.h>
#include <stdio.h>

r_stack rs;

char hit(State s, char n){
	return s->V > n && n >= 0 && s->states[n];
}

State resolve(seng engine, char* str){
	push(&rs, engine->start);
	while( rs.capacity ){
		State temp = pop(&rs);
		if(temp){
			*str -= temp->offset;
			printf("%d\n", *str);
			switch(temp->opt){
				case FINAL:
					return temp;
				break;
				case OPTIONAL:
					if(hit(temp, *str))
						push(&rs, temp->states[*str++]);
					else{
						*str += temp->offset; /* reset offset */
						push(&rs, temp->aux);
					}
				break;
				default:
					if(hit(temp, *str))
						push(&rs, temp->states[*str++]);
			}
		}
	}
	return NULL;
}

#ifdef STATIC
int main(int argc, char** argv){
	if(argc < 2) fprintf(stderr, "Usage: ex [string]\n"),exit(1);
	int offset = 'a'-1;
	init(&rs, 0x80);

	char str[] = "runcommand";
	int size = strlen(str);
	State state_arr[size + 1]; /* Plus Final state */
	int i = 0;while(i < size + 1){
		State s;
		alloc_state(&s, 26, 'a' - 1);
		state_arr[i++] = s;
	}
	i = 0;while(i < size){
		act(state_arr[i], str[i] - 'a' + 1, state_arr[i+1], 0);
		i++;
	}
	act(state_arr[i], 0, NULL, FINAL);

	seng engine;
	alloc_seng(&engine);
	if(!engine) fprintf(stderr, "Failed to allocate engine.\n"),exit(2);
	use_states(engine, state_arr[0]);

	printf("Test String: %s\n", argv[1]);
	State res = resolve(engine, argv[1]);
	if(!res) fprintf(stderr, "result: failed machine\n");
	else printf("result: %d\n", res->opt);
	/* free_state(s1);
	free_state(s2);
	free_state(s3);
	free_state(s4); */
	i = 0;while(i < size + 1)
		free_state(state_arr[i++]);
	free_stack(&rs);
	free_seng(engine);
	return 0;
}
#endif
#endif
