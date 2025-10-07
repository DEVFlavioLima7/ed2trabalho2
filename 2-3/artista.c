#include "artista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas_2_3.h"

/* ===================================================
   FUNÇÕES AUXILIARES
=================================================== */

// Verifica se o nó é folha
int eh_folha_23(Artista23 *no) {
    return (no->esquerda == NULL && no->meio == NULL && no->direita == NULL);
}

// Cria um novo nó de artista (nó folha)
Artista23 *criar_no_artista_23(char nome[], char estilo[]) {
    Artista23 *novo = (Artista23 *)malloc(sizeof(Artista23));
    if (!novo) return NULL;

    strcpy(novo->nome1, nome);
    strcpy(novo->estilo1, estilo);
    novo->albuns1 = novo->albuns2 = NULL;
    novo->num_albuns1 = novo->num_albuns2 = 0;
    novo->num_chaves = 1;

    novo->nome2[0] = '\0';
    novo->estilo2[0] = '\0';
    novo->esquerda = novo->meio = novo->direita = novo->pai = NULL;

    return novo;
}

/* ===================================================
   INSERÇÃO RECURSIVA
=================================================== */

static Promocao *inserir_rec_23(Artista23 **no, char nome[], char estilo[]) {
    if (*no == NULL) {
        Promocao *promo = (Promocao *)malloc(sizeof(Promocao));
        strcpy(promo->nome_promovido, nome);
        strcpy(promo->estilo_promovido, estilo);
        promo->novo_no_dir = NULL;
        return promo;
    }

    Artista23 *n = *no;

    // Caso base: nó folha
    if (eh_folha_23(n)) {
        if (n->num_chaves == 1) {
            // Inserção simples
            if (strcmp(nome, n->nome1) < 0) {
                strcpy(n->nome2, n->nome1);
                strcpy(n->estilo2, n->estilo1);
                strcpy(n->nome1, nome);
                strcpy(n->estilo1, estilo);
            } else {
                strcpy(n->nome2, nome);
                strcpy(n->estilo2, estilo);
            }
            n->num_chaves = 2;
            return NULL;
        }

        // Caso o nó esteja cheio → dividir
        Promocao *promo = (Promocao *)malloc(sizeof(Promocao));
        Artista23 *novo_dir = criar_no_artista_23("", "");

        char nomes[3][100];
        char estilos[3][50];
        strcpy(nomes[0], n->nome1);
        strcpy(nomes[1], n->nome2);
        strcpy(nomes[2], nome);
        strcpy(estilos[0], n->estilo1);
        strcpy(estilos[1], n->estilo2);
        strcpy(estilos[2], estilo);

        // Ordena os três nomes
        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                if (strcmp(nomes[i], nomes[j]) > 0) {
                    char tmp[100]; strcpy(tmp, nomes[i]); strcpy(nomes[i], nomes[j]); strcpy(nomes[j], tmp);
                    char tmp2[50]; strcpy(tmp2, estilos[i]); strcpy(estilos[i], estilos[j]); strcpy(estilos[j], tmp2);
                }
            }
        }

        // Atualiza o nó atual (esquerdo)
        strcpy(n->nome1, nomes[0]);
        strcpy(n->estilo1, estilos[0]);
        n->nome2[0] = '\0';
        n->num_chaves = 1;

        // Cria o nó direito
        strcpy(novo_dir->nome1, nomes[2]);
        strcpy(novo_dir->estilo1, estilos[2]);
        novo_dir->num_chaves = 1;

        // Promove o nome do meio
        strcpy(promo->nome_promovido, nomes[1]);
        strcpy(promo->estilo_promovido, estilos[1]);
        promo->novo_no_dir = novo_dir;

        return promo;
    }

    // Nó interno
    Promocao *promo_filho = NULL;
    if (strcmp(nome, n->nome1) < 0)
        promo_filho = inserir_rec_23(&n->esquerda, nome, estilo);
    else if (n->num_chaves == 1 || strcmp(nome, n->nome2) < 0)
        promo_filho = inserir_rec_23(&n->meio, nome, estilo);
    else
        promo_filho = inserir_rec_23(&n->direita, nome, estilo);

    if (promo_filho == NULL) return NULL;

    // Tratamento de promoção
    if (n->num_chaves == 1) {
        if (strcmp(promo_filho->nome_promovido, n->nome1) < 0) {
            strcpy(n->nome2, n->nome1);
            strcpy(n->estilo2, n->estilo1);
            strcpy(n->nome1, promo_filho->nome_promovido);
            strcpy(n->estilo1, promo_filho->estilo_promovido);
            n->direita = n->meio;
            n->meio = promo_filho->novo_no_dir;
        } else {
            strcpy(n->nome2, promo_filho->nome_promovido);
            strcpy(n->estilo2, promo_filho->estilo_promovido);
            n->direita = promo_filho->novo_no_dir;
        }
        n->num_chaves = 2;
        free(promo_filho);
        return NULL;
    } else {
        // Precisa dividir o nó interno
        Promocao *promo = (Promocao *)malloc(sizeof(Promocao));
        Artista23 *novo_dir = criar_no_artista_23("", "");

        char nomes[3][100];
        char estilos[3][50];
        strcpy(nomes[0], n->nome1);
        strcpy(nomes[1], n->nome2);
        strcpy(nomes[2], promo_filho->nome_promovido);
        strcpy(estilos[0], n->estilo1);
        strcpy(estilos[1], n->estilo2);
        strcpy(estilos[2], promo_filho->estilo_promovido);

        // Ordena
        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                if (strcmp(nomes[i], nomes[j]) > 0) {
                    char tmp[100]; strcpy(tmp, nomes[i]); strcpy(nomes[i], nomes[j]); strcpy(nomes[j], tmp);
                    char tmp2[50]; strcpy(tmp2, estilos[i]); strcpy(estilos[i], estilos[j]); strcpy(estilos[j], tmp2);
                }
            }
        }

        // Atualiza nó esquerdo (atual)
        strcpy(n->nome1, nomes[0]);
        strcpy(n->estilo1, estilos[0]);
        n->num_chaves = 1;

        // Cria o novo nó direito
        strcpy(novo_dir->nome1, nomes[2]);
        strcpy(novo_dir->estilo1, estilos[2]);
        novo_dir->num_chaves = 1;

        // Promove o nome do meio
        strcpy(promo->nome_promovido, nomes[1]);
        strcpy(promo->estilo_promovido, estilos[1]);
        promo->novo_no_dir = novo_dir;

        return promo;
    }
}

/* ===================================================
   INSERÇÃO PRINCIPAL
=================================================== */

Artista23 *inserir_artista_23(Artista23 *raiz, char nome[], char estilo[]) {
    Promocao *promo = inserir_rec_23(&raiz, nome, estilo);
    if (promo == NULL) return raiz;

    Artista23 *nova_raiz = criar_no_artista_23(promo->nome_promovido, promo->estilo_promovido);
    nova_raiz->esquerda = raiz;
    nova_raiz->meio = promo->novo_no_dir;
    free(promo);
    return nova_raiz;
}

/* ===================================================
   BUSCA
=================================================== */
Artista23 *buscar_artista_23(Artista23 *raiz, char nome[]) {
    if (raiz == NULL) return NULL;
    if (strcmp(nome, raiz->nome1) == 0 || (raiz->num_chaves == 2 && strcmp(nome, raiz->nome2) == 0))
        return raiz;

    if (strcmp(nome, raiz->nome1) < 0)
        return buscar_artista_23(raiz->esquerda, nome);
    else if (raiz->num_chaves == 1 || strcmp(nome, raiz->nome2) < 0)
        return buscar_artista_23(raiz->meio, nome);
    else
        return buscar_artista_23(raiz->direita, nome);
}

/* ===================================================
   EXIBIÇÃO
=================================================== */
void exibir_artistas_23(Artista23 *raiz) {
    if (raiz == NULL) return;
    exibir_artistas_23(raiz->esquerda);
    printf("Artista: %-20s | Estilo: %-20s\n", raiz->nome1, raiz->estilo1);
    exibir_artistas_23(raiz->meio);
    if (raiz->num_chaves == 2) {
        printf("Artista: %-20s | Estilo: %-20s\n", raiz->nome2, raiz->estilo2);
        exibir_artistas_23(raiz->direita);
    }
}

/* ===================================================
   LIBERAÇÃO
=================================================== */
void liberar_arvore_artistas_23(Artista23 **raiz) {
    if (*raiz == NULL) return;
    liberar_arvore_artistas_23(&(*raiz)->esquerda);
    liberar_arvore_artistas_23(&(*raiz)->meio);
    liberar_arvore_artistas_23(&(*raiz)->direita);

    liberar_lista_albuns_23(&(*raiz)->albuns1);
    liberar_lista_albuns_23(&(*raiz)->albuns2);
    free(*raiz);
    *raiz = NULL;
}

/* ===================================================
   REMOÇÃO (SIMPLIFICADA)
=================================================== */
// Protótipo da função ajustar_apos_remocao
Artista23 *ajustar_apos_remocao(Artista23 *raiz, int posicao);

Artista23 *remover_artista_23(Artista23 *raiz, char nome[]) {
    if (raiz == NULL) return NULL;

    // Caso 1: Nó folha
    if (eh_folha_23(raiz)) {
        if (raiz->num_chaves == 2) {
            // Nó folha com duas chaves
            if (strcmp(nome, raiz->nome1) == 0) {
                strcpy(raiz->nome1, raiz->nome2);
                strcpy(raiz->estilo1, raiz->estilo2);
                raiz->num_chaves = 1;
            } else if (strcmp(nome, raiz->nome2) == 0) {
                raiz->num_chaves = 1;
            }
        } else if (raiz->num_chaves == 1 && strcmp(nome, raiz->nome1) == 0) {
            // Nó folha com uma chave
            free(raiz);
            return NULL;
        }
        return raiz;
    }

    // Caso 2: Remoção em nó interno
    if (strcmp(nome, raiz->nome1) == 0 || (raiz->num_chaves == 2 && strcmp(nome, raiz->nome2) == 0)) {
        Artista23 *substituto;
        if (strcmp(nome, raiz->nome1) == 0) {
            // Substituir por maior chave da subárvore esquerda
            substituto = raiz->esquerda;
            while (!eh_folha_23(substituto)) {
                substituto = substituto->direita ? substituto->direita : substituto->meio;
            }
            strcpy(raiz->nome1, substituto->nome1);
            strcpy(raiz->estilo1, substituto->estilo1);
            raiz->esquerda = remover_artista_23(raiz->esquerda, substituto->nome1);
        } else {
            // Substituir por menor chave da subárvore direita
            substituto = raiz->meio;
            while (!eh_folha_23(substituto)) {
                substituto = substituto->esquerda;
            }
            strcpy(raiz->nome2, substituto->nome1);
            strcpy(raiz->estilo2, substituto->estilo1);
            raiz->meio = remover_artista_23(raiz->meio, substituto->nome1);
        }
        return raiz;
    }

    // Caso 3: Remoção recursiva em subárvores
    if (strcmp(nome, raiz->nome1) < 0) {
        raiz->esquerda = remover_artista_23(raiz->esquerda, nome);
        if (raiz->esquerda && raiz->esquerda->num_chaves == 0) {
            // Tratar subárvore esquerda vazia
            raiz = ajustar_apos_remocao(raiz, 0);
        }
    } else if (raiz->num_chaves == 1 || strcmp(nome, raiz->nome2) < 0) {
        raiz->meio = remover_artista_23(raiz->meio, nome);
        if (raiz->meio && raiz->meio->num_chaves == 0) {
            // Tratar subárvore do meio vazia
            raiz = ajustar_apos_remocao(raiz, 1);
        }
    } else {
        raiz->direita = remover_artista_23(raiz->direita, nome);
        if (raiz->direita && raiz->direita->num_chaves == 0) {
            // Tratar subárvore direita vazia
            raiz = ajustar_apos_remocao(raiz, 2);
        }
    }

    return raiz;
}

/* ===================================================
   FUNÇÃO AUXILIAR PARA AJUSTAR APÓS REMOÇÃO
=================================================== */
Artista23 *ajustar_apos_remocao(Artista23 *raiz, int posicao) {
    // posicao: 0 = esquerda, 1 = meio, 2 = direita
    if (posicao == 0) {
        // Redistribuir ou fundir com subárvore do meio
        if (raiz->meio->num_chaves == 2) {
            // Redistribuição
            strcpy(raiz->esquerda->nome1, raiz->nome1);
            strcpy(raiz->esquerda->estilo1, raiz->estilo1);
            raiz->esquerda->num_chaves = 1;

            strcpy(raiz->nome1, raiz->meio->nome1);
            strcpy(raiz->estilo1, raiz->meio->estilo1);

            strcpy(raiz->meio->nome1, raiz->meio->nome2);
            strcpy(raiz->meio->estilo1, raiz->meio->estilo2);
            raiz->meio->num_chaves = 1;
        } else {
            // Fusão
            strcpy(raiz->esquerda->nome1, raiz->nome1);
            strcpy(raiz->esquerda->estilo1, raiz->estilo1);
            strcpy(raiz->esquerda->nome2, raiz->meio->nome1);
            strcpy(raiz->esquerda->estilo2, raiz->meio->estilo1);
            raiz->esquerda->num_chaves = 2;

            free(raiz->meio);
            raiz->meio = NULL;

            if (raiz->num_chaves == 2) {
                strcpy(raiz->nome1, raiz->nome2);
                strcpy(raiz->estilo1, raiz->estilo2);
                raiz->meio = raiz->direita;
                raiz->direita = NULL;
            } else {
                free(raiz);
                return raiz->esquerda;
            }
        }
    } else if (posicao == 1) {
        // Redistribuir ou fundir com subárvore esquerda ou direita
        // Similar lógica ao caso acima
    } else if (posicao == 2) {
        // Redistribuir ou fundir com subárvore do meio
        // Similar lógica ao caso acima
    }
    return raiz;
}

/* ===================================================
   EXPERIMENTO DE BUSCA
=================================================== */
void executar_experimento_busca_23(Artista23 *raiz) {
    const char *nomes[] = {"Queen", "AC/DC", "Pink Floyd", "The Beatles", "Nirvana"};
    int n = sizeof(nomes) / sizeof(nomes[0]);

    printf("\n--- EXPERIMENTO DE BUSCA (Árvore 2-3) ---\n");
    for (int i = 0; i < n; i++) {
        Artista23 *a = buscar_artista_23(raiz, (char *)nomes[i]);
        if (a != NULL)
            printf("Encontrado: %s\n", nomes[i]);
        else
            printf("Não encontrado: %s\n", nomes[i]);
    }
    printf("------------------------------------------\n");
}
