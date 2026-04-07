#include "estudiantes.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función auxiliar para no ensuciar el main con grasa de pollo 
estudiante_t* crear_estudiante(uint32_t ci, uint8_t grado, float promedio, const char* nom, const char* ape) {
    estudiante_t* e = malloc(sizeof(estudiante_t));
    if (e) {
        e->ci = ci;
        e->grado = grado;
        e->promedio = promedio;
        strncpy(e->nombre, nom, 63);
        strncpy(e->apellido, ape, 63);
    }
    return e;
}

int main() {
    printf("=== Autogestión UCU ===\n");

    node_t *lista = initialize_list();
    if (!lista) {
        fprintf(stderr, "Error fatal.\n");
        return 1;
    }

    // --- CARGA DE DATOS ---
    insert_student(lista, crear_estudiante(12345678, 1, 9.5, "Nicolas", "Calarco"));
    insert_student(lista, crear_estudiante(87654321, 2, 7.8, "Pedro", "Alonso"));
    insert_student(lista, crear_estudiante(34567890, 3, 8.9, "Lucia", "Benitez"));
    insert_student(lista, crear_estudiante(45678901, 1, 6.5, "Alfredo", "Arnaud"));

    printf("\n=== Lista Inicial ===\n");
    print_list(lista);

    // --- PRUEBAS DE BÚSQUEDA ---
    printf("\n=== Pruebas de Búsqueda ===\n");
    
    printf("Buscando CI 12345678: ");
    print_student(search_student(lista, true, 12345678, NULL, NULL));

    printf("Buscando por nombre 'Pedro Alonso': ");
    print_student(search_student(lista, false, 0, "Pedro", "Alonso"));

    // --- PRUEBAS DE ORDENAMIENTO ---
    printf("\n=== Pruebas de Ordenamiento ===\n");
    
    printf("Ordenando por Apellido:\n");
    sort_by_apellido(lista);
    print_list(lista);

    printf("\nOrdenando por CI:\n");
    sort_by_ci(lista);
    print_list(lista);

    // --- PRUEBAS DE ELIMINACIÓN ---
    printf("\n=== Pruebas de Eliminación ===\n");
    uint32_t ci_a_borrar = 12345678;
    if (remove_student(lista, ci_a_borrar)) {
        printf("Estudiante con CI %u eliminado correctamente.\n", ci_a_borrar);
    } else {
        printf("No se pudo eliminar al estudiante (CI no encontrado).\n");
    }

    printf("\n=== Lista Final ===\n");
    print_list(lista);

    // --- LIMPIEZA DE MEMORIA (FREE) ---
    printf("\n[!] Liberando memoria...\n");
    while (lista->next != NULL) {
        node_t *temp = lista->next;
        lista->next = temp->next;
        free(temp->estudiante); // Liberamos el struct estudiante
        free(temp);             // Liberamos el nodo
    }
    free(lista); // Liberamos el elemento en cuestión 

    printf("FIN DE PRUEBAS.\n");

    return 0;
}
