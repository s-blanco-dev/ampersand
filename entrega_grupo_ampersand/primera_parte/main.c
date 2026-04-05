#include "global.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  init_lab();

  printf("=== TEST 1: Ecuación Cuadrática (Raíces Complejas) ===\n");
  coeff_t coefs = {1, 2, 5}; // x^2 + 2x + 5 = 0 -> Raíces: -1 ± 2i
  root_t *raices = eq_solver(&coefs);
  if (raices) {
    printf("Raiz 1: %.2f + %.2fi\n", raices->real1, raices->imag1);
    printf("Raiz 2: %.2f + %.2fi\n", raices->real2, raices->imag2);
    free(raices);
  }
  printf("\n=== TEST 2: Operaciones Complejas ===\n");
  complex_t c1 = {2.0, 3.0}, c2 = {1.0, -1.0};
  complex_t *s = sum(c1, c2);
  complex_t *p = prod(c1, c2);
  if (s && p) {
    printf("Suma: %.2f + %.2fi\n", s->real, s->imag);
    printf("Prod: %.2f + %.2fi\n", p->real, p->imag);
    free(s);
    free(p);
  }
  printf("\n=== TEST 3: Print Reverse Array (Hexadecimal) ===\n");
  int mi_array[] = {0x11223344, 0x55667788};
  print_reverse_array(mi_array, sizeof(int), 2);
  printf("\n=== TEST 4: Resta de Matrices ===\n");
  matriz_t A, B;
  A.rows = B.rows = 2;
  A.cols = B.cols = 2;
  A.data = malloc(2 * sizeof(int16_t *));
  B.data = malloc(2 * sizeof(int16_t *));
  for (int i = 0; i < 2; i++) {
    A.data[i] = malloc(2 * sizeof(int16_t));
    B.data[i] = malloc(2 * sizeof(int16_t));
    for (int j = 0; j < 2; j++) {
      A.data[i][j] = 10;
      B.data[i][j] = 3;
    }
  }
  matriz_t *res = matrix_sub(A, B);
  if (res) {
    print_matriz_t(res);
  }

  // LIBERO MEMORIA DE CADA MATRIZ
  free_matrix(&A);
  free_matrix(&B);
  free_matrix(res);

  char string[] = "In this lecture we will talk about embebbed systems. For "
                  "instance, take a car, that could be an embbebed devicee.";

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

  printf("\n=== TEST 5: days_left ===\n");
  date_t d1 = {1, 1, 2024};
  date_t d2 = {31, 12, 2024}; // 2024 is a leap year
  date_t d3 = {1, 1, 2023};
  date_t d4 = {31, 12, 2023}; // 2023 is not a leap year
  printf("2024 (bisiesto) Jan 1 -> Dec 31:     %d dias\n", days_left(d1, d2));
  printf("2023 (no bisiesto) Jan 1 -> Dec 31:  %d dias\n", days_left(d3, d4));
  printf("Fechas invertidas (negativo):         %d dias\n", days_left(d2, d1));

  printf("\n=== TEST 6: vocales ===\n");
  printf("'Hello World':     %d vocales\n", vocales("Hello World"));
  printf("'aeiou':           %d vocales\n", vocales("aeiou"));
  printf("'AEIOU':           %d vocales\n", vocales("AEIOU"));
  printf("'bcdfg':           %d vocales\n", vocales("bcdfg"));
  printf("'':                %d vocales\n", vocales(""));

  printf("\n=== TEST 7: consonantes ===\n");
  printf("'Hello World':     %d consonantes\n", consonantes("Hello World"));
  printf("'aeiou':           %d consonantes\n", consonantes("aeiou"));
  printf("'bcdfg':           %d consonantes\n", consonantes("bcdfg"));
  printf("'123!':            %d consonantes\n", consonantes("123!"));

  printf("\n=== TEST 8: max_index / min_index ===\n");
  int nums[] = {3, 7, 1, 9, 4};
  printf("Array: {3, 7, 1, 9, 4}\n");
  printf("Max -> ");
  max_index(nums, sizeof(int), 5);
  printf("\n");
  printf("Min -> ");
  min_index(nums, sizeof(int), 5);
  printf("\n");

  printf("\n=== TEST 9: bin2dec ===\n");
  printf("'1010' sin signo:  %d\n", bin2dec("1010", false));
  printf("'0110' sin signo:  %d\n", bin2dec("0110", false));
  printf("'1010' con signo:  %d\n", bin2dec("1010", true));
  printf("'0110' con signo:  %d\n", bin2dec("0110", true));
  printf("'11111111' con signo: %d\n", bin2dec("11111111", true));

  return 0;
}
