#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "cores.h"
#include "utils.h" 
#include "fila_encadeada.h"
#include "fila_estatica.h"

typedef struct no { // Estrutura do nó da fila encadeada
  Planeta plan;
  struct no *prox;
} No;

typedef struct queueEnc { // Estrutura da fila encadeada
  No *inicio;
  No *fim;
  int N;
} FilaEnc;
 
/* Cria e inicializa a fila encadeada */
FilaEnc *filaCriaEnc() {
  FilaEnc *Ptf = (FilaEnc*) malloc(sizeof(FilaEnc));
  if (Ptf != NULL) {
    Ptf->inicio = NULL;
    Ptf->fim = NULL;
    Ptf->N = 0;
  }
  return Ptf;
}

/* Libera a memória alocada para uma fila encadeada */
FilaEnc *filaLiberaEnc(FilaEnc *Ptf) {
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

/* Verifica se a fila encadeada está vazia */
int filaVaziaEnc(FilaEnc *Ptf) {
  return (Ptf->N == 0);
}

/* Insere um planeta na fila encadeada */
FilaEnc *filaInsereEnc(FilaEnc *Ptf, Planeta plan) {
  if (Ptf == NULL) return Ptf;
  No *novo = (No*) malloc(sizeof(No));
  if (novo == NULL) return Ptf; 
  novo->plan = plan;
  novo->prox = NULL;
  if (filaVaziaEnc(Ptf)) Ptf->inicio = novo; 
  else Ptf->fim->prox = novo; 
  Ptf->fim = novo;
  Ptf->N++;
  return Ptf;
} 

/* Remove um planeta da fila encadeada */
FilaEnc *filaRemoveEnc(FilaEnc *Ptf, Planeta *plan) {
  if (Ptf == NULL || filaVaziaEnc(Ptf)) return Ptf;
  No *temp = Ptf->inicio;
  *plan = temp->plan;
  Ptf->inicio = temp->prox;
  if (Ptf->inicio == NULL) Ptf->fim = NULL;
  free(temp);
  Ptf->N--;
  return Ptf;
}

/* Consulta o primeiro elemento da fila encadeada */
int filaConsultaEnc(FilaEnc *Ptf, Planeta *plan) {
  if (Ptf == NULL || filaVaziaEnc(Ptf)) return 0;
  *plan = Ptf->inicio->plan;
  return 1;
}

/* Exibe a fila encadeada */
int filaExibeEnc(FilaEnc *Ptf) {
  if (filaVaziaEnc(Ptf)) return 0;
  No *temp = Ptf->inicio;
  while (temp != NULL) {
    planetaExibe(temp->plan);
    temp = temp->prox;
  }
  printf("\n");
  return 1;
}

/* Encontra o tamanho da fila encadeada */
int filaTamanhoEnc(FilaEnc *Ptf) {
  return Ptf->N;
}

typedef struct queueEst { // Estrutura p/ armazenar a fila estática
  Planeta fila[MAX];
  int IF;
  int FF;
  int N;
} FilaEst;

/* Cria e inicializa a fila estática */
FilaEst *filaCriaEst() {
  FilaEst *Ptf = (FilaEst*) malloc(sizeof(FilaEst));
  if (Ptf != NULL) {
    Ptf->IF = 0;
    Ptf->FF = 0;
    Ptf->N = 0;
  }
  return Ptf;
}

/* Libera a memória alocada p/ fila estática */
FilaEst *filaLiberaEst(FilaEst *Ptf) {
  if (Ptf == NULL) return Ptf;
  free(Ptf);
  return NULL;
}

/* Verifica se a fila estática está cheia */
int filaCheiaEst(FilaEst *Ptf) {
  return (Ptf->N == MAX);
}

/* Verifica se a fila estática está vazia */
int filaVaziaEst(FilaEst *Ptf) {
  return (Ptf->N == 0);
}

/* Insere um elemento na fila estática */
FilaEst *filaInsereEst(FilaEst *Ptf, Planeta plan) {
  if (Ptf == NULL || filaCheiaEst(Ptf)) return Ptf;
  Ptf->fila[Ptf->FF] = plan;
  Ptf->FF = (Ptf->FF + 1) % MAX;
  Ptf->N++;
  return Ptf;
}

/* Remove um elemento da fila estática */
FilaEst *filaRemoveEst(FilaEst *Ptf, Planeta *plan) {
  if (Ptf == NULL || filaVaziaEst(Ptf)) return Ptf;
  *plan = Ptf->fila[Ptf->IF];
  Ptf->IF = (Ptf->IF + 1) % MAX;
  Ptf->N--;
  return Ptf;
}

/* Consulta um elemento da fila estática */
int filaConsultaEst(FilaEst *Ptf, Planeta *plan) {
  if (Ptf == NULL || filaVaziaEst(Ptf)) return 0;
  *plan = Ptf->fila[Ptf->IF];
  return 1;
}

/* Exibe a fila estática */
int filaExibeEst(FilaEst *Ptf) {
  if (filaVaziaEst(Ptf)) return 0;
  for (int i = 0; i < Ptf->N; i++) {  // Percorre todos os elementos presentes na fila
    planetaExibe(Ptf->fila[(Ptf->IF + i) % MAX]);
  }
  printf("\n");
  return 1;
}

/* Encontra o tamanho da fila estática */
int filaTamanhoEst(FilaEst *Ptf) {
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
void planetaExibe(const Planeta plan) {
  printf(C_FMT(C_NEGRITO C_CIANO, "\n☽-------------------------☀----------------------☾\n"));
  printf(C_FMT(C_NEGRITO C_MAGENTA, "| %-23s | %-20s |\n"), "Nome", plan.nome);
  printf(C_FMT(C_NEGRITO C_CIANO, "☽-------------------------☀----------------------☾\n"));
  printf(C_FMT(C_NEGRITO C_AZUL,    "| %-23s | %-20.2f |\n"), "Gravidade", plan.gravidade);
  printf(C_FMT(C_NEGRITO C_VERDE,   "| %-23s | %-20.2f |\n"), "Massa", plan.massa);
  printf(C_FMT(C_NEGRITO C_LARANJA, "| %-24s | %-20.2f |\n"), "Distância do Sol", plan.distancia_sol);
  printf(C_FMT(C_NEGRITO C_CIANO, "☽-------------------------☀----------------------☾\n"));
}

/* Aleatoriza as informações de um planeta */
Planeta planetaAleatoriza(const int posi) {
  Planeta plan;
  int tam = rand() % (sizeof(plan.nome) / 2) + sizeof(plan.nome) / 4;
  for (int i = 0; i < tam; i++) { // Gera caracteres aleatórios entre 'a' e 'z'
    plan.nome[i] = (rand() % 26) + 'a'; 
  }
  plan.nome[tam] = '\0';
  plan.gravidade = rand() % 16 + 5;
  plan.massa = rand() % 16 + 5; 
  plan.distancia_sol = posi;
  return plan;
}

/* Faz a colisão entre dois planetas */
Planeta planetaBigBang(Planeta plan1, Planeta plan2) {
  Planeta bigBang;
  double nota_plan1 = plan1.massa * 0.5 + plan1.gravidade * 0.3 + plan1.distancia_sol * 0.2;
  double nota_plan2 = plan2.massa * 0.5 + plan2.gravidade * 0.3 + plan2.distancia_sol * 0.2;
  if (nota_plan1 > nota_plan2) {
    bigBang = plan1;
    bigBang.massa -= plan2.massa;
    bigBang.gravidade -= plan2.gravidade;
    bigBang.distancia_sol -= plan2.distancia_sol;
  } else {
    bigBang = plan2;
    bigBang.massa -= plan1.massa;
    bigBang.gravidade -= plan1.gravidade;
    bigBang.distancia_sol -= plan1.distancia_sol;
  }
  if (bigBang.massa < 0) bigBang.massa = 0;
  if (bigBang.gravidade < 0) bigBang.gravidade = 0;
  if (bigBang.distancia_sol < 0) bigBang.distancia_sol = 0;
  return bigBang;
}
 
/* Exibe o conteúdo de um arquivo */
int printArquivo(const char *nome_arqv, const char *cor) {
  FILE *arquivo = fopen(nome_arqv, "r");
  if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
    printf(C_FMT_ERRO("\n[Arquivo '%s' não encontrado!]: %s%s\n"), nome_arqv, strerror(errno), C_RESET);
    return 0;
  }
  char *linha = NULL;
  size_t tam = 0;
  printf("%s", cor);
  while (getline(&linha, &tam, arquivo) != -1) { // Lê todas as linhas do arquivo
    printf("%s", linha);
  }
  printf("%s", C_RESET);
  free(linha);
  fclose(arquivo);
  return 1;
}

/* Salva o tempo de execução em um arquivo */
int arquivoSalva(const char *nome_arqv, const int qtd_t, const int qtd, const clock_t *temp) {
  FILE *arquivo = fopen(nome_arqv, "a");
  if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
    printf(C_FMT_ERRO("\n[Erro ao abrir o arquivo!]: %s\n"), strerror(errno)); 
    return -1;
  }
  fseek(arquivo, 0, SEEK_END);
  if (ftell(arquivo) == 0) { // Se o arquivo estiver vazio, adiciona o cabeçalho
    fprintf(arquivo, "NºBateria,Quantidade,Inserção,Listagem,Remoção\n");
  }
  fprintf(arquivo, "%d,%d,%ld,%ld,%ld\n", qtd_t, qtd, temp[0], temp[1], temp[2]);
  fclose(arquivo);
  return 1;
}