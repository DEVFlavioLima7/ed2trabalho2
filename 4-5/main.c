#include "arvore.h"
#include "bloco_memoria.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Arvore45* arvore = criar_arvore();
    if (arvore == NULL) {
        printf("Erro ao criar a árvore.\n");
        return -1;
    }

    int opcao, blocos_necessarios, blocos_para_liberar;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Cadastrar nós\n");
        printf("2. Alocar memória\n");
        printf("3. Liberar memória\n");
        printf("4. Listar blocos livres e ocupados\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                cadastrar_nos(arvore);
                break;
            case 2:
                printf("Quantos blocos você precisa alocar? ");
                scanf("%d", &blocos_necessarios);
                if (alocar_blocos(arvore, blocos_necessarios) == NULL) {
                    printf("Falha ao alocar blocos. Verifique a disponibilidade de espaço.\n");
                } else {
                    printf("Blocos alocados com sucesso.\n");
                }
                break;
            case 3:
                printf("Quantos blocos você deseja liberar? ");
                scanf("%d", &blocos_para_liberar);
                // Chamar a função de liberar blocos aqui, caso tenha sido implementada
                break;
            case 4:
                listar_blocos(arvore);
                break;
            case 5:
                printf("Saindo...\n");
                destruir_arvore(arvore);
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
