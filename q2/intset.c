#include <stdio.h>
#include <stdlib.h>

//each set must be allocated using malloc and freed, respectively
//they both must accept input with NO whitespace in it, gonna try scanf again!

struct set {
    int *arr;
    int size;
    int cap;
};

struct set *create_set() {
    struct set *s = malloc(sizeof(struct set));
    s->cap = 4;
    s->size = 0;
    s->arr = malloc(sizeof(int)*s->cap);
    return s;
}

int is_element(struct set *s, int element) { //returns 1 if it is an element, 0 if it isn't
    for(int i = 0; i < s->size; ++i) if (s->arr[i] == element) return 1;
    return 0;
}

void add(struct set *s, int num) {
    if (!is_element(s, num)) { //if its not already an element
        if(s->size == s->cap) { // we need to double the capacity of the set
            int *new_arr = malloc(sizeof(int)*s->cap*2);
            for(int i = 0; i < s->size; ++i) {
                new_arr[i] = s->arr[i];
            }
            free(s->arr);
            s->arr = new_arr;
            s->cap *= 2;
        }
        int i = s->size-1;
        while (i >= 0 && s->arr[i] > num) {
            s->arr[i + 1] = s->arr[i];
            i--;
        }
        s->arr[i+1] = num;
        ++s->size;
    }
}

void rem(struct set *s, int num) {
    if(is_element(s, num)) {
        int *new_arr = malloc(sizeof(int)*s->cap);
        for(int i = 0, j = 0; i < s->size; ++i) {
            if(s->arr[i] != num) {
                new_arr[j] = s->arr[i];
                ++j;
            }
        }
        free(s->arr);
        s->arr = new_arr;
        --s->size;
    }
}

void intersect(struct set *s1, struct set *s2) { //assume s1 and s2 have n elements each. this means O(n^2) time...
    if(s1->size && s2->size) { //only execute if both are non-empty
        struct set *min_set = (s1->size < s2->size) ? s1 : s2;
        struct set *other_set = (s1->size >= s2->size) ? s1 : s2; //make sure that this is the proper logical negation
        int first = 1;
        for(int i = 0; i < min_set->size; ++i) {
            if(is_element(other_set, min_set->arr[i])) {
                if(!first) {
                    printf(" ");
                }
                printf("%d", min_set->arr[i]);
                first = 0;
            }
        }
        if(!first) printf("\n"); //added to make sure that we dont print an extra newline whne the intersect is empty
    }
}

//SIMPLIFY THIS!!
void unionize(struct set *s1, struct set *s2) { //prints the elements of both sets in order. note that the union make have duplicates
    if(s1->size || s2->size) { //only execute if at least one is non-empty
        int i = 0; int j = 0;
        int first = 1;
        while (i < s1->size && j < s2->size) {
            if(s1->arr[i] < s2->arr[j]) {
                if(!(first)) {
                    printf(" ");
                }
                printf("%d", s1->arr[i]);
                ++i;
                first = 0;
            } else if (s1->arr[i] > s2->arr[j]){
                if(!(first)) {
                    printf(" ");
                }
                printf("%d", s2->arr[j]);
                ++j;
                first = 0;
            } else if (s1->arr[i] == s2->arr[j]){
                if(!(first)) {
                    printf(" ");
                }
                printf("%d", s1->arr[i]);
                ++i;
                ++j;
                first = 0;
            }
        }
        while (i < s1->size) {
            if(!(first)) {
                printf(" ");
            }
            printf("%d", s1->arr[i]);
            ++i;
            first = 0;
        }
        while (j < s2->size) {
            if(!(first)) {
                printf(" ");
            }
            printf("%d", s2->arr[j]);
            ++j;
            first = 0;
        }
        printf("\n");
    }
}

void print_set(struct set *s) {
    if(s->size) {
        int first = 1;
        for(int i = 0; i < s->size; ++i) {
            if(!first) {
                printf(" ");
            }
            printf("%d", s->arr[i]);
            first = 0;
        }
        printf("\n");
    }
}


int main() { //I see why abstraction is a useful concept...
    char c = '\0';
    int d;
    struct set *x = create_set();
    struct set *y = create_set();
    while(!feof(stdin)) {
        scanf(" %c", &c);
        if(c == 'a') {
            scanf(" %c", &c);
            if(c == 'x') {
                if(scanf("%d", &d) == 1) {
                    add(x, d);
                }

            } else if (c == 'y') {
                if (scanf("%d", &d) == 1) {
                    add(y, d);
                }
            }
        } else if (c == 'r') {
            scanf(" %c", &c);
            if(c == 'x') {
                if(scanf("%d", &d) == 1) {
                    rem(x, d);
                }

            } else if (c == 'y') {
                if(scanf("%d", &d) == 1) {
                    rem(y, d);
                }
            }
        } else if (c == 'p') {
            scanf(" %c", &c);
            if(c == 'x') {
                print_set(x);
            } else if (c == 'y') {
                print_set(y);
            }
        }
        else if (c == 'u') {
            unionize(x, y);
        }
        else if (c == 'i') {
            intersect(x, y);
        }
        else if (c == 'q') {
            break;
        }
    }
    free(x->arr);
    free(x);
    free(y->arr);
    free(y);
    return 0;
}