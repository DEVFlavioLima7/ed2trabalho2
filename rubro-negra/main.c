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
    printf("\n--- Menu de Busca ---\n");
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
    while (scanf("%d", &valor) != 1)
    {
        printf("Entrada invalida. Por favor, digite um numero: ");

        while (getchar() != '\n')
            ;
    }
    getchar();
    return valor;
}

int main()
{
    Artista *raiz_artistas = NULL;
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

            if (buscar_artista(raiz_artistas, nome) != NULL)
            {
                printf("Erro: Artista '%s' ja existe na biblioteca.\n", nome);
            }
            else
            {
                printf("Digite o estilo do artista: ");
                ler_string(estilo, sizeof(estilo));

                raiz_artistas = inserir_artista(raiz_artistas, nome, estilo);
                if (raiz_artistas != NULL)
                {
                    raiz_artistas->cor = PRETO;
                }
                printf("Artista '%s' inserido com sucesso!\n", nome);
            }
        }
        else if (opcao == 2)
        {
            if (raiz_artistas == NULL)
            {
                printf("A biblioteca esta vazia. Insira um artista primeiro.\n");
                continue;
            }

            char nome_artista[100], titulo[100];
            int ano;

            printf("Digite o nome do artista: ");
            ler_string(nome_artista, sizeof(nome_artista));

            Artista *artista = buscar_artista(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Erro: Artista '%s' nao encontrado.\n", nome_artista);
            }
            else
            {
                printf("Digite o titulo do album: ");
                ler_string(titulo, sizeof(titulo));

                if (buscar_album(artista->albuns, titulo) != NULL)
                {
                    printf("Erro: O album '%s' ja existe para o artista '%s'.\n", titulo, nome_artista);
                }
                else
                {
                    printf("Digite o ano do album: ");
                    ano = ler_inteiro();

                    inserir_album(artista, titulo, ano);
                    printf("Album '%s' adicionado ao artista '%s'.\n", titulo, nome_artista);
                }
            }
        }
        else if (opcao == 3)
        {
            if (raiz_artistas == NULL)
            {
                printf("A biblioteca esta vazia. Insira um artista e um album primeiro.\n");
                continue;
            }
            char nome_artista[100], nome_album[100], titulo[100];
            int minutos;

            printf("Digite o nome do artista: ");
            ler_string(nome_artista, sizeof(nome_artista));

            Artista *artista = buscar_artista(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Erro: Artista '%s' nao encontrado.\n", nome_artista);
            }
            else
            {
                printf("Digite o nome do album: ");
                ler_string(nome_album, sizeof(nome_album));

                Album *album = buscar_album(artista->albuns, nome_album);
                if (album == NULL)
                {
                    printf("Erro: Album '%s' nao encontrado para o artista '%s'.\n", nome_album, nome_artista);
                }
                else
                {
                    printf("Digite o titulo da musica: ");
                    ler_string(titulo, sizeof(titulo));

                    if (buscar_musica(album, titulo) != NULL)
                    {
                        printf("Erro: A musica '%s' ja existe no album '%s'.\n", titulo, nome_album);
                    }
                    else
                    {
                        printf("Digite a duracao em minutos: ");
                        minutos = ler_inteiro();

                        Musica *nova_musica = criar_musica(titulo, minutos);

                        if (nova_musica == NULL)
                        {
                            printf("Erro: Falha ao alocar memoria para a musica.\n");
                        }
                        else
                        {
                            inserir_musica_ordenado(&(album->musicas), nova_musica);
                            album->qtd_musicas++;
                            printf("Musica '%s' adicionada ao album '%s'.\n", titulo, nome_album);
                        }
                    }
                }
            }
        }
        else if (opcao == 4)
        {
            if (raiz_artistas == NULL)
            {
                printf("A biblioteca de musicas esta vazia.\n");
            }
            else
            {
                printf("\n--- Biblioteca Completa ---\n");
                exibir_artistas(raiz_artistas);
            }
        }
        else if (opcao == 5) // --- NOVA SEÇÃO DE BUSCA ---
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

                printf("Caminho da busca:\n");
                Artista *encontrado = buscar_artista_com_caminho(raiz_artistas, nome);
                if (encontrado)
                {
                    printf("Artista '%s' encontrado!\n", nome);
                    exibir_albuns_do_artista(encontrado);
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

                Artista *artista = buscar_artista(raiz_artistas, nome_artista);
                if (artista == NULL)
                {
                    printf("Artista '%s' nao encontrado.\n", nome_artista);
                }
                else
                {
                    printf("Digite o titulo do album para buscar: ");
                    ler_string(nome_album, sizeof(nome_album));
                    Album *album_encontrado = buscar_album(artista->albuns, nome_album);
                    if (album_encontrado)
                    {
                        printf("Album '%s' encontrado para o artista '%s'!\n", nome_album, nome_artista);
                        printf(" -> Ano: %d\n", album_encontrado->ano);
                        printf(" -> Musicas:\n");
                        exibir_musicas_do_album(album_encontrado->musicas);
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
                Artista *artista = buscar_artista(raiz_artistas, nome_artista);

                if (artista == NULL)
                {
                    printf("Artista '%s' nao encontrado.\n", nome_artista);
                }
                else
                {
                    printf("Digite o titulo do album: ");
                    ler_string(nome_album, sizeof(nome_album));
                    Album *album = buscar_album(artista->albuns, nome_album);

                    if (album == NULL)
                    {
                        printf("Album '%s' nao encontrado para o artista '%s'.\n", nome_album, nome_artista);
                    }
                    else
                    {
                        printf("Digite o titulo da musica para buscar: ");
                        ler_string(nome_musica, sizeof(nome_musica));
                        Musica *musica_encontrada = buscar_musica(album, nome_musica);

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
            if (raiz_artistas == NULL)
            {
                printf("A biblioteca esta vazia.\n");
                continue;
            }
            char nome_artista[100], nome_album[100], titulo[100];

            printf("Digite o nome do artista: ");
            ler_string(nome_artista, sizeof(nome_artista));

            Artista *artista = buscar_artista(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Erro: Artista '%s' nao encontrado.\n", nome_artista);
            }
            else
            {
                printf("Digite o nome do album: ");
                ler_string(nome_album, sizeof(nome_album));

                Album *album = buscar_album(artista->albuns, nome_album);
                if (album == NULL)
                {
                    printf("Erro: Album '%s' nao encontrado.\n", nome_album);
                }
                else
                {
                    printf("Digite o titulo da musica a ser removida: ");
                    ler_string(titulo, sizeof(titulo));

                    if (buscar_musica(album, titulo) == NULL)
                    {
                        printf("Erro: Musica '%s' nao encontrada no album '%s'.\n", titulo, nome_album);
                    }
                    else
                    {
                        remover_musica(album, titulo);
                        printf("Musica '%s' removida com sucesso.\n", titulo);
                    }
                }
            }
        }
        else if (opcao == 7)
        {
            if (raiz_artistas == NULL)
            {
                printf("A biblioteca esta vazia.\n");
                continue;
            }
            char nome_artista[100], nome_album[100];

            printf("Digite o nome do artista: ");
            ler_string(nome_artista, sizeof(nome_artista));

            Artista *artista = buscar_artista(raiz_artistas, nome_artista);
            if (artista == NULL)
            {
                printf("Erro: Artista '%s' nao encontrado.\n", nome_artista);
            }
            else
            {
                printf("Digite o nome do album a ser removido: ");
                ler_string(nome_album, sizeof(nome_album));

                if (buscar_album(artista->albuns, nome_album) == NULL)
                {
                    printf("Erro: Album '%s' nao encontrado para o artista '%s'.\n", nome_album, nome_artista);
                }
                else
                {
                    remover_album(artista, nome_album);
                    printf("Album '%s' removido com sucesso.\n", nome_album);
                }
            }
        }
        else if (opcao == 8)
        {
            if (raiz_artistas == NULL)
            {
                printf("A biblioteca esta vazia. Nao ha artistas para remover.\n");
                continue;
            }
            char nome[100];
            printf("Digite o nome do artista a remover: ");
            ler_string(nome, sizeof(nome));

            if (buscar_artista(raiz_artistas, nome) == NULL)
            {
                printf("Erro: Artista '%s' nao encontrado.\n", nome);
            }
            else
            {
                remover_artista(&raiz_artistas, nome);
                printf("Artista '%s' e todos os seus dados foram removidos.\n", nome);
            }
        }
        else if (opcao == 9)
        {
            popular_arvore_para_experimento(&raiz_artistas);
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