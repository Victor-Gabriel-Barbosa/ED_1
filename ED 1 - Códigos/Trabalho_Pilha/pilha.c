#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "cores.h"
#include "utils.h"
#include "pilha_encadeada.h"
#include "pilha_estatica.h" 

typedef struct node { // Estrutura do nó da pilha encadeada
  RPG rp;
  struct node *prox;
} No;

typedef struct stackEnc { // Estrutura da pilha encadeada
  No *topo;
  int N;
} PilhaEnc;

/* Cria e inicializa a pilha encadeada */
PilhaEnc *pilhaCriaEnc() {
  PilhaEnc *Ptf = (PilhaEnc*) malloc(sizeof(PilhaEnc));
  if (Ptf != NULL) { // Garante que a alocação foi bem-sucedida
    Ptf->topo = NULL;
    Ptf->N = 0;
  }
  return Ptf;
}

/* Libera a memória alocada p/ uma pilha encadeada */
PilhaEnc *pilhaLiberaEnc(PilhaEnc *Ptf) {
  if (Ptf == NULL) return Ptf;
  No *temp = Ptf->topo;
  while (temp != NULL) {
    No *proximo = temp->prox;
    free(temp);
    temp = proximo;
  }
  free(Ptf);
  return NULL; 
}

/* Verifica se a pilha encadeada está vazia */
int pilhaVaziaEnc(PilhaEnc *Ptf) {
  return (Ptf->N == 0);
}

/* Insere um jogo na pilha encadeada (push) */
PilhaEnc *pilhaInsereEnc(PilhaEnc *Ptf, RPG rp) {
  if (Ptf == NULL) return Ptf;
  No *novo = (No*) malloc(sizeof(No));
  if (novo == NULL) return Ptf; 
  novo->rp = rp;
  novo->prox = Ptf->topo; 
  Ptf->topo = novo; 
  Ptf->N++;
  return Ptf;
}

/* Remove um jogo da pilha encadeada (pop) */
PilhaEnc *pilhaRemoveEnc(PilhaEnc *Ptf, RPG *rp) {
  if (Ptf == NULL || pilhaVaziaEnc(Ptf)) return Ptf;
  No *temp = Ptf->topo;
  *rp = temp->rp;
  Ptf->topo = temp->prox;
  free(temp);
  Ptf->N--;
  return Ptf;
}

/* Consulta o jogo do topo da pilha encadeada */
int pilhaConsultaEnc(PilhaEnc *Ptf, RPG *rp) {
  if (Ptf == NULL || pilhaVaziaEnc(Ptf)) return 0;
  *rp = Ptf->topo->rp;
  return 1;
}

/* Exibe a pilha encadeada */
int pilhaExibeEnc(PilhaEnc *Ptf) {
  if (pilhaVaziaEnc(Ptf)) return 0;
  No *temp = Ptf->topo;
  while (temp != NULL) {
    rpgExibe(temp->rp);
    temp = temp->prox;
  }
  printf("\n");
  return 1;
}

/* Encontra o tamanho da pilha encadeada */
int pilhaTamanhoEnc(PilhaEnc *Ptf) {
  return Ptf->N;
}

typedef struct stackEst { // Estrutura da pilha estática
  RPG pilha[MAX];
  int topo; 
} PilhaEst;

/* Cria e inicializa a pilha estática */
PilhaEst *pilhaCriaEst() {
  PilhaEst *Ptf = (PilhaEst*) malloc(sizeof(PilhaEst));
  if (Ptf != NULL) {
    Ptf->topo = -1; // Inicializa o topo como vazio
  }
  return Ptf;
}

/* Libera a memória alocada p/ a pilha estática */
PilhaEst *pilhaLiberaEst(PilhaEst *Ptf) {
  if (Ptf == NULL) return NULL;
  free(Ptf);
  return NULL;
}

/* Verifica se a pilha está cheia */
int pilhaCheiaEst(PilhaEst *Ptf) {
  return (Ptf->topo == MAX - 1);
}

/* Verifica se a pilha está vazia */
int pilhaVaziaEst(PilhaEst *Ptf) {
  return (Ptf->topo == -1);
}

/* Insere um jogo na pilha estática */
PilhaEst *pilhaInsereEst(PilhaEst *Ptf, RPG rp) {
  if (Ptf == NULL || pilhaCheiaEst(Ptf)) return Ptf;
  Ptf->pilha[++Ptf->topo] = rp; // Incrementa o topo e insere
  return Ptf;
}

/* Remove um jogo da pilha estática */
PilhaEst *pilhaRemoveEst(PilhaEst *Ptf, RPG *rp) {
  if (Ptf == NULL || pilhaVaziaEst(Ptf)) return Ptf;
  *rp = Ptf->pilha[Ptf->topo--]; 
  return Ptf;
}

/* Consulta um jogo do topo da pilha estática */
int pilhaConsultaEst(PilhaEst *Ptf, RPG *rp) {
  if (Ptf == NULL || pilhaVaziaEst(Ptf)) return 0;
  *rp = Ptf->pilha[Ptf->topo]; // Retorna o jogo do topo
  return 1;
}

/* Exibe a pilha estática */
int pilhaExibeEst(PilhaEst *Ptf) {
  if (pilhaVaziaEst(Ptf)) return 0;
  for (int i = 0; i <= Ptf->topo; i++) {
    rpgExibe(Ptf->pilha[i]); // Exibe cada jogo da pilha
  }
  printf("\n");
  return 1;
}

/* Encontra o tamanho da pilha estática */
int pilhaTamanhoEst(PilhaEst *Ptf) {
  return Ptf->topo + 1; // Retorna o número de elementos
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

/* Mostra o estado de uma partida de RPG */
void rpgExibe(const RPG rp) {
  printf(C_FMT(C_NEGRITO C_CIANO, "\n=========================\n"));
  printf(C_FMT(C_NEGRITO C_MAGENTA, "         Turno: %d\n"), rp.turno);
  printf(C_FMT(C_NEGRITO C_CIANO, "=========================\n"));
  for (int i = 0; i < 2; i++) {
    Jogador p = (i == 0) ? rp.p1 : rp.p2;
    printf(C_FMT(C_NEGRITO C_AZUL, "   Jogador[%d]\n"), i + 1);
    printf(C_FMT(C_NEGRITO C_CIANO, "-------------------------\n"));
    printf(C_FMT(C_NEGRITO C_LARANJA, "   LVL:  %d\n"), p.lvl);
    printf(C_FMT(C_NEGRITO C_ROSA, "   Nome: %s\n"), p.nome);
    printf(C_FMT(C_NEGRITO C_VERDE, "   HP:   %d\n"), p.hp);
    printf(C_FMT(C_NEGRITO C_ROXO, "   MP:   %d\n"), p.mp);
    printf(C_FMT(C_NEGRITO C_VERMELHO, "   ATK:  %d\n"), p.atq);
    printf(C_FMT(C_NEGRITO C_CINZA, "   DEF:  %d\n"), p.def);
    printf(C_FMT(C_NEGRITO C_CIANO, "-------------------------\n"));
  }
  printf(C_FMT(C_NEGRITO C_CIANO, "=========================\n\n"));
}

/* Aleatoriza as informações de um Jogador */
Jogador jogadorAleatoriza() {
  Jogador pl;
  int tam = rand() % (sizeof(pl.nome) / 2) + sizeof(pl.nome) / 4;
  for (int i = 0; i < tam; i++) { // Gera caracteres aleatórios entre 'a' e 'z'
    pl.nome[i] = (rand() % 26) + 'a'; 
  }
  pl.nome[tam] = '\0';
  pl.lvl = rand() % 10 + 1;
  pl.def = rand() % 10 + 1;
  pl.hp = rand() % 100 + 1;
  pl.tipAtq = (rand() % 2 == 0) ? ATAQUE_FISICO : ATAQUE_MAGICO;
  if (pl.tipAtq == ATAQUE_FISICO) {
    pl.atq = rand() % 10 + 1; 
    pl.mp = 0;
  } else { 
    pl.mp = rand() % 10 + 1;
    pl.atq = 0;
  }
  return pl;
}

/* Aleatoriza as informações de uma partida de RPG */
RPG rpgAleatoriza(const int turno) {
  RPG rp;
  rp.turno = turno;
  rp.p1 = jogadorAleatoriza();
  rp.p2 = jogadorAleatoriza();
  return rp;
}

/* Realiza uma batalha entre dois players */
RPG rpgBatalha(RPG rp) {
  if (rp.turno % 2 == 1) { // Jogador 1 ataca Jogador 2
    if (rp.p1.tipAtq == ATAQUE_FISICO) rp.p2.hp -= rp.p1.atq;
    else rp.p2.hp -= rp.p1.mp;
    if (rp.p2.hp <= 0) rp.p2.hp = 0;
  } else {
    if (rp.p2.tipAtq == ATAQUE_FISICO) rp.p1.hp -= rp.p2.atq;
    else rp.p1.hp -= rp.p2.mp;
    if (rp.p1.hp <= 0) rp.p1.hp = 0;
  }
  rp.turno++;
  return rp; 
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