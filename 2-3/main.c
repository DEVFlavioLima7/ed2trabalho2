#include "artista.h"
#include "album.h"
#include "musica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void menu()
{
    printf("\n=====================================\n");
    printf("     Biblioteca de Musica - Menu (2-3)\n");
    printf("=====================================\n");
    printf("1 - Inserir artista\n");
    printf("2 - Inserir album\n");
    printf("3 - Inserir musica\n");
    printf("4 - Exibir biblioteca completa\n");
    printf("5 - Buscar artista\n");
    printf("6 - Remover musica\n");
    printf("7 - Remover album\n");
    printf("8 - Remover artista\n");
    printf("9 - Executar experimento de busca\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    // Usamos Artista23* (A estrutura correta para a arvore 2-3)
    Artista23 *raiz_artistas = NULL;
    int opcao;

    do
    {
        menu();
        scanf("%d", &opcao);
        getchar(); // consumir \n do buffer

        if (opcao == 1) // Inserir Artista
        {
            char nome[100], estilo[50];
            printf("Digite o nome do artista: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite o estilo do artista: ");
            fgets(estilo, sizeof(estilo), stdin);
            estilo[strcspn(estilo, "\n")] = '\0';

            // CORREÇÃO: Passa o endereço da raiz (&raiz_artistas)
            inserir_artista_23(&raiz_artistas, nome, estilo); 
            // A cor PRETO não se aplica, mas inserção está correta.
            printf("Artista '%s' inserido com sucesso!\n", nome);
        }
       else if (opcao == 2) // Inserir Album
        {
            char nome_artista[100], titulo[100];
            int ano;

            printf("Digite o nome do artista: ");
            fgets(nome_artista, sizeof(nome_artista), stdin);
            nome_artista[strcspn(nome_artista, "\n")] = '\0';  // Remove o '\n' de fim de linha

            printf("Nome do artista: %s\n", nome_artista); // Print para depuração

            // Busca na árvore 2-3
            Artista23 *artista = buscar_artista_23(raiz_artistas, nome_artista); 
            if (artista == NULL)
            {
                printf("Artista nao encontrado.\n");
            }
            else
            {
                printf("Digite o título do álbum: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';  // Remove o '\n' de fim de linha

                printf("Título do álbum: %s\n", titulo); // Print para depuração

                printf("Digite o ano do album: ");
                while (scanf("%d", &ano) != 1) {
                    printf("Entrada inválida! Digite um número para o ano: ");
                    while (getchar() != '\n'); // Limpa o buffer de entrada
                }

                while (getchar() != '\n'); // Remove o '\n' residual

                printf("Ano do álbum: %d\n", ano); // Print para depuração

                inserir_album_23(&(artista->albuns1), titulo, ano);
                printf("Álbum '%s' adicionado ao artista '%s'.\n", titulo, nome_artista);
            }
        }

        else if (opcao == 3) // Inserir Musica
        {
            char nome_artista[100], nome_album[100], titulo[100];
            int minutos;

            printf("Digite o nome do artista: ");
            fgets(nome_artista, sizeof(nome_artista), stdin);
            nome_artista[strcspn(nome_artista, "\n")] = '\0';

            Artista23 *artista = buscar_artista_23(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Artista nao encontrado.\n");
            }
            else
            {
                printf("Digite o nome do album: ");
                fgets(nome_album, sizeof(nome_album), stdin);
                nome_album[strcspn(nome_album, "\n")] = '\0';

                // CORREÇÃO (1): Passa a lista Artista23->albuns1 para a busca de album
                Album *album = buscar_album_23(artista->albuns1, nome_album); // <--- CORRIGIDO
                if (album == NULL)
                {
                    printf("album nao encontrado.\n");
                }
                else
                {
                    printf("Digite o título da música: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = '\0';

                    printf("Digite a duracao em minutos: ");
                    scanf("%d", &minutos);
                    getchar();

                    inserir_musica_ordenado_23(&(album->musicas), criar_musica_23(titulo, minutos));
                    album->qtd_musicas++;
                    printf("Musica '%s' adicionada ao album '%s'.\n", titulo, nome_album);
                }
            }
        }
        else if (opcao == 4) // Exibir Biblioteca Completa
        {
            printf("\n--- Biblioteca Completa ---\n");
            exibir_artistas_23(raiz_artistas);
        }
        else if (opcao == 5) // Buscar Artista
        {
            char nome[100];
            printf("Digite o nome do artista para buscar: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            Artista23 *encontrado = buscar_artista_23(raiz_artistas, nome);
            if (encontrado)
                printf("Artista '%s' encontrado!\n", nome);
            else
                printf("Artista '%s' nao encontrado.\n", nome);
        }
        else if (opcao == 6) // Remover Musica
        {
            char nome_artista[100], nome_album[100], titulo[100];

            printf("Digite o nome do artista: ");
            fgets(nome_artista, sizeof(nome_artista), stdin);
            nome_artista[strcspn(nome_artista, "\n")] = '\0';

            Artista23 *artista = buscar_artista_23(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Artista nao encontrado.\n");
            }
            else
            {
                printf("Digite o nome do álbum: ");
                fgets(nome_album, sizeof(nome_album), stdin);
                nome_album[strcspn(nome_album, "\n")] = '\0';

                // CORREÇÃO (2): Passa a lista Artista23->albuns1 para a busca de album
                Album *album = buscar_album_23(artista->albuns1, nome_album); // <--- CORRIGIDO
                if (album == NULL)
                {
                    printf("Álbum nao encontrado.\n");
                }
                else
                {
                    printf("Digite o titulo da musica: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = '\0';

                    // Esta linha requer que musica.h tenha a assinatura: void remover_musica_23(Musica **lista_musicas, char titulo[]);
                    remover_musica_23(&(album->musicas), titulo);
                }
            }
        }
        else if (opcao == 7) // Remover Album
        {
           char nome_artista[100], nome_album[100];

            printf("Digite o nome do artista: ");
            fgets(nome_artista, sizeof(nome_artista), stdin);
            nome_artista[strcspn(nome_artista, "\n")] = '\0';

            Artista23 *artista = buscar_artista_23(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Artista nao encontrado.\n");
            }
            else
            {
                printf("Digite o nome do album: ");
                fgets(nome_album, sizeof(nome_album), stdin);
                nome_album[strcspn(nome_album, "\n")] = '\0';

                remover_album_23(&(artista->albuns1), nome_album);
            }
        }
        else if (opcao == 8) // Remover Artista
        {
            char nome[100];
            printf("Digite o nome do artista a remover: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            // CORREÇÃO: Passa o endereço da raiz (&raiz_artistas)
            remover_artista_23(&raiz_artistas, nome);
        }
        else if (opcao == 9) 
        // Executar Experimento
        {
            popular_arvore_experimento(&raiz_artistas); 
            executar_experimento_busca_23(raiz_artistas);
        }
        else if (opcao == 0)
        {
            printf("Encerrando o programa...\n");
        }
        else
        {
            printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    // Liberação no final do programa
    liberar_arvore_artistas_23(&raiz_artistas);

    return 0;
}