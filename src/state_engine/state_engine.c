#define SENG_C
#include <stdlib.h>
#include <state_engine.h>
#include <ring_stack.h>
#include <state.h>
#include <stdio.h>

r_stack rs;

char hit(State s, char n){
	if(s->V > n && n >= 0 && s->states[n] )
		return 1;
	return 0;	
}

State resolve(seng engine, char* str){
	char s;
	push(&rs, engine->start);
	while( rs.capacity ){
		State temp = pop(&rs);
		if(temp){
			s = *str - temp->offset;
			printf("%d\n", s);
			switch(temp->opt){
				case FINAL:
					return (!s)? temp : NULL;
				break;
				case OPTIONAL:
					if(hit(temp, s)){
						push(&rs, temp->states[s]);
						str++;
					}else
						push(&rs, temp->aux);
				break;
				default:
					if(hit(temp, s)){
						push(&rs, temp->states[s]);
						str++;
					}
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
	State s1;
	State s2;
	State s3;
	State s4;
	alloc_state(&s1, 4, offset);
	alloc_state(&s2, 10, '0');
	alloc_state(&s3, 4, offset);
	alloc_state(&s4, 1, 0);

	act(s1, 2, s1, 0);
	act(s1, 2, s2, OPTIONAL);

	act(s2, 9, s3, 0);
	act(s2, 9, s3, OPTIONAL);

	act(s3, 3, s4, 0);
	act(s4, 0, NULL, FINAL);

	seng engine;
	alloc_seng(&engine);
	if(!engine) fprintf(stderr, "Failed to allocate engine.\n"),exit(2);
	use_states(engine, s1);

	printf("Test String: %s\n", argv[1]);
	State res = resolve(engine, argv[1]);
	if(!res) fprintf(stderr, "result: failed machine\n");
	else printf("result: %d\n", res->opt);
	free_state(s1);
	free_state(s2);
	free_state(s3);
	free_state(s4);
	free_stack(&rs);
	free_seng(engine);
	return 0;
}
#endif
