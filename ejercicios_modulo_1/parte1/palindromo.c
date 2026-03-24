#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int get_digits_number(int num); 

int palindrete(int num); 
int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Te faltó algo, flaco\n");
    return -1;
  }
  int num = atoi(argv[1]);
  palindrete(num);
  return 0;
}

/* Determina si un entero es palíndromo o no
 * Recibe un int por parámetro
 * Devuelve 0 si no es palíndromo
 * Devuelve 1 si es palíndromo
 * */
int palindrete(int num) {
  int digitsNum = get_digits_number(num);

  // asumo que los negativos no valen
  if (digitsNum < 0) {
    return 0;
  }

  // dos indices, uno apunta al digito actual desde izq
  // otro apunta al digito actual desde la derecha
  int reverseIndex = digitsNum-1;
  int currentDigit, currentDigitReverse;
  int izq, der;

  // básicamente van comparando simetría. Parten desde el primer y último dígito
  // avanzan hasta el dígito del medio, si encuentran discrepancia, no es palíndromo
  for (int i = 0; i < digitsNum/2; i++) {
    currentDigit = (num / (int)pow(10, digitsNum - 1 - i)) % 10;
    currentDigitReverse = (num / (int)pow(10, i)) % 10;

    if (currentDigitReverse != currentDigit) {
      printf("%d NO ES PALENDRE\n", num);
      return 0;
    }
  }
  
  printf("%d ES PALINDRO\n", num);
  return 1;
}

// Función auxiliar para obtener cantidad de dígitos de un entero
int get_digits_number(int num) {
  int quant = 1;
  for (int i = num; i >= 10; i = i/10) {
    quant += 1;
  }
  return quant;
}
