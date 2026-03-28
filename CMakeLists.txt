cmake_minimum_required(VERSION 3.10)

project(EntregaGrupoAmpersand C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(FUENTES_PARTE1 
    entrega_grupo_ampersand/primera_parte/main.c
    entrega_grupo_ampersand/primera_parte/global.c
)

add_executable(ejecutable_parte1 ${FUENTES_PARTE1})

target_include_directories(ejecutable_parte1 PRIVATE entrega_grupo_ampersand/primera_parte)
target_link_libraries(ejecutable_parte1 PRIVATE m)

set(FUENTES_PARTE2
    entrega_grupo_ampersand/segunda_parte/main.c
    entrega_grupo_ampersand/segunda_parte/estudiantes.c
)

add_executable(ejecutable_parte2 ${FUENTES_PARTE2})

target_include_directories(ejecutable_parte2 PRIVATE entrega_grupo_ampersand/segunda_parte)
