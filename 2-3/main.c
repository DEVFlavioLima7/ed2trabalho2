#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artista.h" // Assumi que o nome do seu cabeçalho é artista.h
#include "album.h"

// Função auxiliar para inserir artistas de teste
// CORRIGIDO: Recebe Artista23 **raiz e NÃO retorna Artista23* (void é mais limpo)
void popular_arvore_teste(Artista23 **raiz) {
    // CORRIGIDO: Não há atribuição 'raiz = ...' aqui. O ponteiro é alterado internamente.
    inserir_artista_23(raiz, "Queen", "Rock");
    inserir_artista_23(raiz, "AC/DC", "Rock");
    inserir_artista_23(raiz, "The Beatles", "Pop/Rock");
    inserir_artista_23(raiz, "Nirvana", "Grunge");
    inserir_artista_23(raiz, "Pink Floyd", "Progressive Rock");
    inserir_artista_23(raiz, "Eminem", "Rap");
    inserir_artista_23(raiz, "Chico Buarque", "MPB");
    inserir_artista_23(raiz, "Elis Regina", "MPB");
    inserir_artista_23(raiz, "Led Zeppelin", "Rock");
    inserir_artista_23(raiz, "Caetano Veloso", "MPB");
    // Removido: return *raiz;
}

// Menu de opções (Mantido)
void menu() {
    printf("\n=====================================\n");
    printf("         ÁRVORE 2-3 DE ARTISTAS       \n");
    printf("=====================================\n");
    printf("1 - Inserir artista\n");
    printf("2 - Buscar artista\n");
    printf("3 - Remover artista\n");
    printf("4 - Exibir todos os artistas\n");
    printf("5 - Popular árvore com artistas de teste\n");
    printf("6 - Executar experimento de busca\n");
    printf("0 - Sair\n");
    printf("=====================================\n");
    printf("Escolha: ");
}

int main() {
    Artista23 *raiz = NULL;
    int opcao;
    char nome[100], estilo[50];

    do {
        menu();
        scanf("%d", &opcao);
        getchar(); // consome '\n'

        switch (opcao) {
            case 1:
                printf("Nome do artista: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Estilo musical: ");
                fgets(estilo, sizeof(estilo), stdin);
                estilo[strcspn(estilo, "\n")] = '\0';

                // CORRIGIDO: Passa o endereço da raiz (&raiz). Remove a atribuição.
                inserir_artista_23(&raiz, nome, estilo); 
                printf("✅ Artista '%s' inserido com sucesso!\n", nome);
                break;

            case 2: {
                printf("Nome do artista a buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                Artista23 *encontrado = buscar_artista_23(raiz, nome);
                if (encontrado) {
                    printf("🎵 Artista encontrado: %s (%s)\n", 
                        (strcmp(encontrado->nome1, nome) == 0) ? encontrado->nome1 : encontrado->nome2,
                        (strcmp(encontrado->nome1, nome) == 0) ? encontrado->estilo1 : encontrado->estilo2
                    );
                } else {
                    printf("❌ Artista não encontrado.\n");
                }
                break;
            }

            case 3:
                printf("Nome do artista a remover: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                // CORRIGIDO: Passa o endereço da raiz (&raiz). Remove a atribuição.
                remover_artista_23(&raiz, nome); 
                printf("🗑️  Artista '%s' removido (se existia).\n", nome);
                break;

            case 4:
                if (raiz == NULL)
                    printf("⚠️  Nenhum artista cadastrado.\n");
                else {
                    printf("\n===== LISTA DE ARTISTAS (em ordem) =====\n");
                    exibir_artistas_23(raiz);
                    printf("========================================\n");
                }
                break;

            case 5:
                // CORRIGIDO: Passa o endereço da raiz (&raiz).
                popular_arvore_teste(&raiz); 
                printf("🎶 Árvore populada com artistas de teste!\n");
                break;

            case 6:
                executar_experimento_busca_23(raiz);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);

    // Libera a memória no final, passando o endereço de 'raiz'
    liberar_arvore_artistas_23(&raiz);
    return 0;
}