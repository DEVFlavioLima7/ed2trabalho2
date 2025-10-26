#ifndef BLOCO_MEMORIA_H
#define BLOCO_MEMORIA_H

#include "arvore.h"

void cadastrar_nos(Arvore45 *arvore);
void listar_blocos(Arvore45 *arvore);

void imprimir_no(No *no);
void liberar_no(No *no);
int calcular_tamanho_em_blocos(No *no);
No *fragmentar_no(No *no, int blocos_necessarios);

void listar_nos_livres(Arvore45 *arvore);
void listar_nos_ocupados(Arvore45 *arvore);

void listar_nos_livres_recursivo(No *no);
void listar_nos_ocupados_recursivo(No *no);

int calcular_bloco(unsigned int endereco);
unsigned int calcular_endereco_inicial(int bloco);
unsigned int calcular_endereco_final(int bloco);
int nos_sao_adjacentes(No *no1, No *no2);
int mesmo_status(No *no1, No *no2);

#endif
