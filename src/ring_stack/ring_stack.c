#include <ring_stack.h>
#include <malloc.h>

void init(void** o, unsigned int size){
	*o = malloc(sizeof(r_stack));
	r_stack* rs = (r_stack*)*o;
	rs->capacity = 0;
	rs->size = size;
	rs->stack = malloc(sizeof(item) * size);
	rs->head = rs->stack;
	rs->tail = rs->stack;
	rs->end = rs->stack + rs->size - 1;
}

void free_stack(struct stack* s){
	free(s->stack);
	free(s);
}

static void** next_tail(r_stack* rs){
	return (rs->tail+1 > rs->end)? rs->stack: rs->tail+1;
}

static void** next_head(r_stack* rs){
	return (rs->head+1 < rs->stack)? rs->end: rs->head+1;
}

char push(void* o, item e){
	r_stack* rs = (r_stack*)o;
	if(rs->capacity && rs->tail == rs->head) return 1;
	*rs->tail = e;
	rs->capacity++;
	rs->tail = next_tail(rs);
	return 0;
}

item pop(void* o){
	r_stack* rs = (r_stack*)o;
	if(!rs->capacity && rs->head == rs->tail) return NULL;
	item temp = *rs->head;
	rs->capacity--;
	rs->head = next_head(rs);
	return temp;
}

#ifdef STATIC
#include <stdio.h>
int main(){
	int i;
	char a[] = "a";
	char b[] = "b";
	char c[] = "c";
	char d[] = "d";
	char e[] = "e";
	r_stack* rs;
	init((void**)&rs, 3);
	push(rs, a);
	push(rs, b);
	push(rs, c);
	push(rs, d);
	push(rs, e);
	i = 0;while( i < rs->size ) printf("`%s` ", rs->stack[i++]);
	printf("\n");
	char* res = (char*) pop(rs);
	res = (char*) pop(rs);
	printf("Second out %s\n", res);
	free(rs->stack);
	free(rs);
	return 0;
}
#endif
