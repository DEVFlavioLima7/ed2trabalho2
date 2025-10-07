#include "album.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===================================================
   CRIAÇÃO DE ÁLBUM
=================================================== */
Album *criar_album_23(char titulo[], int ano) {
    Album *novo = (Album *)malloc(sizeof(Album));
    if (!novo) return NULL;

    strcpy(novo->titulo, titulo);
    novo->ano = ano;
    novo->qtd_musicas = 0;
    novo->musicas = NULL;
    novo->proximo = NULL;

    return novo;
}

/* ===================================================
   INSERÇÃO ORDENADA NA LISTA DE ÁLBUNS
=================================================== */
Album *inserir_album_23(Album **lista_albuns, char titulo[], int ano) {
    Album *novo = criar_album_23(titulo, ano);
    if (!novo) return NULL;

    if (*lista_albuns == NULL || strcmp(titulo, (*lista_albuns)->titulo) < 0) {
        novo->proximo = *lista_albuns;
        *lista_albuns = novo;
    } else {
        Album *atual = *lista_albuns;
        while (atual->proximo != NULL && strcmp(titulo, atual->proximo->titulo) > 0)
            atual = atual->proximo;
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }

    return novo;
}

/* ===================================================
   BUSCAR ÁLBUM
=================================================== */
Album *buscar_album_23(Album *lista_albuns, char titulo[]) {
    Album *atual = lista_albuns;
    while (atual != NULL) {
        int cmp = strcmp(titulo, atual->titulo);
        if (cmp == 0)
            return atual;
        else if (cmp < 0)
            return NULL; // lista ordenada
        atual = atual->proximo;
    }
    return NULL;
}

/* ===================================================
   REMOVER ÁLBUM
=================================================== */
void remover_album_23(Album **lista_albuns, char titulo[]) {
    if (*lista_albuns == NULL) {
        printf("  -> AVISO: Nenhum álbum para remover.\n");
        return;
    }

    Album *atual = *lista_albuns;
    Album *anterior = NULL;

    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("  -> AVISO: Álbum '%s' não encontrado.\n", titulo);
        return;
    }

    if (anterior == NULL)
        *lista_albuns = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    liberar_lista_musicas_23(&atual->musicas);
    free(atual);

    printf("  -> SUCESSO: Álbum '%s' removido.\n", titulo);
}

/* ===================================================
   EXIBIR LISTA DE ÁLBUNS
=================================================== */
void exibir_albuns_23(Album *lista_albuns) {
    if (lista_albuns == NULL) {
        printf("  -> Nenhum álbum cadastrado.\n");
        return;
    }

    Album *atual = lista_albuns;
    while (atual != NULL) {
        printf("  Álbum: %-25s | Ano: %d | %d músicas\n",
               atual->titulo, atual->ano, atual->qtd_musicas);
        exibir_musicas_do_album_23(atual->musicas);
        atual = atual->proximo;
    }
}

/* ===================================================
   LIBERAÇÃO DE MEMÓRIA
=================================================== */
void liberar_lista_albuns_23(Album **lista_albuns) {
    Album *atual = *lista_albuns;
    while (atual != NULL) {
        Album *prox = atual->proximo;
        liberar_lista_musicas_23(&atual->musicas);
        free(atual);
        atual = prox;
    }
    *lista_albuns = NULL;
}
