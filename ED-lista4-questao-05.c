/*
** Função :
** Autor : Maysa de Lima Maciel
** Data : 02/06/2024
** Observações:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char descricao[100];
} Processo;

typedef struct Node {
  Processo processo;
  struct Node *proximo;
} Node;

typedef struct {
  Node *topo;
} Pilha;

void inicializar_pilha(Pilha *p) { p->topo = NULL; }

int pilha_vazia(Pilha *p) { return (p->topo == NULL); }

void empilhar(Pilha *p, Processo proc) {
  Node *novo_node = (Node *)malloc(sizeof(Node));
  novo_node->processo = proc;
  novo_node->proximo = p->topo;
  p->topo = novo_node;
}

Processo desempilhar(Pilha *p) {
  if (pilha_vazia(p)) {
    Processo vazio = {0, "Pilha Vazia"};
    return vazio;
  }
  Node *temp = p->topo;
  Processo proc = temp->processo;
  p->topo = p->topo->proximo;
  free(temp);
  return proc;
}

void esvaziar_pilha(Pilha *p) {
  while (!pilha_vazia(p)) {
    desempilhar(p);
  }
}

void exibir_pilha(Pilha *p) {
  if (pilha_vazia(p)) {
    printf("Pilha vazia\n");
    return;
  }
  Node *atual = p->topo;
  while (atual != NULL) {
    printf("Processo #%d - %s\n", atual->processo.id,
           atual->processo.descricao);
    atual = atual->proximo;
  }
}

int main() {
  Pilha p;
  inicializar_pilha(&p);
  int escolha, id;
  char descricao[100];
  Processo proc;

  do {
    printf("\nMenu:\n");
    printf("1. Incluir processo\n");
    printf("2. Retirar processo\n");
    printf("3. Encerrar\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      printf("Digite o identificador: ");
      scanf("%d", &id);
      printf("Digite a descricao: ");
      getchar();
      fgets(descricao, sizeof(descricao), stdin);
      descricao[strcspn(descricao, "\n")] = '\0';

      proc.id = id;
      strcpy(proc.descricao, descricao);

      empilhar(&p, proc);
      printf("Processo incluído. \n Estado atual da pilha:\n");
      exibir_pilha(&p);
      break;

    case 2:
      proc = desempilhar(&p);
      if (strcmp(proc.descricao, "Pilha Vazia") == 0) {
        printf("Pilha vazia\n");
      } else {
        printf("Removido #%d - %s\n", proc.id, proc.descricao);
        printf("Estado atual:\n");
        exibir_pilha(&p);
      }
      break;

    case 3:
      esvaziar_pilha(&p);
      printf("Fim\n");
      break;

    default:
      printf("Opcao invalida\n");
    }
  } while (escolha != 3);

  return 0;
}