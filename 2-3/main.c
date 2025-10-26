#include "artista.h"
#include "album.h"
#include "musica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu()
{
    printf("\n=====================================\n");
    printf("    Biblioteca de Musica - Menu (2-3)\n");
    printf("=====================================\n");
    printf("1 - Inserir artista\n");
    printf("2 - Inserir album\n");
    printf("3 - Inserir musica\n");
    printf("4 - Exibir biblioteca completa\n");
    printf("5 - Buscar...\n"); // Opção de busca principal
    printf("6 - Remover musica\n");
    printf("7 - Remover album\n");
    printf("8 - Remover artista\n");
    printf("9 - Executar experimento de busca\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

void menu_busca()
{
    printf("\n--- Menu de Busca (2-3) ---\n");
    printf("1 - Buscar Artista\n");
    printf("2 - Buscar Album\n");
    printf("3 - Buscar Musica\n");
    printf("0 - Voltar ao menu principal\n");
    printf("Escolha uma opcao: ");
}

void ler_string(char *buffer, int tamanho)
{
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

int ler_inteiro()
{
    int valor;
    char buffer[50];
    while (1)
    {
        ler_string(buffer, sizeof(buffer));
        if (sscanf(buffer, "%d", &valor) == 1)
        {
            return valor;
        }
        printf("Entrada invalida. Por favor, digite um numero: ");
    }
}

int main()
{
    Artista23 *raiz_artistas = NULL;
    int opcao;

    do
    {
        menu();
        opcao = ler_inteiro();

        if (opcao == 1)
        {
            char nome[100], estilo[50];
            printf("Digite o nome do artista: ");
            ler_string(nome, sizeof(nome));

            printf("Digite o estilo do artista: ");
            ler_string(estilo, sizeof(estilo));

            inserir_artista_23(&raiz_artistas, nome, estilo);

            printf("Artista '%s' inserido com sucesso!\n", nome);
        }
        else if (opcao == 2)
        {
            char nome_artista[100], titulo[100];
            int ano;

            printf("Digite o nome do artista: ");
            ler_string(nome_artista, sizeof(nome_artista));

            Artista23 *artista = buscar_artista_23(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Erro: Artista '%s' nao encontrado.\n", nome_artista);
            }
            else
            {
                printf("Digite o titulo do album: ");
                ler_string(titulo, sizeof(titulo));

                if (buscar_album_23(artista->albuns1, titulo) != NULL)
                {
                    printf("Erro: O album '%s' ja existe para o artista '%s'.\n", titulo, nome_artista);
                }
                else
                {
                    printf("Digite o ano do album: ");
                    ano = ler_inteiro();
                    inserir_album_23(&(artista->albuns1), titulo, ano);
                    printf("Album '%s' adicionado ao artista '%s'.\n", titulo, nome_artista);
                }
            }
        }

        else if (opcao == 3)
        {
            char nome_artista[100], nome_album[100], titulo[100];
            int minutos;

            printf("Digite o nome do artista: ");
            ler_string(nome_artista, sizeof(nome_artista));

            Artista23 *artista = buscar_artista_23(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Erro: Artista '%s' nao encontrado.\n", nome_artista);
            }
            else
            {
                printf("Digite o nome do album: ");
                ler_string(nome_album, sizeof(nome_album));

                Album *album = buscar_album_23(artista->albuns1, nome_album);
                if (album == NULL)
                {
                    printf("Erro: album '%s' nao encontrado.\n", nome_album);
                }
                else
                {
                    printf("Digite o titulo da musica: ");
                    ler_string(titulo, sizeof(titulo));

                    if (buscar_musica_23(album, titulo) != NULL)
                    {
                        printf("Erro: A musica '%s' ja existe no album '%s'.\n", titulo, nome_album);
                    }
                    else
                    {
                        printf("Digite a duracao em minutos: ");
                        minutos = ler_inteiro();

                        inserir_musica_ordenado_23(&(album->musicas), criar_musica_23(titulo, minutos));
                        album->qtd_musicas++;
                        printf("Musica '%s' adicionada ao album '%s'.\n", titulo, nome_album);
                    }
                }
            }
        }
        else if (opcao == 4)
        {
            printf("\n--- Biblioteca Completa (Arvore 2-3) ---\n");
            exibir_artistas_23(raiz_artistas);
        }
        else if (opcao == 5)
        {
            int op_busca;
            menu_busca();
            op_busca = ler_inteiro();

            if (op_busca == 1) // Buscar Artista
            {
                if (raiz_artistas == NULL)
                {
                    printf("A biblioteca esta vazia. Nao ha artistas para buscar.\n");
                    continue;
                }
                char nome[100];
                printf("Digite o nome do artista para buscar: ");
                ler_string(nome, sizeof(nome));

                Artista23 *encontrado = buscar_artista_23(raiz_artistas, nome);
                if (encontrado)
                {
                    printf("Artista '%s' encontrado!\n", nome);
                    printf("Estilo: %s\n", encontrado->estilo1);
                    exibir_albuns_23(encontrado->albuns1);
                }
                else
                {
                    printf("Artista '%s' nao encontrado.\n", nome);
                }
            }
            else if (op_busca == 2) // Buscar Álbum
            {
                if (raiz_artistas == NULL)
                {
                    printf("A biblioteca esta vazia.\n");
                    continue;
                }
                char nome_artista[100], nome_album[100];
                printf("Digite o nome do artista: ");
                ler_string(nome_artista, sizeof(nome_artista));

                Artista23 *artista = buscar_artista_23(raiz_artistas, nome_artista);
                if (artista == NULL)
                {
                    printf("Artista '%s' nao encontrado.\n", nome_artista);
                }
                else
                {
                    printf("Digite o titulo do album para buscar: ");
                    ler_string(nome_album, sizeof(nome_album));
                    Album *album_encontrado = buscar_album_23(artista->albuns1, nome_album);
                    if (album_encontrado)
                    {
                        printf("Album '%s' encontrado para o artista '%s'!\n", nome_album, nome_artista);
                        printf(" -> Ano: %d\n", album_encontrado->ano);
                        exibir_musicas_do_album_23(album_encontrado->musicas);
                    }
                    else
                    {
                        printf("Album '%s' nao encontrado para o artista '%s'.\n", nome_album, nome_artista);
                    }
                }
            }
            else if (op_busca == 3) // Buscar Música
            {
                if (raiz_artistas == NULL)
                {
                    printf("A biblioteca esta vazia.\n");
                    continue;
                }
                char nome_artista[100], nome_album[100], nome_musica[100];

                printf("Digite o nome do artista: ");
                ler_string(nome_artista, sizeof(nome_artista));
                Artista23 *artista = buscar_artista_23(raiz_artistas, nome_artista);

                if (artista == NULL)
                {
                    printf("Artista '%s' nao encontrado.\n", nome_artista);
                }
                else
                {
                    printf("Digite o titulo do album: ");
                    ler_string(nome_album, sizeof(nome_album));
                    Album *album = buscar_album_23(artista->albuns1, nome_album);

                    if (album == NULL)
                    {
                        printf("Album '%s' nao encontrado para o artista '%s'.\n", nome_album, nome_artista);
                    }
                    else
                    {
                        printf("Digite o titulo da musica para buscar: ");
                        ler_string(nome_musica, sizeof(nome_musica));
                        Musica *musica_encontrada = buscar_musica_23(album, nome_musica);

                        if (musica_encontrada)
                        {
                            printf("Musica '%s' encontrada no album '%s'!\n", nome_musica, nome_album);
                            printf(" -> Duracao: %d minutos.\n", musica_encontrada->minutos);
                        }
                        else
                        {
                            printf("Musica '%s' nao encontrada no album '%s'.\n", nome_musica, nome_album);
                        }
                    }
                }
            }
        }
        else if (opcao == 6)
        {
            char nome_artista[100], nome_album[100], titulo[100];

            printf("Digite o nome do artista: ");
            ler_string(nome_artista, sizeof(nome_artista));

            Artista23 *artista = buscar_artista_23(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Artista nao encontrado.\n");
            }
            else
            {
                printf("Digite o nome do album: ");
                ler_string(nome_album, sizeof(nome_album));

                Album *album = buscar_album_23(artista->albuns1, nome_album);
                if (album == NULL)
                {
                    printf("Album nao encontrado.\n");
                }
                else
                {
                    printf("Digite o titulo da musica: ");
                    ler_string(titulo, sizeof(titulo));
                    remover_musica_23(&(album->musicas), titulo);
                }
            }
        }
        else if (opcao == 7)
        {
            char nome_artista[100], nome_album[100];

            printf("Digite o nome do artista: ");
            ler_string(nome_artista, sizeof(nome_artista));

            Artista23 *artista = buscar_artista_23(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Artista nao encontrado.\n");
            }
            else
            {
                printf("Digite o nome do album: ");
                ler_string(nome_album, sizeof(nome_album));
                remover_album_23(&(artista->albuns1), nome_album);
                printf("Album '%s' removido.\n", nome_album);
            }
        }
        else if (opcao == 8)
        {
            char nome[100];
            printf("Digite o nome do artista a remover: ");
            ler_string(nome, sizeof(nome));

            remover_artista_23(&raiz_artistas, nome);
            printf("Artista '%s' removido.\n", nome);
        }
        else if (opcao == 9)

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

    liberar_arvore_artistas_23(&raiz_artistas);

    return 0;
}