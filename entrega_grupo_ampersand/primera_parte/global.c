/* IMPLEMENTEN LAS FUNCIONES ACÁ */
#include "global.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/* Resuelve ecuación cuadrática admitiendo raíces complejas. */
root_t* eq_solver(coeff_t *coeficientes) {
  if (coeficientes == NULL) {
    return NULL;
  }

  root_t* result = malloc(sizeof(root_t));
  if (result == NULL) {
    // falleció malloc
    return NULL;
  }

  /* por defecto inicializo el resultado con raíces reales
   * (parte imaginaria 0) */
  result->imag1 = 0;
  result->imag2 = 0;
  result->complex = false;

  float a, b, c;
  a = coeficientes->a;
  b = coeficientes->b;
  c = coeficientes->c;

  float disc = b*b - (4.0 * a * c);
  if (disc < 0) {
    float c1 = sqrt(-disc) / (2.0*a);
    result->complex = true;

    result->imag1 = c1;
    result->imag2 = -c1;

    result->real1 = (-b) / (2.0*a);
    result->real2 = (-b) / (2.0*a);
    return result;
  }

  if (disc == 0) {
    float r = (-b / (2.0*a));
    result->real1 = r;
    result->real2 = r;
    return result;
  }

  if (disc > 0) {
    float disc_root = sqrt(disc);
    float r1 = (-b + disc_root) / (2.0*a);
    float r2 = (-b - disc_root) / (2.0*a);
    result->real1 = r1;
    result->real2 = r2;
    return result;
  }

  return NULL;
}

/* Co-autores: Gilbert Strang, José Job Flores */
matriz_t* matrix_sub(matriz_t A, matriz_t B){
  /* La suma de matrices para dos matrices A y B de mxn resulta en una matriz
   * C de mxn donde cada entrada c_ij = a_ij + b_ij
   * --> Evidentemente, la resta se define de manera análoga */

  if (A.rows != B.rows || A.cols != B.cols) {
    // NO SE PUEDEN SUMAR DOS MATRICES DE DIMENSIONES DISTINTAS
    // el usuario es un nabo
    return NULL;
  }

  matriz_t* C = malloc(sizeof(matriz_t));
  if (C == NULL) {
    return NULL;
  }

  C->cols = A.cols;
  C->rows = A.rows;

  // pido espacio para las entradas de la matriz
  C->data = malloc(C->rows * sizeof(int16_t*));
  if (C->data == NULL) {
    return NULL;
  }

  // O(n^2)
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.cols; j++) {
      C->data[i][j] = A.data[i][j] - B.data[i][j]; 
    }
  }

  return C;
}


complex_t* sum(complex_t a, complex_t b){
  complex_t *result = malloc(sizeof(complex_t*));
  if (result == NULL) {
    return NULL;
  }

  result->imag = a.imag + b.imag;
  result->real = a.real + b.real;

  return result;
}

complex_t* prod(complex_t a, complex_t b){
  complex_t *result = malloc(sizeof(complex_t*));
  if (result == NULL) {
    return NULL;
  }

  result->real = (a.real * b.real) - (a.imag * b.imag);
  result->imag = (a.real * b.imag) + (a.imag * b.real);

  return result;
}

void print_reverse_array(void* array, size_t data_type, size_t array_size){
  if (array == NULL || array_size == 0 || data_type == 0) {
    return;
  }

  unsigned char* arr_ptr = (unsigned char*) array; // camina de a 1 byte ahora

  for (size_t i = array_size; i >= 0; i--) {
    void* curr = arr_ptr + ((i-1)*data_type); 

    // chanchada, embarrada, desastre, engrasada, enchastre, salame
    if (data_type == 4) {
      printf("%d\n", *(int*) curr);
    }
  }
}
