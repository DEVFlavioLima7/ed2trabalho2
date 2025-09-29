#ifndef ALBUM_H
#define ALBUM_H

#include "estrutura.h"

Album *inserir_album(Artista *artista, char titulo[], int ano);
void remover_album(Artista *artista, char titulo[]);
void exibir_albuns_do_artista(Artista *artista);
Album *buscar_album(Album *raiz_album, char titulo[]);
void liberar_arvore_albuns(Album **raiz_albuns);

#endif // ALBUM_H