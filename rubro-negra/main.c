#include "artista.h"
#include "album.h"
#include "musica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu()
{
    printf("\n=====================================\n");
    printf("   Biblioteca de Musica - Menu\n");
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
    Artista *raiz_artistas = NULL;
    int opcao;

    do
    {
        menu();
        scanf("%d", &opcao);
        getchar(); // consumir \n do buffer

        if (opcao == 1)
        {
            char nome[100], estilo[50];
            printf("Digite o nome do artista: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite o estilo do artista: ");
            fgets(estilo, sizeof(estilo), stdin);
            estilo[strcspn(estilo, "\n")] = '\0';

            raiz_artistas = inserir_artista(raiz_artistas, nome, estilo);
            if (raiz_artistas != NULL)
                raiz_artistas->cor = PRETO;

            printf("Artista '%s' inserido com sucesso!\n", nome);
        }
        else if (opcao == 2)
        {
            char nome_artista[100], titulo[100];
            int ano;

            printf("Digite o nome do artista: ");
            fgets(nome_artista, sizeof(nome_artista), stdin);
            nome_artista[strcspn(nome_artista, "\n")] = '\0';

            Artista *artista = buscar_artista(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Artista nao encontrado.\n");
            }
            else
            {
                printf("Digite o título do álbum: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                printf("Digite o ano do album: ");
                scanf("%d", &ano);
                getchar();

                inserir_album(artista, titulo, ano);
                printf("album '%s' adicionado ao artista '%s'.\n", titulo, nome_artista);
            }
        }
        else if (opcao == 3)
        {
            char nome_artista[100], nome_album[100], titulo[100];
            int minutos;

            printf("Digite o nome do artista: ");
            fgets(nome_artista, sizeof(nome_artista), stdin);
            nome_artista[strcspn(nome_artista, "\n")] = '\0';

            Artista *artista = buscar_artista(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Artista nao encontrado.\n");
            }
            else
            {
                printf("Digite o nome do album: ");
                fgets(nome_album, sizeof(nome_album), stdin);
                nome_album[strcspn(nome_album, "\n")] = '\0';

                Album *album = buscar_album(artista->albuns, nome_album);
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

                    inserir_musica_ordenado(&(album->musicas), criar_musica(titulo, minutos));
                    album->qtd_musicas++;
                    printf("Musica '%s' adicionada ao album '%s'.\n", titulo, nome_album);
                }
            }
        }
        else if (opcao == 4)
        {
            printf("\n--- Biblioteca Completa ---\n");
            exibir_artistas(raiz_artistas);
        }
        else if (opcao == 5)
        {
            char nome[100];
            printf("Digite o nome do artista para buscar: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            Artista *encontrado = buscar_artista_com_caminho(raiz_artistas, nome);
            if (encontrado)
                printf("Artista '%s' encontrado!\n", nome);
            else
                printf("Artista '%s' nao encontrado.\n", nome);
        }
        else if (opcao == 6)
        {
            char nome_artista[100], nome_album[100], titulo[100];

            printf("Digite o nome do artista: ");
            fgets(nome_artista, sizeof(nome_artista), stdin);
            nome_artista[strcspn(nome_artista, "\n")] = '\0';

            Artista *artista = buscar_artista(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Artista nao encontrado.\n");
            }
            else
            {
                printf("Digite o nome do álbum: ");
                fgets(nome_album, sizeof(nome_album), stdin);
                nome_album[strcspn(nome_album, "\n")] = '\0';

                Album *album = buscar_album(artista->albuns, nome_album);
                if (album == NULL)
                {
                    printf("Álbum nao encontrado.\n");
                }
                else
                {
                    printf("Digite o titulo da musica: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = '\0';

                    remover_musica(album, titulo);
                }
            }
        }
        else if (opcao == 7)
        {
            char nome_artista[100], nome_album[100];

            printf("Digite o nome do artista: ");
            fgets(nome_artista, sizeof(nome_artista), stdin);
            nome_artista[strcspn(nome_artista, "\n")] = '\0';

            Artista *artista = buscar_artista(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Artista nao encontrado.\n");
            }
            else
            {
                printf("Digite o nome do album: ");
                fgets(nome_album, sizeof(nome_album), stdin);
                nome_album[strcspn(nome_album, "\n")] = '\0';

                remover_album(artista, nome_album);
            }
        }
        else if (opcao == 8)
        {
            char nome[100];
            printf("Digite o nome do artista a remover: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            remover_artista(&raiz_artistas, nome);
        }
        else if (opcao == 9)
        {
            executar_experimento_busca(raiz_artistas);
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

    return 0;
}
