#ifndef MUSICA_2_3_H
#define MUSICA_2_3_H

#include "estruturas_2_3.h"

Musica *criar_musica_23(char titulo[], int minutos);

void inserir_musica_ordenado_23(Musica **lista_musicas, Musica *nova_musica);

Musica *buscar_musica_23(Album *album, char titulo[]);

void exibir_musicas_do_album_23(Musica *lista_musicas);

void liberar_lista_musicas_23(Musica **lista_musicas);

void remover_musica_23(Musica **lista_musicas, char titulo[]);

#endif
