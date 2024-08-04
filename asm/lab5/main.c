#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lab5.h"


enum STATUS_CODE {
  OK=0,
  ERROR_USAGE,
  ERROR_OPEN_FILE,
  ERROR_FILE_FORMAT
};

int main (int argc, char *argv[]) {
  if (argc != 3) {
    printf("Incorrect Usage\n");
    return ERROR_USAGE;
  }
  char* src = argv[1];
  char* dst = argv[2];


  int count, height, width;
  unsigned char* loadImage = stbi_load(src, &width, &height, &count, 0);
  if (!loadImage){
      printf ("File not found\n");
      return ERROR_OPEN_FILE;
  }

  printf("%d\n\n", count);

  unsigned char* newImage = malloc(width * height * count);

  clock_t start = clock();
#ifdef ASM//ASM
  fromColour2bwAsm(newImage, loadImage, width, height, count);
#else //C
  fromColour2bw(newImage, loadImage, width, height, count);
#endif
  clock_t finish = clock();
  double time = (double)(finish - start) / CLOCKS_PER_SEC;
  printf ("Time: %20f sec\n", time);


  stbi_write_bmp(dst, width, height, count, newImage);


  free(newImage);
  stbi_image_free(loadImage);

  return OK;
}


void fromColour2bw(unsigned char* res, unsigned char* src,
                             int width, int height, int channels) {
  printf("C\n");

  for (int i = 0; i < channels * height * width; i += channels){
    int sum = 0;
    for (int j = 0; j < channels; ++j) {
      sum += (int)src[i+j];
    }
    double averageValue = (double)(sum) / channels;

    double up  = averageValue/CONVERSION_FACTOR + 0.5;
    int gray = (int)up * (int)CONVERSION_FACTOR;

    for (int j = i; j < i + channels; ++j){
        res[j] = (unsigned char)gray;
    }

  }
}
