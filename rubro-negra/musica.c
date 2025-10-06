#include "musica.h"

Musica *criar_musica(char titulo[], int minutos)
{
  Musica *nova_musica = (Musica *)malloc(sizeof(Musica));
  if (nova_musica != NULL)
  {
    strcpy(nova_musica->titulo, titulo);
    nova_musica->minutos = minutos;
    nova_musica->proximo = NULL;
  }
  return nova_musica;
}

void inserir_musica_ordenado(Musica **lista_musicas, Musica *nova_musica)
{
    if (*lista_musicas == NULL || strcmp(nova_musica->titulo, (*lista_musicas)->titulo) < 0)
    {
        nova_musica->proximo = *lista_musicas;
        *lista_musicas = nova_musica;
    }
    else
    {
        Musica *atual = *lista_musicas;
        while (atual->proximo != NULL && strcmp(nova_musica->titulo, atual->proximo->titulo) > 0)
        {
            atual = atual->proximo;
        }
        nova_musica->proximo = atual->proximo;
        atual->proximo = nova_musica;
    }
}

Musica *buscar_musica(Album *album, char titulo[])
{

  Musica *musica_encontrada = NULL;

  if (album != NULL && album->musicas != NULL)
  {
    Musica *atual = album->musicas;

    while (atual != NULL)
    {
      int comparacao = strcmp(titulo, atual->titulo);

      if (comparacao == 0)
      {

        musica_encontrada = atual;
        break;
      }

      if (comparacao < 0)
      {
        break;
      }

      atual = atual->proximo;
    }
  }

  return musica_encontrada;
}

void exibir_musicas_do_album(Musica *lista_musicas)
{
  if (lista_musicas == NULL)
  {
    printf("    -> Nenhuma música neste álbum.\n");
    return;
  }
  Musica *atual = lista_musicas;
  while (atual != NULL)
  {
    printf("    -> Título: %-20s | Duração: %d min\n", atual->titulo, atual->minutos);
    atual = atual->proximo;
  }
}

void liberar_lista_musicas(Musica **lista_musicas)
{
  Musica *atual = *lista_musicas;
  Musica *proximo_no;
  while (atual != NULL)
  {
    proximo_no = atual->proximo;
    free(atual);
    atual = proximo_no;
  }
  *lista_musicas = NULL;
}

void remover_musica(Album *album, char titulo[])
{

  if (album != NULL && album->musicas != NULL)
  {
    Musica *atual = album->musicas;
    Musica *anterior = NULL;

    while (atual != NULL && strcmp(atual->titulo, titulo) != 0)
    {
      anterior = atual;
      atual = atual->proximo;
    }

    if (atual != NULL)
    {

      if (anterior == NULL)
      {
        album->musicas = atual->proximo;
      }

      else
      {
        anterior->proximo = atual->proximo;
      }

      free(atual);
      album->qtd_musicas--;
      printf("  -> SUCESSO: Música '%s' removida.\n", titulo);
    }

    else
    {
      printf("  -> AVISO: Música '%s' não encontrada no álbum.\n", titulo);
    }
  }

  else
  {
    printf("  -> AVISO: Não há músicas neste álbum para remover.\n");
  }

  return;
}