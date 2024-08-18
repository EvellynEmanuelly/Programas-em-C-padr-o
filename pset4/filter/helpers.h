#ifndef HELPERS_H
#define HELPERS_H

#include "bmp.h"

// Protótipos das funções

int cap(int value);

void grayscale(int height, int width, RGBTRIPLE image[height][width]);
void reflect(int height, int width, RGBTRIPLE image[height][width]);
void blur(int height, int width, RGBTRIPLE image[height][width]);
void edges(int height, int width, RGBTRIPLE image[height][width]);

#endif // HELPERS_H
