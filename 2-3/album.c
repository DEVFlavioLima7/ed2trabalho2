#include "album.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Album *criar_album_23(char titulo[], int ano)
{

    Album *novo_album = (Album *)malloc(sizeof(Album));

    if (novo_album != NULL)
    {
        strcpy(novo_album->titulo, titulo);
        novo_album->ano = ano;
        novo_album->qtd_musicas = 0;
        novo_album->musicas = NULL;
        novo_album->proximo = NULL;
    }

    return novo_album;
}

Album *inserir_album_23(Album **lista_albuns, char titulo[], int ano)
{

    Album *novo_album = criar_album_23(titulo, ano);

    if (novo_album != NULL)
    {

        if (*lista_albuns == NULL || strcmp(titulo, (*lista_albuns)->titulo) < 0)
        {
            novo_album->proximo = *lista_albuns;
            *lista_albuns = novo_album;
        }

        else
        {
            Album *atual = *lista_albuns;

            while (atual->proximo != NULL && strcmp(titulo, atual->proximo->titulo) > 0)
            {
                atual = atual->proximo;
            }
            novo_album->proximo = atual->proximo;
            atual->proximo = novo_album;
        }
    }

    return novo_album;
}

Album *buscar_album_23(Album *lista_albuns, char titulo[])
{
    Album *album_encontrado = NULL;
    Album *atual = lista_albuns;

    while (atual != NULL && strcmp(titulo, atual->titulo) > 0)
    {
        atual = atual->proximo;
    }

    if (atual != NULL && strcmp(titulo, atual->titulo) == 0)
    {
        album_encontrado = atual;
    }

    return album_encontrado;
}

void remover_album(Album **lista_albuns, char titulo[])
{

    if (*lista_albuns != NULL)
    {
        Album *atual = *lista_albuns;
        Album *anterior = NULL;

        while (atual != NULL && strcmp(atual->titulo, titulo) != 0)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        if (atual != NULL)
        {
            if (anterior == NULL)
            {

                *lista_albuns = atual->proximo;
            }
            else
            {

                anterior->proximo = atual->proximo;
            }
            free(atual);
        }
    }
}

void exibir_albuns_23(Album *lista_albuns)
{
    if (lista_albuns == NULL)
    {
        printf("  -> Nenhum álbum cadastrado.\n");
        return;
    }

    Album *atual = lista_albuns;
    while (atual != NULL)
    {
        printf("  Álbum: %-25s | Ano: %d | %d músicas\n",
               atual->titulo, atual->ano, atual->qtd_musicas);
        exibir_musicas_do_album_23(atual->musicas);
        atual = atual->proximo;
    }
}

void liberar_lista_albuns_23(Album **lista_albuns)
{
    Album *atual = *lista_albuns;
    while (atual != NULL)
    {
        Album *prox = atual->proximo;
        liberar_lista_musicas_23(&atual->musicas);
        free(atual);
        atual = prox;
    }
    *lista_albuns = NULL;
}
