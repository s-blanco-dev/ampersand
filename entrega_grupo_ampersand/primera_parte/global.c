/* IMPLEMENTEN LAS FUNCIONES ACÁ */
#include "global.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void init_lab() {
  printf("AMPERSAND:\nSantiago Blanco\nFelipe Paladino\nPiero Saucedo\n");
}

/*
 * @brief Resuelve una ecuación cuadrática de coeficientes enteros 
 * permitiendo raíces complejas
 *
 * El lector ya está familiarizado con la resolución de ecuaciones cuadráticas.
 *
 * @param coeficientes      Puntero a estructura de coeficientes enteros a,b,c.
 * * @return root_t*      Devuelve puntero a estructura de raíces (partes reales e imag).
 */
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

/* 
 * @brief Efectúa la resta de dos matrices A y B, ambas de dimensión mxn.
 *
 * Verifica que ambas matrices sean de la misma dimensión, reserva memoria
 * dinámica para la struct de la matriz resultante y sus datos. Luego itera
 * sobre cada coeficiente efectuando la resta entre ambos. Operación de 
 * complejidad temporal cuadrática -> O(n^2).
 *
 * @param A   matriz_t que se pasa por valor, se le restará B
 * @param B   matriz_t que se pasa por valor, será restada a A
 * * @return matriz_t*  Puntero a estructura de matriz resultado de la resta.
 * * NULL si no se pudo completar la operación.
 * */
matriz_t* matrix_sub(matriz_t A, matriz_t B){
  /* La suma de matrices para dos matrices A y B de mxn resulta en una matriz
   * C de mxn donde cada entrada c_ij = a_ij + b_ij
   * --> Evidentemente, la resta se define de manera análoga */

  if (A.rows != B.rows || A.cols != B.cols) {
    // NO SE PUEDEN SUMAR DOS MATRICES DE DIMENSIONES DISTINTAS
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
  for (int i = 0; i < C->rows; i++) {
    C->data[i] = malloc(C->cols * sizeof(int16_t)); 
  }
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


/*
 * @brief efectúa la suma de dos números complejos
 *
 * Asigna memoria para el complejo resultante, suma parte real e imaginaria de a y b
 *
 * @param a struct complex_t que se pasa por valor
 * @param b idem
 * * @return complex_t*, un número complejo con dos atributos para la parte real e imaginaria 
 * * NULL si hay un error asignando memoria
 * */
complex_t* sum(complex_t a, complex_t b){
  complex_t *result = malloc(sizeof(complex_t));
  if (result == NULL) {
    return NULL;
  }

  result->imag = a.imag + b.imag;
  result->real = a.real + b.real;

  return result;
}

/*
 * @brief efectúa el producto de dos números complejos
 *
 * Asigna memoria para el complejo resultante, básicamente realiza una operación
 * distributiva teniendo en cuenta que i^2 = -1
 *
 * @param a struct complex_t que se pasa por valor
 * @param b idem
 * * @return complex_t*, un puntero a número complejo con dos atributos para la 
 * * parte real e imaginaria. NULL si hay un error asignando memoria
 * */
complex_t* prod(complex_t a, complex_t b){
  complex_t *result = malloc(sizeof(complex_t));
  if (result == NULL) {
    return NULL;
  }

  result->real = (a.real * b.real) - (a.imag * b.imag);
  result->imag = (a.real * b.imag) + (a.imag * b.real);

  return result;
}

/*
 * @brief imprime el array en orden inverso usando un puntero genérico
 *
 * Recorre un array genérico desde el último al primer elemento imprimiendo
 * su contenido en hexadecimal. Como es de tipo void*, necesita el tamaño 
 * de cada elemento para poder iterar correctamente.
 *
 * @param array   Array genérico (puntero al inicio del array)
 * @param data_type  tamaño del tipo de dato 
 * @param array_size  cantidad de elementos 
 * * @return void
 * */
void print_reverse_array(void* array, size_t data_type, size_t array_size){
  if (array == NULL || array_size == 0 || data_type == 0) {
    return;
  }

  unsigned char* arr_ptr = (unsigned char*) array; // camina de a 1 byte ahora

  for (size_t i = array_size; i > 0; i--) {
    unsigned char* curr = arr_ptr + ((i-1)*data_type); 
    // ante la incertidumbre, imprimo lo que haya adentro en hexa 
    // temporal
    printf("%02X\n", *(arr_ptr + i));
  }
}

/* DEFINO FUNCIONES DE IMPRESION DE TIPOS */
/* ------------------------------------- */

void print_matriz_t(matriz_t *matriz){
  for (int i = 0; i < matriz->rows; i++) {
    for (int j = 0; j < matriz->cols; j++) {
      printf("%d\t", matriz->data[i][j]);
    }
    printf("\n");
  }
}
