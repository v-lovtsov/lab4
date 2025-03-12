#include <stdlib.h>
#include <stdio.h>

#ifndef stack_h
#define stack_h

typedef struct Element {
    int data;
    struct Element * next;
} Element;

typedef struct Stack {
    Element * top;
} Stack;

Stack * initStack() {
    Stack * stack = (Stack *)malloc(sizeof(Stack));
    return stack;
}

int isEmpty(Stack * stack) {
    return stack->top == NULL;
}

void push(Stack * stack, int value) {
    Element * newElement = (Element *)malloc(sizeof(Element));

    if (newElement == NULL)
        return;

    newElement->data = value;
    newElement->next = stack->top;
    stack->top = newElement;
}

int pop(Stack * stack) {
    if (isEmpty(stack))
        exit(0);

    Element * temp = stack->top;
    int data = temp->data;
    stack->top = stack->top->next;
    free(temp);

    return data;
}

int tops(Stack * stack) {
    if (isEmpty(stack))
        exit(0);

    return stack->top->data;
}

void freeStack(Stack * stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
}


#endif