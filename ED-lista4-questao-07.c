/*
** Função :
** Autor : Maysa de Lima Maciel
** Data : 02/06/2024
** Observações:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char nome[100];
  struct Node *proximo;
} Node;

typedef struct {
  Node *frente;
  Node *tras;
  int tamanho;
} Fila;

void inicializar(Fila *f) {
  f->frente = NULL;
  f->tras = NULL;
  f->tamanho = 0;
}

int vazia(Fila *f) { return (f->tamanho == 0); }

void adicionar(Fila *f, char *nome) {
  Node *novo = (Node *)malloc(sizeof(Node));
  strcpy(novo->nome, nome);
  novo->proximo = NULL;
  if (vazia(f)) {
    f->frente = novo;
  } else {
    f->tras->proximo = novo;
  }
  f->tras = novo;
  f->tamanho++;
}

char *proximo(Fila *f) {
  if (vazia(f)) {
    return "Não há pacientes na fila";
  }
  Node *temp = f->frente;
  char *nome = (char *)malloc(strlen(temp->nome) + 1);
  strcpy(nome, temp->nome);
  f->frente = f->frente->proximo;
  if (f->frente == NULL) {
    f->tras = NULL;
  }
  free(temp);
  f->tamanho--;
  return nome;
}

int quantidade(Fila *f) { return f->tamanho; }

int main() {
  Fila fila;
  inicializar(&fila);
  int opcao;
  char nome[100];

  do {
    printf("\nMenu:\n");
    printf("1. Adicionar paciente\n");
    printf("2. Próximo paciente\n");
    printf("3. Quantidade de pacientes\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Digite o nome do paciente: ");
      getchar();
      fgets(nome, sizeof(nome), stdin);
      nome[strcspn(nome, "\n")] = '\0';
      adicionar(&fila, nome);
      printf("Paciente adicionado.\n");
      break;
    case 2: {
      char *prox = proximo(&fila);
      if (strcmp(prox, "Não há pacientes na fila") == 0) {
        printf("%s\n", prox);
      } else {
        printf("Próximo paciente: %s\n", prox);
        free(prox);
      }
      break;
    }
    case 3:
      printf("Quantidade de pacientes na fila: %d\n", quantidade(&fila));
      break;
    case 4:
      printf("Fim...\n");
      break;
    default:
      printf("Opcao invalida.\n");
    }
  } while (opcao != 4);

  while (!vazia(&fila)) {
    char *nome = proximo(&fila);
    free(nome);
  }

  return 0;
}