#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DO NOT FORGET TO FREE MEMORY

struct pixel {
    int r, g, b;
};

struct image {
    int width, height;
    struct pixel **arr;
};

struct image *create_image() { //check amount of whitespace
    struct image *new_image = malloc(sizeof(struct image));

    char c;
    // Consume characters until "P3" is found
    while ((c = getchar()) != EOF) {
        if (c == 'P') {
            if ((c = getchar()) == '3') {
                break; // Found "P3"
            }
        }
    }

    // Consume all digits after "P3" (e.g., "4444")
    while ((c = getchar()) != EOF) {
        if (c < '0' || c > '9') {
            break; // Stop when a non-digit is encountered
        }
    }

    // Consume all non-digit characters until the first number
    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9') {
            ungetc(c, stdin); // Put the first digit back into the input stream
            break;
        }
    }

    scanf("%d %d", &new_image->width, &new_image->height);
    new_image->arr = malloc(sizeof(struct pixel *) * new_image->height); //dynamically allocate some row pointers
    for(int i = 0; i < new_image->height; ++i) {
        new_image->arr[i] = malloc(sizeof(struct pixel) * new_image->width); //for each row, allocate pixels, upto the last row
    }

    int max;
    scanf("%d", &max);
    return new_image; // READ 256
}

void read_image(struct image *img) {
    // cycle holds the last successfully read values for each channel.
    int cycle[3] = {0, 0, 0};
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            int r, g, b;
            if (scanf("%d", &r) == 1)
                cycle[0] = r;
            else
                r = cycle[0];
            if (scanf("%d", &g) == 1)
                cycle[1] = g;
            else
                g = cycle[1];
            if (scanf("%d", &b) == 1)
                cycle[2] = b;
            else
                b = cycle[2];
            img->arr[i][j].r = r;
            img->arr[i][j].g = g;
            img->arr[i][j].b = b;
        }
    }
}


void print_image(struct image *current_image) {
    printf("P3\n");
    printf("%d %d\n", current_image->width, current_image->height);
    printf("255\n");
    for(int h = 0; h < current_image->height; ++h) {
        for(int w = 0; w < current_image->width; ++w) {
            printf("%d %d %d ", current_image->arr[h][w].r, current_image->arr[h][w].g, current_image->arr[h][w].b);
        }
        printf("\n");
    }
}

int min(int x, int y) {
    if (x < y) {
        return x;
    }else {
        return y;
    }
}

void sepia(struct image *current_image) {
    for(int h = 0; h < current_image->height; ++h) {
        for(int w = 0; w < current_image->width; ++w) {
            int old_r = current_image->arr[h][w].r, old_g = current_image->arr[h][w].g, old_b = current_image->arr[h][w].b;
            current_image->arr[h][w].r = min(255, old_r*0.393 + old_g*0.769 + old_b*0.189);
            current_image->arr[h][w].g = min(255, old_r*0.349 + old_g*0.686 + old_b*0.168);
            current_image->arr[h][w].b = min(255, old_r*0.272 + old_g*0.534 + old_b*0.131);
        }
    }
}

void flip_image(struct image *current_image) { //GO THROUGH THIS
    for(int h = 0; h < current_image->height; ++h) {
        struct pixel *new_row = malloc(sizeof(struct pixel) * current_image->width);
        for(int w = 0; w < current_image->width; ++w) {
            new_row[w] = current_image->arr[h][current_image->width - 1 - w];  // Swap left & right
        }
        free(current_image->arr[h]); // Free old row memory
        current_image->arr[h] = new_row; // Assign the flipped row
    }
}


int main(int argc, char *argv[]) {
    struct image *new_image = create_image();
    read_image(new_image);
    for(int i = 1; i < argc; ++i) {
        if(strcmp(argv[i], "-s") == 0) {
            sepia(new_image);
        }
        else if(strcmp(argv[i], "-f") == 0) {
            flip_image(new_image);
        }
    }
    print_image(new_image);
    for(int i = 0; i < new_image->height; ++i) {
        free(new_image->arr[i]);
    }
    free(new_image->arr);
    free(new_image);

}