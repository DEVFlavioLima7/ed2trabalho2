#ifndef ARTISTA_2_3_H
#define ARTISTA_2_3_H

#include "estruturas_2_3.h"
#include "album.h"

/* ===================================================
   FUNÇÕES RELACIONADAS À ÁRVORE 2-3 DE ARTISTAS
=================================================== */

// Cria um novo nó de artista
Artista23 *criar_no_artista_23(char nome[], char estilo[]);

// Insere um artista na árvore 2-3
Artista23 *inserir_artista_23(Artista23 *raiz, char *nome, char estilo[]);

// Busca um artista na árvore
Artista23 *buscar_artista_23(Artista23 *raiz, char nome[]);

// Exibe todos os artistas em ordem alfabética
void exibir_artistas_23(Artista23 *raiz);

// Remove um artista da árvore
Artista23 *remover_artista_23(Artista23 *raiz, char nome[]);

// Libera toda a árvore
void liberar_arvore_artistas_23(Artista23 **raiz);

// Executa experimento de busca (opcional)
void executar_experimento_busca_23(Artista23 *raiz);

#endif // ARTISTA_2_3_H
