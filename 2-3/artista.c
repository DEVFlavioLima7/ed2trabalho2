#include "artista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas_2_3.h"
#include <time.h>

int eh_folha_23(Artista23 *no)
{

    return (no->esquerda == NULL && no->meio == NULL && no->direita == NULL);
}

Artista23 *criar_no_artista_23(char nome[], char estilo[])
{

    Artista23 *novo = (Artista23 *)malloc(sizeof(Artista23));

    if (novo)
    {

        strcpy(novo->nome1, nome);
        strcpy(novo->estilo1, estilo);
        novo->albuns1 = NULL;
        novo->num_albuns1 = 0;
        novo->num_chaves = 1;

        novo->nome2[0] = '\0';
        novo->estilo2[0] = '\0';
        novo->albuns2 = NULL;
        novo->num_albuns2 = 0;

        novo->esquerda = NULL;
        novo->meio = NULL;
        novo->direita = NULL;
    }

    return novo;
}

static Promocao *inserir_rec_23(Artista23 **no, char nome[], char estilo[])
{

    Promocao *promo_final = NULL;

    if (*no == NULL)
    {

        promo_final = (Promocao *)malloc(sizeof(Promocao));
        if (promo_final)
        {
            strcpy(promo_final->nome_promovido, nome);
            strcpy(promo_final->estilo_promovido, estilo);
            promo_final->novo_no_dir = NULL;
        }
    }
    else
    {
        Artista23 *n = *no;

        if (eh_folha_23(n))
        {

            if (n->num_chaves == 1)
            {

                if (strcmp(nome, n->nome1) < 0)
                {
                    strcpy(n->nome2, n->nome1);
                    strcpy(n->estilo2, n->estilo1);
                    strcpy(n->nome1, nome);
                    strcpy(n->estilo1, estilo);
                }
                else
                {
                    strcpy(n->nome2, nome);
                    strcpy(n->estilo2, estilo);
                }
                n->num_chaves = 2;
            }
            else
            {
                promo_final = (Promocao *)malloc(sizeof(Promocao));
                Artista23 *novo_dir = criar_no_artista_23("", "");

                if (promo_final && novo_dir)
                {
                    char nomes[3][100];
                    char estilos[3][50];

                    strcpy(nomes[0], n->nome1);
                    strcpy(estilos[0], n->estilo1);
                    strcpy(nomes[1], n->nome2);
                    strcpy(estilos[1], n->estilo2);
                    strcpy(nomes[2], nome);
                    strcpy(estilos[2], estilo);

                    for (int i = 0; i < 2; i++)
                    {
                        for (int j = i + 1; j < 3; j++)
                        {
                            if (strcmp(nomes[i], nomes[j]) > 0)
                            {
                                char temp_nome[100];
                                strcpy(temp_nome, nomes[i]);
                                strcpy(nomes[i], nomes[j]);
                                strcpy(nomes[j], temp_nome);

                                char temp_estilo[50];
                                strcpy(temp_estilo, estilos[i]);
                                strcpy(estilos[i], estilos[j]);
                                strcpy(estilos[j], temp_estilo);
                            }
                        }
                    }

                    strcpy(n->nome1, nomes[0]);
                    strcpy(n->estilo1, estilos[0]);
                    n->nome2[0] = '\0';
                    n->estilo2[0] = '\0';
                    n->num_chaves = 1;

                    strcpy(novo_dir->nome1, nomes[2]);
                    strcpy(novo_dir->estilo1, estilos[2]);
                    novo_dir->num_chaves = 1;

                    strcpy(promo_final->nome_promovido, nomes[1]);
                    strcpy(promo_final->estilo_promovido, estilos[1]);
                    promo_final->novo_no_dir = novo_dir;
                }
            }
        }
        else
        {

            Promocao *promo_filho = NULL;
            if (strcmp(nome, n->nome1) < 0)
                promo_filho = inserir_rec_23(&n->esquerda, nome, estilo);
            else if (n->num_chaves == 1 || strcmp(nome, n->nome2) < 0)
                promo_filho = inserir_rec_23(&n->meio, nome, estilo);
            else
                promo_filho = inserir_rec_23(&n->direita, nome, estilo);

            if (promo_filho != NULL)
            {

                if (n->num_chaves == 1)
                {

                    if (strcmp(promo_filho->nome_promovido, n->nome1) < 0)
                    {
                        strcpy(n->nome2, n->nome1);
                        strcpy(n->estilo2, n->estilo1);
                        strcpy(n->nome1, promo_filho->nome_promovido);
                        strcpy(n->estilo1, promo_filho->estilo_promovido);
                        n->direita = n->meio;
                        n->meio = promo_filho->novo_no_dir;
                    }
                    else
                    {
                        strcpy(n->nome2, promo_filho->nome_promovido);
                        strcpy(n->estilo2, promo_filho->estilo_promovido);
                        n->direita = promo_filho->novo_no_dir;
                    }
                    n->num_chaves = 2;
                }
                else
                {
                    promo_final = (Promocao *)malloc(sizeof(Promocao));
                    Artista23 *novo_dir = criar_no_artista_23("", "");

                    if (promo_final && novo_dir)
                    {
                        char nomes[3][100];
                        char estilos[3][50];
                        Artista23 *filhos[4];

                        if (strcmp(promo_filho->nome_promovido, n->nome1) < 0)
                        {
                            strcpy(nomes[0], promo_filho->nome_promovido);
                            strcpy(estilos[0], promo_filho->estilo_promovido);
                            strcpy(nomes[1], n->nome1);
                            strcpy(estilos[1], n->estilo1);
                            strcpy(nomes[2], n->nome2);
                            strcpy(estilos[2], n->estilo2);
                            filhos[0] = n->esquerda;
                            filhos[1] = promo_filho->novo_no_dir;
                            filhos[2] = n->meio;
                            filhos[3] = n->direita;
                        }
                        else if (strcmp(promo_filho->nome_promovido, n->nome2) < 0)
                        {
                            strcpy(nomes[0], n->nome1);
                            strcpy(estilos[0], n->estilo1);
                            strcpy(nomes[1], promo_filho->nome_promovido);
                            strcpy(estilos[1], promo_filho->estilo_promovido);
                            strcpy(nomes[2], n->nome2);
                            strcpy(estilos[2], n->estilo2);
                            filhos[0] = n->esquerda;
                            filhos[1] = n->meio;
                            filhos[2] = promo_filho->novo_no_dir;
                            filhos[3] = n->direita;
                        }
                        else
                        {
                            strcpy(nomes[0], n->nome1);
                            strcpy(estilos[0], n->estilo1);
                            strcpy(nomes[1], n->nome2);
                            strcpy(estilos[1], n->estilo2);
                            strcpy(nomes[2], promo_filho->nome_promovido);
                            strcpy(estilos[2], promo_filho->estilo_promovido);
                            filhos[0] = n->esquerda;
                            filhos[1] = n->meio;
                            filhos[2] = n->direita;
                            filhos[3] = promo_filho->novo_no_dir;
                        }

                        strcpy(n->nome1, nomes[0]);
                        strcpy(n->estilo1, estilos[0]);
                        n->nome2[0] = '\0';
                        n->estilo2[0] = '\0';
                        n->num_chaves = 1;
                        n->esquerda = filhos[0];
                        n->meio = filhos[1];
                        n->direita = NULL;

                        strcpy(novo_dir->nome1, nomes[2]);
                        strcpy(novo_dir->estilo1, estilos[2]);
                        novo_dir->num_chaves = 1;
                        novo_dir->esquerda = filhos[2];
                        novo_dir->meio = filhos[3];
                        novo_dir->direita = NULL;

                        if (novo_dir->esquerda)
                            novo_dir->esquerda->pai = novo_dir;
                        if (novo_dir->meio)
                            novo_dir->meio->pai = novo_dir;

                        strcpy(promo_final->nome_promovido, nomes[1]);
                        strcpy(promo_final->estilo_promovido, estilos[1]);
                        promo_final->novo_no_dir = novo_dir;
                    }
                }

                free(promo_filho);
            }
        }
    }

    return promo_final;
}

Artista23 *inserir_artista_23(Artista23 **raiz, char nome[], char estilo[])
{

    if (buscar_artista_23(*raiz, nome) != NULL)
    {
        printf("ERRO: Artista '%s' já existe na árvore.\n", nome);
    }
    else
    {

        Promocao *promo = inserir_rec_23(raiz, nome, estilo);

        if (promo != NULL)
        {

            Artista23 *nova_raiz = criar_no_artista_23(promo->nome_promovido, promo->estilo_promovido);

            nova_raiz->esquerda = *raiz;
            nova_raiz->meio = promo->novo_no_dir;

            if (*raiz)
                (*raiz)->pai = nova_raiz;
            if (promo->novo_no_dir)
                promo->novo_no_dir->pai = nova_raiz;

            *raiz = nova_raiz;

            free(promo);
        }
    }

    return *raiz;
}

typedef enum
{
    OK,
    UNDERFLOW
} StatusRemocao;

Artista23 *get_inorder_predecessor(Artista23 *no)
{
    if (no == NULL)
        return NULL;

    Artista23 *atual = no->esquerda;
    while (!eh_folha_23(atual))
    {
        atual = atual->direita ? atual->direita : atual->meio;
    }
    return atual;
}

StatusRemocao ajustar_apos_remocao(Artista23 **no);

static StatusRemocao remover_rec_23(Artista23 **no, char nome[])
{
    if (*no == NULL)
        return OK;

    Artista23 *n = *no;

    if (eh_folha_23(n))
    {
        if (strcmp(nome, n->nome1) == 0)
        {

            if (n->num_chaves == 2)
            {
                strcpy(n->nome1, n->nome2);
                strcpy(n->estilo1, n->estilo2);
                n->nome2[0] = '\0';
                n->estilo2[0] = '\0';
                n->num_chaves = 1;
                return OK;
            }
            else
            {
                free(n);
                *no = NULL;
                return UNDERFLOW;
            }
        }
        else if (n->num_chaves == 2 && strcmp(nome, n->nome2) == 0)
        {

            n->nome2[0] = '\0';
            n->estilo2[0] = '\0';
            n->num_chaves = 1;
            return OK;
        }
        return OK;
    }

    StatusRemocao status;
    int pos_filho_removido = -1;

    if (strcmp(nome, n->nome1) == 0)
    {

        Artista23 *predecessor = get_inorder_predecessor(n);

        strcpy(n->nome1, predecessor->nome1);
        strcpy(n->estilo1, predecessor->estilo1);

        status = remover_rec_23(&n->esquerda, predecessor->nome1);
        pos_filho_removido = 0;
    }
    else if (n->num_chaves == 2 && strcmp(nome, n->nome2) == 0)
    {

        Artista23 *predecessor = get_inorder_predecessor(n->meio);

        strcpy(n->nome2, predecessor->nome1);
        strcpy(n->estilo2, predecessor->estilo1);

        status = remover_rec_23(&n->meio, predecessor->nome1);
        pos_filho_removido = 1;
    }
    else if (strcmp(nome, n->nome1) < 0)
    {

        status = remover_rec_23(&n->esquerda, nome);
        pos_filho_removido = 0;
    }
    else if (n->num_chaves == 1 || strcmp(nome, n->nome2) < 0)
    {

        status = remover_rec_23(&n->meio, nome);
        pos_filho_removido = 1;
    }
    else
    {

        status = remover_rec_23(&n->direita, nome);
        pos_filho_removido = 2;
    }

    if (status == UNDERFLOW)
    {

        return ajustar_apos_remocao(no);
    }

    return OK;
}

Artista23 *remover_artista_23(Artista23 **raiz, char nome[])
{
    if (*raiz == NULL)
        return NULL;

    if (buscar_artista_23(*raiz, nome) == NULL)
    {
        printf("AVISO: Artista '%s' não encontrado para remoção.\n", nome);
        return *raiz;
    }

    StatusRemocao status = remover_rec_23(raiz, nome);

    if (status == UNDERFLOW && *raiz != NULL && (*raiz)->num_chaves == 0)
    {

        Artista23 *nova_raiz = (*raiz)->esquerda ? (*raiz)->esquerda : (*raiz)->meio;
        if (nova_raiz)
            nova_raiz->pai = NULL;
        free(*raiz);
        *raiz = nova_raiz;
    }

    return *raiz;
}

StatusRemocao ajustar_apos_remocao(Artista23 **raiz)
{

    Artista23 *n = *raiz;
    Artista23 *no_vazio = NULL;
    Artista23 *irmao_esq = NULL;
    Artista23 *irmao_dir = NULL;
    int pos_vazio = -1;

    if (n->esquerda == NULL)
    {
        pos_vazio = 0;
        irmao_dir = n->meio;
        if (n->num_chaves == 2)
            irmao_dir = n->meio;
    }
    else if (n->meio == NULL)
    {
        pos_vazio = 1;
        irmao_esq = n->esquerda;
        irmao_dir = n->direita;
    }
    else if (n->direita == NULL && n->num_chaves == 2)
    {
        pos_vazio = 2;
        irmao_esq = n->meio;
    }
    else
    {
        return OK;
    }

    if (pos_vazio == 0 && irmao_dir != NULL && irmao_dir->num_chaves == 2)
    {

        n->esquerda = criar_no_artista_23(n->nome1, n->estilo1);
        n->esquerda->num_chaves = 1;

        strcpy(n->nome1, irmao_dir->nome1);
        strcpy(n->estilo1, irmao_dir->estilo1);

        strcpy(irmao_dir->nome1, irmao_dir->nome2);
        strcpy(irmao_dir->estilo1, irmao_dir->estilo2);
        irmao_dir->num_chaves = 1;
        irmao_dir->nome2[0] = '\0';
        irmao_dir->estilo2[0] = '\0';

        if (irmao_dir->esquerda)
            n->esquerda->meio = irmao_dir->esquerda;
        irmao_dir->esquerda = irmao_dir->meio;
        irmao_dir->meio = irmao_dir->direita;
        irmao_dir->direita = NULL;

        return OK;
    }
    else if (pos_vazio == 1 && irmao_esq != NULL && irmao_esq->num_chaves == 2)
    {

        n->meio = criar_no_artista_23(n->nome1, n->estilo1);
        n->meio->num_chaves = 1;

        strcpy(n->nome1, irmao_esq->nome2);
        strcpy(n->estilo1, irmao_esq->estilo2);
        irmao_esq->num_chaves = 1;
        irmao_esq->nome2[0] = '\0';
        irmao_esq->estilo2[0] = '\0';

        n->meio->esquerda = irmao_esq->direita;
        irmao_esq->direita = NULL;

        return OK;
    }
    else if (pos_vazio == 1 && irmao_dir != NULL && n->num_chaves == 2 && irmao_dir->num_chaves == 2)
    {

        n->meio = criar_no_artista_23(n->nome2, n->estilo2);
        n->meio->num_chaves = 1;

        strcpy(n->nome2, irmao_dir->nome1);
        strcpy(n->estilo2, irmao_dir->estilo1);

        strcpy(irmao_dir->nome1, irmao_dir->nome2);
        strcpy(irmao_dir->estilo1, irmao_dir->estilo2);
        irmao_dir->num_chaves = 1;
        irmao_dir->nome2[0] = '\0';
        irmao_dir->estilo2[0] = '\0';

        n->meio->direita = irmao_dir->esquerda;
        irmao_dir->esquerda = irmao_dir->meio;
        irmao_dir->meio = irmao_dir->direita;
        irmao_dir->direita = NULL;

        return OK;
    }
    else if (pos_vazio == 2 && irmao_esq != NULL && irmao_esq->num_chaves == 2)
    {

        n->direita = criar_no_artista_23(n->nome2, n->estilo2);
        n->direita->num_chaves = 1;

        strcpy(n->nome2, irmao_esq->nome2);
        strcpy(n->estilo2, irmao_esq->estilo2);
        irmao_esq->num_chaves = 1;
        irmao_esq->nome2[0] = '\0';
        irmao_esq->estilo2[0] = '\0';

        n->direita->esquerda = irmao_esq->direita;
        irmao_esq->direita = NULL;

        return OK;
    }

    if (pos_vazio == 0)
    {

        strcpy(irmao_dir->nome2, irmao_dir->nome1);
        strcpy(irmao_dir->estilo2, irmao_dir->estilo1);
        strcpy(irmao_dir->nome1, n->nome1);
        strcpy(irmao_dir->estilo1, n->estilo1);
        irmao_dir->num_chaves = 2;

        irmao_dir->direita = irmao_dir->meio;
        irmao_dir->meio = irmao_dir->esquerda;

        irmao_dir->pai = n->pai;
        n->esquerda = irmao_dir;
        n->meio = n->direita;
        n->direita = NULL;
    }
    else if (pos_vazio == 1)
    {

        strcpy(irmao_esq->nome2, n->nome1);
        strcpy(irmao_esq->estilo2, n->estilo1);
        irmao_esq->num_chaves = 2;

        irmao_esq->direita = n->direita;
        if (irmao_esq->direita)
            irmao_esq->direita->pai = irmao_esq;

        n->meio = n->direita;
        n->direita = NULL;
    }
    else if (pos_vazio == 2)
    {

        strcpy(irmao_esq->nome2, n->nome2);
        strcpy(irmao_esq->estilo2, n->estilo2);
        irmao_esq->num_chaves = 2;

        n->direita = NULL;
    }

    if (n->num_chaves == 2)
    {

        if (pos_vazio == 0 || pos_vazio == 1)
        {
            strcpy(n->nome1, n->nome2);
            strcpy(n->estilo1, n->estilo2);
            n->num_chaves = 1;
            n->nome2[0] = '\0';
            n->estilo2[0] = '\0';
        }

        else if (pos_vazio == 2)
        {
            n->num_chaves = 1;
            n->nome2[0] = '\0';
            n->estilo2[0] = '\0';
        }
        return OK;
    }
    else
    {

        return UNDERFLOW;
    }
}

Artista23 *buscar_artista_23(Artista23 *raiz, char nome[])
{
    if (raiz == NULL)
        return NULL;

    if (strcmp(nome, raiz->nome1) == 0)
        return raiz;
    if (raiz->num_chaves == 2 && strcmp(nome, raiz->nome2) == 0)
        return raiz;

    if (strcmp(nome, raiz->nome1) < 0)
        return buscar_artista_23(raiz->esquerda, nome);
    else if (raiz->num_chaves == 1 || strcmp(nome, raiz->nome2) < 0)
        return buscar_artista_23(raiz->meio, nome);
    else
        return buscar_artista_23(raiz->direita, nome);
}

void exibir_artistas_23(Artista23 *raiz)
{
    if (raiz == NULL)
        return;

    exibir_artistas_23(raiz->esquerda);
    printf("Artista: %-20s | Estilo: %-20s\n", raiz->nome1, raiz->estilo1);
    exibir_artistas_23(raiz->meio);
    if (raiz->num_chaves == 2)
    {
        printf("Artista: %-20s | Estilo: %-20s\n", raiz->nome2, raiz->estilo2);
        exibir_artistas_23(raiz->direita);
    }
}

void liberar_arvore_artistas_23(Artista23 **raiz)
{
    if (*raiz == NULL)
        return;

    liberar_arvore_artistas_23(&(*raiz)->esquerda);
    liberar_arvore_artistas_23(&(*raiz)->meio);
    liberar_arvore_artistas_23(&(*raiz)->direita);

    liberar_lista_albuns_23(&(*raiz)->albuns1);
    liberar_lista_albuns_23(&(*raiz)->albuns2);

    free(*raiz);
    *raiz = NULL;
}

void registrar_passo(CaminhoBusca *caminho, Artista23 *no, int chave)
{
    if (caminho->count < MAX_PASSOS)
    {

        if (chave == 1)
        {
            strcpy(caminho->passos[caminho->count].nome_no, no->nome1);
        }
        else
        {
            strcpy(caminho->passos[caminho->count].nome_no, no->nome2);
        }
        caminho->passos[caminho->count].chave_acessada = chave;
        caminho->count++;
    }
}

Artista23 *buscar_artista_23_com_caminho(Artista23 *raiz, char nome[], CaminhoBusca *caminho)
{
    if (raiz == NULL)
        return NULL;

    if (strcmp(nome, raiz->nome1) == 0)
    {
        if (caminho != NULL)
            registrar_passo(caminho, raiz, 1);
        return raiz;
    }

    if (raiz->num_chaves == 2 && strcmp(nome, raiz->nome2) == 0)
    {
        if (caminho != NULL)
            registrar_passo(caminho, raiz, 2);
        return raiz;
    }

    if (strcmp(nome, raiz->nome1) < 0)
    {
        if (caminho != NULL)
            registrar_passo(caminho, raiz, 1);
        return buscar_artista_23_com_caminho(raiz->esquerda, nome, caminho);
    }
    else if (raiz->num_chaves == 1 || strcmp(nome, raiz->nome2) < 0)
    {
        if (caminho != NULL)
            registrar_passo(caminho, raiz, 1);
        return buscar_artista_23_com_caminho(raiz->meio, nome, caminho);
    }
    else
    {
        if (caminho != NULL)
            registrar_passo(caminho, raiz, 2);
        return buscar_artista_23_com_caminho(raiz->direita, nome, caminho);
    }
}

void popular_arvore_experimento(Artista23 **raiz)
{
    char nome[100];
    const char *estilo = "Teste Rock";

    for (int i = 1; i <= 30; i++)
    {

        sprintf(nome, "Artista %02d", i);

        if (buscar_artista_23(*raiz, nome) == NULL)
        {

            inserir_artista_23(raiz, nome, (char *)estilo);
        }
    }
    printf("--- 30 Artistas de Experimento Inseridos ---\n");
}

#include <time.h>

void executar_experimento_busca_23(Artista23 *raiz)
{

    const int REPETICOES = 10000;

    const char *nomes_a_buscar[] = {
        "Artista 01", "Artista 02", "Artista 03", "Artista 04", "Artista 05",
        "Artista 06", "Artista 07", "Artista 08", "Artista 09", "Artista 10",
        "Artista 11", "Artista 12", "Artista 13", "Artista 14", "Artista 15",
        "Artista 16", "Artista 17", "Artista 18", "Artista 19", "Artista 20",
        "Artista 21", "Artista 22", "Artista 23", "Artista 24", "Artista 25",
        "Artista 26", "Artista 27", "Artista 28", "Artista 29", "Artista 30"};
    int n = sizeof(nomes_a_buscar) / sizeof(nomes_a_buscar[0]);

    printf("\n--- EXPERIMENTO DE BUSCA DETALHADA (Árvore 2-3) ---\n");
    printf("| Artista  | Status     | Tempo Medio (ms) | Caminho Percorrido |\n");
    printf("|----------|------------|------------------|--------------------|\n");

    for (int i = 0; i < n; i++)
    {
        CaminhoBusca caminho = {.count = 0};
        clock_t inicio, fim;
        double tempo_total;
        Artista23 *a = NULL;

        inicio = clock();
        for (int k = 0; k < REPETICOES; k++)
        {

            CaminhoBusca *caminho_ptr = (k == 0) ? &caminho : NULL;

            a = buscar_artista_23_com_caminho(
                raiz,
                (char *)nomes_a_buscar[i],
                caminho_ptr);
        }
        fim = clock();

        tempo_total = (double)(fim - inicio) * 1000.0 / CLOCKS_PER_SEC;
        double tempo_medio_por_busca = tempo_total / REPETICOES;

        printf("| %-8s | %-10s | %-16.6f | ",
               nomes_a_buscar[i],
               (a != NULL ? "Encontrado" : "Falha"),
               tempo_medio_por_busca);

        for (int j = 0; j < caminho.count; j++)
        {
            printf("%s%s", caminho.passos[j].nome_no, (j == caminho.count - 1 ? "" : " -> "));
        }
        printf(" |\n");
    }
    printf("---------------------------------------------------\n");
}