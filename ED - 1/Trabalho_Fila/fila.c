#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cores.h"
#include "utils.h"
#include "fila_encadeada.h"
#include "fila_estatica.h"

typedef struct node { // Estrutura do nó da fila encadeada
  Planeta plan;
  struct node *prox;
} No;

typedef struct queue_e { // Estrutura da fila encadeada
  No *inicio;
  No *fim;
  int N;
} Fila_E;
 
/* Cria e inicializa a fila */
Fila_E *filaCria_E() {
  Fila_E *Ptf = (Fila_E*) malloc(sizeof(Fila_E));
  if (Ptf != NULL) {
    Ptf->inicio = NULL;
    Ptf->fim = NULL;
    Ptf->N = 0;
  }
  return Ptf;
}

/* Libera a memória alocada para uma fila */
Fila_E *filaLibera_E(Fila_E *Ptf) {
  if (Ptf == NULL) return Ptf;
  No *temp = Ptf->inicio;
  while (temp != NULL) {
    No *proximo = temp->prox;
    free(temp);
    temp = proximo;
  }
  free(Ptf);
  return NULL;
}

/* Verifica se a fila está vazia */
int filaVazia_E(Fila_E *Ptf) {
  return (Ptf->N == 0);
}

/* Insere um planeta na fila */
Fila_E *filaInsere_E(Fila_E *Ptf, Planeta plan) {
  if (Ptf == NULL) return Ptf;
  No *novo = (No*) malloc(sizeof(No));
  if (novo == NULL) return Ptf; 
  novo->plan = plan;
  novo->prox = NULL;
  if (filaVazia_E(Ptf)) Ptf->inicio = novo; 
  else Ptf->fim->prox = novo; 
  Ptf->fim = novo;
  Ptf->N++;
  return Ptf;
}

/* Remove um planeta da fila */
Fila_E *filaRemove_E(Fila_E *Ptf, Planeta *plan) {
  if (Ptf == NULL || filaVazia_E(Ptf)) return Ptf;
  No *temp = Ptf->inicio;
  *plan = temp->plan;
  Ptf->inicio = temp->prox;
  if (Ptf->inicio == NULL) Ptf->fim = NULL;
  free(temp);
  Ptf->N--;
  return Ptf;
}

/* Consulta o primeiro elemento da fila */
int filaConsulta_E(Fila_E *Ptf, Planeta *plan) {
  if (Ptf == NULL || filaVazia_E(Ptf)) return 0;
  *plan = Ptf->inicio->plan;
  return 1;
}

/* Exibe a fila */
int filaExibe_E(Fila_E *Ptf) {
  if (filaVazia_E(Ptf)) return 0;
  No *temp = Ptf->inicio;
  while (temp != NULL) {
    planetaExibe(temp->plan);
    temp = temp->prox;
  }
  printf("\n");
  return 1;
}

/* Encontra o tamanho da fila encadeada */
int filaTamanho_E(Fila_E *Ptf) {
  return Ptf->N;
}

typedef struct queue_s { // Estrutura p/ armazenar a fila estática
  Planeta fila[MAX];
  int IF;
  int FF;
  int N;
} Fila_S;

/* Cria e inicializa a fila estática */
Fila_S *filaCria_S() {
  Fila_S *Ptf = (Fila_S*) malloc(sizeof(Fila_S));
  if (Ptf != NULL) {
    Ptf->IF = 0;
    Ptf->FF = 0;
    Ptf->N = 0;
  }
  return Ptf;
}

/* Libera a memória alocada p/ fila estática */
Fila_S *filaLibera_S(Fila_S *Ptf) {
  if (Ptf == NULL) return Ptf;
  free(Ptf);
  return NULL;
}

/* Verifica se a fila estática está cheia */
int filaCheia_S(Fila_S *Ptf) {
  return (Ptf->N == MAX);
}

/* Verifica se a fila estática está vazia */
int filaVazia_S(Fila_S *Ptf) {
  return (Ptf->N == 0);
}

/* Insere um elemento na fila estática */
Fila_S *filaInsere_S(Fila_S *Ptf, Planeta plan) {
  if (Ptf == NULL || filaCheia_S(Ptf)) return Ptf;
  Ptf->fila[Ptf->FF] = plan;
  Ptf->FF = (Ptf->FF + 1) % MAX;
  Ptf->N++;
  return Ptf;
}

/* Remove um elemento da fila estática */
Fila_S *filaRemove_S(Fila_S *Ptf, Planeta *plan) {
  if (Ptf == NULL || filaVazia_S(Ptf)) return Ptf;
  *plan = Ptf->fila[Ptf->IF];
  Ptf->IF = (Ptf->IF + 1) % MAX;
  Ptf->N--;
  return Ptf;
}

/* Consulta um elemento da fila estática */
int filaConsulta_S(Fila_S *Ptf, Planeta *plan) {
  if (Ptf == NULL || filaVazia_S(Ptf)) return 0;
  *plan = Ptf->fila[Ptf->IF];
  return 1;
}

/* Exibe a fila estática */
int filaExibe_S(Fila_S *Ptf) {
  if (filaVazia_S(Ptf)) return 0;
  for (int i = 0; i < Ptf->N; i++) {  // Percorre todos os elementos presentes na fila
    planetaExibe(Ptf->fila[(Ptf->IF + i) % MAX]);
  }
  printf("\n");
  return 1;
}

/* Encontra o tamanho da fila estática */
int filaTamanho_S(Fila_S *Ptf) {
  return Ptf->N;
} 

/* Limpa o buffer do teclado */
void limpaBuffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}

/* Limpa a tela do terminal */
void cls() {
  #ifdef _WIN32
    system("cls");
  #else 
    system("clear");
  #endif 
} 

/* Espera uma entrado do usuário antes de limpar a tela do terminal */
void limpaTela(const char *msg) {
  printf("\n%s", msg);
  limpaBuffer();
  cls();
}

/* Escolhe um número inteiro dentro de um intervalo */
int escolheInt(const char *msg, const int min, const int max) {
  while (1) { // Verifica se o número é válido
    int num;
    printf("\n%s\n", msg);
    printf("%s[%d%s-%s%d]%s: ", C_NEGRITO C_AZUL, min, C_MAGENTA, C_VERMELHO, max, C_RESET);
    scanf("%d", &num);
    limpaBuffer();
    if (num >= min && num <= max) return num;
    printf(C_FMT_ERRO("\n[Número inválido! Tente novamente...]\n"));
  }
}

/* Confirma uma ação */
int simOuNao(const char *msg) { 
  while (1) { // Confirma uma ação
    printf("\nDeseja %s%s%s?\n", C_NEGRITO C_VERMELHO, msg, C_RESET);
    printf("%s[S%s/%sN]%s: ", C_NEGRITO C_AZUL, C_MAGENTA, C_VERMELHO, C_RESET);
    char op = tolower(getchar());
    limpaBuffer();
    if (op == 's') return 1;
    if (op == 'n') return 0;
    printf(C_FMT_ERRO("\n[Opção inválida!]\n"));
  } 
}

/* Mostra um planeta */
void planetaExibe(const Planeta planeta) {
  printf("\n+-------------------------+----------------------+\n");
  printf("| %-23s | %-20s |\n", "Nome", planeta.nome);
  printf("+-------------------------+----------------------+\n");
  printf("| %-23s | %-20.2f |\n", "Gravidade", planeta.gravidade);
  printf("| %-23s | %-20.2f |\n", "Massa", planeta.massa);
  printf("| %-24s | %-20.2f |\n", "Distância do Sol", planeta.distancia_sol);
  printf("+-------------------------+----------------------+\n");
}

/* Aleatoriza as informações de um planeta */
Planeta planetaAleatoriza(const int posi) {
  Planeta plan;
  int tam = rand() % (sizeof(plan.nome) - 5) + 5;
  for (int i = 0; i < tam; i++) { // Gera caracteres aleatórios entre 'a' e 'z'
    plan.nome[i] = (rand() % 26) + 'a'; 
  }
  plan.nome[tam] = '\0';
  plan.gravidade = rand() % 20 + 5; 
  plan.massa = rand() % 20 + 5; 
  plan.distancia_sol = posi;
  return plan;
}
