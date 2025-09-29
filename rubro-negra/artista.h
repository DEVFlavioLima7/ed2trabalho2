#ifndef ARTISTA_H
#define ARTISTA_H

#include "estrutura.h"

Artista *rotacao_esquerda_artista(Artista *raiz_subarvore);
Artista *rotacao_direita_artista(Artista *raiz_subarvore);

Artista *criar_artista(char nome[], char estilo[]);

Artista *inserir_artista(Artista *no, char nome[], char estilo[]);
void remover_artista(Artista **raiz, char nome[]);
void exibir_artistas(Artista *raiz);
Artista *buscar_artista(Artista *raiz, char nome[]);
Artista *buscar_artista_com_caminho(Artista *raiz, char nome[]);
void executar_experimento_busca(Artista *raiz);

#endif