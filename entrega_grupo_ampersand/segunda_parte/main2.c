#include "estudiantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
    printf("=== Iniciando Prueba de Estudiantes ===\n");

    node_t* lista = initialize_list();
    if (lista == NULL) {
        printf("Error al inicializar la lista.\n");
        return 1;
    }

    estudiante_t* e1 = malloc(sizeof(estudiante_t));
    estudiante_t* e2 = malloc(sizeof(estudiante_t));
    estudiante_t* e3 = malloc(sizeof(estudiante_t));

    if (e1 == NULL || e2 == NULL || e3 == NULL) {
        printf("Error al reservar memoria para estudiantes.\n");
        return 1;
    }

    e1->ci = 12345678;
    e1->grado = 1;
    e1->promedio = 9.5;
    strcpy(e1->nombre, "Nicolas");
    strcpy(e1->apellido, "Calarco");

    e2->ci = 87654321;
    e2->grado = 2;
    e2->promedio = 7.8;
    strcpy(e2->nombre, "Pedro");
    strcpy(e2->apellido, "Alonso");

    e3->ci = 34567890;
    e3->grado = 3;
    e3->promedio = 8.9;
    strcpy(e3->nombre, "Lucia");
    strcpy(e3->apellido, "Benitez");

    printf("\nInsertando estudiantes...\n");
    insert_student(lista, e1);
    insert_student(lista, e2);
    insert_student(lista, e3);

    printf("\n=== Lista original ===\n");
    print_list(lista);

    printf("\n=== Busqueda por CI ===\n");
    estudiante_t* encontrado_ci = search_student(lista, true, 12345678, NULL, NULL);
    print_student(encontrado_ci);

    printf("\n=== Busqueda por nombre y apellido ===\n");
    estudiante_t* encontrado_nombre = search_student(lista, false, 0, "Pedro", "Alonso");
    print_student(encontrado_nombre);

    printf("\n=== Ordenando por apellido ===\n");
    sort_by_apellido(lista);
    print_list(lista);

    printf("\n=== Ordenando por CI ===\n");
    sort_by_ci(lista);
    print_list(lista);

    printf("\n=== Eliminando estudiante con CI 12345678 ===\n");
    if (remove_student(lista, 12345678)) {
        printf("Estudiante eliminado correctamente.\n");
    } else {
        printf("No se pudo eliminar el estudiante.\n");
    }

    printf("\n=== Lista final ===\n");
    print_list(lista);

    /* Liberar memoria restante */
    while (lista->next != NULL) {
        node_t* temp = lista->next;
        lista->next = temp->next;
        free(temp->estudiante);
        free(temp);
    }
    free(lista);

    return 0;
}
