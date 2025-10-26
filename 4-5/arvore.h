#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct No No;

typedef struct Arvore45
{
    No *raiz;
    int total_nos;
} Arvore45;

struct No
{
    char status;
    unsigned int end_inicial;
    unsigned int end_final;
    int bloco_inicial;
    int bloco_final;
    struct No *filhos[5];
    int num_filhos;
    struct No *pai;
};

Arvore45 *criar_arvore();
void destruir_arvore(Arvore45 *arvore);
void inserir_no_arvore(Arvore45 *arvore, No *novo_no);
void imprimir_arvore(Arvore45 *arvore);
void inserir_recursivo(No *pai, No *novo_no);
void imprimir_arvore_recursivo(No *no, int nivel);
void liberar_no(No *no);
char determinar_status_no(Arvore45 *arvore, unsigned int end_inicial, unsigned int end_final);

No *alocar_blocos(Arvore45 *arvore, int blocos_necessarios);
No *encontrar_no_livre_recursivo(No *no, int blocos_necessarios);
void reorganizar_arvore(Arvore45 *arvore, No *no);
void concatenar_nos_adjacentes(Arvore45 *arvore, No *no_atual);
int buscar_e_concatenar(Arvore45 *arvore, No *no, No *no_referencia);

No *concatenar_dois_nos(No *no1, No *no2);

int calcular_tamanho_em_blocos(No *no);
No *fragmentar_no(No *no, int blocos_necessarios);
int nos_sao_adjacentes(No *no1, No *no2);
int mesmo_status(No *no1, No *no2);

int verificar_sobreposicao(No *no, unsigned int end_inicial, unsigned int end_final);
int esta_dentro_intervalo(unsigned int inicio1, unsigned int fim1, unsigned int inicio2, unsigned int fim2);
void imprimir_no(No *no);
void remover_no_da_arvore(Arvore45 *arvore, No *no_para_remover);
void remover_no(No *pai, No *no_para_remover);

#endif
