#include "lista_encadeada.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>

/* Cria uma lista vazia */
Lista *cria_lista() { 
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  lista->cabeca = NULL;
  return lista;
}

/* Insere um novo nó no início da lista */
int insere_no_inicio(Lista *lista, int valor) { 
  No *novo_no = (No *)malloc(sizeof(No));
  if (novo_no == NULL) { // Verifica se a alocação de memória foi bem-sucedida
    return 0;
  }
  novo_no->dado = valor;
  novo_no->proximo = lista->cabeca;
  lista->cabeca = novo_no;
  return 1;
}

/* Insere um novo nó no final da lista */
int insere_no_final(Lista *lista, int valor) { 
  No *novo_no = (No *)malloc(sizeof(No));
  if (novo_no == NULL) { // Verifica se a alocação de memória foi bem-sucedida
    return 0;
  }
  novo_no->dado = valor;
  novo_no->proximo = NULL;
  if (lista->cabeca == NULL) { // Verifica se a lista está vazia
    lista->cabeca = novo_no;
  } else { 
    No *atual = lista->cabeca;
    while (atual->proximo != NULL) { // Percorre a lista até o último nó
      atual = atual->proximo;
    }
    atual->proximo = novo_no;
  }
  return 1;
}

/* Remove um nó com o valor especificado */
int remove_No(Lista *lista, int valor) { 
  No *atual = lista->cabeca;
  No *anterior = NULL;
  while (atual != NULL && atual->dado != valor) { // Percorre a lista até encontrar o nó com o valor especificado
    anterior = atual;
    atual = atual->proximo;
  }
  if (atual == NULL) { // Verifica se o nó com o valor especificado foi encontrado
    return 0;
  }
  if (anterior == NULL) { // Verifica se o nó a ser removido é a cabeça da lista
    lista->cabeca = atual->proximo;
  } else {
    anterior->proximo = atual->proximo;
  }
  free(atual); 
  return 1;
}

/* Consulta se um nó com o valor especificado está na lista */
int consulta_No(Lista *lista, int valor) { 
  No *atual = lista->cabeca;
  while (atual != NULL && atual->dado != valor) { // Percorre a lista até encontrar o nó com o valor especificado
    atual = atual->proximo;
  }
  return (atual != NULL);
}

/* Imprime a lista */
void imprime_lista(Lista *lista) { 
  No *atual = lista->cabeca;
  while (atual != NULL) { // Percorre a lista e imprime o valor de cada nó
    printf("%d -> ", atual->dado);
    atual = atual->proximo;
  }
  printf("NULL\n");
}

/* Libera a memória alocada pela lista */
void libera_lista(Lista *lista) { 
  No *atual = lista->cabeca;
  while (atual != NULL) { // Percorre a lista e libera a memória de cada nó
    No *temp = atual;
    atual = atual->proximo;
    free(temp);
  }
  free(lista);
}

/* Barra de divisão */
void barra(char *ini, char *fin) { 
  printf("%s\033[38;5;51m<>\033[0m==============\033[38;5;201m<>\033[0m==============\033[38;5;51m<>\033[0m%s", ini, fin);
}

/* Limpa o buffer do teclado */
void limpa_buffer() { 
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}

/* Limpa a tela */
void limpa_tela() { 
  printf("\033[0m\nAperte \033[38;5;39m[ENTER]\033[0m para continuar...");
  limpa_buffer();
  system("clear");
}

/* Confirmação de ação */
int sim_ou_nao(char *msg) { 
  int opcao;
  bool loop = false;
  do { // [LOOP P/ VALIDAÇÃO]
    limpa_tela();
    opcao = -1;
    barra("\n", "\n");
    printf("\033[38;5;201m[Tem certeza que deseja %s?]\033[0m", msg);
    barra("\n", "\n");
    printf("|[\033[38;5;51m1\033[0m]> Sim\n");
    printf("|[\033[38;5;51m0\033[0m]> Não");
    barra("\n", "\n");
    printf("Opção\033[38;5;51m: ");
    scanf("%d", &opcao);
    limpa_buffer();
    barra("", "\n");
    loop = (opcao != 0 && opcao != 1);
    if (loop) { // [VALIDAÇÃO]
      printf("\n\033[38;5;196m[Opção inválida! Tente novamente...]\033[0m\n");
    }
  } while (loop);
  return opcao;
}

/* Salva a lista em um arquivo */
void salva_lista(Lista *lista, char *nome_arqv) { 
  FILE *arquivo = fopen(nome_arqv, "w");
  if (arquivo == NULL) {
    printf("\n\033[38;5;196m[Erro ao abrir o arquivo!]\033[0m\n");
    return;
  }
  No *atual = lista->cabeca;
  while (atual != NULL) {
    fprintf(arquivo, "%d\n", atual->dado);
    atual = atual->proximo;
  }
  fclose(arquivo);
}

/* Escolha do menu */
int escolha_menu() { 
  int opcao;
  bool loop = false;
  do { // Validação do menu
    limpa_tela();
    opcao = -1;
    barra("\n", "\n");
    printf("\033[38;5;201m[MENU PRINCIPAL]\033[0m");
    barra("\n", "\n");
    printf("|[\033[38;5;51m1\033[0m]> Inserir no início\n");
    printf("|[\033[38;5;51m2\033[0m]> Inserir no final\n");
    printf("|[\033[38;5;51m3\033[0m]> Remover Nó\n");
    printf("|[\033[38;5;51m4\033[0m]> Imprimir lista\n");
    printf("|[\033[38;5;51m5\033[0m]> Salvar lista\n");
    printf("|[\033[38;5;51m0\033[0m]> Sair\n");
    barra("", "\n");
    printf("Opção\033[38;5;51m: ");
    scanf("%d", &opcao);
    limpa_buffer();
    barra("", "\n");
    loop = (opcao < 0 || opcao > 5);
    if (loop) { 
      printf("\n\033[38;5;196m[Opção inválida! Tente novamente...]\033[0m\n");
    }
  } while (loop);
  return opcao;
}

/* Funcionalidade do menu */
void menu(Lista *lista) { 
  int opcao;
  bool loop = true;
  while (loop) { // Loop do menu
    opcao = escolha_menu();
    if (opcao == 0 && sim_ou_nao("sair")) { // Confirmação de saída
      printf("Saindo...\n");
      loop = false;
      continue;
    } else if (opcao == 1) { // Inserir no início
      int valor;
      do {
        valor = -1;
        limpa_tela();
        barra("\n", "\n");
        printf("\033[38;5;201m[INSERIR NO INÍCIO]\033[0m");
        barra("\n", "\n");
        printf("Digite o valor a ser inserido \n[-1 P/ Sair]: ");
        scanf("%d", &valor);
        limpa_buffer();
        if (valor != -1) { // Verifica se o valor é diferente de -1
          insere_no_inicio(lista, valor);
          printf("\n\033[38;5;51m[Valor inserido com sucesso!]\033[0m\n");
        }
      } while (valor != -1); // Loop para inserir valores
    } else if (opcao == 2) { // Inserir no final
      int valor;
      do {
        valor = -1;
        limpa_tela();
        barra("\n", "\n");
        printf("\033[38;5;201m[INSERIR NO FINAL]\033[0m");
        barra("\n", "\n");
        printf("Digite o valor a ser inserido \n[-1 P/ Sair]: ");
        scanf("%d", &valor);
        limpa_buffer();
        if (valor != -1) { // Verifica se o valor é diferente de -1
          insere_no_final(lista, valor);
          printf("\n\033[38;5;51m[Valor inserido com sucesso!]\033[0m\n");
        }
      } while (valor != -1); // Loop para inserir valores
    } else if (opcao == 3) { // Remover Nos
      limpa_tela();
      int valor;
      barra("\n", "\n");
      printf("\033[38;5;201m[REMOVER No]\033[0m");
      barra("\n", "\n");
      printf("Digite o valor a ser removido: ");
      scanf("%d", &valor);
      limpa_buffer();
      if (remove_No(lista, valor)) { // Verifica se o valor foi removido
        printf("\n\033[38;5;51m[Valor removido com sucesso!]\033[0m\n");
        imprime_lista(lista);
      } else {
        printf("\n\033[38;5;196m[Valor %d não encontrado na lista]\033[0m\n", valor);
      }
    } else if (opcao == 4) { // Imprimir lista
      limpa_tela();
      barra("\n", "\n");
      printf("\033[38;5;201m[IMPRIMIR LISTA]\033[0m");
      barra("\n", "\n");
      imprime_lista(lista);
    } else if (opcao == 5) { // Salvar lista
      limpa_tela();
      char nome_arqv[100];
      barra("\n", "\n");
      printf("\033[38;5;201m[SALVAR LISTA]\033[0m");
      barra("\n", "\n");
      printf("Digite o nome do arquivo: ");
      scanf("%s", nome_arqv);
      limpa_buffer();
      salva_lista(lista, nome_arqv);
      printf("\n\033[38;5;51m[Lista salva com sucesso!]\033[0m\n");
    } else {
      printf("\n\033[38;5;196m[Opção inválida! Tente novamente...]\033[0m\n");
    }
  }
}