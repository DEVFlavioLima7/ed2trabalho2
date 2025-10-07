#ifndef MUSICA_2_3_H
#define MUSICA_2_3_H

#include "estruturas_2_3.h"

/* ===================================================
   FUNÇÕES RELACIONADAS ÀS MÚSICAS
=================================================== */

// Cria uma nova música
Musica *criar_musica_23(char titulo[], int minutos);

// Insere música de forma ordenada dentro do álbum
void inserir_musica_ordenado_23(Musica **lista_musicas, Musica *nova_musica);

// Busca uma música dentro de um álbum
Musica *buscar_musica_23(Album *album, char titulo[]);

// Exibe todas as músicas de um álbum
void exibir_musicas_do_album_23(Musica *lista_musicas);

// Libera memória de todas as músicas
void liberar_lista_musicas_23(Musica **lista_musicas);

// Remove uma música de um álbum
void remover_musica_23(Album *album, char titulo[]);

#endif // MUSICA_2_3_H
