#include"stack.h"

Stack *new_stack(){
	Stack *st = (Stack*)malloc(sizeof(Stack));
	st->sommet = -1;
	return st;
}

int is_empty(Stack st){
	return st.sommet == -1;
}
void push(int x,Stack *st){
	(st->sommet)++;
	st->pile[st->sommet]=x;
}

int top(Stack st){
	return st.pile[st.sommet];
}

void pop(Stack *st){
	(st->sommet)--;
}


