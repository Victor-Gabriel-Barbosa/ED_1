#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "cores.h"
#include "utils.h"
#include "lladae2_cocktail_sort.h"

typedef struct no { // Estrutura que armazena os nós da lista
  int dado;
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
  if (Ptd != NULL) { // Inicializa a lista se a alocação for bem-sucedida
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
Lista* listaInsereInicio(Lista *Ptd, const int dado) {
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
Lista *listaInsereFim(Lista *Ptd, const int dado) {
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
Lista *listaRemove(Lista *Ptd, const int dado) {
  if (Ptd == NULL) return Ptd;
  No *atual = Ptd->inicio;
  while (atual != NULL) { // Percorre a lista
    if (atual->dado == dado) { // Se encontrou o dado, remove e retorna a lista
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

/* Libera toda a memória alocada p/ a lista */
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
    printf("%5d", atual->dado);
    printf((++cont % 10 == 0) ? "\n" : " ");
    atual = atual->prox;
  }
  return 1;
} 

/* Ordena a lista usando o algoritmo Cocktail Sort */
Lista *listaCocktailSort(Lista *Ptd) {
  if (Ptd == NULL || Ptd->inicio == NULL) return Ptd;
  int trocou, temp; // Variáveis auxiliares p/ trocas
  No *inicio = Ptd->inicio; 
  No *fim = Ptd->fim;
  No *atual;
  do { // Repete enquanto houver trocas
    trocou = 0;
    atual = inicio;
    while (atual != fim) { // Percorre da esquerda p/ a direita
      if (atual->dado > atual->prox->dado) { // Troca os valores dos nós se o dado atual for maior que o próximo
        temp = atual->dado;
        atual->dado = atual->prox->dado;
        atual->prox->dado = temp;
        trocou = 1;
      }
      atual = atual->prox;
    }
    if (!trocou) break; // A lista já está ordenada se não houve trocas
    fim = fim->ant; // Atualiza o ponteiro fim p/ a próxima iteração
    trocou = 0;
    atual = fim;
    while (atual != inicio) {  // Percorre da direita p/ a esquerda
      if (atual->dado < atual->ant->dado) { // Troca os valores dos nós se o dado atual for menor que o anterior
        temp = atual->dado;
        atual->dado = atual->ant->dado;
        atual->ant->dado = temp;
        trocou = 1;
      }
      atual = atual->ant;
    }
    inicio = inicio->prox; // Atualiza o ponteiro início p/ a próxima iteração
  } while (trocou);
  return Ptd;
}

/* Mescla duas listas */
Lista *listaMescla(Lista *Ptd1, Lista *Ptd2) {
  No *n1 = Ptd1->inicio;
  No *n2 = Ptd2->inicio;
  Lista *novaLista = listaCria();
  while (n1 != NULL && n2 != NULL) { // Percorre as duas listas
    if (n1->dado < n2->dado) { // Insere o menor elemento das listas
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

/* Espera uma entrada do usuário p/ limpar a tela */
void limpaTela(const char *msg) {
  printf("\n%s", msg);
  limpaBuffer();
  cls();
}

/* Faz uma operação de potência */
double potencia(double a, int b) {
  double result = 1;
  while (b-- > 0) result *= a; 
  return result;
}

/* Confirma uma ação */
int simOuNao(const char *msg) { 
  while (1) { // Confirma uma ação
    printf("\nDeseja %s%s%s?\n", C_VERMELHO, msg, C_RESET);
    printf("%s[S%s/%sN]%s: ", C_AZUL, C_MAGENTA, C_VERMELHO, C_RESET);
    char op = tolower(getchar());
    limpaBuffer();
    if (op == 's') return 1;
    if (op == 'n') return 0;
    cls();
    printf(C_FMT_ERRO("\n[Opção inválida!]\n"));
  }
}

/* Pede um nº dentro de um intervalo ao usuário */
int intervalo(const char *msg, int min, int max) {
  while (1) { // Confirma se o nº está no intervalo
    int num = -1;
    printf("\nDigite %s%s%s\n", C_MAGENTA, msg, C_RESET);
    printf("%s[%d%s-%s%d]%s: ", C_VERDE, min, C_MAGENTA, C_AZUL, max, C_RESET);
    scanf("%d", &num);
    limpaBuffer();
    if (num >= min && num <= max) return num; // Retorna o nº se ele estiver dentro do intervalo
    cls();
    printf(C_FMT_ERRO("\n[Nº inválido! Tente novamente!]\n"));
  }
} 

/* Insere todos os nºs de um arquivo em uma lista */
Lista *arquivoCarrega(Lista *Ptd, const char *nome_arqv, int qtd) {
  FILE *arquivo = fopen(nome_arqv, "r");
  if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
    printf(C_FMT_ERRO("\n[Erro ao abrir o arquivo!]: %s\n"), strerror(errno));
    return Ptd;
  }
  char *linha = NULL, *campo = NULL;
  size_t tam = 0;
  int dado;
  while ((getline(&linha, &tam, arquivo) != -1) && qtd > 0) { // Lê todas as linhas do arquivo até o final ou até preencher a quantidade de números necessária
    campo = strtok(linha, ","); // Divide a linha em strings usando ','
    while (campo != NULL && qtd > 0) { // Insere todos os nºs da linha na lista
      dado = atoi(campo); // Transforma a string em um inteiro
      Ptd = (rand() % 2 == 0) ? listaInsereInicio(Ptd, dado) : listaInsereFim(Ptd, dado); // Insere no início ou no fim de forma aleatória
      campo = strtok(NULL, ","); // Pega a próxima string
      qtd--;
    }
  }
  free(linha);
  fclose(arquivo); 
  return (qtd > 0) ? arquivoCarrega(Ptd, nome_arqv, qtd) : Ptd; // Faz uma chamada recursiva se ainda houver nºs p/ serem inseridos
} 

/* Gera nºs aleatórios e armazena em um arquivo */
int arquivoAleatoriza(const char *nome_arqv, const int min, const int max, const int qtd) { 
  int cont_a = 1;
  if (access(nome_arqv, F_OK) == 0) { // F_OK verifica se o arquivo existe
    printf(C_FMT_ERRO("\n[Arquivo '%s' localizado!]%s\n"), nome_arqv);
    return 0;
  }
  FILE *arquivo = fopen(nome_arqv, "w"); // Abre o arquivo p/ escrita
  if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
    printf(C_FMT_ERRO("\n[Erro ao criar o arquivo!]: %s\n"), strerror(errno));
    return -1;
  }
  printf("\n%sAleatorizando%s nºs...\n", C_AZUL, C_RESET);
  for (int i = 0; i < qtd; i++) { // Gera nºs aleatórios entre min e max
    fprintf(arquivo, "%d", (rand() % (max - min + 1) + min));
    fprintf(arquivo, (i + 1) % 10 == 0 ? "\n" : ","); // Quebra de linha a cada 10 nºs
  }
  fclose(arquivo);
  printf(C_FMT_SUCESSO("\n[Arquivo '%s' criado com sucesso!]\n"), nome_arqv);
  return 1;
}

/* Salva os dados da lista em um arquivo */
int arquivoSalva(Lista *Ptd, const char *nome_arqv) {
  if (Ptd == NULL || Ptd->inicio == NULL) return 0;
  char nome_final[strlen(nome_arqv) + 10];
  char nome_base[strlen(nome_arqv) + 1];
  char *ext = strrchr(nome_arqv, '.');  // Encontra a última ocorrência de '.'
  char extensao[6]; 
  if (ext != NULL) { // Verifica se o arquivo possui extensão
    strcpy(extensao, ext); // Copia a extensão
    strncpy(nome_base, nome_arqv, ext - nome_arqv); // Copia a parte base (sem extensão)
    nome_base[ext - nome_arqv] = '\0';
  } else { // Se não possuir adiciona a extensão '.csv' 
    strcpy(nome_base, nome_arqv);
    strcpy(extensao, ".csv");
  }
  int cont_a = 1;
  sprintf(nome_final, "%s%s", nome_base, extensao); // Começa com o nome original
  while (access(nome_final, F_OK) == 0) { // Verifica se o arquivo existe e incrementa o nome se necessário
    sprintf(nome_final, "%s(%d)%s", nome_base, cont_a++, extensao);
  }
  FILE *arquivo = fopen(nome_final, "w");
  if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
    printf(C_FMT_ERRO("\n[Erro ao abrir o arquivo!]: %s\n"), strerror(errno));
    return -1;
  }
  No *atual = Ptd->inicio;
  int cont_n = 0;
  while (atual != NULL) { // Salva a lista no arquivo
    fprintf(arquivo, "%d", atual->dado);
    fprintf(arquivo, (++cont_n % 10 == 0) ? "\n" : ","); // Quebra de linha a cada 10 nºs
    atual = atual->prox;
  }
  fclose(arquivo);
  printf(C_FMT_SUCESSO("\n[Arquivo '%s' salvo com sucesso!]\n"), nome_final);
  return 1;
}


/* Exclui todas as ocorrências de um arquivo */
int arquivoExclui(const char *nome_arqv) {
  char nome_final[strlen(nome_arqv) + 10], msg[strlen(nome_arqv) + 20];
  char base[strlen(nome_arqv) + 1], extensao[6];
  char *ext = strrchr(nome_arqv, '.');
  int cont_a = 0;
  if (ext != NULL) { // Verifica se há uma extensão e separa o nome base e a extensão
    strcpy(extensao, ext); // Copia a extensão
    strncpy(base, nome_arqv, ext - nome_arqv); // Copia a parte base (sem extensão)
    base[ext - nome_arqv] = '\0'; // Adiciona o terminador nulo
  } else strcpy(base, nome_arqv);
  strcpy(nome_final, nome_arqv);
  while (access(nome_final, F_OK) == 0) { // Verifica a existência do arquivo original
    sprintf(msg, "excluir '%s'", nome_final);
    if (simOuNao(msg)) { // Chama a função simOuNao p/ confirmar a exclusão
      if (remove(nome_final) == 0) printf(C_FMT_SUCESSO("\n[Arquivo '%s' excluído com sucesso!]\n"), nome_final);
      else printf(C_FMT_ERRO("\n[Erro ao excluir o arquivo '%s'!]: %s\n"), nome_final, strerror(errno));
    }
    sprintf(nome_final, "%s(%d)%s", base, ++cont_a, extensao); 
  }
  return cont_a;
}

/* Pede o nome de um arquivo ao usuário */
char *arquivoNome(const char *msg) {
  char *nome_arqv = NULL;
  size_t tam = 0;
  printf("\nDigite o nome do arquivo %s'%s'%s:\n", C_MAGENTA, msg, C_RESET);
  getline(&nome_arqv, &tam, stdin);
  nome_arqv[strcspn(nome_arqv, "\n")] = '\0';
  return nome_arqv;
}

/* Mostra todo o conteúdo de um arquivo na tela */
int printArquivo(const char *nome, const char *cor) {
  FILE *arquivo = fopen(nome, "r");
  if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
    printf(C_FMT_ERRO("\n[Arquivo '%s' não encontrado!]: %s%s\n"), nome, strerror(errno), C_RESET);
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