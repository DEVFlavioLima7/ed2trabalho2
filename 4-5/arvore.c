#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arvore45 *criar_arvore()
{
    Arvore45 *arvore = (Arvore45 *)malloc(sizeof(Arvore45));
    if (arvore == NULL)
    {
        printf("Erro: Falha na alocação de memória para a árvore!\n");
        return NULL;
    }

    arvore->raiz = NULL;
    arvore->total_nos = 0;
    return arvore;
}

void inserir_no_arvore(Arvore45 *arvore, No *novo_no)
{
    if (arvore != NULL && novo_no != NULL)
    {
        if (arvore->raiz == NULL)
        {
            arvore->raiz = novo_no;
        }
        else
        {
            inserir_recursivo(arvore->raiz, novo_no);
        }

        arvore->total_nos++;
    }
}

void inserir_recursivo(No *pai, No *novo_no)
{
    if (pai != NULL && novo_no != NULL)
    {
        if (pai->num_filhos < 5)
        {
            pai->filhos[pai->num_filhos] = novo_no;
            novo_no->pai = pai;
            pai->num_filhos++;
        }
        else
        {
            int inserido = 0;
            for (int i = 0; i < pai->num_filhos && !inserido; i++)
            {
                if (pai->filhos[i]->num_filhos < 5)
                {
                    inserir_recursivo(pai->filhos[i], novo_no);
                    inserido = 1;
                }
            }

            if (!inserido && pai->filhos[0] != NULL)
            {
                inserir_recursivo(pai->filhos[0], novo_no);
            }
        }
    }
}

char determinar_status_no(Arvore45 *arvore, unsigned int end_inicial, unsigned int end_final)
{
    char status = 'L';

    if (arvore != NULL && arvore->raiz != NULL)
    {
        if (verificar_sobreposicao(arvore->raiz, end_inicial, end_final))
        {
            status = 'O';
        }
    }

    return status;
}

int verificar_sobreposicao(No *no, unsigned int end_inicial, unsigned int end_final)
{
    int sobreposicao = 0;

    if (no != NULL)
    {

        if (no->status == 'O' && esta_dentro_intervalo(no->end_inicial, no->end_final, end_inicial, end_final))
        {
            sobreposicao = 1;
        }
        else
        {

            for (int i = 0; i < no->num_filhos && !sobreposicao; i++)
            {
                if (verificar_sobreposicao(no->filhos[i], end_inicial, end_final))
                {
                    sobreposicao = 1;
                }
            }
        }
    }

    return sobreposicao;
}

int esta_dentro_intervalo(unsigned int inicio1, unsigned int fim1, unsigned int inicio2, unsigned int fim2)
{
    return !(fim1 < inicio2 || fim2 < inicio1);
}

void imprimir_arvore(Arvore45 *arvore)
{
    if (arvore != NULL && arvore->raiz != NULL)
    {
        printf("\n=== ESTRUTURA DA ÁRVORE 4-5 ===\n");
        printf("Total de nós: %d\n\n", arvore->total_nos);
        imprimir_arvore_recursivo(arvore->raiz, 0);
    }
}

void imprimir_arvore_recursivo(No *no, int nivel)
{
    if (no != NULL)
    {

        for (int i = 0; i < nivel; i++)
        {
            printf("  ");
        }

        printf("├─ ");
        imprimir_no(no);

        for (int i = 0; i < no->num_filhos; i++)
        {
            imprimir_arvore_recursivo(no->filhos[i], nivel + 1);
        }
    }
}

void destruir_arvore(Arvore45 *arvore)
{
    if (arvore != NULL)
    {
        if (arvore->raiz != NULL)
        {
            liberar_no(arvore->raiz);
        }
        free(arvore);
    }
}

No *encontrar_no_livre_recursivo(No *no, int blocos_necessarios)
{
    if (no == NULL)
        return NULL;

    if (no->status == 'L' && calcular_tamanho_em_blocos(no) >= blocos_necessarios)
    {
        return no;
    }

    for (int i = 0; i < no->num_filhos; i++)
    {
        No *resultado = encontrar_no_livre_recursivo(no->filhos[i], blocos_necessarios);
        if (resultado != NULL)
        {
            return resultado;
        }
    }

    return NULL;
}

No *alocar_blocos(Arvore45 *arvore, int blocos_necessarios)
{
    No *no_livre = encontrar_no_livre_recursivo(arvore->raiz, blocos_necessarios);

    if (no_livre == NULL)
    {
        printf("Não há espaço livre suficiente para alocar %d blocos!\n", blocos_necessarios);
        return NULL;
    }

    printf("Nó livre encontrado:\n");
    imprimir_no(no_livre);

    if (calcular_tamanho_em_blocos(no_livre) == blocos_necessarios)
    {
        no_livre->status = 'O';
        printf("Nó convertido para ocupado (tamanho exato):\n");
        imprimir_no(no_livre);
    }
    else
    {
        No *novo_no = fragmentar_no(no_livre, blocos_necessarios);
        if (novo_no != NULL)
        {
            inserir_no_arvore(arvore, novo_no);
        }
    }

    reorganizar_arvore(arvore, arvore->raiz);
    return no_livre;
}

void reorganizar_arvore(Arvore45 *arvore, No *no)
{
    if (no != NULL && arvore != NULL)
    {
        for (int i = 0; i < no->num_filhos; i++)
        {
            reorganizar_arvore(arvore, no->filhos[i]);
        }

        concatenar_nos_adjacentes(arvore, no);
    }
}

void concatenar_nos_adjacentes(Arvore45 *arvore, No *no_atual)
{
    if (no_atual != NULL && arvore != NULL)
    {
        buscar_e_concatenar(arvore, arvore->raiz, no_atual);
    }
}

int buscar_e_concatenar(Arvore45 *arvore, No *no, No *no_referencia)
{
    if (no == NULL || no_referencia == NULL || no == no_referencia)
        return 0;

    if (nos_sao_adjacentes(no, no_referencia) && mesmo_status(no, no_referencia))
    {
        No *no_concatenado = concatenar_dois_nos(no, no_referencia);
        if (no_concatenado != NULL)
        {
            printf("\nNós adjacentes concatenados:\n");
            imprimir_no(no_concatenado);
            if (no_concatenado == no)
            {
                remover_no_da_arvore(arvore, no_referencia);
            }
            else
            {
                remover_no_da_arvore(arvore, no);
            }
            return 1;
        }
    }

    for (int i = 0; i < no->num_filhos; i++)
    {
        if (buscar_e_concatenar(arvore, no->filhos[i], no_referencia))
        {
            return 1;
        }
    }

    return 0;
}

No *concatenar_dois_nos(No *no1, No *no2)
{
    if (no1 == NULL || no2 == NULL || !mesmo_status(no1, no2))
    {
        return NULL;
    }

    No *primeiro = (no1->end_inicial < no2->end_inicial) ? no1 : no2;
    No *segundo = (no1->end_inicial < no2->end_inicial) ? no2 : no1;

    if (primeiro->end_final + 1 != segundo->end_inicial)
    {
        return NULL;
    }

    primeiro->end_final = segundo->end_final;
    primeiro->bloco_final = segundo->bloco_final;

    return primeiro;
}

void remover_no_da_arvore(Arvore45 *arvore, No *no_para_remover)
{
    if (arvore != NULL && no_para_remover != NULL)
    {
        if (arvore->raiz == no_para_remover)
        {
            arvore->raiz = NULL;
            free(no_para_remover);
            arvore->total_nos--;
        }
        else
        {
            remover_no(arvore->raiz, no_para_remover);
            arvore->total_nos--;
        }
    }
}

void remover_no(No *pai, No *no_para_remover)
{
    if (pai != NULL && no_para_remover != NULL)
    {
        int removido = 0;
        for (int i = 0; i < pai->num_filhos && !removido; i++)
        {
            if (pai->filhos[i] == no_para_remover)
            {
                for (int j = i; j < pai->num_filhos - 1; j++)
                {
                    pai->filhos[j] = pai->filhos[j + 1];
                }
                pai->filhos[pai->num_filhos - 1] = NULL;
                pai->num_filhos--;
                free(no_para_remover);
                removido = 1;
            }
        }

        if (!removido)
        {
            for (int i = 0; i < pai->num_filhos; i++)
            {
                remover_no(pai->filhos[i], no_para_remover);
            }
        }
    }
}
