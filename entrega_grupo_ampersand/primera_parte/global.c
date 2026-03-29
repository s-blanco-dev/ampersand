/* IMPLEMENTEN LAS FUNCIONES ACÁ */

/**
 * @brief Convierte un string a mayúsculas in-place.
 *
 * Recorre el string carácter por carácter y, si encuentra una letra
 * minúscula en ASCII, la transforma en su equivalente mayúscula.
 *
 * @param string Puntero al string a modificar.
 * @return void
 */
void string_to_caps(char *string){
    if (string == NULL) return;

    while (*string != '\0'){
        if (*string >= 'a' && *string <= 'z'){
      // En ACII, la diferencia entre las mayusculas y minusculas es de 32. 
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
void string_to_min(char *string){
    if (string == NULL) return;

    while (*string != '\0'){
        if (*string >= 'A' && *string <= 'Z'){
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
int32_t string_length(char* string){
  // Evidentemente, si se proporciona un string NULL, no me sirve para nada. 
  if (string == NULL){
    return -1;
  }
  int32_t count = 0;
  while (string[count] != '\0'){
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
int32_t string_words(char* string){
    if (string == NULL){
        return -1;
    }

    int32_t palabras = 0;
    int pp = 0;

    while (string[pp] != '\0'){
        /* Puedo decir que hay una palabrita si:
         * el indice en el que estoy parado NO es " ", y ademas, si el indice anterior SI era " " o bien es el inicio. 
        */
        if (string[pp] != ' ' && (pp == 0 || string[pp-1] == ' ')){

            palabras++;
        }
        pp++;
    }
    return palabras;
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
int swap(void *elem1, void *elem2, size_t data_type){
  if(elem1 == NULL || elem2 == NULL){
    return -1;
  }
  char *a = (char *)elem1; 
  // al castear a char puedo copiar cualquier dato byte a byte, esto independientemente del tipo de dato original. 
  char *b = (char *)elem2;

  for (size_t pp = 0; pp < data_type; pp++){
    char temp = a[pp];
    a[pp] = b[pp];
    b[pp] = temp;
  }
  return 0;
}
