#include "album.h"
#include "musica.h"

Album *rotacao_esquerda_album(Album *raiz_subarvore)
{
  Album *nova_raiz_subarvore = raiz_subarvore->direita;
  raiz_subarvore->direita = nova_raiz_subarvore->esquerda;
  if (nova_raiz_subarvore->esquerda != NULL)
    nova_raiz_subarvore->esquerda->pai = raiz_subarvore;
  nova_raiz_subarvore->pai = raiz_subarvore->pai;
  nova_raiz_subarvore->esquerda = raiz_subarvore;
  raiz_subarvore->pai = nova_raiz_subarvore;
  nova_raiz_subarvore->cor = raiz_subarvore->cor;
  raiz_subarvore->cor = VERMELHO;
  return nova_raiz_subarvore;
}

Album *rotacao_direita_album(Album *raiz_subarvore)
{
  Album *nova_raiz_subarvore = raiz_subarvore->esquerda;
  raiz_subarvore->esquerda = nova_raiz_subarvore->direita;
  if (nova_raiz_subarvore->direita != NULL)
    nova_raiz_subarvore->direita->pai = raiz_subarvore;
  nova_raiz_subarvore->pai = raiz_subarvore->pai;
  nova_raiz_subarvore->direita = raiz_subarvore;
  raiz_subarvore->pai = nova_raiz_subarvore;
  nova_raiz_subarvore->cor = raiz_subarvore->cor;
  raiz_subarvore->cor = VERMELHO;
  return nova_raiz_subarvore;
}

Album *minimo_album(Album *no)
{
  if (no->esquerda == NULL)
    return no;
  return minimo_album(no->esquerda);
}

Album *inserir_album_recursivo(Album *no, char titulo[], int ano)
{
  if (no == NULL)
  {
    Album *novo_no = (Album *)malloc(sizeof(Album));
    strcpy(novo_no->titulo, titulo);
    novo_no->ano = ano;
    novo_no->qtd_musicas = 0;
    novo_no->musicas = NULL;
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    novo_no->pai = NULL;
    novo_no->cor = VERMELHO;
    return novo_no;
  }
  int comparacao = strcmp(titulo, no->titulo);
  if (comparacao < 0)
  {
    no->esquerda = inserir_album_recursivo(no->esquerda, titulo, ano);
    if (no->esquerda != NULL)
      no->esquerda->pai = no;
  }
  else if (comparacao > 0)
  {
    no->direita = inserir_album_recursivo(no->direita, titulo, ano);
    if (no->direita != NULL)
      no->direita->pai = no;
  }

  if ((no->direita != NULL && no->direita->cor == VERMELHO) && !(no->esquerda != NULL && no->esquerda->cor == VERMELHO))
    no = rotacao_esquerda_album(no);
  if ((no->esquerda != NULL && no->esquerda->cor == VERMELHO) && (no->esquerda->esquerda != NULL && no->esquerda->esquerda->cor == VERMELHO))
    no = rotacao_direita_album(no);
  if ((no->esquerda != NULL && no->esquerda->cor == VERMELHO) && (no->direita != NULL && no->direita->cor == VERMELHO))
  {
    no->cor = !no->cor;
    no->esquerda->cor = !no->esquerda->cor;
    no->direita->cor = !no->direita->cor;
  }
  return no;
}

Album *inserir_album(Artista *artista, char titulo[], int ano)
{
  if (artista == NULL)
  {
    printf("Erro: Artista nulo.\n");
    return NULL;
  }
  artista->albuns = inserir_album_recursivo(artista->albuns, titulo, ano);
  if (artista->albuns != NULL)
    artista->albuns->cor = PRETO;
  artista->num_albuns++;
  return artista->albuns;
}

Album *balancear_album_rb(Album *no)
{
  if ((no->direita != NULL && no->direita->cor == VERMELHO))
    no = rotacao_esquerda_album(no);
  if ((no->esquerda != NULL && no->esquerda->cor == VERMELHO) && (no->esquerda->esquerda != NULL && no->esquerda->esquerda->cor == VERMELHO))
    no = rotacao_direita_album(no);
  if ((no->esquerda != NULL && no->esquerda->cor == VERMELHO) && (no->direita != NULL && no->direita->cor == VERMELHO))
  {
    no->cor = !no->cor;
    no->esquerda->cor = !no->esquerda->cor;
    no->direita->cor = !no->direita->cor;
  }
  return no;
}

Album *mover_vermelho_esquerda_album(Album *no)
{
  no->cor = !no->cor;
  if (no->esquerda != NULL)
    no->esquerda->cor = !no->esquerda->cor;
  if (no->direita != NULL)
    no->direita->cor = !no->direita->cor;

  if ((no->direita->esquerda != NULL && no->direita->esquerda->cor == VERMELHO))
  {
    no->direita = rotacao_direita_album(no->direita);
    no = rotacao_esquerda_album(no);

    no->cor = !no->cor;
    if (no->esquerda != NULL)
      no->esquerda->cor = !no->esquerda->cor;
    if (no->direita != NULL)
      no->direita->cor = !no->direita->cor;
  }
  return no;
}

Album *mover_vermelho_direita_album(Album *no)
{
  no->cor = !no->cor;
  if (no->esquerda != NULL)
    no->esquerda->cor = !no->esquerda->cor;
  if (no->direita != NULL)
    no->direita->cor = !no->direita->cor;

  if ((no->esquerda->esquerda != NULL && no->esquerda->esquerda->cor == VERMELHO))
  {
    no = rotacao_direita_album(no);

    no->cor = !no->cor;
    if (no->esquerda != NULL)
      no->esquerda->cor = !no->esquerda->cor;
    if (no->direita != NULL)
      no->direita->cor = !no->direita->cor;
  }
  return no;
}

Album *remover_menor_album(Album *no)
{
  if (no->esquerda == NULL)
  {
    free(no);
    return NULL;
  }
  if (!(no->esquerda != NULL && no->esquerda->cor == VERMELHO) && !(no->esquerda->esquerda != NULL && no->esquerda->esquerda->cor == VERMELHO))
  {
    no = mover_vermelho_esquerda_album(no);
  }
  no->esquerda = remover_menor_album(no->esquerda);
  if (no->esquerda != NULL)
    no->esquerda->pai = no;

  return balancear_album_rb(no);
}

Album *remover_no_album(Album *no, char titulo[])
{
  if (strcmp(titulo, no->titulo) < 0)
  {
    if (!(no->esquerda != NULL && no->esquerda->cor == VERMELHO) && !(no->esquerda->esquerda != NULL && no->esquerda->esquerda->cor == VERMELHO))
    {
      no = mover_vermelho_esquerda_album(no);
    }
    no->esquerda = remover_no_album(no->esquerda, titulo);
    if (no->esquerda != NULL)
      no->esquerda->pai = no;
  }
  else
  {
    if ((no->esquerda != NULL && no->esquerda->cor == VERMELHO))
    {
      no = rotacao_direita_album(no);
    }
    if (strcmp(titulo, no->titulo) == 0 && (no->direita == NULL))
    {
      liberar_lista_musicas(&(no->musicas));
      free(no);
      return NULL;
    }
    if (!(no->direita != NULL && no->direita->cor == VERMELHO) && !(no->direita->esquerda != NULL && no->direita->esquerda->cor == VERMELHO))
    {
      no = mover_vermelho_direita_album(no);
    }
    if (strcmp(titulo, no->titulo) == 0)
    {
      Album *sucessor = minimo_album(no->direita);
      strcpy(no->titulo, sucessor->titulo);
      no->ano = sucessor->ano;
      no->direita = remover_menor_album(no->direita);
      if (no->direita != NULL)
        no->direita->pai = no;
    }
    else
    {
      no->direita = remover_no_album(no->direita, titulo);
      if (no->direita != NULL)
        no->direita->pai = no;
    }
  }
  return balancear_album_rb(no);
}

void remover_album(Artista *artista, char titulo[])
{
  if (artista == NULL || artista->albuns == NULL)
  {
    printf("Artista ou lista de albuns vazia.\n");
    return;
  }

  if (!(artista->albuns != NULL && artista->albuns->esquerda != NULL && artista->albuns->esquerda->cor == VERMELHO) && !(artista->albuns != NULL && artista->albuns->direita != NULL && artista->albuns->direita->cor == VERMELHO))
  {
    (artista->albuns)->cor = VERMELHO;
  }

  artista->albuns = remover_no_album(artista->albuns, titulo);
  artista->num_albuns--;

  if (artista->albuns != NULL)
  {
    artista->albuns->cor = PRETO;
    artista->albuns->pai = NULL;
  }
}

void exibir_albuns_recursivo(Album *raiz)
{
  if (raiz != NULL)
  {
    exibir_albuns_recursivo(raiz->esquerda);
    const char *cor_str = (raiz->cor == VERMELHO) ? "VERMELHO" : "PRETO";
    printf("  -> album: %-25s | Ano: %d | Cor: %s\n", raiz->titulo, raiz->ano, cor_str);
    exibir_musicas_do_album(raiz->musicas);
    exibir_albuns_recursivo(raiz->direita);
  }
}

void exibir_albuns_do_artista(Artista *artista)
{
  if (artista != NULL)
  {
    printf("albuns de '%s':\n", artista->nome);
    if (artista->albuns == NULL)
    {
      printf("  -> Nenhum album cadastrado.\n");
    }
    else
    {
      exibir_albuns_recursivo(artista->albuns);
    }
  }
}

Album *buscar_album(Album *raiz_album, char titulo[])
{
  Album *resultado = raiz_album;
  while (resultado != NULL)
  {
    int comparacao = strcmp(titulo, resultado->titulo);
    if (comparacao == 0)
      break;
    resultado = (comparacao < 0) ? resultado->esquerda : resultado->direita;
  }
  return resultado;
}

void liberar_arvore_albuns(Album **raiz_albuns)
{
  if (*raiz_albuns != NULL)
  {
    liberar_arvore_albuns(&((*raiz_albuns)->esquerda));
    liberar_arvore_albuns(&((*raiz_albuns)->direita));
    liberar_lista_musicas(&((*raiz_albuns)->musicas));
    free(*raiz_albuns);
    *raiz_albuns = NULL;
  }
}