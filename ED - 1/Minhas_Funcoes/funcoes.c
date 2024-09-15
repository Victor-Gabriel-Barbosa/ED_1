#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "funcoes.h"

/* Variáveis que armazenam cores de texto */
const char *C_RSET = "\033[0m";
const char *C_AZUL = "\033[38;5;39m"; 
const char *C_VERD = "\033[38;5;46m";
const char *C_CIAN = "\033[38;5;51m";
const char *C_VERM = "\033[38;5;196m";
const char *C_MAGE = "\033[38;5;201m";
const char *C_AMAR = "\033[38;5;220m";

typedef struct no { // Estrutura que armazena os nós da lista
  Info dado;
  struct no *prox;
  struct no *ant;
} No;

typedef struct lista { // Estrutura que armazena a lista
  No *inicio;
  No *fim;
  int tam;
} Lista;

/* Cria uma nova lista vazia */ 
Lista *listaCria() {
  Lista *Ptd = (Lista *)malloc(sizeof(Lista));
  if (Ptd != NULL) { // Inicializa a lista se a alocação for bem sucedida
    Ptd->inicio = NULL;
    Ptd->fim = NULL;
    Ptd->tam = 0;
  }
  return Ptd;
}

/* Tamanho da lista */
int listaSize(Lista *Ptd) { 
  return Ptd->tam;
}

/* Insere um novo elemento no início da lista */
Lista* listaInsereInicio(Lista *Ptd, const Info dado) {
  No *novo = (No *)malloc(sizeof(No));
  if (novo == NULL) return Ptd; 
  novo->dado = dado;
  novo->prox = Ptd->inicio;
  novo->ant = NULL;
  if (Ptd->inicio != NULL) Ptd->inicio->ant = novo; 
  Ptd->inicio = novo;
  if (Ptd->fim == NULL) Ptd->fim = novo; 
  Ptd->tam++;
  return Ptd;
}

/* Insere um novo elemento no fim da lista */
Lista *listaInsereFim(Lista *Ptd, const Info dado) {
  No *novo = (No *)malloc(sizeof(No));
  if (novo == NULL) return Ptd;
  novo->dado = dado;
  novo->prox = NULL;
  novo->ant = Ptd->fim;
  if (Ptd->fim != NULL) Ptd->fim->prox = novo;
  Ptd->fim = novo;
  if (Ptd->inicio == NULL) Ptd->inicio = novo;
  Ptd->tam++;
  return Ptd;
}

/* Remove um elemento da lista */
Lista *listaRemove(Lista *Ptd, const Info dado) {
  if (Ptd == NULL) return Ptd;
  No *atual = Ptd->inicio;
  while (atual != NULL) { // Percorre a lista
    if (atual->dado.id == dado.id) { // Se encontrou o dado, remove e retorna a lista
      if (atual->ant != NULL) atual->ant->prox = atual->prox;
      else Ptd->inicio = atual->prox;
      if (atual->prox != NULL) atual->prox->ant = atual->ant;
      else Ptd->fim = atual->ant;
      free(atual);
      Ptd->tam--;
      return Ptd;
    }
    atual = atual->prox;
  }
  return Ptd;
}

/* Libera toda a memória alocada para a lista */
Lista *listaLibera(Lista *Ptd) {
  if (Ptd == NULL) return Ptd;
  No *atual = Ptd->inicio;
  No *prox;
  while (atual != NULL) { // Libera todos os nós da lista
    prox = atual->prox;
    free(atual); 
    atual = prox;
  }
  free(Ptd); 
}

/* Imprime a lista */
int listaImprime(Lista *Ptd) {
  if (Ptd == NULL || Ptd->inicio == NULL) return 0;
  int cont = 0;
  No *atual = Ptd->inicio;
  while (atual != NULL) { // Mostra todos os elementos da lista
    cont++;
    printf("ID: %d\n", atual->dado.id);
    printf("Nome: %s\n", atual->dado.nome);
    printf("Idade: %d\n", atual->dado.idade);
    printf("Salário: %.2f\n", atual->dado.salario);
    printf((cont % 10 == 0) ? "\n" : " ");
    atual = atual->prox;
  }
  return 1;
} 

/* Ordena usando o Insertion Sort */
void insertionSort(No *inicio, No *fim) {
  No *i, *j;
  Info temp;
  for (i = inicio->prox; i != NULL && i != fim->prox; i = i->prox) {
    temp = i->dado;
    j = i;
    while (j->ant != NULL && j->ant->dado.id > temp.id) {
      j->dado = j->ant->dado;
      j = j->ant;
    }
    j->dado = temp;
  }
}

/* Função para mesclar duas runs */
No* merge(No *inicio1, No *fim1, No *inicio2, No *fim2) {
  No dummy;
  No *tail = &dummy;
  dummy.prox = NULL;
  while (inicio1 != NULL && inicio2 != NULL && inicio1 != fim1->prox && inicio2 != fim2->prox) {
    if (inicio1->dado.id <= inicio2->dado.id) {
      tail->prox = inicio1;
      inicio1->ant = tail;
      tail = tail->prox;
      inicio1 = inicio1->prox;
    } else {
      tail->prox = inicio2;
      inicio2->ant = tail;
      tail = tail->prox;
      inicio2 = inicio2->prox;
    }
  }
  while (inicio1 != NULL && inicio1 != fim1->prox) {
    tail->prox = inicio1;
    inicio1->ant = tail;
    tail = tail->prox;
    inicio1 = inicio1->prox;
  }
  while (inicio2 != NULL && inicio2 != fim2->prox) {
    tail->prox = inicio2;
    inicio2->ant = tail;
    tail = tail->prox;
    inicio2 = inicio2->prox;
  }
  tail->prox = NULL;
  return dummy.prox;
}

/* Função principal do Tim Sort */
Lista* listaTimSort(Lista *Ptd) {
  if (Ptd == NULL || Ptd->inicio == NULL) return Ptd;
  int minRun = 32; // Tamanho mínimo da run
  No *inicio = Ptd->inicio;
  No *fim;
  No *tempInicio;
  while (inicio != NULL) { // Ordena por runs usando Insertion Sort
    tempInicio = inicio;
    fim = inicio;
    int count = 1;
    while (fim->prox != NULL && count < minRun) {
      fim = fim->prox;
      count++;
    }
    if (fim->prox != NULL) {
      insertionSort(tempInicio, fim);
      inicio = fim->prox;
    } else {
      insertionSort(tempInicio, fim);
      break;
    }
  }
  No *leftStart, *leftEnd, *rightStart, *rightEnd;
  inicio = Ptd->inicio;
  while (inicio != NULL && inicio->prox != NULL) {
    leftStart = inicio;
    leftEnd = inicio;
    int count = 1;
    while (leftEnd->prox != NULL && count < minRun) {
      leftEnd = leftEnd->prox;
      count++;
    }
    if (leftEnd->prox != NULL) {
      rightStart = leftEnd->prox;
      rightEnd = rightStart;
      count = 1;
      while (rightEnd->prox != NULL && count < minRun) {
        rightEnd = rightEnd->prox;
        count++;
      }
      inicio = rightEnd->prox;
      Ptd->inicio = merge(leftStart, leftEnd, rightStart, rightEnd);
    } else break;
  }
  return Ptd;
}

/* Mescla duas listas */
Lista *listaMescla(Lista *Ptl1, Lista *Ptl2) {
  No *n1 = Ptl1->inicio;
  No *n2 = Ptl2->inicio;
  Lista *novaLista = listaCria();
  while (n1 != NULL && n2 != NULL) { // Percorre as duas listas
    if (n1->dado.id < n2->dado.id) { // Insere o menor elemento das listas
      novaLista = listaInsereFim(novaLista, n1->dado);
      n1 = n1->prox;
    } else {
      novaLista = listaInsereFim(novaLista, n2->dado);
      n2 = n2->prox;
    }
  }
  while (n1 != NULL) { // Insere os elementos restantes da lista 1
    novaLista = listaInsereFim(novaLista, n1->dado);
    n1 = n1->prox;
  }
  while (n2 != NULL) { // Insere os elementos restantes da lista 2
    novaLista = listaInsereFim(novaLista, n2->dado);
    n2 = n2->prox;
  }
  return novaLista;
}

/* Limpa o buffer do teclado */
void limpaBuffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}

/* Limpa a tela */
void cls() {
  #ifdef _WIN32
    system("cls");
  #else 
    system("clear");
  #endif
}

/* Espera uma entrada do usuário para limpar a tela */
void limpaTela(const char *msg) {
  printf("\n%s", msg);
  limpaBuffer();
  cls();
}

/* Faz uma operação de potência */
double potencia(double a, double b) {
  double resultado = 1;
  for (int i = 0; i < b; i++) {
    resultado *= a;
  }
  return resultado;
}

/* Confirma uma ação */
int simOuNao(const char *msg) { 
  while (1) {
    printf("\nTem certeza que deseja %s%s%s?\n", C_VERM, msg, C_RSET);
    printf("[%sS%s/%sN%s]: ", C_AZUL, C_RSET, C_VERM, C_RSET);
    char op = tolower(getchar());
    limpaBuffer();
    if (op == 's') return 1;
    if (op == 'n') return 0;
    cls();
    printf("\n%s[Opção inválida!]%s\n", C_VERM, C_RSET);
  }
}

/* Insere todos os números de um arquivo em uma lista */
Lista *arquivoCarrega(Lista *Ptd, const char *nome_arqv, int qtde) {
  FILE *arquivo = fopen(nome_arqv, "r");
  if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
    printf("\n%s[Erro ao abrir o arquivo!]%s\n", C_VERM, C_RSET);
    return Ptd;
  }
  char *linha = NULL;
  size_t len = 0;
  
  if ((getline(&linha, &len, arquivo)) == -1) {
    printf("\n%s[Erro ao ler a primeira linha do arquivo!]%s\n", C_VERM, C_RSET);
    fclose(arquivo);
    return Ptd;
  }

  Info dado;
  while (((getline(&linha, &len, arquivo)) != -1) && qtde > 0) {
    dado.id = atoi(strtok(linha, ","));
    char *nome = strtok(NULL, ",");
    if (nome != NULL) dado.nome = strdup(nome);
    dado.idade = atoi(strtok(NULL, ","));
    dado.salario = atof(strtok(NULL, ","));
    Ptd = (rand() % 2 == 0) ? listaInsereInicio(Ptd, dado) : listaInsereFim(Ptd, dado);
    qtde--;
  }
  free(linha);
  fclose(arquivo); 
  return Ptd;
} 

int arquivoAleatoriza(const char *nome_arqv, const int min, const int max, const int qtde) { 
  int cont_a = 1;
  if (access(nome_arqv, F_OK) == 0) { // F_OK verifica se o arquivo existe
    printf("\n%s[Arquivo '%s' localizado!]%s\n", C_VERD, nome_arqv, C_RSET);
    return 0;
  }
  FILE *arquivo = fopen(nome_arqv, "w"); // Abre o arquivo para escrita
  if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
    printf("\n%s[Erro ao criar o arquivo!]%s\n", C_VERM, C_RSET);
    return -1;
  }
  for (int i = 0; i < qtde; i++) { // Gera números aleatórios entre min e max
    int numero = rand() % (max - min + 1) + min; 
    fprintf(arquivo, "%d", numero);
    fprintf(arquivo, (i + 1) % 10 == 0 ? "\n" : ","); // Quebra de linha a cada 10 números
  }
  fclose(arquivo); // Fecha o arquivo
  printf("\n%s[Arquivo '%s' criado com sucesso!]%s\n", C_VERD, nome_arqv, C_RSET);
  return 1;
}

int arquivoSalva(Lista *Ptd, const char *nome_arqv) {
  if (Ptd == NULL || Ptd->inicio == NULL) return 0;
  char nome_final[100];
  char base[100], extensao[10];
  char *ext = strrchr(nome_arqv, '.');  // Encontra a última ocorrência de '.' para identificar a extensão do arquivo
  if (ext != NULL) {
    strcpy(extensao, ext); // Copia a extensão
    strncpy(base, nome_arqv, ext - nome_arqv); // Copia a parte base (sem extensão)
    base[ext - nome_arqv] = '\0';
  } else {
    strcpy(base, nome_arqv);
    strcpy(extensao, "");
  }
  int cont_a = 1;
  sprintf(nome_final, "%s%s", base, extensao); // Começa com o nome original
  while (access(nome_final, F_OK) == 0) { // Verifica se o arquivo existe e incrementa o nome se necessário
    sprintf(nome_final, "%s(%d)%s", base, cont_a++, extensao);
  }
  FILE *arquivo = fopen(nome_final, "w");
  if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
    printf("\n%s[Erro ao abrir o arquivo!]%s\n", C_VERM, C_RSET);
    return -1;
  }
  No *atual = Ptd->inicio;
  int cont_n = 0;
  while (atual != NULL) { // Salva a lista no arquivo
    cont_n++;
    fprintf(arquivo, "ID,Nome,Idade,Salario\n");
    fprintf(arquivo, "%d,%s,%d,%.2f\n", atual->dado.id, atual->dado.nome, atual->dado.idade, atual->dado.salario);
    atual = atual->prox;
  }
  if (fclose(arquivo) != 0) { // Fecha o arquivo e verifica se houve erro
    printf("\n%s[Erro ao fechar o arquivo!]%s\n", C_VERM, C_RSET);
    return -1;
  } 
  printf("\n%s[Arquivo '%s' salvo com sucesso!]%s\n", C_VERD, nome_final, C_RSET);
  return 1;
}


/* Exclui todas as ocorrências de um arquivo */
int arquivoExclui(const char *nome_arqv) {
  char nome_final[100], msg[100];
  char base[100], extensao[10] = "";
  int cont_a = 0;
  char *ext = strrchr(nome_arqv, '.');
  if (ext != NULL) { // Verifica se há uma extensão e separa o nome base e a extensão
    strcpy(extensao, ext); // Copia a extensão
    strncpy(base, nome_arqv, ext - nome_arqv); // Copia a parte base (sem extensão)
    base[ext - nome_arqv] = '\0'; // Adiciona o terminador nulo
  } else strcpy(base, nome_arqv);
  strcpy(nome_final, nome_arqv);
  while (access(nome_final, F_OK) == 0) { // Verifica a existência do arquivo original
    sprintf(msg, "excluir '%s'", nome_final);
    if (simOuNao(msg)) { // Chama a função simOuNao para confirmar a exclusão
      if (remove(nome_final) == 0) printf("\n%s[Arquivo '%s' excluído com sucesso!]%s\n", C_VERM, nome_final, C_RSET);
      else printf("\n%s[Erro ao excluir o arquivo '%s'!]%s\n", C_VERM, nome_final, C_RSET);
    }
    sprintf(nome_final, "%s(%d)%s", base, ++cont_a, extensao); 
  }
  return cont_a;
}