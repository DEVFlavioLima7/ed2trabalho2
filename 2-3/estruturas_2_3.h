#ifndef ESTRUTURAS_2_3_H
#define ESTRUTURAS_2_3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Musica
{
    char titulo[100];
    int minutos;
    struct Musica *proximo;
} Musica;

typedef struct Album
{
    char titulo[100];
    int ano;
    int qtd_musicas;
    Musica *musicas;
    struct Album *proximo;
} Album;

typedef struct Artista23
{
    char nome1[100];
    char nome2[100];
    char estilo1[50];
    char estilo2[50];
    Album *albuns1;
    Album *albuns2;
    int num_albuns1;
    int num_albuns2;
    int num_chaves;

    struct Artista23 *esquerda;
    struct Artista23 *meio;
    struct Artista23 *direita;

    struct Artista23 *pai;
} Artista23;

typedef struct
{
    char nome_promovido[100];
    char estilo_promovido[50];
    Artista23 *novo_no_dir;
} Promocao;

typedef struct
{
    char nome_no[100];
    int chave_acessada;
} Passo;

#define MAX_PASSOS 50

typedef struct
{
    Passo passos[MAX_PASSOS];
    int count;
} CaminhoBusca;

#endif
