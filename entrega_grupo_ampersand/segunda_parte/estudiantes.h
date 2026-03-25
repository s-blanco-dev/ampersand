#include <cstdint>

/* DECLARACION DE TIPOS */
/* -------------------- */

typedef struct estudiante_s {
  char nombre[65];
  char apellido[65];
  uint32_t ci;
  uint8_t grado;
  float promedio;
} estudiante_t;
