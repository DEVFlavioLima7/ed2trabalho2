#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H


// ---------- Estrutura de Músicas (Lista Ordenada) ----------
typedef struct Musica {
    char titulo[100];       // Título da música
    int minutos;            // Duração em minutos
    struct Musica *prox;    // Ponteiro para a próxima música na lista
} Musica;

// ----------Estrutura de Álbum (Árvore Rubro-Negra / 2-3) ----------
typedef struct Album {
    char titulo[100];       // Título do álbum (chave principal)
    int ano;                // Ano de lançamento
    int qtd_musicas;        // Quantidade de músicas
    Musica *musicas;        // Lista encadeada de músicas

    // Ponteiros para Árvore Rubro-Negra (Parte 1)
    struct Album *esq, *dir;
    int cor;                // 1 = Vermelho, 0 = Preto

    // Preparado para Árvore 2-3 (Parte 2)
    struct Album *meio;     // Ponteiro para o filho do meio (apenas na 2-3)
    char chaveExtra[100];   // Segunda chave na 2-3
} Album;

// ---------- Estrutura de Artista (Árvore Rubro-Negra / 2-3) ----------
typedef struct Artista {
    char nome[100];         // Nome do artista (chave principal)
    char estilo[50];        // Estilo musical
    int qtd_albuns;         // Quantidade de álbuns
    Album *albuns;          // Árvore de álbuns

    // Ponteiros para Árvore Rubro-Negra (Parte 1)
    struct Artista *esq, *dir;
    int cor;                // 1 = Vermelho, 0 = Preto

    // Árvore 2-3 (Parte 2)
    struct Artista *meio;   // Ponteiro para o filho do meio (apenas na 2-3)
    char chaveExtra[100];   // Segunda chave na 2-3
} Artista;

// ======================================
// Parte 3: Gerenciamento de Memória (Árvore 4-5)
// ======================================

typedef struct BlocoMemoria {
    char status;            // 'L' = Livre, 'O' = Ocupado
    int blocoInicial;       // Número do bloco inicial
    int blocoFinal;         // Número do bloco final
    unsigned long enderecoInicial; // Endereço inicial
    unsigned long enderecoFinal;   // Endereço final

    // Estrutura da Árvore 4-5
    struct BlocoMemoria *filhos[5]; // Até 5 filhos
    int numChaves;                  // Quantidade de chaves
    int chaves[4];                  // Chaves do nó
} BlocoMemoria;

#endif
