/*
** Função :
** Autor : Maysa de Lima Maciel
** Data : 02/06/2024
** Observações:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
  char nome[100];
  int quantidade;
  struct Item *proximo;
} Item;

Item *criar_item(char *nome, int quantidade) {
  Item *novo_item = (Item *)malloc(sizeof(Item));
  strcpy(novo_item->nome, nome);
  novo_item->quantidade = quantidade;
  novo_item->proximo = NULL;
  return novo_item;
}

void inserir_item(Item **cabeca, char *nome, int quantidade) {
  Item *novo_item = criar_item(nome, quantidade);
  novo_item->proximo = *cabeca;
  *cabeca = novo_item;
}

void remover_item(Item **cabeca, char *nome) {
  Item *atual = *cabeca;
  Item *anterior = NULL;

  while (atual != NULL && strcmp(atual->nome, nome) != 0) {
    anterior = atual;
    atual = atual->proximo;
  }

  if (atual == NULL) {
    printf("Item nao encontrado na lista.\n");
    return;
  }

  if (anterior == NULL) {
    *cabeca = atual->proximo;
  } else {
    anterior->proximo = atual->proximo;
  }

  free(atual);
  printf("Item '%s' removido da lista.\n", nome);
}

void consultar_item(Item *cabeca, char *nome) {
  Item *atual = cabeca;

  while (atual != NULL) {
    if (strcmp(atual->nome, nome) == 0) {
      printf("Item encontrado: %s, Quantidade: %d\n", atual->nome,
             atual->quantidade);
      return;
    }
    atual = atual->proximo;
  }

  printf("Item nao encontrado na lista.\n");
}

void mostrar_lista(Item *cabeca) {
  if (cabeca == NULL) {
    printf("A lista de compras esta vazia.\n");
    return;
  }

  Item *atual = cabeca;
  while (atual != NULL) {
    printf("Item: %s, Quantidade: %d\n", atual->nome, atual->quantidade);
    atual = atual->proximo;
  }
}

int main() {
  Item *lista = NULL;
  int opcao;
  char nome[100];
  int quantidade;

  do {
    printf("\nMenu:\n");
    printf("1. Inserir item\n");
    printf("2. Remover item\n");
    printf("3. Consultar item\n");
    printf("4. Mostrar todos os itens\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Digite o nome do item: ");
      getchar();
      fgets(nome, sizeof(nome), stdin);
      nome[strcspn(nome, "\n")] = '\0';

      printf("Digite a quantidade: ");
      scanf("%d", &quantidade);

      inserir_item(&lista, nome, quantidade);
      printf("Item inserido.\n");
      break;

    case 2:
      printf("Digite o nome do item a ser removido: ");
      getchar();
      fgets(nome, sizeof(nome), stdin);
      nome[strcspn(nome, "\n")] = '\0';

      remover_item(&lista, nome);
      break;

    case 3:
      printf("Digite o nome do item a ser consultado: ");
      getchar();
      fgets(nome, sizeof(nome), stdin);
      nome[strcspn(nome, "\n")] = '\0';

      consultar_item(lista, nome);
      break;

    case 4:
      mostrar_lista(lista);
      break;

    case 5:
      printf("Fim\n");
      break;

    default:
      printf("Opcao invalida.\n");
    }
  } while (opcao != 5);

  Item *atual = lista;
  while (atual != NULL) {
    Item *temp = atual;
    atual = atual->proximo;
    free(temp);
  }

  return 0;
}