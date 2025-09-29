#include "artista.h"
#include "album.h"
#include "musica.h"
#include <stdio.h>

int main()
{
  printf("Biblioteca de Música - Estrutura de Dados II\n\n");
  Artista *raiz_artistas = NULL;

  // =======================================================
  // ETAPA 1: INSERÇÃO DE ARTISTAS
  // =======================================================
  printf("--- ETAPA 1: INSERINDO ARTISTAS ---\n");
  raiz_artistas = inserir_artista(raiz_artistas, "Queen", "Rock");
  raiz_artistas = inserir_artista(raiz_artistas, "Pink Floyd", "Rock Progressivo");
  raiz_artistas = inserir_artista(raiz_artistas, "Led Zeppelin", "Rock");
  raiz_artistas = inserir_artista(raiz_artistas, "AC/DC", "Hard Rock");
  raiz_artistas = inserir_artista(raiz_artistas, "The Beatles", "Rock");

  if (raiz_artistas != NULL)
  {
    raiz_artistas->cor = PRETO;
  }

  exibir_artistas(raiz_artistas);
  printf("-----------------------------------\n\n");

  // =======================================================
  // ETAPA 2: INSERÇÃO DE ÁLBUNS
  // =======================================================
  printf("--- ETAPA 2: ADICIONANDO ÁLBUNS ---\n");
  Artista *artista_encontrado = buscar_artista(raiz_artistas, "Queen");
  if (artista_encontrado != NULL)
  {
    inserir_album(artista_encontrado, "A Night at the Opera", 1975);
    inserir_album(artista_encontrado, "News of the World", 1977);
  }
  artista_encontrado = buscar_artista(raiz_artistas, "Pink Floyd");
  if (artista_encontrado != NULL)
  {
    inserir_album(artista_encontrado, "The Dark Side of the Moon", 1973);
  }
  printf("Álbuns adicionados com sucesso.\n");
  printf("-----------------------------------\n\n");

  // =======================================================
  // ETAPA 3: INSERÇÃO DE MÚSICAS NOS ÁLBUNS
  // =======================================================
  printf("--- ETAPA 3: ADICIONANDO MÚSICAS ---\n");
  artista_encontrado = buscar_artista(raiz_artistas, "Queen");
  if (artista_encontrado != NULL)
  {
    Album *album_encontrado = buscar_album(artista_encontrado->albuns, "A Night at the Opera");
    if (album_encontrado != NULL)
    {
      printf("Adicionando músicas em 'A Night at the Opera'...\n");
      inserir_musica_ordenado(&(album_encontrado->musicas), criar_musica("Bohemian Rhapsody", 6));
      inserir_musica_ordenado(&(album_encontrado->musicas), criar_musica("Love of My Life", 4));
    }
  }
  artista_encontrado = buscar_artista(raiz_artistas, "Pink Floyd");
  if (artista_encontrado != NULL)
  {
    Album *album_encontrado = buscar_album(artista_encontrado->albuns, "The Dark Side of the Moon");
    if (album_encontrado != NULL)
    {
      printf("Adicionando músicas em 'The Dark Side of the Moon'...\n");
      inserir_musica_ordenado(&(album_encontrado->musicas), criar_musica("Time", 7));
      inserir_musica_ordenado(&(album_encontrado->musicas), criar_musica("Money", 6));
    }
  }
  printf("Músicas adicionadas com sucesso.\n");
  printf("------------------------------------\n\n");

  // =======================================================
  // ETAPA 4: EXIBIÇÃO DA BIBLIOTECA COMPLETA
  // =======================================================
  printf("--- ETAPA 4: EXIBINDO BIBLIOTECA COMPLETA ---\n");
  artista_encontrado = buscar_artista(raiz_artistas, "Queen");
  if (artista_encontrado != NULL)
    exibir_albuns_do_artista(artista_encontrado);

  printf("\n");

  artista_encontrado = buscar_artista(raiz_artistas, "Pink Floyd");
  if (artista_encontrado != NULL)
    exibir_albuns_do_artista(artista_encontrado);
  printf("---------------------------------------------\n\n");

  // =======================================================
  // ETAPA 5: EXPERIMENTO DE BUSCA
  // =======================================================
  executar_experimento_busca(raiz_artistas);

  // =======================================================
  // ETAPA 6: TESTANDO REMOÇÃO DE MÚSICA
  // =======================================================
  printf("\n--- ETAPA 6: TESTANDO REMOÇÃO DE MÚSICA ---\n");
  artista_encontrado = buscar_artista(raiz_artistas, "Queen");
  if (artista_encontrado != NULL)
  {
    Album *album_encontrado = buscar_album(artista_encontrado->albuns, "A Night at the Opera");
    if (album_encontrado != NULL)
    {
      printf("\nMúsicas ANTES da remoção:\n");
      exibir_musicas_do_album(album_encontrado->musicas);
      printf("\nRemovendo 'Love of My Life'...\n");
      remover_musica(album_encontrado, "Love of My Life");
      printf("\nMúsicas DEPOIS da remoção:\n");
      exibir_musicas_do_album(album_encontrado->musicas);
    }
  }
  printf("-------------------------------------------\n\n");

  // =======================================================
  // ETAPA 7: TESTANDO REMOÇÃO DE ÁLBUM
  // =======================================================
  printf("--- ETAPA 7: TESTANDO REMOÇÃO DE ÁLBUM ---\n");
  artista_encontrado = buscar_artista(raiz_artistas, "Queen");
  if (artista_encontrado != NULL)
  {
    printf("\nÁlbuns de 'Queen' ANTES da remoção:\n");
    exibir_albuns_do_artista(artista_encontrado);
    printf("\nRemovendo 'News of the World'...\n");
    remover_album(artista_encontrado, "News of the World");
    printf("\nÁlbuns de 'Queen' DEPOIS da remoção:\n");
    exibir_albuns_do_artista(artista_encontrado);
  }
  printf("-------------------------------------------\n\n");

  // =======================================================
  // ETAPA 8: TESTANDO REMOÇÃO DE ARTISTA
  // =======================================================
  printf("--- ETAPA 8: TESTANDO REMOÇÃO DE ARTISTA ---\n");
  printf("\nBiblioteca ANTES da remoção de 'Pink Floyd':\n");
  exibir_artistas(raiz_artistas);
  printf("\nRemovendo 'Pink Floyd'...\n");
  remover_artista(&raiz_artistas, "Pink Floyd");
  printf("\nBiblioteca DEPOIS da remoção:\n");
  exibir_artistas(raiz_artistas);
  printf("------------------------------------------\n\n");

  return 0;
}