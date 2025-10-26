#ifndef ARTISTA_2_3_H
#define ARTISTA_2_3_H

#include "estruturas_2_3.h"
#include "album.h"

Artista23 *criar_no_artista_23(char nome[], char estilo[]);
Artista23 *inserir_artista_23(Artista23 **raiz, char *nome, char estilo[]);
Artista23 *buscar_artista_23(Artista23 *raiz, char nome[]);

void exibir_artistas_23(Artista23 *raiz);
Artista23 *remover_artista_23(Artista23 **raiz, char nome[]);

void liberar_arvore_artistas_23(Artista23 **raiz);

void executar_experimento_busca_23(Artista23 *raiz);
void popular_arvore_experimento(Artista23 **raiz);

Artista23 *buscar_artista_23_com_caminho(Artista23 *raiz, char nome[], CaminhoBusca *caminho);

#endif
