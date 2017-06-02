#include <assert.h>
#include <stdio.h>

#define STACK_MAX_SIZE 3

typedef struct {
    int data[STACK_MAX_SIZE];
    int size;
} Stack;

void push(Stack * stack, int value) {
    if (stack->size == STACK_MAX_SIZE) {
        printf("Stack is full\n");
        return;
    }
    stack->data[stack->size] = value;
    stack->size++;
}

int pop(Stack * stack) {
    if (stack->size == 0) {
        printf("Stack is empty\n");
        return 0;
    }
    stack->size--;
    return stack->data[stack->size];
}

void print(Stack * stack) {
    for (int i = 0; i < stack->size; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

int main() {
    Stack stack;
    stack.size = 0;

    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    push(&stack, 11111); // Stack is full
    assert(stack.size == 3);
    print(&stack); // 1 2 3
    assert(pop(&stack) == 3);
    assert(pop(&stack) == 2);
    push(&stack, 4);
    print(&stack); // 1 4
    assert(pop(&stack) == 4);
    assert(pop(&stack) == 1);
    assert(stack.size == 0);
}