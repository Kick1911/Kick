#ifndef R_STACK_H
#define R_STACK_H

typedef void* item;

typedef struct stack{
	unsigned int size;
	unsigned int capacity;
	item* stack;
	item* head;
	item* tail;
	item* end;
} r_stack;

void init(r_stack*, unsigned int);
char push(r_stack*, item);
item pop(r_stack*);
void free_stack(r_stack*);

#endif
