#include "bloco_memoria.h"
#include <stdio.h>
#include <stdlib.h>
// Defina o tamanho do bloco
#define TAMANHO_BLOCO 4096

No* criar_no(char status, unsigned int end_inicial, unsigned int end_final) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        return NULL;
    }

    novo_no->status = status;
    novo_no->end_inicial = end_inicial;
    novo_no->end_final = end_final;
    novo_no->bloco_inicial = calcular_bloco(end_inicial);
    novo_no->bloco_final = calcular_bloco(end_final);
    novo_no->num_filhos = 0;
    novo_no->pai = NULL;
    
    for (int i = 0; i < 5; i++) {
        novo_no->filhos[i] = NULL;
    }

    return novo_no;
}

void cadastrar_nos(Arvore45* arvore) {
    char status;
    unsigned int end_inicial, end_final;

    printf("Cadastro do primeiro nó\n");
    printf("Digite o status (L para livre, O para ocupado): ");
    scanf(" %c", &status);
    printf("Digite o endereço inicial do bloco: ");
    scanf("%u", &end_inicial);
    printf("Digite o endereço final do bloco: ");
    scanf("%u", &end_final);

    No* novo_no = criar_no(status, end_inicial, end_final);
    if (novo_no != NULL) {
        inserir_no_arvore(arvore, novo_no);
    } else {
        printf("Erro ao criar o nó!\n");
    }

    // Cadastro dos nós subsequentes
    while (1) {
        printf("\nDigite o endereço final do próximo nó (0 para terminar): ");
        scanf("%u", &end_final);
        if (end_final == 0) break;

        status = 'L';  // Aqui definimos como livre por padrão, mas pode ser alterado
        if (end_final <= end_inicial) {
            printf("Erro: O endereço final deve ser maior que o endereço inicial.\n");
            continue;
        }
        
        No* novo_no = criar_no(status, end_inicial + 1, end_final);
        if (novo_no != NULL) {
            inserir_no_arvore(arvore, novo_no);
        } else {
            printf("Erro ao criar o nó!\n");
            break;
        }
        end_inicial = end_final;
    }
}

void listar_nos_livres(Arvore45* arvore) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("A árvore está vazia.\n");
        return;
    }

    printf("Nós livres na árvore:\n");
    listar_nos_livres_recursivo(arvore->raiz);
}

void listar_nos_ocupados(Arvore45* arvore) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("A árvore está vazia.\n");
        return;
    }

    printf("Nós ocupados na árvore:\n");
    listar_nos_ocupados_recursivo(arvore->raiz);
}

void listar_nos_livres_recursivo(No* no) {
    if (no == NULL) return;

    if (no->status == 'L') {
        imprimir_no(no);
    }

    for (int i = 0; i < no->num_filhos; i++) {
        listar_nos_livres_recursivo(no->filhos[i]);
    }
}

void listar_nos_ocupados_recursivo(No* no) {
    if (no == NULL) return;

    if (no->status == 'O') {
        imprimir_no(no);
    }

    for (int i = 0; i < no->num_filhos; i++) {
        listar_nos_ocupados_recursivo(no->filhos[i]);
    }
}

void listar_blocos(Arvore45* arvore) {
    printf("\nListando nós livres:\n");
    listar_nos_livres(arvore);

    printf("\nListando nós ocupados:\n");
    listar_nos_ocupados(arvore);
}

int calcular_bloco(unsigned int endereco) {
    return endereco / TAMANHO_BLOCO;
}

unsigned int calcular_endereco_inicial(int bloco) {
    return bloco * TAMANHO_BLOCO;
}

unsigned int calcular_endereco_final(int bloco) {
    return (bloco * TAMANHO_BLOCO) + TAMANHO_BLOCO - 1;
}

void imprimir_no(No* no) {
   if (no != NULL) {
        printf("Status: %c | Blocos: %d-%d | Endereços: 0x%08X-0x%08X\n",
               no->status, no->bloco_inicial, no->bloco_final, 
               no->end_inicial, no->end_final);
    }
}

void liberar_no(No* no) {
    if (no != NULL) {
        for (int i = 0; i < no->num_filhos; i++) {
            liberar_no(no->filhos[i]);
        }
        free(no);
    }
}

int calcular_tamanho_em_blocos(No* no) {
    if (no == NULL) return 0;
    return no->bloco_final - no->bloco_inicial + 1;
}

No* fragmentar_no(No* no, int blocos_necessarios) {
    if (no == NULL || no->status != 'L') return NULL;
    
    int tamanho_total = calcular_tamanho_em_blocos(no);
    if (blocos_necessarios >= tamanho_total) {
        no->status = 'O';
        return no;
    }

    unsigned int novo_end_final_ocupado = no->end_inicial + (blocos_necessarios * TAMANHO_BLOCO) - 1;
    unsigned int novo_end_inicial_livre = novo_end_final_ocupado + 1;

    No* no_livre = criar_no('L', novo_end_inicial_livre, no->end_final);
    if (no_livre == NULL) return NULL;

    no->status = 'O';
    no->end_final = novo_end_final_ocupado;
    no->bloco_final = calcular_bloco(novo_end_final_ocupado);

    return no;
}

int nos_sao_adjacentes(No* no1, No* no2) {
    if (no1 == NULL || no2 == NULL) return 0;
    return (no1->end_final + 1 == no2->end_inicial) || 
           (no2->end_final + 1 == no1->end_inicial);
}

int mesmo_status(No* no1, No* no2) {
    if (no1 == NULL || no2 == NULL) return 0;
    return no1->status == no2->status;
}
