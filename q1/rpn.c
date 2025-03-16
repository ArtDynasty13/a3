//RECHECK VALGRIND BEFORE SUBMITTING AND ALSO DO ALL THE COMPILATION FLAGS!!!!!!!!!!!!
//WILL THERE BE ANY CASES WHERE SCANF FAILS?
#include <stdio.h>
#include <stdlib.h>

//We are going to create a dynamically allocated stack using malloc, using a struct. Don't forget to free it!
//This needs to work for negative input
//This needs to work for arbitrary amounts of whitespace...
//We loop until EOF

struct stack{
    int *arr; //this will be our array
    int size;
    int cap;
};

struct stack *create_stack() {
    struct stack *st = malloc(sizeof(struct stack)); //DO NOT FORGET TO ALLOCATE SPACE FOR THE STRUCT ITSELF
    st->cap = 4;
    st->arr = malloc(sizeof(int)*st->cap);
    st->size = 0;
    return st;
}

int pop(struct stack *st) {
    //ideally this should be gracefully handled for empty arrays.
    return st->arr[--st->size];
}

void push(struct stack *st, int num) { //this will need to handle our doubling logic!!, check if we need a pointer to a pointer here
    if(st->size == st->cap) { //we need to double the array
        int *new_arr = malloc(sizeof(int)*st->cap*2);
        for(int i = 0; i < st->size; ++i) {
            new_arr[i] = st->arr[i];
        }
        free(st->arr);
        st->arr = new_arr;
        st->cap *= 2;
    }
    st->arr[st->size++] = num;
}

int calculate(int num1, int num2, char operator) {
    if(operator == 'p') return num1 + num2;
    else if (operator == 's') return num1 - num2;
    else if (operator == '*') return num1 * num2;
    else if (operator == '/') return num1 / num2;
    else return 0; //this is an ERROR
    //fprintf(stderr, "Operator not recognized.");
}

void print_array(struct stack *st) {
    for(int i = 0; i < st->size; ++i) printf("%d ", st->arr[i]);
}

int main() {
    struct stack *st = create_stack();
    //scan for integers and add them to the stack, irrespective of whitespace. Let's try scanf first and see how that goes.

    while(1) {
        int x;
        char c;
        if(scanf("%d", &x) == 1) { //we got a number in! recall that it wont absorb non-ints
            push(st, x);
        }
        else if(scanf(" %c", &c) == 1) { //we got a char in! YOU MUST CHECK THAT IT IS EQUAL TO 1
            int num1 = pop(st);
            int num2 = pop(st);
            push(st, calculate(num2, num1, c));
        }
        else if(feof(stdin)) break;
    }
    //if(st->size != 1) printf("Invalid input\n");
    printf("%d\n", *st->arr);
    free(st->arr);
    free(st);
}