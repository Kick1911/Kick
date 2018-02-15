#ifndef STACK_H
#define STACK_H

typedef void* item;

struct stack{
	unsigned int size;
	unsigned int capacity;
	item* stack;
	item* head;
	item* tail;
	item* end;
};
typedef struct stack r_stack;

void init(void**, unsigned int);
char push(void*, item);
item pop(void*);
void free_stack(struct stack*);

#endif
