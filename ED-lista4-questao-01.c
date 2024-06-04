/*
** Função :
** Autor : Maysa de Lima Maciel
** Data : 02/06/2024
** Observações:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livro {
  char autor[100];
  char titulo[100];
  char editora[100];
  int ano;
} Livro;

typedef struct No {
  Livro livro;
  struct No *proximo;
} No;

No *criar_no(Livro livro) {
  No *novo = (No *)malloc(sizeof(No));
  novo->livro = livro;
  novo->proximo = NULL;
  return novo;
}

void inserir(No **cabeca, Livro livro) {
  No *novo = criar_no(livro);
  if (*cabeca == NULL || strcmp((*cabeca)->livro.titulo, livro.titulo) > 0) {
    novo->proximo = *cabeca;
    *cabeca = novo;
  } else {
    No *atual = *cabeca;
    while (atual->proximo != NULL &&
           strcmp(atual->proximo->livro.titulo, livro.titulo) < 0) {
      atual = atual->proximo;
    }
    novo->proximo = atual->proximo;
    atual->proximo = novo;
  }
}

void remover(No **cabeca, char *titulo) {
  No *atual = *cabeca;
  No *anterior = NULL;

  while (atual != NULL && strcmp(atual->livro.titulo, titulo) != 0) {
    anterior = atual;
    atual = atual->proximo;
  }

  if (atual == NULL) {
    printf("Livro não encontrado.\n");
    return;
  }

  if (anterior == NULL) {
    *cabeca = atual->proximo;
  } else {
    anterior->proximo = atual->proximo;
  }

  free(atual);
  printf("Livro removido com sucesso.\n");
}

void alterar(No *cabeca, char *titulo) {
  No *atual = cabeca;

  while (atual != NULL && strcmp(atual->livro.titulo, titulo) != 0) {
    atual = atual->proximo;
  }

  if (atual == NULL) {
    printf("Livro não encontrado.\n");
    return;
  }

  printf("Entre com os novos dados do livro:\n");
  printf("Autor: ");
  scanf(" %[^\n]", atual->livro.autor);
  printf("Título: ");
  scanf(" %[^\n]", atual->livro.titulo);
  printf("Editora: ");
  scanf(" %[^\n]", atual->livro.editora);
  printf("Ano: ");
  scanf("%d", &atual->livro.ano);
  printf("Livro alterado com sucesso.\n");
}

void buscar_titulo(No *cabeca, char *titulo) {
  No *atual = cabeca;

  while (atual != NULL) {
    if (strcmp(atual->livro.titulo, titulo) == 0) {
      printf("Livro encontrado:\n");
      printf("Autor: %s\n", atual->livro.autor);
      printf("Título: %s\n", atual->livro.titulo);
      printf("Editora: %s\n", atual->livro.editora);
      printf("Ano: %d\n", atual->livro.ano);
      return;
    }
    atual = atual->proximo;
  }
  printf("Livro não encontrado.\n");
}

void buscar_autor(No *cabeca, char *autor) {
  No *atual = cabeca;
  int encontrado = 0;

  while (atual != NULL) {
    if (strcmp(atual->livro.autor, autor) == 0) {
      if (!encontrado) {
        printf("Livros encontrados:\n");
        encontrado = 1;
      }
      printf("Título: %s\n", atual->livro.titulo);
      printf("Editora: %s\n", atual->livro.editora);
      printf("Ano: %d\n", atual->livro.ano);
    }
    atual = atual->proximo;
  }

  if (!encontrado) {
    printf("Nenhum livro encontrado para o autor %s.\n", autor);
  }
}

void exibir_livros(No *cabeca) {
  No *atual = cabeca;
  if (atual == NULL) {
    printf("Nenhum livro na biblioteca.\n");
    return;
  }

  printf("Lista de livros:\n");
  while (atual != NULL) {
    printf("Autor: %s\n", atual->livro.autor);
    printf("Título: %s\n", atual->livro.titulo);
    printf("Editora: %s\n", atual->livro.editora);
    printf("Ano: %d\n\n", atual->livro.ano);
    atual = atual->proximo;
  }
}

int main() {
  No *cabeca = NULL;
  int opcao;
  Livro livro;
  char titulo[100];
  char autor[100];

  do {
    printf("\nBiblioteca\n");
    printf("1. Inserir livro\n");
    printf("2. Remover livro\n");
    printf("3. Alterar livro\n");
    printf("4. Buscar livro por título\n");
    printf("5. Buscar livro por autor\n");
    printf("6. Exibir todos os livros\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Entre com os dados do livro:\n");
      printf("Autor: ");
      scanf(" %[^\n]", livro.autor);
      printf("Título: ");
      scanf(" %[^\n]", livro.titulo);
      printf("Editora: ");
      scanf(" %[^\n]", livro.editora);
      printf("Ano: ");
      scanf("%d", &livro.ano);
      inserir(&cabeca, livro);
      break;
    case 2:
      printf("Entre com o título do livro a ser removido: ");
      scanf(" %[^\n]", titulo);
      remover(&cabeca, titulo);
      break;
    case 3:
      printf("Entre com o título do livro a ser alterado: ");
      scanf(" %[^\n]", titulo);
      alterar(cabeca, titulo);
      break;
    case 4:
      printf("Entre com o título do livro a ser buscado: ");
      scanf(" %[^\n]", titulo);
      buscar_titulo(cabeca, titulo);
      break;
    case 5:
      printf("Entre com o nome do autor: ");
      scanf(" %[^\n]", autor);
      buscar_autor(cabeca, autor);
      break;
    case 6:
      exibir_livros(cabeca);
      break;
    case 0:
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
    }
  } while (opcao != 0);

  No *atual = cabeca;
  while (atual != NULL) {
    No *temp = atual;
    atual = atual->proximo;
    free(temp);
  }

  return 0;
}