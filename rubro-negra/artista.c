#include "artista.h"
#include "album.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



static void atualizar_filho_do_pai(Artista *pai, Artista *antigo, Artista *novo) {
    if (pai == NULL) return;
    if (pai->esquerda == antigo) pai->esquerda = novo;
    else if (pai->direita == antigo) pai->direita = novo;
}



Artista *rotacao_esquerda_artista(Artista *raiz_subarvore)
{
    if (raiz_subarvore == NULL || raiz_subarvore->direita == NULL) return raiz_subarvore;

    Artista *nova_raiz_subarvore = raiz_subarvore->direita;
    raiz_subarvore->direita = nova_raiz_subarvore->esquerda;
    if (nova_raiz_subarvore->esquerda != NULL)
        nova_raiz_subarvore->esquerda->pai = raiz_subarvore;

    // Atualiza pai da nova raiz e também o ponteiro do pai antigo
    Artista *pai_antigo = raiz_subarvore->pai;
    nova_raiz_subarvore->pai = pai_antigo;
    atualizar_filho_do_pai(pai_antigo, raiz_subarvore, nova_raiz_subarvore);

    nova_raiz_subarvore->esquerda = raiz_subarvore;
    raiz_subarvore->pai = nova_raiz_subarvore;

    // troca cores preservando propriedade de LLRB/RB
    nova_raiz_subarvore->cor = raiz_subarvore->cor;
    raiz_subarvore->cor = VERMELHO;

    return nova_raiz_subarvore;
}


Artista *rotacao_direita_artista(Artista *raiz_subarvore)
{
    if (raiz_subarvore == NULL || raiz_subarvore->esquerda == NULL) return raiz_subarvore;

    Artista *nova_raiz_subarvore = raiz_subarvore->esquerda;
    raiz_subarvore->esquerda = nova_raiz_subarvore->direita;
    if (nova_raiz_subarvore->direita != NULL)
        nova_raiz_subarvore->direita->pai = raiz_subarvore;

    Artista *pai_antigo = raiz_subarvore->pai;
    nova_raiz_subarvore->pai = pai_antigo;
    atualizar_filho_do_pai(pai_antigo, raiz_subarvore, nova_raiz_subarvore);

    nova_raiz_subarvore->direita = raiz_subarvore;
    raiz_subarvore->pai = nova_raiz_subarvore;

    nova_raiz_subarvore->cor = raiz_subarvore->cor;
    raiz_subarvore->cor = VERMELHO;

    return nova_raiz_subarvore;
}

static Artista *minimo_artista(Artista *no)
{
  Artista *no_minimo = no;
  while (no_minimo != NULL && no_minimo->esquerda != NULL)
  {
    no_minimo = no_minimo->esquerda;
  }
  return no_minimo;
}

Artista *inserir_artista(Artista *no, char nome[], char estilo[])
{
  Artista *no_retorno = no;
  if (no == NULL)
  {
    Artista *novo_no = (Artista *)malloc(sizeof(Artista));
    strcpy(novo_no->nome, nome);
    strcpy(novo_no->estilo, estilo);
    novo_no->num_albuns = 0;
    novo_no->albuns = NULL;
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    novo_no->pai = NULL;
    novo_no->cor = VERMELHO;
    no_retorno = novo_no;
  }
  else
  {
    int comparacao = strcmp(nome, no->nome);
    if (comparacao < 0)
    {
      no->esquerda = inserir_artista(no->esquerda, nome, estilo);
      if (no->esquerda != NULL)
        no->esquerda->pai = no;
    }
    else if (comparacao > 0)
    {
      no->direita = inserir_artista(no->direita, nome, estilo);
      if (no->direita != NULL)
        no->direita->pai = no;
    }

    if ((no->direita != NULL && no->direita->cor == VERMELHO) && !(no->esquerda != NULL && no->esquerda->cor == VERMELHO))
      no = rotacao_esquerda_artista(no);
    if ((no->esquerda != NULL && no->esquerda->cor == VERMELHO) && (no->esquerda->esquerda != NULL && no->esquerda->esquerda->cor == VERMELHO))
      no = rotacao_direita_artista(no);
    if ((no->esquerda != NULL && no->esquerda->cor == VERMELHO) && (no->direita != NULL && no->direita->cor == VERMELHO))
    {
      no->cor = !no->cor;
      no->esquerda->cor = !no->esquerda->cor;
      no->direita->cor = !no->direita->cor;
    }
    no_retorno = no;
  }
  return no_retorno;
}

Artista *balancear_artista_rb(Artista *no)
{
  Artista *no_balanceado = no;
  if ((no_balanceado->direita != NULL && no_balanceado->direita->cor == VERMELHO))
    no_balanceado = rotacao_esquerda_artista(no_balanceado);
  if ((no_balanceado->esquerda != NULL && no_balanceado->esquerda->cor == VERMELHO) && (no_balanceado->esquerda->esquerda != NULL && no_balanceado->esquerda->esquerda->cor == VERMELHO))
    no_balanceado = rotacao_direita_artista(no_balanceado);
  if ((no_balanceado->esquerda != NULL && no_balanceado->esquerda->cor == VERMELHO) && (no_balanceado->direita != NULL && no_balanceado->direita->cor == VERMELHO))
  {
    no_balanceado->cor = !no_balanceado->cor;
    no_balanceado->esquerda->cor = !no_balanceado->esquerda->cor;
    no_balanceado->direita->cor = !no_balanceado->direita->cor;
  }
  return no_balanceado;
}

Artista *mover_vermelho_esquerda(Artista *no)
{
  Artista *no_movido = no;
  no_movido->cor = !no_movido->cor;
  if (no_movido->esquerda != NULL)
    no_movido->esquerda->cor = !no_movido->esquerda->cor;
  if (no_movido->direita != NULL)
    no_movido->direita->cor = !no_movido->direita->cor;

  if ((no_movido->direita->esquerda != NULL && no_movido->direita->esquerda->cor == VERMELHO))
  {
    no_movido->direita = rotacao_direita_artista(no_movido->direita);
    no_movido = rotacao_esquerda_artista(no_movido);

    no_movido->cor = !no_movido->cor;
    if (no_movido->esquerda != NULL)
      no_movido->esquerda->cor = !no_movido->esquerda->cor;
    if (no_movido->direita != NULL)
      no_movido->direita->cor = !no_movido->direita->cor;
  }
  return no_movido;
}

Artista *mover_vermelho_direita(Artista *no)
{
  Artista *no_movido = no;
  no_movido->cor = !no_movido->cor;
  if (no_movido->esquerda != NULL)
    no_movido->esquerda->cor = !no_movido->esquerda->cor;
  if (no_movido->direita != NULL)
    no_movido->direita->cor = !no_movido->direita->cor;

  if ((no_movido->esquerda->esquerda != NULL && no_movido->esquerda->esquerda->cor == VERMELHO))
  {
    no_movido = rotacao_direita_artista(no_movido);

    no_movido->cor = !no_movido->cor;
    if (no_movido->esquerda != NULL)
      no_movido->esquerda->cor = !no_movido->esquerda->cor;
    if (no_movido->direita != NULL)
      no_movido->direita->cor = !no_movido->direita->cor;
  }
  return no_movido;
}

Artista *remover_menor_artista(Artista *no)
{
  Artista *no_retorno = no;
  if (no->esquerda == NULL)
  {
    free(no);
    no_retorno = NULL;
  }
  else
  {
    if (!(no->esquerda != NULL && no->esquerda->cor == VERMELHO) && !(no->esquerda->esquerda != NULL && no->esquerda->esquerda->cor == VERMELHO))
    {
      no_retorno = mover_vermelho_esquerda(no);
    }
    no_retorno->esquerda = remover_menor_artista(no_retorno->esquerda);
    if (no_retorno->esquerda != NULL)
      no_retorno->esquerda->pai = no_retorno;
    no_retorno = balancear_artista_rb(no_retorno);
  }
  return no_retorno;
}

Artista *remover_no_artista(Artista *no, char nome[])
{
  Artista *no_retorno = no;
  if (strcmp(nome, no_retorno->nome) < 0)
  {
    if (!(no_retorno->esquerda != NULL && no_retorno->esquerda->cor == VERMELHO) && !(no_retorno->esquerda->esquerda != NULL && no_retorno->esquerda->esquerda->cor == VERMELHO))
    {
      no_retorno = mover_vermelho_esquerda(no_retorno);
    }
    no_retorno->esquerda = remover_no_artista(no_retorno->esquerda, nome);
    if (no_retorno->esquerda != NULL)
      no_retorno->esquerda->pai = no_retorno;
  }
  else
  {
    if ((no_retorno->esquerda != NULL && no_retorno->esquerda->cor == VERMELHO))
    {
      no_retorno = rotacao_direita_artista(no_retorno);
    }
    if (strcmp(nome, no_retorno->nome) == 0 && (no_retorno->direita == NULL))
    {
      free(no_retorno);
      no_retorno = NULL;
    }
    else
    {
      if (!(no_retorno->direita != NULL && no_retorno->direita->cor == VERMELHO) && !(no_retorno->direita->esquerda != NULL && no_retorno->direita->esquerda->cor == VERMELHO))
      {
        no_retorno = mover_vermelho_direita(no_retorno);
      }
      if (strcmp(nome, no_retorno->nome) == 0)
      {
        Artista *sucessor = minimo_artista(no_retorno->direita);
        strcpy(no_retorno->nome, sucessor->nome);
        strcpy(no_retorno->estilo, sucessor->estilo);
        no_retorno->albuns = sucessor->albuns;
        no_retorno->num_albuns = sucessor->num_albuns;
        no_retorno->direita = remover_menor_artista(no_retorno->direita);
        if (no_retorno->direita != NULL)
          no_retorno->direita->pai = no_retorno;
      }
      else
      {
        no_retorno->direita = remover_no_artista(no_retorno->direita, nome);
        if (no_retorno->direita != NULL)
          no_retorno->direita->pai = no_retorno;
      }
    }
  }

  if (no_retorno != NULL)
  {
    no_retorno = balancear_artista_rb(no_retorno);
  }

  return no_retorno;
}

void remover_artista(Artista **raiz, char nome[])
{
  if (*raiz != NULL)
  {
    Artista *no_a_remover = buscar_artista(*raiz, nome);
    if (no_a_remover != NULL)
    {
      liberar_arvore_albuns(&(no_a_remover->albuns));
      no_a_remover->albuns = NULL;

      if (!((*raiz)->esquerda != NULL && (*raiz)->esquerda->cor == VERMELHO) && !((*raiz)->direita != NULL && (*raiz)->direita->cor == VERMELHO))
      {
        (*raiz)->cor = VERMELHO;
      }

      *raiz = remover_no_artista(*raiz, nome);

      if (*raiz != NULL)
      {
        (*raiz)->cor = PRETO;
        (*raiz)->pai = NULL;
      }
    }
    else
    {
      printf("Artista '%s' não encontrado para remoção.\n", nome);
    }
  }
  else
  {
    printf("A árvore está vazia.\n");
  }
  return;
}

void exibir_artistas(Artista *raiz)
{
  if (raiz != NULL)
  {
    exibir_artistas(raiz->esquerda);
    const char *cor_str = (raiz->cor == VERMELHO) ? "VERMELHO" : "PRETO";
    printf("Artista: %-20s | Estilo: %-20s | Cor: %s\n", raiz->nome, raiz->estilo, cor_str);
    exibir_artistas(raiz->direita);
  }
}

Artista *buscar_artista(Artista *raiz, char nome[])
{
  Artista *resultado = NULL;
  if (raiz == NULL)
  {
    resultado = NULL;
  }
  else
  {
    int comparacao = strcmp(nome, raiz->nome);
    if (comparacao == 0)
    {
      resultado = raiz;
    }
    else if (comparacao < 0)
    {
      resultado = buscar_artista(raiz->esquerda, nome);
    }
    else
    {
      resultado = buscar_artista(raiz->direita, nome);
    }
  }
  return resultado;
}

Artista *buscar_artista_com_caminho(Artista *raiz, char nome[])
{
  Artista *resultado = NULL;
  if (raiz != NULL)
  {
    printf(" -> Visitando: %s\n", raiz->nome);
  }

  if (raiz == NULL)
  {
    resultado = NULL;
  }
  else
  {
    int comparacao = strcmp(nome, raiz->nome);
    if (comparacao == 0)
    {
      resultado = raiz;
    }
    else if (comparacao < 0)
    {
      resultado = buscar_artista_com_caminho(raiz->esquerda, nome);
    }
    else
    {
      resultado = buscar_artista_com_caminho(raiz->direita, nome);
    }
  }
  return resultado;
}

void executar_experimento_busca(Artista *raiz)
{
  const char *lista_de_nomes[] = {
      "Queen",
      "AC/DC",
      "Nirvana",
      "The Beatles",
      "Metallica"};
  int num_buscas = sizeof(lista_de_nomes) / sizeof(lista_de_nomes[0]);
  printf("--- Iniciando Experimento de Busca para %d Itens ---\n", num_buscas);
  clock_t inicio = clock();
  for (int i = 0; i < num_buscas; i++)
  {
    printf("\nBuscando por: '%s'...\n", lista_de_nomes[i]);
    Artista *encontrado = buscar_artista_com_caminho(raiz, (char *)lista_de_nomes[i]);
    if (encontrado != NULL)
    {
      printf("... Artista '%s' ENCONTRADO.\n", lista_de_nomes[i]);
    }
    else
    {
      printf("... Artista '%s' NÃO ENCONTRADO.\n", lista_de_nomes[i]);
    }
  }
  clock_t fim = clock();
  double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("\n--- Fim do Experimento ---\n");
  printf("Tempo total gasto nas %d buscas: %f segundos.\n", num_buscas, tempo_gasto);
}

// Função wrapper para garantir raiz preta e pai NULL
Artista *inserir_artista_root(Artista *raiz, char nome[], char estilo[])
{
    raiz = inserir_artista(raiz, nome, estilo);
    if (raiz != NULL) {
        raiz->cor = PRETO;
        raiz->pai = NULL;
    }
    return raiz;
}
