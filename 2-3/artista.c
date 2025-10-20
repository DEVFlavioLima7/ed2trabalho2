#include "artista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas_2_3.h" 
#include <time.h> // Para experimento de busca


/* ===================================================
    FUNÇÕES AUXILIARES GERAIS
=================================================== */

// Verifica se o nó é folha
int eh_folha_23(Artista23 *no) {
    // Uma folha tem todos os ponteiros de filhos NULL
    return (no->esquerda == NULL && no->meio == NULL && no->direita == NULL);
}

// Cria um novo nó de artista (nó folha, ou nó interno inicial)
Artista23 *criar_no_artista_23(char nome[], char estilo[]) {
    Artista23 *novo = (Artista23 *)malloc(sizeof(Artista23));
    if (!novo) return NULL;

    strcpy(novo->nome1, nome);
    strcpy(novo->estilo1, estilo);
    
    // Inicialização do restante dos campos
    novo->albuns1 = novo->albuns2 = NULL;
    novo->num_albuns1 = novo->num_albuns2 = 0;
    novo->num_chaves = (nome[0] != '\0') ? 1 : 0; // Se o nome não é vazio, tem 1 chave

    novo->nome2[0] = '\0';
    novo->estilo2[0] = '\0';
    novo->esquerda = novo->meio = novo->direita = NULL; // Ponteiro pai será setado na inserção/remoção

    return novo;
}


/* ===================================================
    INSERÇÃO RECURSIVA E PRINCIPAL (Não alterada)
=================================================== */

// Usei o seu código de inserção pois ele estava funcional e a lógica de promoção estava correta.
// A Promocao deve ser uma estrutura definida em "estruturas_2_3.h"


// (Seu código de inserir_rec_23 e inserir_artista_23 está aqui)
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
        n->estilo2[0] = '\0';
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
        // Nó com 1 chave (tornar 2-nó)
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
        // Precisa dividir o nó interno (estava com 2 chaves, recebe 1 do filho = 3 chaves)
        Promocao *promo = (Promocao *)malloc(sizeof(Promocao));
        Artista23 *novo_dir = criar_no_artista_23("", "");

        // Array para ordenação (3 chaves)
        char nomes[3][100];
        char estilos[3][50];
        
        // Ponteiros de filhos (4 ponteiros)
        Artista23 *p[4];

        // Determinar a ordem das chaves e filhos
        if (strcmp(promo_filho->nome_promovido, n->nome1) < 0) {
            strcpy(nomes[0], promo_filho->nome_promovido); strcpy(estilos[0], promo_filho->estilo_promovido);
            strcpy(nomes[1], n->nome1); strcpy(estilos[1], n->estilo1);
            strcpy(nomes[2], n->nome2); strcpy(estilos[2], n->estilo2);
            p[0] = n->esquerda; p[1] = promo_filho->novo_no_dir; p[2] = n->meio; p[3] = n->direita;
        } else if (strcmp(promo_filho->nome_promovido, n->nome2) < 0) {
            strcpy(nomes[0], n->nome1); strcpy(estilos[0], n->estilo1);
            strcpy(nomes[1], promo_filho->nome_promovido); strcpy(estilos[1], promo_filho->estilo_promovido);
            strcpy(nomes[2], n->nome2); strcpy(estilos[2], n->estilo2);
            p[0] = n->esquerda; p[1] = n->meio; p[2] = promo_filho->novo_no_dir; p[3] = n->direita;
        } else {
            strcpy(nomes[0], n->nome1); strcpy(estilos[0], n->estilo1);
            strcpy(nomes[1], n->nome2); strcpy(estilos[1], n->estilo2);
            strcpy(nomes[2], promo_filho->nome_promovido); strcpy(estilos[2], promo_filho->estilo_promovido);
            p[0] = n->esquerda; p[1] = n->meio; p[2] = n->direita; p[3] = promo_filho->novo_no_dir;
        }

        // Atualiza nó esquerdo (atual)
        strcpy(n->nome1, nomes[0]);
        strcpy(n->estilo1, estilos[0]);
        n->nome2[0] = '\0';
        n->estilo2[0] = '\0';
        n->num_chaves = 1;
        n->esquerda = p[0];
        n->meio = p[1];
        n->direita = NULL;

        // Cria o novo nó direito
        strcpy(novo_dir->nome1, nomes[2]);
        strcpy(novo_dir->estilo1, estilos[2]);
        novo_dir->num_chaves = 1;
        novo_dir->esquerda = p[2];
        novo_dir->meio = p[3];
        novo_dir->direita = NULL;
        
        // Atualiza pai dos filhos do novo nó direito (IMPORTANTE)
        if (p[2]) p[2]->pai = novo_dir;
        if (p[3]) p[3]->pai = novo_dir;

        // Promove o nome do meio
        strcpy(promo->nome_promovido, nomes[1]);
        strcpy(promo->estilo_promovido, estilos[1]);
        promo->novo_no_dir = novo_dir;
        
        free(promo_filho);
        return promo;
    }
}

Artista23 *inserir_artista_23(Artista23 **raiz, char nome[], char estilo[]) {
    // Verifica duplicatas
    if (buscar_artista_23(*raiz, nome) != NULL) {
        printf("ERRO: Artista '%s' já existe na árvore.\n", nome);
        return *raiz;
    }
    
    Promocao *promo = inserir_rec_23(raiz, nome, estilo); 
    if (promo == NULL) return *raiz; // Nenhuma promoção ocorreu

    // Cria uma nova raiz se houver promoção
    Artista23 *nova_raiz = criar_no_artista_23(promo->nome_promovido, promo->estilo_promovido);
    nova_raiz->esquerda = *raiz;
    nova_raiz->meio = promo->novo_no_dir;
    
    // Atualiza o pai dos filhos
    if (*raiz) (*raiz)->pai = nova_raiz;
    if (promo->novo_no_dir) promo->novo_no_dir->pai = nova_raiz;

    *raiz = nova_raiz; // Atualiza a raiz da árvore
    free(promo);

    return *raiz; // Retorna a raiz atualizada
}


/* ===================================================
    REMOÇÃO (LÓGICA AJUSTADA)
=================================================== */

// Enum para o status de rebalanceamento
typedef enum {
    OK,         // Tudo certo, não precisa de rebalanceamento
    UNDERFLOW   // Nó ficou com 0 chaves (precisa de rebalanceamento)
} StatusRemocao;

// Função auxiliar para encontrar o predecessor em ordem (inorder predecessor)
// Usada para substituir a chave no nó interno.
Artista23 *get_inorder_predecessor(Artista23 *no) {
    if (no == NULL) return NULL;
    // O predecessor está no nó folha mais à direita da subárvore esquerda.
    Artista23 *atual = no->esquerda;
    while (!eh_folha_23(atual)) {
        atual = atual->direita ? atual->direita : atual->meio;
    }
    return atual;
}

// Protótipo da função auxiliar de rebalanceamento
StatusRemocao ajustar_apos_remocao(Artista23 **no);

// Função de remoção recursiva
static StatusRemocao remover_rec_23(Artista23 **no, char nome[]) {
    if (*no == NULL) return OK; 

    Artista23 *n = *no;

    // 1. Caso Base: Nó Folha
    if (eh_folha_23(n)) {
        if (strcmp(nome, n->nome1) == 0) {
            // Remove nome1
            if (n->num_chaves == 2) {
                strcpy(n->nome1, n->nome2);
                strcpy(n->estilo1, n->estilo2);
                n->nome2[0] = '\0';
                n->estilo2[0] = '\0';
                n->num_chaves = 1;
                return OK;
            } else { // Nó folha com 1 chave (após remoção, fica com 0)
                free(n);
                *no = NULL; // Deleta o nó
                return UNDERFLOW;
            }
        } else if (n->num_chaves == 2 && strcmp(nome, n->nome2) == 0) {
            // Remove nome2 (o nó fica com 1 chave)
            n->nome2[0] = '\0';
            n->estilo2[0] = '\0';
            n->num_chaves = 1;
            return OK;
        }
        return OK; // Nome não encontrado na folha (deveria ser encontrado)
    }

    // 2. Nó Interno: Encontra o caminho
    StatusRemocao status;
    int pos_filho_removido = -1; // 0=esq, 1=meio, 2=dir

    if (strcmp(nome, n->nome1) == 0) {
        // Chave 1 encontrada no nó interno
        Artista23 *predecessor = get_inorder_predecessor(n);
        
        // Substituir a chave pelo predecessor
        strcpy(n->nome1, predecessor->nome1);
        strcpy(n->estilo1, predecessor->estilo1);
        
        // Remove a chave original do predecessor na folha
        status = remover_rec_23(&n->esquerda, predecessor->nome1);
        pos_filho_removido = 0;
    } 
    else if (n->num_chaves == 2 && strcmp(nome, n->nome2) == 0) {
        // Chave 2 encontrada no nó interno
        Artista23 *predecessor = get_inorder_predecessor(n->meio); // Ou o sucessor do filho da direita
        
        // Substituir a chave pelo predecessor
        strcpy(n->nome2, predecessor->nome1);
        strcpy(n->estilo2, predecessor->estilo1);
        
        // Remove a chave original do predecessor na folha
        status = remover_rec_23(&n->meio, predecessor->nome1);
        pos_filho_removido = 1;

    } else if (strcmp(nome, n->nome1) < 0) {
        // Busca na subárvore esquerda
        status = remover_rec_23(&n->esquerda, nome);
        pos_filho_removido = 0;
    } else if (n->num_chaves == 1 || strcmp(nome, n->nome2) < 0) {
        // Busca na subárvore do meio
        status = remover_rec_23(&n->meio, nome);
        pos_filho_removido = 1;
    } else {
        // Busca na subárvore direita
        status = remover_rec_23(&n->direita, nome);
        pos_filho_removido = 2;
    }

    // 3. Rebalanceamento
    if (status == UNDERFLOW) {
        // Passamos o ponteiro para o nó que teve um filho com underflow
        return ajustar_apos_remocao(no); 
    }

    return OK; // Não houve underflow
}

Artista23 *remover_artista_23(Artista23 **raiz, char nome[]) {
    if (*raiz == NULL) return NULL;
    
    // Verificamos se o artista existe antes de tentar remover
    if (buscar_artista_23(*raiz, nome) == NULL) {
        printf("AVISO: Artista '%s' não encontrado para remoção.\n", nome);
        return *raiz;
    }
    
    StatusRemocao status = remover_rec_23(raiz, nome);

    // Se o status for UNDERFLOW na raiz (apenas 1 chave e ela foi removida)
    if (status == UNDERFLOW && *raiz != NULL && (*raiz)->num_chaves == 0) {
        // A raiz deve ser o único filho restante (esquerda ou meio, se houver)
        Artista23 *nova_raiz = (*raiz)->esquerda ? (*raiz)->esquerda : (*raiz)->meio;
        if (nova_raiz) nova_raiz->pai = NULL;
        free(*raiz);
        *raiz = nova_raiz;
    }

    return *raiz;
}

/* ===================================================
    AJUSTE APÓS REMOÇÃO (Lógica de Rebalanceamento/Fusão)
    Esta é a parte mais crítica e ajustada
=================================================== */

StatusRemocao ajustar_apos_remocao(Artista23 **raiz) {
    // Esta função lida com o nó pai (*raiz) cujo filho ficou NULL (0 chaves)
    // O filho com underflow já foi liberado e seu ponteiro no pai é NULL
    
    Artista23 *n = *raiz;
    Artista23 *no_vazio = NULL; // Ponteiro que está NULL
    Artista23 *irmao_esq = NULL;
    Artista23 *irmao_dir = NULL;
    int pos_vazio = -1; // 0=esq, 1=meio, 2=dir

    // Identifica o ponteiro NULL e os irmãos
    if (n->esquerda == NULL) {
        pos_vazio = 0;
        irmao_dir = n->meio;
        if (n->num_chaves == 2) irmao_dir = n->meio;
    } else if (n->meio == NULL) {
        pos_vazio = 1;
        irmao_esq = n->esquerda;
        irmao_dir = n->direita; // Se existir
    } else if (n->direita == NULL && n->num_chaves == 2) {
        pos_vazio = 2;
        irmao_esq = n->meio;
    } else {
        return OK; // Não há underflow real a ser tratado
    }

    // TENTA REDISTRIBUIÇÃO
    if (pos_vazio == 0 && irmao_dir != NULL && irmao_dir->num_chaves == 2) {
        // Redistribuição com o irmão da direita (n->meio)
        n->esquerda = criar_no_artista_23(n->nome1, n->estilo1);
        n->esquerda->num_chaves = 1;
        
        // Promove a chave do meio
        strcpy(n->nome1, irmao_dir->nome1);
        strcpy(n->estilo1, irmao_dir->estilo1);
        
        // Puxa a chave do irmão
        strcpy(irmao_dir->nome1, irmao_dir->nome2);
        strcpy(irmao_dir->estilo1, irmao_dir->estilo2);
        irmao_dir->num_chaves = 1;
        irmao_dir->nome2[0] = '\0';
        irmao_dir->estilo2[0] = '\0';
        
        // Reatribui filhos (caso sejam nós internos)
        // O filho mais à esquerda do irmao_dir (antigo) vai para o novo n->esquerda (novo)
        if (irmao_dir->esquerda) n->esquerda->meio = irmao_dir->esquerda;
        irmao_dir->esquerda = irmao_dir->meio;
        irmao_dir->meio = irmao_dir->direita;
        irmao_dir->direita = NULL;
        
        return OK;

    } else if (pos_vazio == 1 && irmao_esq != NULL && irmao_esq->num_chaves == 2) {
        // Redistribuição com o irmão da esquerda (n->esquerda)
        n->meio = criar_no_artista_23(n->nome1, n->estilo1);
        n->meio->num_chaves = 1;

        // Puxa a chave mais à direita do irmão (nome2)
        strcpy(n->nome1, irmao_esq->nome2);
        strcpy(n->estilo1, irmao_esq->estilo2);
        irmao_esq->num_chaves = 1;
        irmao_esq->nome2[0] = '\0';
        irmao_esq->estilo2[0] = '\0';

        // Reatribui filhos
        // O filho mais à direita do irmao_esq (antigo) vai para o novo n->meio (novo)
        n->meio->esquerda = irmao_esq->direita;
        irmao_esq->direita = NULL;
        
        return OK;

    } else if (pos_vazio == 1 && irmao_dir != NULL && n->num_chaves == 2 && irmao_dir->num_chaves == 2) {
        // Redistribuição com o irmão da direita (n->direita) (Se n é 2-chave e pos_vazio=1)
        n->meio = criar_no_artista_23(n->nome2, n->estilo2);
        n->meio->num_chaves = 1;
        
        // Promove a chave do meio (nome2)
        strcpy(n->nome2, irmao_dir->nome1);
        strcpy(n->estilo2, irmao_dir->estilo1);

        // Puxa a chave do irmão
        strcpy(irmao_dir->nome1, irmao_dir->nome2);
        strcpy(irmao_dir->estilo1, irmao_dir->estilo2);
        irmao_dir->num_chaves = 1;
        irmao_dir->nome2[0] = '\0';
        irmao_dir->estilo2[0] = '\0';

        // Reatribui filhos
        // O filho mais à esquerda do irmao_dir (antigo) vai para o novo n->meio (novo)
        n->meio->direita = irmao_dir->esquerda;
        irmao_dir->esquerda = irmao_dir->meio;
        irmao_dir->meio = irmao_dir->direita;
        irmao_dir->direita = NULL;
        
        return OK;
        
    } else if (pos_vazio == 2 && irmao_esq != NULL && irmao_esq->num_chaves == 2) {
        // Redistribuição com o irmão da esquerda (n->meio)
        n->direita = criar_no_artista_23(n->nome2, n->estilo2);
        n->direita->num_chaves = 1;

        // Puxa a chave mais à direita do irmão (nome2)
        strcpy(n->nome2, irmao_esq->nome2);
        strcpy(n->estilo2, irmao_esq->estilo2);
        irmao_esq->num_chaves = 1;
        irmao_esq->nome2[0] = '\0';
        irmao_esq->estilo2[0] = '\0';

        // Reatribui filhos
        // O filho mais à direita do irmao_esq (antigo) vai para o novo n->direita (novo)
        n->direita->esquerda = irmao_esq->direita;
        irmao_esq->direita = NULL;

        return OK;
    }

    // TENTA FUSÃO (Merge) - Se a redistribuição falhou
    // Fusão sempre é feita com o irmão adjacente que tiver a menor chave,
    // ou seja, se a posição vazia for 0 (esquerda), funde com o meio (1).
    if (pos_vazio == 0) {
        // Fusão de esquerda (vazio) com meio (irmão)
        // A chave n->nome1 desce para o n->meio (que se torna o novo n->esquerda)
        strcpy(irmao_dir->nome2, irmao_dir->nome1);
        strcpy(irmao_dir->estilo2, irmao_dir->estilo1);
        strcpy(irmao_dir->nome1, n->nome1);
        strcpy(irmao_dir->estilo1, n->estilo1);
        irmao_dir->num_chaves = 2;
        
        // Puxa o ponteiro da esquerda para o meio (se não for folha)
        irmao_dir->direita = irmao_dir->meio;
        irmao_dir->meio = irmao_dir->esquerda;

        // Atualiza o pai
        irmao_dir->pai = n->pai;
        n->esquerda = irmao_dir;
        n->meio = n->direita;
        n->direita = NULL;
    } 
    else if (pos_vazio == 1) {
        // Fusão de meio (vazio) com esquerda (irmão)
        // A chave n->nome1 desce para o n->esquerda
        strcpy(irmao_esq->nome2, n->nome1);
        strcpy(irmao_esq->estilo2, n->estilo1);
        irmao_esq->num_chaves = 2;
        
        // O ponteiro do meio vai para a direita do n->esquerda
        irmao_esq->direita = n->direita; // Se n->direita existe, é o filho direito do n->nome1
        if (irmao_esq->direita) irmao_esq->direita->pai = irmao_esq;

        // Atualiza ponteiros do pai
        n->meio = n->direita;
        n->direita = NULL;
    } 
    else if (pos_vazio == 2) {
        // Fusão de direita (vazio) com meio (irmão)
        // A chave n->nome2 desce para o n->meio
        strcpy(irmao_esq->nome2, n->nome2);
        strcpy(irmao_esq->estilo2, n->estilo2);
        irmao_esq->num_chaves = 2;

        // O ponteiro da direita (n->direita) é NULL, então só precisa limpar o ponteiro
        n->direita = NULL;
    }
    
    // Atualiza o nó pai (diminui o número de chaves)
    if (n->num_chaves == 2) {
        // Se fundiu a chave 1 (pos_vazio=0 ou 1)
        if (pos_vazio == 0 || pos_vazio == 1) {
            strcpy(n->nome1, n->nome2);
            strcpy(n->estilo1, n->estilo2);
            n->num_chaves = 1;
            n->nome2[0] = '\0';
            n->estilo2[0] = '\0';
        } 
        // Se fundiu a chave 2 (pos_vazio=2)
        else if (pos_vazio == 2) {
            n->num_chaves = 1;
            n->nome2[0] = '\0';
            n->estilo2[0] = '\0';
        }
        return OK; // Nó pai agora é um nó-2, OK
    } else {
        // Nó pai tinha 1 chave e perdeu-a (underflow)
        return UNDERFLOW;
    }
}


/* ===================================================
    BUSCA
=================================================== */
Artista23 *buscar_artista_23(Artista23 *raiz, char nome[]) {
    if (raiz == NULL) return NULL;

    // Chaves no nó atual
    if (strcmp(nome, raiz->nome1) == 0) return raiz;
    if (raiz->num_chaves == 2 && strcmp(nome, raiz->nome2) == 0) return raiz;

    // Decisão de busca
    if (strcmp(nome, raiz->nome1) < 0)
        return buscar_artista_23(raiz->esquerda, nome);
    else if (raiz->num_chaves == 1 || strcmp(nome, raiz->nome2) < 0)
        return buscar_artista_23(raiz->meio, nome);
    else
        return buscar_artista_23(raiz->direita, nome);
}

/* ===================================================
    EXIBIÇÃO (In-Order)
=================================================== */
void exibir_artistas_23(Artista23 *raiz) {
    if (raiz == NULL) return;
    
    // In-order traversal (esquerda, chave1, meio, chave2, direita)
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
    
    // Liberação pós-ordem
    liberar_arvore_artistas_23(&(*raiz)->esquerda);
    liberar_arvore_artistas_23(&(*raiz)->meio);
    liberar_arvore_artistas_23(&(*raiz)->direita);

    // Assumindo que essa função libera a lista de álbuns
    // Você deve garantir que 'liberar_lista_albuns_23' está implementada
    // e acessível (em 'estruturas_2_3.h')
    liberar_lista_albuns_23(&(*raiz)->albuns1);
    liberar_lista_albuns_23(&(*raiz)->albuns2);
    
    free(*raiz);
    *raiz = NULL;
}

void registrar_passo(CaminhoBusca *caminho, Artista23 *no, int chave) {
    if (caminho->count < MAX_PASSOS) {
        // Assume que a busca sempre é feita pela chave 1 no nó (para simplificar a exibição do nó)
        if (chave == 1) {
            strcpy(caminho->passos[caminho->count].nome_no, no->nome1);
        } else {
            strcpy(caminho->passos[caminho->count].nome_no, no->nome2);
        }
        caminho->passos[caminho->count].chave_acessada = chave;
        caminho->count++;
    }
}

// Busca que registra o caminho percorrido
// Sua função de busca (em artista.c) DEVE MUDAR PARA:
Artista23 *buscar_artista_23_com_caminho(Artista23 *raiz, char nome[], CaminhoBusca *caminho) {
    if (raiz == NULL) return NULL;

    // --- Nova Verificação de Segurança (CORREÇÃO) ---
    // A função auxiliar de registro agora faz a checagem:
    
    // Procura na Chave 1
    if (strcmp(nome, raiz->nome1) == 0) {
        if (caminho != NULL) registrar_passo(caminho, raiz, 1);
        return raiz;
    }
    // Procura na Chave 2
    if (raiz->num_chaves == 2 && strcmp(nome, raiz->nome2) == 0) {
        if (caminho != NULL) registrar_passo(caminho, raiz, 2);
        return raiz;
    }

    // --- Navegação e Chamada Recursiva ---

    if (strcmp(nome, raiz->nome1) < 0) {
        if (caminho != NULL) registrar_passo(caminho, raiz, 1);
        return buscar_artista_23_com_caminho(raiz->esquerda, nome, caminho);
        
    } else if (raiz->num_chaves == 1 || strcmp(nome, raiz->nome2) < 0) {
        if (caminho != NULL) registrar_passo(caminho, raiz, 1);
        return buscar_artista_23_com_caminho(raiz->meio, nome, caminho);
        
    } else { // Deve ir para a direita (nó 3)
        if (caminho != NULL) registrar_passo(caminho, raiz, 2);
        return buscar_artista_23_com_caminho(raiz->direita, nome, caminho);
    }
}
// Depende de: inserir_artista_23(Artista23 **raiz, char nome[], char estilo[])
// Depende de: Artista23 *buscar_artista_23(Artista23 *raiz, char nome[])

void popular_arvore_experimento(Artista23 **raiz) {
    char nome[100];
    const char *estilo = "Teste Rock";

    // Insere 30 artistas genéricos (de "Artista 01" a "Artista 30")
    for (int i = 1; i <= 30; i++) {
        // Cria um nome formatado (ex: "Artista 05")
        sprintf(nome, "Artista %02d", i); 
        
        // Verifica se o artista já existe antes de inserir (melhor prática)
        if (buscar_artista_23(*raiz, nome) == NULL) {
            // Chama a inserção real na árvore 2-3
            inserir_artista_23(raiz, nome, (char*)estilo);
        }
    }
    printf("--- 30 Artistas de Experimento Inseridos ---\n");
}

/* ===================================================
    EXPERIMENTO DE BUSCA
=================================================== */
#include <time.h> // Essencial para clock() e CLOCKS_PER_SEC

void executar_experimento_busca_23(Artista23 *raiz) {
    // Número de vezes que cada busca será repetida para forçar a medição
    const int REPETICOES = 10000; 

    // Lista de 30 nomes a serem buscados
    const char *nomes_a_buscar[] = {
        "Artista 01", "Artista 02", "Artista 03", "Artista 04", "Artista 05",
        "Artista 06", "Artista 07", "Artista 08", "Artista 09", "Artista 10",
        "Artista 11", "Artista 12", "Artista 13", "Artista 14", "Artista 15",
        "Artista 16", "Artista 17", "Artista 18", "Artista 19", "Artista 20",
        "Artista 21", "Artista 22", "Artista 23", "Artista 24", "Artista 25",
        "Artista 26", "Artista 27", "Artista 28", "Artista 29", "Artista 30" 
    };
    int n = sizeof(nomes_a_buscar) / sizeof(nomes_a_buscar[0]);

    printf("\n--- EXPERIMENTO DE BUSCA DETALHADA (Árvore 2-3) ---\n");
    printf("| Artista  | Status     | Tempo Medio (ms) | Caminho Percorrido |\n");
    printf("|----------|------------|------------------|--------------------|\n");

    for (int i = 0; i < n; i++) {
        CaminhoBusca caminho = { .count = 0 };
        clock_t inicio, fim;
        double tempo_total;
        Artista23 *a = NULL; 

        // --- EXECUÇÃO EM LOTE E MEDIÇÃO ---
        inicio = clock();
        for (int k = 0; k < REPETICOES; k++) {
    // Para a medição, NÃO precisamos registrar o caminho em k > 0.
    // Usamos um ponteiro temporário para não registrar o caminho, mas manter a chamada correta.
            CaminhoBusca *caminho_ptr = (k == 0) ? &caminho : NULL; 
    
            a = buscar_artista_23_com_caminho(
            raiz, 
            (char *)nomes_a_buscar[i], 
            caminho_ptr // Agora passamos o ponteiro (ou NULL)
            );
        }
        fim = clock();
        
        // --- CÁLCULO DO TEMPO MÉDIO ---
        tempo_total = (double)(fim - inicio) * 1000.0 / CLOCKS_PER_SEC;
        double tempo_medio_por_busca = tempo_total / REPETICOES;

        // --- IMPRESSÃO DOS RESULTADOS ---
        printf("| %-8s | %-10s | %-16.6f | ", 
            nomes_a_buscar[i], 
            (a != NULL ? "Encontrado" : "Falha"), 
            tempo_medio_por_busca); 

        // Imprime a sequência de nós visitados
        for (int j = 0; j < caminho.count; j++) {
            printf("%s%s", caminho.passos[j].nome_no, (j == caminho.count - 1 ? "" : " -> "));
        }
        printf(" |\n");
    }
    printf("---------------------------------------------------\n");
}