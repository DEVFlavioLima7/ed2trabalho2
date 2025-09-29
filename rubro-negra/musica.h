#ifndef MUSICA_H
#define MUSICA_H

#include "estrutura.h"

Musica *criar_musica(char titulo[], int minutos);
void inserir_musica_ordenado(Musica **lista_musicas, Musica *nova_musica);
Musica *buscar_musica(Album *album, char titulo[]);
void exibir_musicas_do_album(Musica *lista_musicas);
void liberar_lista_musicas(Musica **lista_musicas);
void remover_musica(Album *album, char titulo[]);

#endif // MUSICA_H