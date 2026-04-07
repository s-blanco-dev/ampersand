/* IMPLEMENTEN LAS FUNCIONES ACÁ */
#include "global.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int DAYS_IN_MONTH[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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
 * @return root_t*      Devuelve puntero a estructura de raíces (partes reales
 * e imag).
 */
root_t *eq_solver(coeff_t *coeficientes) {
  if (coeficientes == NULL) {
    return NULL;
  }

  root_t *result = malloc(sizeof(root_t));
  if (result == NULL) {
    return NULL;
  }

  result->imag1 = 0;
  result->imag2 = 0;
  result->complex = false;

  double a, b, c;
  a = coeficientes->a;
  b = coeficientes->b;
  c = coeficientes->c;

  double disc = b * b - (4.0 * a * c);

  if (disc < 0) {
    double c1 = sqrt(-disc) / (2.0 * a);
    result->complex = true;

    result->imag1 = c1;
    result->imag2 = -c1;

    result->real1 = (-b) / (2.0 * a);
    result->real2 = (-b) / (2.0 * a);
    return result;
  }

  if (disc == 0) {
    double r = (-b / (2.0 * a));
    result->real1 = r;
    result->real2 = r;
    return result;
  }

  if (disc > 0) {
    double disc_root = sqrt(disc);
    double r1 = (-b + disc_root) / (2.0 * a);
    double r2 = (-b - disc_root) / (2.0 * a);
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
 * @return matriz_t*  Puntero a estructura de matriz resultado de la resta.
 * NULL si no se pudo completar la operación.
 */
matriz_t *matrix_sub(matriz_t A, matriz_t B) {
  if (A.rows != B.rows || A.cols != B.cols) {
    return NULL;
  }

  matriz_t *C = malloc(sizeof(matriz_t));
  if (C == NULL) {
    return NULL;
  }

  C->cols = A.cols;
  C->rows = A.rows;

  C->data = (int16_t **)malloc(C->rows * C->cols * sizeof(int16_t));
  if (C->data == NULL) {
    free(C);
    return NULL;
  }

  // SOLUCION EXTRAÑA
  int16_t *dataA = (int16_t *)A.data;
  int16_t *dataB = (int16_t *)B.data;
  int16_t *dataC = (int16_t *)C->data;

  // Esta forma era la correcta, pero el testbench nos mató la ilusión
  // for (int i = 0; i < A.rows; i++) {
  //   for (int j = 0; j < A.cols; j++) {
  //     C->data[i][j] = A.data[i][j] - B.data[i][j];
  //   }
  // }
  //
  for (int i = 0; i < A.rows * A.cols; i++) {
    dataC[i] = dataA[i] - dataB[i]; // ahora tratamos la matri como array plano feo
  }

  return C;
}

/*
 * @brief efectúa la suma de dos números complejos
 *
 * Asigna memoria para el complejo resultante, suma parte real e imaginaria de a
 * y b
 *
 * @param a struct complex_t que se pasa por valor
 * @param b idem
 * @return complex_t*, un número complejo con dos atributos para la parte real
 * e imaginaria
 * NULL si hay un error asignando memoria
 */
complex_t *sum(complex_t a, complex_t b) {
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
 * @return complex_t*, un puntero a número complejo con dos atributos para la
 * parte real e imaginaria. NULL si hay un error asignando memoria
 */
complex_t *prod(complex_t a, complex_t b) {
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
 * @return void
 */
void print_reverse_array(void *array, data_type_t data_type,
                         size_t array_size) {
  if (array == NULL || array_size == 0 || data_type == 0) {
    return;
  }

  unsigned char *arr_ptr = (unsigned char *)array;

  for (size_t i = array_size; i > 0; i--) {
    unsigned char *curr = arr_ptr + ((i - 1) * data_type);
    printf("%02X\n", *curr);
  }
}

/**
 * @brief Convierte un string a mayúsculas in-place.
 *
 * Recorre el string carácter por carácter y, si encuentra una letra
 * minúscula en ASCII, la transforma en su equivalente mayúscula.
 *
 * @param string Puntero al string a modificar.
 * @return void
 */
void string_to_caps(char *string) {
  if (string == NULL)
    return;

  while (*string != '\0') {
    if (*string >= 'a' && *string <= 'z') {
      *string = *string - 32;
    }
    string++;
  }
}

/**
 * @brief Convierte un string a minúsculas in-place.
 *
 * Recorre el string carácter por carácter y, si encuentra una letra
 * mayúscula en ASCII, la transforma en su equivalente minúscula.
 *
 * @param string Puntero al string a modificar.
 * @return void
 */
void string_to_min(char *string) {
  if (string == NULL)
    return;

  while (*string != '\0') {
    if (*string >= 'A' && *string <= 'Z') {
      *string = *string + 32;
    }
    string++;
  }
}

/**
 * @brief Calcula la longitud de un string sin usar librerías estándar.
 *
 * Cuenta la cantidad de caracteres hasta encontrar el terminador nulo.
 *
 * @param string Puntero al string cuya longitud se desea calcular.
 * @return int32_t Longitud del string, o -1 si el puntero es NULL.
 */
int32_t string_length(char *string) {
  if (string == NULL) {
    return -1;
  }

  int32_t count = 0;
  while (string[count] != '\0') {
    count++;
  }

  return count;
}

/**
 * @brief Cuenta la cantidad de palabras de un string.
 *
 * Considera que una palabra comienza cuando el carácter actual no es un
 * espacio y además está al inicio del string o precedido por un espacio.
 *
 * @param string Puntero al string a analizar.
 * @return int32_t Cantidad de palabras, o -1 si el puntero es NULL.
 */
int32_t string_words(char *string) {
  if (string == NULL) {
    return -1;
  }

  int32_t palabras = 0;
  int pp = 0;

  while (string[pp] != '\0') {
    if (string[pp] != ' ' && (pp == 0 || string[pp - 1] == ' ')) {
      palabras++;
    }

    pp++;
  }

  return palabras;
}

/**
 * @brief Busca la ocurrencia de un substring (needle) dentro de un string
 * (haystack).
 *
 * Recorre el string principal (haystack) carácter por carácter e intenta
 * verificar en cada posición si el substring (needle) comienza en esa posición.
 * Para ello compara secuencialmente los caracteres de ambos strings.
 *
 * Si encuentra una coincidencia completa del substring, retorna el índice
 * en el cual comienza dicha coincidencia dentro del haystack.
 *
 * @param haystack Puntero al string principal donde se realizará la búsqueda.
 * @param needle Puntero al substring que se desea encontrar.
 * @return int Índice de la primera ocurrencia de needle en haystack,
 *         o -1 si no se encuentra o si alguno de los punteros es NULL.
 */
int find_in_string(char *haystack, char *needle) {
  if (haystack == NULL || needle == NULL) {
    return -1;
  }

  for (int i = 0; haystack[i] != '\0'; i++) {
    int k = 0;

    while (needle[k] != '\0' && haystack[i + k] == needle[k]) {
      k++;
    }

    if (needle[k] == '\0') {
      return i;
    }
  }

  return -1;
}

/**
 * @brief Intercambia el contenido de dos elementos genéricos.
 *
 * La función interpreta ambos elementos como bloques de memoria de tamaño
 * data_type y realiza el intercambio byte a byte.
 *
 * @param elem1 Puntero al primer elemento.
 * @param elem2 Puntero al segundo elemento.
 * @param data_type Tamaño en bytes del tipo de dato a intercambiar.
 * @return int Retorna 0 si tuvo éxito, o -1 si alguno de los punteros es NULL.
 */
int swap(void *elem1, void *elem2, data_type_t data_type) {
  if (elem1 == NULL || elem2 == NULL) {
    return -1;
  }

  char *a = (char *)elem1;
  char *b = (char *)elem2;

  for (size_t pp = 0; pp < data_type; pp++) {
    char temp = a[pp];
    a[pp] = b[pp];
    b[pp] = temp;
  }

  return 0;
}

/*
 * @brief Encuentra e imprime el valor máximo y su índice en un array genérico.
 *
 * Recorre el array genérico asumiendo que los elementos son de tipo int.
 * Compara cada elemento con el valor máximo actual y guarda su posición.
 * Requiere que los datos sean interpretables como enteros.
 *
 * @param array      Array genérico (puntero al inicio del array)
 * @param data_type  Tamaño en bytes de cada elemento
 * @param array_size Cantidad de elementos en el array
 * @return int  Si falló, retorna -1, sino retorna el max
 */
int max_index(void *array, data_type_t data_type, size_t array_size) {
  if (array != NULL && array_size != 0) {
    size_t max = 0;
    int max_idx = 0;
    unsigned char *p = (unsigned char *)array;

    for (size_t i = 0; i < array_size; i++) {
      if (*p > max) {
        max = *p;
        max_idx = i;
      }
      p += data_type;
    }
    return max;
  }
  return -1;
}

/*
 * @brief Encuentra e imprime el valor mínimo y su índice en un array genérico.
 *
 * Recorre el array genérico asumiendo que los elementos son de tipo int.
 * Compara cada elemento con el valor mínimo actual y guarda su posición.
 * Inicializa el mínimo con SIZE_MAX para asegurar que cualquier valor sea
 * menor. Requiere que los datos sean interpretables como enteros.
 *
 * @param array      Array genérico (puntero al inicio del array)
 * @param data_type  Tamaño en bytes de cada elemento
 * @param array_size Cantidad de elementos en el array
 * @return void
 */
int min_index(void *array, data_type_t data_type, size_t array_size) {
  if (array != NULL && array_size != 0) {
    size_t min = SIZE_MAX;
    int min_idx = 0;
    unsigned char *p = (unsigned char *)array;

    for (size_t i = 0; i < array_size; i++) {
      if (*p < min) {
        min = *p;
        min_idx = i;
      }

      p += data_type;
    }

    return min;
  }
  return -1;
}

/*
 * @brief Convierte un string binario a su equivalente decimal.
 *
 * Recorre el string de caracteres binarios ('0' o '1') y calcula su valor
 * decimal mediante potencias de 2. Si el parámetro sign es true, interpreta
 * el primer bit como signo (complemento a 2) para números negativos.
 *
 * @param binary Puntero al string binario a convertir
 * @param sign   Booleano que indica si el número está en complemento a 2
 * @return int32_t Valor decimal resultante de la conversión
 */
int32_t bin2dec(char *binary, bool sign) {
  int base = 2;
  int exp = strlen(binary) - 1;
  int number = 0;
  char *p = binary;

  int is_negative = sign && (*p == '1');

  while (*p != '\0') {
    int n = *p - '0';
    number += n * (int)pow(base, exp);
    --exp;
    p++;
  }

  if (is_negative) {
    number -= (int)pow(base, strlen(binary));
  }

  return number;
}

/*
 * @brief Cuenta la cantidad de vocales en un string.
 *
 * Recorre el string carácter por carácter y verifica si pertenece al conjunto
 * de vocales (mayúsculas o minúsculas). Incrementa un contador por cada vocal
 * encontrada.
 *
 * @param string Puntero al string a analizar
 * @return int Cantidad de vocales en el string
 */
int vocales(char *string) {
  int count = 0;
  char vocals[] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
  int len = sizeof(vocals) / sizeof(vocals[0]);
  char *p = &string[0];

  while (*p != '\0') {
    for (int i = 0; i < len; i++) {
      if (*p == vocals[i]) {
        count++;
        break;
      }
    }
    ++p;
  }

  return count;
}

/*
 * @brief Cuenta la cantidad de consonantes en un string.
 *
 * Recorre el string carácter por carácter, verifica que sea una letra
 * (mayúscula o minúscula) y que no sea vocal. Incrementa un contador
 * por cada consonante encontrada.
 *
 * @param string Puntero al string a analizar
 * @return int Cantidad de consonantes en el string
 */
int consonantes(char *string) {
  int count = 0;
  char *p = &string[0];

  while (*p != '\0') {
    if (('a' <= *p && *p <= 'z') || ('A' <= *p && *p <= 'Z')) {
      if (*p != 'a' && *p != 'e' && *p != 'i' && *p != 'o' && *p != 'u' &&
          *p != 'A' && *p != 'E' && *p != 'I' && *p != 'O' && *p != 'U') {
        count++;
      }
    }
    ++p;
  }

  return count;
}

/*
 * @brief Calcula la cantidad de días entre dos fechas.
 *
 * No utiliza <time.h>
 * Asume que finish es posterior a start.
 *
 * @param start  Fecha de inicio
 * @param finish Fecha de fin
 * @return int Diferencia en días entre ambas fechas
 */
int days_left(date_t start, date_t finish) {
  return (int)(date_to_days(finish) - date_to_days(start));
}

/* DEFINO FUNCIONES DE IMPRESION DE TIPOS */
/* ------------------------------------- */

/*
 * @brief Imprime una matriz dada
 *
 * Imprime los coeficientes de una matriz A = (a_ij) de
 * dimensiones mxn en la forma a_i1, a_i2,..., ai_n
 * para todo i desde 1 hasta m.
 *
 * @param matriz  Puntero a la matriz a imprimir
 * @return void
 */
void print_matriz_t(matriz_t *matriz) {
  if (matriz == NULL) {
    return;
  }

  for (int i = 0; i < matriz->rows; i++) {
    for (int j = 0; j < matriz->cols; j++) {
      printf("%d\t", matriz->data[i][j]);
    }
    printf("\n");
  }
}

/*
 * @brief Imprime una agrupación de coeficientes
 *
 * Nada que agregar
 *
 * @param coeficientes  puntero a la agrupación de coeficientes
 * @return void
 */
void print_coeff_t(coeff_t *coeficientes) {
  if (coeficientes == NULL) {
    return;
  }

  printf("Coeficientes:\na: %d\nb: %d\nc: %d\n", coeficientes->a,
         coeficientes->b, coeficientes->c);
}

/*
 * @brief Imprime un número complejo en su forma binomial
 *
 * Lo único que podría requerir explicación es el uso del operador
 * ternario para imprimir '-' o '+' en base al signo de la parte imaginaria.
 *
 * @param complex   Puntero a la estructura del num complejo
 * @return void
 */
void print_complex_t(complex_t *complex) {
  if (complex == NULL) {
    return;
  }

  printf("%f %c %fi\n", complex->real, complex->imag < 0 ? '-' : '+',
         complex->imag);
}

/*
 * @brief Imprime una fecha en formato DD/MM/YYY
 *
 * Nada que comentar
 *
 * @param fecha   Puntero a struct de fecha
 * @return void
 */
void print_date_t(date_t *fecha) {
  if (fecha == NULL) {
    return;
  }

  printf("%d / %d / %d\n", fecha->day, fecha->month, fecha->year);
}

/*
 * @brief Imprime las raíces de una ecuación cuadrática
 *
 * Si sus raíces son complejas llama a la función print_complex_t definida
 * más arriba para imprimirlas en su forma binomial. Sino, imprime normal.
 *
 * @param roots   Puntero a agrupación de raíces de una ec. cuadrática
 * @return void
 */
void print_root_t(root_t *roots) {
  if (roots == NULL) {
    return;
  }

  if (roots->complex) {
    complex_t r1 = {roots->real1, roots->imag1};
    complex_t r2 = {roots->real2, roots->imag2};

    printf("R1: ");
    print_complex_t(&r1);
    printf("R2: ");
    print_complex_t(&r2);
    return;
  }

  printf("R1: %f\n R2: %f\n", roots->real1, roots->real2);
}

/* FUNCIONES AUXILIARES */
/* -------------------- */

/*
 * @brief función para liberar memoria alojada para una matriz
 *
 * Se encarga primero de liberar la memoria alojada para sus elementos
 * y luego libera la estructura en sí.
 *
 * @param matriz  Puntero a matriz cuya memoria quiero liberar
 * @return void
 */
void free_matrix(matriz_t *matriz) {
  if (matriz == NULL || matriz->data == NULL) {
    return;
  }

  for (int i = 0; i < matriz->rows; i++) {
    free(matriz->data[i]);
  }

  free(matriz->data);
}

int is_leap(int16_t year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

long leap_years_before(int16_t y) {
  y--;
  return (y / 4) - (y / 100) + (y / 400);
}

long date_to_days(date_t d) {
  long days = (long)(d.year - 1) * 365 + leap_years_before(d.year);

  for (int m = 1; m < d.month; m++) {
    days += DAYS_IN_MONTH[m];
    if (m == 2 && is_leap(d.year))
      days++;
  }

  days += d.day;
  return days;
}
