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
  return (no == NULL || no->esquerda == NULL) ? no : minimo_album(no->esquerda);
}

int eh_vermelho(Album *no)
{
  return no != NULL && no->cor == VERMELHO;
}

Album *criar_album(char titulo[], int ano)
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

Album *inserir_album_recursivo(Album *no, char titulo[], int ano)
{

  if (no == NULL)
  {

    no = criar_album(titulo, ano);
  }
  else
  {

    int comparacao = strcmp(titulo, no->titulo);

    if (comparacao < 0)
    {

      Album *filho_esquerdo = inserir_album_recursivo(no->esquerda, titulo, ano);
      no->esquerda = filho_esquerdo;

      if (filho_esquerdo != NULL)
      {
        filho_esquerdo->pai = no;
      }
    }
    else if (comparacao > 0)
    {

      Album *filho_direito = inserir_album_recursivo(no->direita, titulo, ano);
      no->direita = filho_direito;

      if (filho_direito != NULL)
      {
        filho_direito->pai = no;
      }
    }

    if (eh_vermelho(no->direita) && !eh_vermelho(no->esquerda))
    {
      no = rotacao_esquerda_album(no);
    }

    if (eh_vermelho(no->esquerda) && eh_vermelho(no->esquerda->esquerda))
    {
      no = rotacao_direita_album(no);
    }

    if (eh_vermelho(no->esquerda) && eh_vermelho(no->direita))
    {
      no->cor = VERMELHO;
      no->esquerda->cor = PRETO;
      no->direita->cor = PRETO;
    }
  }

  return no;
}

Album *inserir_album(Artista *artista, char titulo[], int ano)
{

  Album *album_retornado = NULL;

  if (artista == NULL)
  {
    printf("Erro: Artista nulo.\n");
  }
  else
  {

    artista->albuns = inserir_album_recursivo(artista->albuns, titulo, ano);

    if (artista->albuns != NULL)
    {
      artista->albuns->cor = PRETO;
    }

    artista->num_albuns++;

    album_retornado = artista->albuns;
  }

  return album_retornado;
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

  Album *no_retornado = no;

  if (no->esquerda == NULL)
  {

    free(no);

    no_retornado = NULL;
  }
  else
  {

    if (!eh_vermelho(no_retornado->esquerda) && !eh_vermelho(no_retornado->esquerda->esquerda))
    {
      no_retornado = mover_vermelho_esquerda_album(no_retornado);
    }

    no_retornado->esquerda = remover_menor_album(no_retornado->esquerda);
    if (no_retornado->esquerda != NULL)
    {
      no_retornado->esquerda->pai = no_retornado;
    }

    no_retornado = balancear_album_rb(no_retornado);
  }

  return no_retornado;
}

Album *remover_no_album(Album *no, char titulo[])
{
  Album *no_a_retornar = no;

  if (strcmp(titulo, no_a_retornar->titulo) < 0)
  {
    if (!(no_a_retornar->esquerda != NULL && no_a_retornar->esquerda->cor == VERMELHO) && !(no_a_retornar->esquerda->esquerda != NULL && no_a_retornar->esquerda->esquerda->cor == VERMELHO))
      no_a_retornar = mover_vermelho_esquerda_album(no_a_retornar);

    no_a_retornar->esquerda = remover_no_album(no_a_retornar->esquerda, titulo);
    if (no_a_retornar->esquerda != NULL)
      no_a_retornar->esquerda->pai = no_a_retornar;
  }
  else
  {
    if ((no_a_retornar->esquerda != NULL && no_a_retornar->esquerda->cor == VERMELHO))
      no_a_retornar = rotacao_direita_album(no_a_retornar);

    if (strcmp(titulo, no_a_retornar->titulo) == 0 && (no_a_retornar->direita == NULL))
    {
      liberar_lista_musicas(&(no_a_retornar->musicas));
      free(no_a_retornar);
      no_a_retornar = NULL;
    }
    else
    {
      if (!(no_a_retornar->direita != NULL && no_a_retornar->direita->cor == VERMELHO) && !(no_a_retornar->direita->esquerda != NULL && no_a_retornar->direita->esquerda->cor == VERMELHO))
        no_a_retornar = mover_vermelho_direita_album(no_a_retornar);

      if (strcmp(titulo, no_a_retornar->titulo) == 0)
      {
        Album *sucessor = minimo_album(no_a_retornar->direita);
        strcpy(no_a_retornar->titulo, sucessor->titulo);
        no_a_retornar->ano = sucessor->ano;
        no_a_retornar->direita = remover_menor_album(no_a_retornar->direita);
        if (no_a_retornar->direita != NULL)
          no_a_retornar->direita->pai = no_a_retornar;
      }
      else
      {
        no_a_retornar->direita = remover_no_album(no_a_retornar->direita, titulo);
        if (no_a_retornar->direita != NULL)
          no_a_retornar->direita->pai = no_a_retornar;
      }
    }
  }

  if (no_a_retornar != NULL)
    no_a_retornar = balancear_album_rb(no_a_retornar);

  return no_a_retornar;
}

void remover_album(Artista *artista, char titulo[])
{

  if (artista != NULL && artista->albuns != NULL)
  {

    if (!(artista->albuns->esquerda != NULL && artista->albuns->esquerda->cor == VERMELHO) && !(artista->albuns->direita != NULL && artista->albuns->direita->cor == VERMELHO))
      artista->albuns->cor = VERMELHO;

    artista->albuns = remover_no_album(artista->albuns, titulo);
    artista->num_albuns--;

    if (artista->albuns != NULL)
    {
      artista->albuns->cor = PRETO;
      artista->albuns->pai = NULL;
    }
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

Album *buscar_album(Album *no, char titulo[])
{
  return (no == NULL || strcmp(titulo, no->titulo) == 0)
             ? no
             : buscar_album(
                   (strcmp(titulo, no->titulo) < 0) ? no->esquerda : no->direita,
                   titulo);
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