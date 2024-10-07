#include "lista_encadeada.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Lista *criar_lista() { // Função para criar uma nova lista
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  lista->cabeca = NULL;
  return lista;
}

int inserir_no_inicio(Lista *lista, int valor) { // Função para inserir um ponto no início da lista
  ponto *novo_ponto = (ponto *)malloc(sizeof(ponto));
  if (novo_ponto == NULL) {
    return 0;
  }
  novo_ponto->dado = valor;
  novo_ponto->proximo = lista->cabeca;
  lista->cabeca = novo_ponto;
  return 1;
}

int inserir_no_final(Lista *lista, int valor) { // Função para inserir um ponto no final da lista
  ponto *novo_ponto = (ponto *)malloc(sizeof(ponto));
  if (novo_ponto == NULL) {
    return 0;
  }
  novo_ponto->dado = valor;
  novo_ponto->proximo = NULL;
  if (lista->cabeca == NULL) {
    lista->cabeca = novo_ponto;
  } else {
    ponto *atual = lista->cabeca;
    while (atual->proximo != NULL) {
      atual = atual->proximo;
    }
    atual->proximo = novo_ponto;
  }
  return 1;
}

int remover_ponto(Lista *lista, int valor) { // Função para remover um ponto da lista
  ponto *atual = lista->cabeca;
  ponto *anterior = NULL;
  while (atual != NULL && atual->dado != valor) {
    anterior = atual;
    atual = atual->proximo;
  }
  if (atual == NULL) {
    return 0;
  }
  if (anterior == NULL) {
    lista->cabeca = atual->proximo;
  } else {
    anterior->proximo = atual->proximo;
  }
  free(atual);
  return 1;
}

int consultar_ponto(Lista *lista, int valor) { // Função para consultar um ponto na lista
  ponto *atual = lista->cabeca;
  while (atual != NULL && atual->dado != valor) {
    atual = atual->proximo;
  }
  return (atual != NULL);
}

void imprimir_lista(Lista *lista) { // Função para imprimir os elementos da lista
  ponto *atual = lista->cabeca;
  while (atual != NULL) {
    printf("%d -> ", atual->dado);
    atual = atual->proximo;
  }
  printf("NULL\n");
}

void liberar_lista(Lista *lista) { // Função para liberar a memória da lista
  ponto *atual = lista->cabeca;
  while (atual != NULL) { // Percorre a lista e libera a memória de cada nó
    ponto *temp = atual;
    atual = atual->proximo;
    free(temp);
  }
  free(lista);
}

void barra(char *ini, char *fin) {
  printf("%s\033[38;5;51m<>\033[0m==============\033[38;5;201m<>\033[0m==============\033[38;5;51m<>\033[0m%s", ini, fin);
}

void limpBuffer() {
    char c;
    while ((c = getchar())!= '\n' && c!= EOF);
}

void limpTela() { // [FUNÇÃO DE LIMPAR TELA]
  printf("\033[0m\nAperte [\033[38;5;39mENTER\033[0m] para continuar...");
  getchar();
  limpBuffer();
  system("clear");
}

int simNao(char *msg) { // [FUNÇÃO DE SIM OU NÃO]
  int opcao;
  bool loop = false;
  do { // [LOOP P/ VALIDAÇÃO]
    limpTela();
    opcao = -1;
    barra("\n", "\n");
    printf("\033[38;5;201m[Tem certeza que deseja %s?]\033[0m", msg);
    barra("\n", "\n");
    printf("|[\033[38;5;51m1\033[0m]> Sim\n");
    printf("|[\033[38;5;51m0\033[0m]> Não");
    barra("\n", "\n");
    printf("Opção\033[38;5;51m: ");
    scanf("%d", &opcao);
    limpBuffer();
    barra("", "\n");
    loop = (opcao != 0 && opcao != 1);
    if (loop) { // [VALIDAÇÃO]
      printf("\n\033[38;5;196m[Opção inválida! Tente novamente...]\033[0m\n");
    }
  } while (loop);
  return opcao;
}

int escolhMenu() { // [FUNÇÃO DE ESCOLHA DE MENU]
  int opcao;
  bool loop = false;
  do { // [LOOP P/ VALIDAÇÃO]
    limpTela();
    opcao = -1;
    barra("\n", "\n");
    printf("\033[38;5;201m[MENU PRINCIPAL]\033[0m");
    barra("\n", "\n");
    printf("|[\033[38;5;51m1\033[0m]> Inserir no início\n");
    printf("|[\033[38;5;51m2\033[0m]> Inserir no final\n");
    printf("|[\033[38;5;51m3\033[0m]> Remover pontos\n");
    printf("|[\033[38;5;51m4\033[0m]> Imprimir lista\n");
    printf("|[\033[38;5;51m0\033[0m]> Sair\n");
    barra("", "\n");
    printf("Opção\033[38;5;51m: ");
    scanf("%d", &opcao);
    limpBuffer();
    barra("", "\n");
    loop = (opcao < 0 || opcao > 4);
    if (loop) {
      printf("\n\033[38;5;196m[Opção inválida! Tente novamente...]\033[0m\n");
    }
  } while (loop);
  return opcao;
}

void menu(Lista *lista) { // [FUNÇÃO DE MENU]
  int opcao;
  bool loop = true;
  while (loop) { // [LOOP P/ MENU]
    opcao = escolhMenu();
    if (opcao == 0 && simNao("sair")) {
      loop = false;
      continue;
    } else if (opcao == 1) {
      limpTela();
      int valor;
      barra("\n", "\n");
      printf("\033[38;5;201m[INSERIR NO INÍCIO]\033[0m");
      barra("\n", "\n");
      printf("Digite o valor a ser inserido: ");
      scanf("%d", &valor);
      limpBuffer();
      inserir_no_inicio(lista, valor);
      printf("\n\033[38;5;51m[Valor inserido com sucesso!]\033[0m\n");
    } else if (opcao == 2) {
      limpTela();
      int valor;
      barra("\n", "\n");
      printf("\033[38;5;201m[INSERIR NO FINAL]\033[0m");
      barra("\n", "\n");
      printf("Digite o valor a ser inserido: ");
      scanf("%d", &valor);
      limpBuffer();
      inserir_no_final(lista, valor);
      printf("\n\033[38;5;51m[Valor inserido com sucesso!]\033[0m\n");
    } else if (opcao == 3) {
      limpTela();
      int valor;
      barra("\n", "\n");
      printf("\033[38;5;201m[REMOVER PONTO]\033[0m");
      barra("\n", "\n");
      printf("Digite o valor a ser removido: ");
      scanf("%d", &valor);
      limpBuffer();
      if (remover_ponto(lista, valor)) {
        printf("\n\033[38;5;51m[Valor removido com sucesso!]\033[0m\n");
      } else {
        printf("\n\033[38;5;196m[Valor %d não encontrado na lista]\033[0m\n", valor);
      }
    } else if (opcao == 4) {
      limpTela();
      barra("\n", "\n");
      printf("\033[38;5;201m[IMPRIMIR LISTA]\033[0m");
      barra("\n", "\n");
      imprimir_lista(lista);
      printf("\n\033[38;5;196m[Lista vazia!]\033[0m\n");
    } else {
      printf("\n\033[38;5;196m[Opção inválida! Tente novamente...]\033[0m\n");
    }
  }
}