#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef GLOBAL_H
#define GLOBAL_H

extern const int DAYS_IN_MONTH[];

typedef enum data_type_t {
    TYPE_INT8,
    TYPE_INT32,
    TYPE_FLOAT,
    TYPE_DOUBLE,
} data_type_t;

/* DECLARACION DE TIPOS */
/* ------------------- */

typedef struct coeff_s {
    int32_t a;
    int32_t b;
    int32_t c;
} coeff_t;

typedef struct root_s {
    double real1;
    double imag1;
    double real2;
    double imag2;
    bool complex;
} root_t;

typedef struct complex_s {
    int32_t real;
    int32_t imag;
} complex_t;

typedef struct date_s {
    int8_t day;
    int8_t month;
    int16_t year;
} date_t;

typedef struct matriz_s {
    int16_t **data;
    size_t rows;
    size_t cols;
} matriz_t;

/* DECLARACION DE FUNCIONES */
/* ------------------------ */

void init_lab();

root_t *eq_solver(coeff_t *coeficientes);

int32_t bin2dec(char *binary, bool sign);

void print_reverse_array(void *array, data_type_t data_type, size_t array_size);

int max_index(void *array, data_type_t data_type, size_t array_size);

int min_index(void *array, data_type_t data_type, size_t array_size);

matriz_t *matrix_sub(matriz_t A, matriz_t B);

int swap(void *elem1, void *elem2, data_type_t data_type);

int consonantes(char *string);

int vocales(char *string);

char *reverse_string(char *string);

int32_t string_length(char *string);

int string_copy(char *source, char *destination);

int string_words(char *string);

int find_in_string(char *haystack, char *needle);

void string_to_caps(char *string);

void string_to_min(char *string);

complex_t *sum(complex_t a, complex_t b);

complex_t *prod(complex_t a, complex_t b);

int days_left(date_t start, date_t finish);

/* FUNCIONES PARA IMPRIMIR TIPOS POR PANTALLA */
/* ------------------------------------------ */

void print_matriz_t(matriz_t *matriz);
void print_coeff_t(coeff_t *coeficientes);
void print_root_t(root_t *roots);
void print_complex_t(complex_t *complex);
void print_date_t(date_t *fecha);

/* FUNCIONES AUXILIARES */
/* -------------------- */

void free_matrix(matriz_t *matriz);
int is_leap(int16_t year);
long date_to_days(date_t d);
size_t data_type_size(data_type_t dt);

#endif // !GLOBAL_H
