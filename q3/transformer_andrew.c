#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLOR 255

typedef struct {
    int r, g, b;
} Pixel;

void readPPM(Pixel **image, int *width, int *height) {
    char format[3];
    scanf("%2s", format);
    if (strcmp(format, "P3") != 0) {
        fprintf(stderr, "Unsupported format\n");
        exit(1);
    }

    scanf("%d %d", width, height);
    int max_val;
    scanf("%d", &max_val);

    *image = malloc((*width) * (*height) * sizeof(Pixel));
    if (!*image) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < (*width) * (*height); i++) {
        scanf("%d %d %d", &(*image)[i].r, &(*image)[i].g, &(*image)[i].b);
    }
}

void printPPM(Pixel *image, int width, int height) {
    printf("P3\n%d %d\n255\n", width, height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Pixel p = image[i * width + j];
            printf("%d %d %d ", p.r, p.g, p.b);
        }
        printf("\n");
    }
}

void flipImage(Pixel *image, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            int left = i * width + j;
            int right = i * width + (width - j - 1);
            Pixel temp = image[left];
            image[left] = image[right];
            image[right] = temp;
        }
    }
}

void applySepia(Pixel *image, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        int newR = (int)(image[i].r * 0.393 + image[i].g * 0.769 + image[i].b * 0.189);
        int newG = (int)(image[i].r * 0.349 + image[i].g * 0.686 + image[i].b * 0.168);
        int newB = (int)(image[i].r * 0.272 + image[i].g * 0.534 + image[i].b * 0.131);

        image[i].r = (newR > MAX_COLOR) ? MAX_COLOR : newR;
        image[i].g = (newG > MAX_COLOR) ? MAX_COLOR : newG;
        image[i].b = (newB > MAX_COLOR) ? MAX_COLOR : newB;
    }
}

int main(int argc, char *argv[]) {
    int flip = 0, sepia = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            flip = 1;
        } else if (strcmp(argv[i], "-s") == 0) {
            sepia = 1;
        }
    }

    int width, height;
    Pixel *image;
    readPPM(&image, &width, &height);

    if (flip) {
        flipImage(image, width, height);
    }
    if (sepia) {
        applySepia(image, width, height);
    }

    printPPM(image, width, height);
    free(image);
    return 0;
}