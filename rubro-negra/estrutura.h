
#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Cor
{
  VERMELHO,
  PRETO
} Cor;

typedef struct Musica Musica;
typedef struct Album Album;

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
  Cor cor;
  struct Album *pai;
  struct Album *esquerda;
  struct Album *direita;
} Album;

typedef struct Artista
{
  char nome[100];
  char estilo[50];
  int num_albuns;
  Album *albuns;
  Cor cor;
  struct Artista *pai;
  struct Artista *esquerda;
  struct Artista *direita;
} Artista;

#endif