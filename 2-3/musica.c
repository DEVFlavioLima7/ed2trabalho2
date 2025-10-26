#include "musica.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Musica *criar_musica_23(char titulo[], int minutos)
{
    Musica *m = (Musica *)malloc(sizeof(Musica));
    if (!m)
        return NULL;
    strncpy(m->titulo, titulo, sizeof(m->titulo) - 1);
    m->titulo[sizeof(m->titulo) - 1] = '\0';
    m->minutos = minutos;
    m->proximo = NULL;
    return m;
}

void inserir_musica_ordenado_23(Musica **lista_musicas, Musica *nova_musica)
{
    if (lista_musicas == NULL || nova_musica == NULL)
        return;

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

Musica *buscar_musica_23(Album *album, char titulo[])
{
    if (album == NULL || album->musicas == NULL)
        return NULL;
    Musica *atual = album->musicas;
    while (atual != NULL)
    {
        int cmp = strcmp(titulo, atual->titulo);
        if (cmp == 0)
            return atual;
        if (cmp < 0)
            return NULL;
        atual = atual->proximo;
    }
    return NULL;
}

void exibir_musicas_do_album_23(Musica *lista_musicas)
{
    if (lista_musicas == NULL)
    {
        printf("    -> Nenhuma música neste álbum.\n");
        return;
    }
    Musica *atual = lista_musicas;
    while (atual != NULL)
    {
        printf("    -> Título: %-30s | Duração: %d min\n", atual->titulo, atual->minutos);
        atual = atual->proximo;
    }
}

void liberar_lista_musicas_23(Musica **lista_musicas)
{
    if (lista_musicas == NULL)
        return;
    Musica *atual = *lista_musicas;
    while (atual != NULL)
    {
        Musica *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    *lista_musicas = NULL;
}

void remover_musica_23(Musica **lista_musicas, char titulo[])
{

    if (*lista_musicas == NULL)
    {
        printf("  -> AVISO: Nao ha musicas neste album para remover.\n");
        return;
    }

    Musica *atual = *lista_musicas;
    Musica *anterior = NULL;

    while (atual != NULL && strcmp(atual->titulo, titulo) != 0)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("  -> AVISO: Musica '%s' nao encontrada no album.\n", titulo);
        return;
    }

    if (anterior == NULL)
        *lista_musicas = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("  -> SUCESSO: Musica '%s' removida.\n", titulo);
}
