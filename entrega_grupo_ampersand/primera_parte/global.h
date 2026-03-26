#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifndef GLOBAL_H
#define GLOBAL_H

/* DECLARACION DE TIPOS */
/* ------------------- */

typedef struct coeff_s {
  int32_t a;
  int32_t b;
  int32_t c;
} coeff_t;

typedef struct root_s {
  int32_t real1;
  int32_t imag1;
  int32_t real2;
  int32_t imag2;
  bool complex;
} root_t;

typedef struct complex_s {
  int32_t real;
  int32_t imag;
} complex_t;

typedef struct date_s {
  int8_t day;
} date_t;

typedef struct matriz_s {
  int16_t** data;
  size_t rows;
  size_t cols;
} matriz_t;

/* DECLARACION DE FUNCIONES */
/* ------------------------ */

void init_lab();

root_t* eq_solver(coeff_t *coeficientes);

int32_t bin2dec(char* binary, bool sign);

void print_reverse_array(void* array, size_t data_type, size_t array_size);

void max_index(void* array, size_t data_type, size_t array_size);

void min_index(void* array, size_t data_type, size_t array_size);

matriz_t* matrix_sub(matriz_t A, matriz_t B);

int swap(void *elem1, void *elem2, size_t data_type);

int consonantes(char *string);

int vocales(char *string);

char* reverse_string(char* string);

int32_t string_length(char *string);

int string_copy(char *source, char *destination);

int find_in_string(char *haystack, char *needle);

void string_to_caps(char *string);

void string_to_min(char *string);

complex_t* sum(complex_t a, complex_t b);

complex_t* prod(complex_t a, complex_t b);

int days_left(date_t start, date_t finish);

#endif // !GLOBAL_H
