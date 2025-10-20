#include "musica.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Musica *criar_musica_23(char titulo[], int minutos)
{
    Musica *m = (Musica*) malloc(sizeof(Musica));
    if (!m) return NULL;
    strncpy(m->titulo, titulo, sizeof(m->titulo)-1);
    m->titulo[sizeof(m->titulo)-1] = '\0';
    m->minutos = minutos;
    m->proximo = NULL;
    return m;
}

void inserir_musica_ordenado_23(Musica **lista_musicas, Musica *nova_musica)
{
    if (lista_musicas == NULL || nova_musica == NULL) return;

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
    if (album == NULL || album->musicas == NULL) return NULL;
    Musica *atual = album->musicas;
    while (atual != NULL)
    {
        int cmp = strcmp(titulo, atual->titulo);
        if (cmp == 0) return atual;
        if (cmp < 0) return NULL; // lista ordenada por título
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
    if (lista_musicas == NULL) return;
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
    // CUIDADO: Este trecho pressupõe que a chamada externa cuida da verificação do Album* ser NULL.
    // O ponteiro *lista_musicas pode ser NULL (lista vazia)
    if (*lista_musicas == NULL)
    {
        printf("  -> AVISO: Nao ha musicas neste album para remover.\n");
        return;
    }

    Musica *atual = *lista_musicas;
    Musica *anterior = NULL;
    
    // Busca na lista de músicas (que é encadeada)
    while (atual != NULL && strcmp(atual->titulo, titulo) != 0)
    {
        anterior = atual;
        atual = atual->proximo;
    }
    
    // Não encontrou
    if (atual == NULL)
    {
        printf("  -> AVISO: Musica '%s' nao encontrada no album.\n", titulo);
        return;
    }

    // Remoção: Atualiza o ponteiro do nó anterior ou a cabeça da lista
    if (anterior == NULL) 
        *lista_musicas = atual->proximo; // O ponteiro principal (cabeça) é atualizado
    else 
        anterior->proximo = atual->proximo;

    // Você deve manter o controle de qtd_musicas no nó Album*, que não está aqui.
    // Assumindo que a chamada que usa esta função cuida disso.
    // if (album->qtd_musicas > 0) album->qtd_musicas--; 
    
    free(atual);
    printf("  -> SUCESSO: Musica '%s' removida.\n", titulo);
}
