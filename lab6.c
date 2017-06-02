#include <assert.h>
#define STACK_MAX_SIZE 3
typedef int T;


typedef struct Stack_tag {
    T data[STACK_MAX_SIZE];
    size_t size;
} Stack_t;


#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101

void push(Stack_t *stack, const T value) {
    if (stack->size >= STACK_MAX_SIZE) {
        exit(STACK_OVERFLOW);
    }
    stack->data[stack->size] = value;
    stack->size++;
}


T pop(Stack_t *stack) {
    if (stack->size == 0) {
        exit(STACK_UNDERFLOW);
    }
    stack->size--;
    return stack->data[stack->size];
}


T peek(const Stack_t *stack) {
    if (stack->size <= 0) {
        exit(STACK_UNDERFLOW);
    }
    return stack->data[stack->size - 1];
}


void printStackValue(const T value) {
    printf("%d", value);
}

void printStack(const Stack_t *stack, void (*printStackValue)(const T)) {
    int i;
    int len = stack->size - 1;
    printf("stack %d > ", stack->size);
    for (i = 0; i < len; i++) {
        printStackValue(stack->data[i]);
        printf(" | ");
    }
    if (stack->size != 0) {
        printStackValue(stack->data[i]);
    }
    printf("\n");
}

int main() {

Stack_t stack;
stack.size = 0;


    struct Stack stack;
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    push(&stack, 11111);
    assert(stack_size(&stack) == 3);
    print(&stack); // 1 2 3
    assert(pop(&stack) == 3);
    assert(pop(&stack) == 2);
    push(&stack, 4);
    print(&stack); // 1 4
    assert(pop(&stack) == 4);
    assert(pop(&stack) == 1);
    assert(stack_size(&stack) == 0);
}