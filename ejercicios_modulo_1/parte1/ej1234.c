#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Complex {
  float Re; // parte real
  float Im; // parte imaginaria
} Complex; 

/* Dado que los reales están incluidos en los complejos, 
 * puedo representar cualquier real como un complejo z 
 * sin parte imaginaria, es decir Im(z) = 0 */
typedef struct Result {
  Complex r1;
  Complex r2;
} Result;

typedef struct Equation {
  float a, b, c;
} Equation;

void solve(Equation* eq, Result* result);

int bin_to_dec(char* binum); 

void type_size() {
  printf("char: %d\n", sizeof(char));
  printf("unsigned char: %d\n", sizeof(unsigned char));
  printf("short: %d\n", sizeof(short));
  printf("unsigned short: %d\n", sizeof(unsigned short));
  printf("int: %d\n", sizeof(int));
  printf("unsigned int: %d\n", sizeof(unsigned int));
  printf("unsigned long: %d\n", sizeof(unsigned long));
  printf("long: %d\n", sizeof(long));
  printf("float: %d\n", sizeof(float));
  printf("double: %d\n", sizeof(double));
}

/* ----------------------------------- */

int main(int argc, char *argv[])
{
  printf("hello world\n");
  char* ni = "10101";

  if (argc < 4) {
    printf("Te faltó algo\n");
    return -1;
  }

  int a, b, c;
  // obtengo cada coeficiente como argumento del programa
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  c = atoi(argv[3]);


  // creo una ecuación y le asigno los coeficientes
  Equation* eq = malloc(sizeof(Equation));
  eq->a = a;
  eq->b = b;
  eq->c = c;

  // uuuu, complejos
  Result* res = malloc(sizeof(Result));

  solve(eq, res);
  printf("R1:\n Re(z) = %f \n Im(z) = %f\n", res->r1.Re, res->r1.Im);  
  printf("R2:\n Re(z) = %f \n Im(z) = %f\n", res->r2.Re, res->r2.Im);  
  printf("Binario: %s\nDecimal: %d\n", ni, bin_to_dec(ni));

  // no quiero fugas
  free(eq);
  free(res);
}

/* ----------------------------------- */

void solve(Equation* eq, Result* result) {
  float a,b,c;
  a = eq->a;
  b = eq->b;
  c = eq->c;

  // por defecto inicializo el resultado con raíces reales
  result->r1.Im = 0;
  result->r2.Im = 0;

  float disc = b*b - (4.0 * a * c);
  if (disc < 0) {
    float c1 = sqrt(-disc) / (2*a);
    result->r1.Im = c1;
    result->r2.Im = - c1;
    result->r1.Re = (-b) / (2*a);
    result->r2.Re = (-b) / (2*a);
    return; 
  } else if (disc == 0) {
    float r = (-b / (2.0*a));
    result->r1.Re = r; 
    result->r2.Re = r; 
    return;
  }
  else {
    float disc_root = sqrt(disc);
    float r1 = (-b + disc_root) / (2.0*a); 
    float r2 = (-b -disc_root) / ( 2.0*a); 
    result->r1.Re = r1; 
    result->r2.Re = r2; 
    return;
  }
}

/* ----------------------------------- */

int bin_to_dec(char* binum) {
  int binum_size = strlen(binum);
  int dec_num = 0;

  int curr_pot = 0;
  for (int i = binum_size-1; i >= 0; i--) {
    curr_pot = pow(2, i);
    if (binum[i] == '1') {
      dec_num += curr_pot;
    }
  }
  return dec_num;
}


