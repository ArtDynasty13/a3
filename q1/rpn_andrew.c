#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 4

typedef struct {
    int *data;
    int size;
    int capacity;
} Stack;

void init_stack(Stack *stack) {
    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;
    stack->data = (int *)malloc(sizeof(int) * stack->capacity);
}

void free_stack(Stack *stack) {
    free(stack->data);
}

void resize_stack(Stack *stack) {
    stack->capacity *= 2;
    stack->data = (int *)realloc(stack->data, sizeof(int) * stack->capacity);
}

void push(Stack *stack, int value) {
    if (stack->size == stack->capacity) {
        resize_stack(stack);
    }
    stack->data[stack->size++] = value;
}

int pop(Stack *stack) {
    if (stack->size == 0) {
        return -1;
    }
    return stack->data[--stack->size];
}

int is_operator(char c) {
    return c == 'p' || c == 's' || c == '*' || c == '/';
}

int apply_operator(int operand1, int operand2, char operator) {
    switch (operator) {
        case 'p': return operand1 + operand2;
        case 's': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default:
            fprintf(stderr, "letts go %c\n", operator);
            return -1;
    }
}

int main() {
    Stack stack;
    init_stack(&stack);

    size_t buffer_size = 1000;
    char *expression = (char *)malloc(buffer_size * sizeof(char));
    size_t length = 0;

    while (fgets(expression + length, buffer_size - length, stdin)) {
        length += strlen(expression + length);
        if (expression[length - 1] == '\n') break;

        buffer_size *= 2;
        expression = (char *)realloc(expression, buffer_size * sizeof(char));
    }

    if (length == 0 || (length == 1 && expression[0] == '\n')) {
        printf("0\n");
        free_stack(&stack);
        free(expression);
        return 0;
    }

    char *token = strtok(expression, " \t\n");
    while (token != NULL) {
        if (is_operator(token[0])) {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            int result = apply_operator(operand1, operand2, token[0]);
            if (result == -1) {
                free_stack(&stack);
                free(expression);
                return 0;
            }
            push(&stack, result);
        } else {
            int operand = atoi(token);
            push(&stack, operand);
        }
        token = strtok(NULL, " \t\n");
    }

    if (stack.size > 1) {
        fprintf(stderr, "Letts go\n");
        printf("1\n");
    } else {
        printf("%d\n", pop(&stack));
    }

    free_stack(&stack);
    free(expression);
    return 0;
}