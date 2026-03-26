/* IMPLEMENTEN LAS FUNCIONES ACÁ */
#include "global.h"
#include <cstdlib>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* Resuelve ecuación cuadrática admitiendo raíces complejas. */
root_t* eq_solver(coeff_t *coeficientes) {
  root_t* result = malloc(sizeof(root_t));

  /* por defecto inicializo el resultado con raíces reales
   * (parte imaginaria 0) */
  result->imag1 = 0;
  result->imag2 = 0;
  result->complex = false;

  int32_t a, b, c;
  a = coeficientes->a;
  b = coeficientes->b;
  c = coeficientes->c;

  float disc = b*b - (4.0 * a * c);
  if (disc < 0) {
    float c1 = sqrt(-disc) / (2*a);
    result->complex = true;

    result->imag1 = c1;
    result->imag2 = -c1;

    result->real1 = (-b) / (2*a);
    result->real2 = (-b) / (2*a);
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
  C->cols = A.cols;
  C->rows = A.rows;

  // pido espacio para las entradas de la matriz
  C->data = malloc(C->rows * sizeof(int16_t*));

  // O(n^2)
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.cols; j++) {
      C->data[i][j] = A.data[i][j] - B.data[i][j]; 
    }
  }

  return C;
}


complex_t* sum(complex_t a, complex_t b){

}

complex_t* prod(complex_t a, complex_t b);
