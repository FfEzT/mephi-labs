#ifndef LAB5_H
#define LAB5_H

#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WHITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_ONLY_BMP

#include "stb_image.h"
#include "stb_image_write.h"


#define NUMBER_OF_SHADES 5

#define CONVERSION_FACTOR ((double)255 / (NUMBER_OF_SHADES - 1))


void fromColour2bw(unsigned char* res, unsigned char* src,
                             int width, int height);
void fromColour2bwAsm(unsigned char* res, unsigned char* src,
                                int width, int height);

#endif //LAB5_H
