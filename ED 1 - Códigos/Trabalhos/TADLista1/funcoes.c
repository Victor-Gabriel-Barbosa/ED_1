#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10

/* Variáveis que armazenam cores de texto */
const char *rset = "\033[0m";
const char *azul = "\033[38;5;39m";
const char *verd = "\033[38;5;46m";
const char *cian = "\033[38;5;51m";
const char *verm = "\033[38;5;196m";
const char *mage = "\033[38;5;201m";
const char *amar = "\033[38;5;220m";

/* Estrutura p/ armazenar a lista */
struct lista { 
  int FL;
  Transacao trans[MAX];
};

typedef struct lista Lista;

/* Cria a lista */
Lista *Cria_lista(void) {
  Lista *pt = (Lista *)malloc(sizeof(Lista));
  if (pt != NULL) // Se a lista foi criada com sucesso
    pt->FL = 0;
  return pt;
}

/* Libera a lista */
Lista *Libera_lista(Lista *Ptl) {
  free(Ptl);
  return NULL;
}

/* Insere um elemento no final da lista */
Lista *Insere_elem(Lista *Ptl, Transacao info) {
  if (Ptl == NULL || Ptl->FL == MAX) // Se a lista não foi criada ou está cheia
    return Ptl;
  Ptl->trans[Ptl->FL] = info;
  Ptl->FL++;
  return Ptl;
}

/* Remove um elemento da lista movendo os elementos restantes */
Lista *Remove_elem_mov(Lista *Ptl, int valor_ID) {
  int i, k;
  if (Ptl == NULL || Ptl->FL == 0) // Se a lista não foi criada ou está vazia
    return Ptl;

  // Procura o elemento na lista
  i = 0;
  while (i < Ptl->FL && Ptl->trans[i].ID != valor_ID)
    i++;

  if (i == Ptl->FL) // Se o elemento não foi encontrado
    return Ptl;

  // Remove o elemento da lista
  for (k = i; k < Ptl->FL - 1; k++)
    Ptl->trans[k] = Ptl->trans[k + 1];

  Ptl->FL--; // Atualiza o tamanho da lista
  return Ptl;
}

/* Remove um elemento da lista substituindo pelo último */
Lista *Remove_elem(Lista *Ptl, int valor_ID) {
  int i;
  if (Ptl != NULL) { // Se a lista foi criada
    i = 0;
    while (i < Ptl->FL && Ptl->trans[i].ID != valor_ID) // Procura o elemento na lista
      i++;
    if (i == Ptl->FL) { // Se o elemento não foi encontrado
      return Ptl; 
    }
    Ptl->trans[i] = Ptl->trans[Ptl->FL - 1]; // Substitui pelo último
    Ptl->FL--; // Atualiza o tamanho da lista
  }
  return Ptl;
}

/* Retorna o elemento da posição dada */
int Consulta_nodo(Lista *Ptl, int valor_ID, Transacao *info) {
  if (Ptl == NULL || Ptl->FL == 0) // Se a lista não foi criada
    return 0;
  int i;
  for (i = 0; i < Ptl->FL; i++) { // Percorre a lista
    if (Ptl->trans[i].ID == valor_ID) { // Se encontrou o elemento
      *info = Ptl->trans[i];
      return 1;
    }
  }
  return 0;
}

/* Retorna o tamanho da lista */
int Tamanho_lista(Lista *Ptl) {
  if (Ptl == NULL) // Se a lista não foi criada
    return -1;
  return Ptl->FL;
}

/* Verifica se a lista está cheia */
int E_cheia(Lista *Ptl) {
  if (Ptl == NULL) { // Se a lista não foi criada
    return -1;
  }
  if (Ptl->FL == MAX) { // Se a lista está cheia
    return 1;
  }
  return 0;
}

/* Verifica se a lista está vazia */
int E_vazia(Lista *Ptl) { 
  if (Ptl == NULL) // Se a lista não foi criada
    return -1;
  if (Ptl->FL == 0) // Se a lista está vazia
    return 1;
  return 0;
}

/* Limpa o buffer do teclado */
void Limpa_buffer() { 
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}

/* Limpa a tela do terminal */
void Cls_screen() { 
  #ifdef _WIN32 // Verifica se o sistema é Windows
    system("cls");
  #else // Caso contrário, assume que é um sistema Unix
    system("clear");
  #endif 
}

/* Aguarda uma entrada do usuário p/ limpar a tela do terminal */
void Limpa_tela() {
  printf("%s\nAperte %s[ENTER]%s p/ continuar...", rset, azul, rset);
  Limpa_buffer();
  Cls_screen();
}

/* Exibe uma barra de divisão */
void Barra_div(const char *i, const char *f) {
  printf("%s%s<>%s==============%s<>%s==============%s<>%s%s", i, cian, rset, mage, rset, cian, rset, f);
}

/* Solicita e retorna a confirmação de uma ação do usuário */
int Sim_ou_nao(const char *msg) { 
  while (1) { // Loop infinito
    Limpa_tela();
    Barra_div("", "\n");
    printf("Tem certeza que deseja %s%s?%s\n", azul, msg, rset);
    printf("[%sS%s|%sN%s]: ", verd, rset, verm, rset);
    char resp = getchar();
    Limpa_buffer();
    if (resp == 's' || resp == 'S' || resp == '1') { // Se a resposta for sim
      return 1;
    } else if (resp == 'n' || resp == 'N' || resp == '0') { // Se a resposta for não
      return 0;
    } else { // Se a resposta for inválida
      printf("\n%s[Opção inválida!]%s\n", verm, rset);
    }
  }
}

/* Exibe a lista de transações */
int Exibe_lista(Lista *Ptl) { 
  if (Ptl == NULL) { // Se a lista não foi criada
    return -1;
  }
  for (int i = 0; i < Ptl->FL; i++) { // Percorre a lista
    Barra_div("", "\n");
    printf("%s╔═════════════════════════════╗%s\n", azul, rset);
    printf("%s║ [Transação ID: %04d]        ║%s\n", azul, Ptl->trans[i].ID, rset);
    printf("%s╚═════════════════════════════╝%s\n", azul, rset);
    printf("%sTipo:       %-20s%s\n", azul, Ptl->trans[i].tipo == DEBITO ? "Débito" : "Crédito", rset);
    printf("%sValor:      R$ %10.2f%s\n", azul, Ptl->trans[i].valor, rset);
    printf("%sData:       %02d/%02d/%04d%s\n", azul, Ptl->trans[i].data.dia, Ptl->trans[i].data.mes, Ptl->trans[i].data.ano, rset);
    printf("%sHora:       %02d:%02d:%02d%s\n", azul, Ptl->trans[i].hora.hora, Ptl->trans[i].hora.minuto, Ptl->trans[i].hora.segundo, rset);
    printf("%sDescrição:  %-20s%s\n", azul, Ptl->trans[i].descricao, rset);
    Barra_div("", "\n");
  }
  return 1;
}

/* Grava a lista em um arquivo */
int Grava_lista(Lista *Ptl, char *nome_arqv) { 
  if (Ptl == NULL) { // Se a lista não foi criada
    return -1;
  }
  FILE *fp = fopen(nome_arqv, "w"); // Abre o arquivo para escrita
  if (fp == NULL) { // Se o arquivo não foi aberto
    printf("\n[Erro ao abrir o arquivo %s]\n", nome_arqv);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < Ptl->FL; i++) { // Percorre a lista
    fprintf(fp, "%d\n", Ptl->trans[i].ID);
    fprintf(fp, "%d\n", Ptl->trans[i].tipo);
    fprintf(fp, "%.2f\n", Ptl->trans[i].valor);
    fprintf(fp, "%d\n", Ptl->trans[i].data.dia);
    fprintf(fp, "%d\n", Ptl->trans[i].data.mes);
    fprintf(fp, "%d\n", Ptl->trans[i].data.ano);
    fprintf(fp, "%s\n", Ptl->trans[i].descricao);
  }
  fclose(fp); // Fecha o arquivo
  return 1;
}

/* Retorna a data atual */
Data Get_data() { 
  Data data;
  time_t t = time(NULL); // Obtém o tempo atual
  struct tm tm = *localtime(&t); // Converte o tempo em uma estrutura tm
  data.dia = tm.tm_mday;
  data.mes = tm.tm_mon + 1;
  data.ano = tm.tm_year + 1900;
  return data;
}

/* Retorna a hora atual */
Hora Get_hora() { 
  Hora hora;
  time_t t = time(NULL); // Obtém o tempo atual
  struct tm tm = *localtime(&t); // Converte o tempo em uma estrutura tm
  hora.hora = tm.tm_hour;
  hora.minuto = tm.tm_min;
  hora.segundo = tm.tm_sec;
  return hora;
}

/* Função para capturar os dados da transação */
Transacao Get_transacao() { 
  Transacao trans;
  printf("\n%s[Inserir transação]%s\n", amar, rset);
  printf("ID: ");
  scanf("%d", &trans.ID);
  Limpa_buffer();
  printf("Tipo (%s0 - Débito%s, %s1 - Crédito%s): ", azul, rset, amar, rset);
  scanf("%d", &trans.tipo);
  Limpa_buffer();
  printf("Valor %sR$:%s ", amar, rset);
  scanf("%f", &trans.valor);
  Limpa_buffer();
  printf("Descrição: ");
  scanf("%99[^\n]", trans.descricao);
  Limpa_buffer();
  trans.data = Get_data();
  trans.hora = Get_hora();
  return trans;
}

/* Exibe uma transação da lista */
void Exibe_transacao(Transacao info) {
  Barra_div("", "\n");
  printf("%s╔═════════════════════════════╗%s\n", azul, rset);
  printf("%s║ [Transação ID: %04d]        ║%s\n", azul, info.ID, rset);
  printf("%s╚═════════════════════════════╝%s\n", azul, rset);
  printf("%sTipo:       %-20s%s\n", azul, info.tipo == DEBITO ? "Débito" : "Crédito", rset);
  printf("%sValor:      R$ %10.2f%s\n", azul, info.valor, rset);
  printf("%sData:       %02d/%02d/%04d%s\n", azul, info.data.dia, info.data.mes, info.data.ano, rset);
  printf("%sHora:       %02d:%02d:%02d%s\n", azul, info.hora.hora, info.hora.minuto, info.hora.segundo, rset);
  printf("%sDescrição:  %-20s%s\n", azul, info.descricao, rset);
  Barra_div("", "\n");
}

/* Compara duas datas */
int Compara_datas(Data a1, Data a2) {
  if (a1.ano != a2.ano) // Se os anos são diferentes
    return a1.ano - a2.ano; 
  if (a1.mes != a2.mes) // Se os meses são diferentes
    return a1.mes - a2.mes; 
  return a1.dia - a2.dia; // Se os dias são diferentes
}

/* Edita uma transação existente */
Lista *Edita_transacao(Lista *Ptl, int valor_ID) {
  Transacao info;
  if (Consulta_nodo(Ptl, valor_ID, &info)) { // Se encontrou a transação
    printf("\n%s[Editar transação]%s\n", amar, rset);
    printf("ID atual: %d\n", info.ID);
    printf("Novo tipo (%s0 - Débito%s, %s1 - Crédito%s): ", azul, rset, amar, rset);
    scanf("%d", &info.tipo);
    Limpa_buffer();
    printf("Novo valor %sR$:%s ", amar, rset); 
    scanf("%f", &info.valor);
    Limpa_buffer();
    printf("Nova descrição: ");
    scanf("%99[^\n]", info.descricao);
    Limpa_buffer();
    info.data = Get_data();
    info.hora = Get_hora();
    for (int i = 0; i < Ptl->FL; i++) { // Percorre a lista
      if (Ptl->trans[i].ID == valor_ID) { // Se encontrou a transação
        Ptl->trans[i] = info;
        i = Ptl->FL;
      }
    }
    printf("\n%s[Transação editada com sucesso!]%s\n", azul, rset);
  } else { // Se não encontrou a transação
    printf("\n%s[Transação não encontrada!]%s\n", verm, rset);
  }
  return Ptl;
}

/* Exibe transações de um tipo específico */
void Filtra_transacoes(Lista *Ptl, int tipo) {
  printf("\n%s[Filtrando transações por tipo]%s\n", amar, rset);
  for (int i = 0; i < Ptl->FL; i++) { // Percorre a lista
    if (Ptl->trans[i].tipo == tipo) { // Se encontrou a transação
      Exibe_transacao(Ptl->trans[i]);
    }
  }
}

/* Exibe transações dentro de um intervalo de datas */
void Exibe_transacoes_por_data(Lista *Ptl, Data inicio, Data fim) {
  printf("\n%s[Filtrando transações por intervalo de datas]%s\n", amar, rset);
  for (int i = 0; i < Ptl->FL; i++) { // Percorre a lista
    if (Compara_datas(Ptl->trans[i].data, inicio) >= 0 && 
        Compara_datas(Ptl->trans[i].data, fim) <= 0) { // Se encontrou a transação
      Exibe_transacao(Ptl->trans[i]);
    }
  }
}

/* Calcula o saldo total */
float Calcula_saldo(Lista *Ptl) {
  float saldo = 0.0;
  for (int i = 0; i < Ptl->FL; i++) { // Percorre a lista
    if (Ptl->trans[i].tipo == DEBITO) // Se é um débito
      saldo -= Ptl->trans[i].valor;
    else // Se é um crédito
      saldo += Ptl->trans[i].valor;
  }
  return saldo;
}

/* Ordena transações por data */
void Ordena_transacoes_por_data(Lista *Ptl) {
  for (int i = 0; i < Ptl->FL - 1; i++) { // Percorre a lista
    for (int j = i + 1; j < Ptl->FL; j++) { // Percorre a lista a partir do próximo elemento
      if (Compara_datas(Ptl->trans[i].data, Ptl->trans[j].data) > 0) { // Compara as datas
        Transacao temp = Ptl->trans[i];
        Ptl->trans[i] = Ptl->trans[j];
        Ptl->trans[j] = temp;
      }
    }
  }
}

/* Função para exibir o menu e capturar a escolha do usuário */
int Escolha_menu() {
  int opcao;
  Limpa_tela();
  Barra_div("", "\n");
  printf("%sMENU DE TRANSAÇÕES🪙%s\n", mage, rset);
  Barra_div("", "\n");
  printf("%s[1]%s Fazer transação\n", cian, rset);
  printf("%s[2]%s Excluir transação\n", cian, rset);
  printf("%s[3]%s Consultar transação\n", cian, rset);
  printf("%s[4]%s Exibir transações\n", cian, rset);
  printf("%s[5]%s Baixar transações\n", cian, rset);
  printf("%s[6]%s Editar transação\n", cian, rset);
  printf("%s[7]%s Filtrar transações\n", cian, rset);
  printf("%s[8]%s Exibir transações por data\n", cian, rset);
  printf("%s[9]%s Calcular saldo\n", cian, rset);
  printf("%s[10]%s Ordenar transações por data\n", cian, rset);
  Barra_div("", "\n");
  printf("%s[0]%s Sair\n", cian, rset);  
  Barra_div("", "\n");
  printf("%sOpcao: %s", azul, rset);
  scanf("%d", &opcao);
  Limpa_buffer();
  return opcao;
}