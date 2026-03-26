/* IMPLEMENTEN LAS FUNCIONES ACÁ */

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

void string_to_min(char *string){
    if (string == NULL) return;

    while (*string != '\0'){
        if (*string >= 'A' && *string <= 'Z'){
            *string = *string + 32;
        }
        string++;
    }
}

int32_t string_length(char* string){
  // evidentemente, si se proporciona un string NULL, no me sirve para nada. 
  if (string == NULL){
    return -1;
  }
  int32_t count = 0;
  while (string[count] != '\0'){
    count++;
  }
  return count;
}

int32_t string_words(char* string){
    if (string == NULL){
        return -1;
    }

    int32_t palabras = 0;
    int pp = 0;

    while (string[pp] != '\0'){
        /* puedo decir que hay una palabrita si:
         * el indice en el que estoy parado NO es " ", y ademas, si el indice anterior SI era " " o bien es el inicio. 
        */
        if (string[pp] != ' ' && (pp == 0 || string[pp-1] == ' ')){

            palabras++;
        }
        pp++;
    }
    return palabras;
}


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
