#ifndef ESTRUTURAS_2_3_H
#define ESTRUTURAS_2_3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
====================================================
 ESTRUTURAS DE DADOS PARA ÁRVORE 2-3
====================================================
Cada nó da árvore pode conter:
  - 1 ou 2 chaves (valores)
  - 2 ou 3 ponteiros para filhos
Isso garante que a árvore permaneça balanceada
sem precisar de cores (como na rubro-negra).
====================================================
*/

/* -----------------------------------------------
   ESTRUTURA BÁSICA DE MÚSICA
------------------------------------------------*/
typedef struct Musica {
    char titulo[100];
    int minutos;
    struct Musica *proximo;
} Musica;

/* -----------------------------------------------
   ESTRUTURA DE ÁLBUM
------------------------------------------------*/
typedef struct Album {
    char titulo[100];
    int ano;
    int qtd_musicas;
    Musica *musicas;
    struct Album *proximo;
} Album;

/* -----------------------------------------------
   ESTRUTURA DE ARTISTA (NÓ DA ÁRVORE 2-3)
------------------------------------------------*/
typedef struct Artista23 {
    char nome1[100];       // primeira chave (sempre usada)
    char nome2[100];       // segunda chave (usada se nó for 3-nó)
    char estilo1[50];
    char estilo2[50];
    Album *albuns1;        // lista de álbuns do primeiro artista
    Album *albuns2;        // lista de álbuns do segundo artista
    int num_albuns1;
    int num_albuns2;
    int num_chaves;        // 1 ou 2 (quantas chaves o nó possui)

    // filhos
    struct Artista23 *esquerda;
    struct Artista23 *meio;
    struct Artista23 *direita;

    // ponteiro para o pai (opcional, pode ajudar na remoção)
    struct Artista23 *pai;
} Artista23;

#endif
