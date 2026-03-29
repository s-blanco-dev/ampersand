#include <stdio.h>
#include "global.h"
#include "global.c"

int main(){

  char string[] = "In this lecture we will talk about embebbed systems. For instance, take a car, that could be an embbebed dedive.";

  printf("%s\n", string);

  printf("\n==========\n");

  // string_to_caps
  
  string_to_caps(string);
  printf("%s\n", string);

  printf("\n==========\n");

  // string_to_min

  string_to_min(string);
  printf("%s\n", string);

  printf("\n==========\n");

  // string_length

  int32_t longitud_string = string_length(string);

  printf("%d\n", longitud_string);

  printf("\n=========\n");

  // string_words

  int32_t cantidad_palabras = string_words(string);

  printf("%d\n", cantidad_palabras);

  printf("\n====SWAP====\n");

  // SWAP

  int a = 5;
  int b = 4;

  printf("Elemento 1: %d -> Elemento 2: %d\n", a, b);

  swap(&a, &b, sizeof(int));

  printf("Elemento 1: %d -> Elemento 2: %d\n", a, b);
  
}
