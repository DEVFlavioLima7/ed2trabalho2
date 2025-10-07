#ifndef ALBUM_2_3_H
#define ALBUM_2_3_H

#include "estruturas_2_3.h"
#include "musica.h"

Album *criar_album_23(char titulo[], int ano);
Album *inserir_album_23(Album **lista_albuns, char titulo[], int ano);
Album *buscar_album_23(Album *lista_albuns, char titulo[]);
void remover_album_23(Album **lista_albuns, char titulo[]);
void exibir_albuns_23(Album *lista_albuns);
void liberar_lista_albuns_23(Album **lista_albuns);

#endif
