#include <math.h>
#include <stdio.h>

typedef enum {
  EQUILATERO,
  ISOSCELES,
  ESCALENO,
  DESGRACIADO
} TipoTriangulo;

TipoTriangulo tipo_triangulo(float a, float b, float c);

int es_perfecto(int num); 

/* ------------------------------- */

int main(int argc, char *argv[])
{
  printf("%d\n", tipo_triangulo(2, 3, 3));
  es_perfecto(8128);
  return 0;
}

/* ------------------------------- */

TipoTriangulo tipo_triangulo(float a, float b, float c) {
  if (a == b && b == c) {
    return EQUILATERO;
  } else if (a != b && b != c && a != c) {
    return ESCALENO;
  } else if ((a == b && b != c) || (a == c && a != b) || (b == c && b != a)) {
    return ISOSCELES;
  } else {
    // triangulo que no es nada, desgraciado y miserable
    return DESGRACIADO;
  }
}

int es_perfecto(int num) {
  // remando voy hasta la raíz cuadrada del numerongo
  int suma_divisores = 0;
  for (int i = 1; i <= num/2; i++) {
    if (num % i == 0) {
      suma_divisores += i;
    }
  }

  if (suma_divisores == num) {
    printf("ES PERFECTO\n");
    return 1;
  }

  printf("ES HORRIBLE\n");
  return 0;
}
