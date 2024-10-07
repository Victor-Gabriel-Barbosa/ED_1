#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "cores.h"
#include "utils.h"
#include "pilha_estatica.h" 

typedef struct stackEst { // Estrutura p/ armazenar a pilha estática
  char pilha[MAX];
  int topo; 
} PilhaEst;

/* Cria e inicializa a pilha estática */
PilhaEst *pilhaCriaEst() {
  PilhaEst *Ptp = (PilhaEst*) malloc(sizeof(PilhaEst));
  if (Ptp != NULL) Ptp->topo = -1;
  return Ptp;
}

/* Libera a memória alocada p/ a pilha estática */
PilhaEst *pilhaLiberaEst(PilhaEst *Ptp) {
  if (Ptp == NULL) return NULL;
  free(Ptp);
  return NULL;
}

/* Verifica se a pilha está cheia */
int pilhaCheiaEst(PilhaEst *Ptp) {
  return (Ptp->topo == MAX - 1);
}

/* Verifica se a pilha está vazia */
int pilhaVaziaEst(PilhaEst *Ptp) {
  return (Ptp->topo == -1);
}

/* Insere um elemento na pilha estática */
PilhaEst *pilhaInsereEst(PilhaEst *Ptp, char letra) {
  if (Ptp == NULL || pilhaCheiaEst(Ptp)) return Ptp;
  Ptp->pilha[++Ptp->topo] = letra; // Incrementa o topo e insere
  return Ptp;
}

/* Remove um elemento da pilha estática */
PilhaEst *pilhaRemoveEst(PilhaEst *Ptp, char *letra) {
  if (Ptp == NULL || pilhaVaziaEst(Ptp)) return Ptp;
  *letra = Ptp->pilha[Ptp->topo--]; 
  return Ptp;
}

/* Consulta um elemento do topo da pilha estática */
int pilhaConsultaEst(PilhaEst *Ptp, char *letra) {
  if (Ptp == NULL || pilhaVaziaEst(Ptp)) return 0;
  *letra = Ptp->pilha[Ptp->topo]; // Retorna o elemento do topo
  return 1;
}

/* Exibe a pilha estática */
int pilhaExibeEst(PilhaEst *Ptp) {
  if (pilhaVaziaEst(Ptp)) return 0;
  for (int i = Ptp->topo; i >= 0; i--) {
    printf("%c ", Ptp->pilha[i]);
  }
  return 1;
}

/* Encontra o tamanho da pilha estática */
int pilhaTamanhoEst(PilhaEst *Ptp) {
  return Ptp->topo + 1;
}

/* Verifica se uma palavra é um palíndromo */ 
int pilhaPalinEst(PilhaEst *Ptp, char *palavra) {
  char letra;
  for (int i = 0; i < pilhaTamanhoEst(Ptp) / 2; i++) {
    Ptp = pilhaRemoveEst(Ptp, &letra);
    if (tolower(palavra[i]) != tolower(letra)) return 0;
  }
  return 1;
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