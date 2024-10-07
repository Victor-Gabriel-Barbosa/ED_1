#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Variáveis que armazenam cores de texto */
const char *rset = "\033[0m";
const char *azul = "\033[38;5;39m";
const char *verd = "\033[38;5;46m";
const char *cian = "\033[38;5;51m";
const char *verm = "\033[38;5;196m";
const char *mage = "\033[38;5;201m";
const char *amar = "\033[38;5;220m";

/* Estrutura para um nó da lista encadeada */
typedef struct no {
  Transacao trans;
  struct no *proximo;
} No;

/* Estrutura para a lista */
typedef struct lista {
  No *inicio;
} Lista;

/* Cria a lista */
Lista *Cria_lista(void) {
  Lista *pt = (Lista *)malloc(sizeof(Lista));
  if (pt != NULL) { // Se a alocação foi bem-sucedida
    pt->inicio = NULL;
  }
  return pt;
}

/* Libera a lista */
Lista* Libera_lista(Lista *Ptl) {
  if (Ptl == NULL) // Verifica se a lista é válida
    return Ptl;
  No *atual = Ptl->inicio;
  while (atual != NULL) { // Percorre a lista e libera cada nó
    No *prox = atual->proximo;
    free(atual);
    atual = prox;
  }
  free(Ptl);
  return NULL;
}

/* Insere um elemento no final da lista */
Lista *Insere_elem(Lista *Ptl, Transacao info) {
  if (Ptl == NULL) // Verifica se a lista é válida
    return Ptl;
  No *novo = (No *)malloc(sizeof(No));
  if (novo == NULL) // Verifica se o novo nó foi alocado corretamente
    return Ptl;
  novo->trans = info;
  novo->proximo = NULL;
  if (Ptl->inicio == NULL) { // Se a lista está vazia
    Ptl->inicio = novo;
  } else {
    No *temp = Ptl->inicio;
    while (temp->proximo != NULL) {
      temp = temp->proximo;
    }
    temp->proximo = novo;
  }
  return Ptl;
}

/* Remove um elemento da lista */
Lista *Remove_elem(Lista *Ptl, int valor_ID) {
  if (Ptl == NULL || Ptl->inicio == NULL)
    return Ptl;
  No *atual = Ptl->inicio;
  No *anterior = NULL;
  while (atual != NULL && atual->trans.ID != valor_ID) {
    anterior = atual;
    atual = atual->proximo;
  }
  if (atual == NULL) // elemento não encontrado
    return Ptl;
  if (anterior == NULL) // elemento a ser removido é o primeiro
    Ptl->inicio = atual->proximo;
  else
    anterior->proximo = atual->proximo;
  free(atual);
  return Ptl;
}

/* Consulta um elemento na lista */
int Consulta_nodo(Lista *Ptl, int valor_ID, Transacao *info) {
  if (Ptl == NULL || Ptl->inicio == NULL) // Se a lista estiver vazia
    return 0;
  No *atual = Ptl->inicio;
  while (atual != NULL) { // Percorre a lista até o final
    if (atual->trans.ID == valor_ID) { // Se o ID for encontrado
      *info = atual->trans;
      return 1;
    }
    atual = atual->proximo;
  }
  return 0;
}

/* Retorna o tamanho da lista */
int Tamanho_lista(Lista *Ptl) {
  if (Ptl == NULL) // Se a lista não foi criada
    return -1;
  int tam = 0;
  No *atual = Ptl->inicio;
  while (atual != NULL) { // Percorre a lista até o final
    tam++;
    atual = atual->proximo;
  }
  return tam;
}

/* Verifica se a lista está vazia */
int E_vazia(Lista *Ptl) {
  if (Ptl == NULL)
    return -1;
  return Ptl->inicio == NULL;
}

/* Verifica se a lista está ordenada */
int E_ordenada(Lista *Ptl) { 
  if (Ptl == NULL || Ptl->inicio == NULL) {
    return 1;  // Considera que uma lista vazia ou NULL está ordenada
  }
  No *atual = Ptl->inicio;
  while (atual->proximo != NULL) {
    if (atual->trans.ID > atual->proximo->trans.ID) {
      return 0;  // Lista não está ordenada
    }
    atual = atual->proximo;
  }
  return 1;  // Lista está ordenada
}

/* Ordena a lista por ID */
Lista* Ordena_lista(Lista *Ptl) { 
  if (Ptl == NULL || Ptl->inicio == NULL) { // Verifica se a lista está vazia ou não
    return Ptl;
  }
  int tam = Tamanho_lista(Ptl);
  for (int i = 0; i < tam - 1; i++) { // Percorre a lista até o penúltimo elemento
    No *atual = Ptl->inicio;
    No *proximo = atual->proximo;
    int trocou = 0; 
    while (proximo != NULL) { // Percorre a lista até o último elemento
      if (atual->trans.ID > proximo->trans.ID) { // Verifica se o ID do atual é maior que o do próximo
        Transacao temp = atual->trans;
        atual->trans = proximo->trans;
        proximo->trans = temp;
        trocou = 1;  // Marca que houve troca
      }
      atual = proximo;
      proximo = proximo->proximo;
    }
    if (!trocou) { // Se não houve troca, a lista já está ordenada
      i = tam - 1; 
      continue;
    }
  }
  return Ptl;
}

/* Função que mescla duas listas */
Lista* Mescla_listas(Lista* lista1, Lista* lista2) {
  if (lista1 == NULL && lista2 == NULL) { // Verifica se as listas são vazias
    return NULL;
  }
  Lista* lista_mesclada = Cria_lista();
  No* atual1 = lista1->inicio;
  No* atual2 = lista2->inicio;
  while (atual1 != NULL && atual2 != NULL) { // Percorre as listas até o final
    if (atual1->trans.ID < atual2->trans.ID) { // Verifica qual ID é menor
      Insere_elem(lista_mesclada, atual1->trans);
      atual1 = atual1->proximo;
    } else {
      Insere_elem(lista_mesclada, atual2->trans);
      atual2 = atual2->proximo;
    }
  }
  while (atual1 != NULL) { // Insere os elementos restantes da lista1
    Insere_elem(lista_mesclada, atual1->trans);
    atual1 = atual1->proximo;
  }
  while (atual2 != NULL) { // Insere os elementos restantes da lista2
    Insere_elem(lista_mesclada, atual2->trans);
    atual2 = atual2->proximo;
  }
  return lista_mesclada;
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
    } else if (resp == 'n' || resp == 'N' ||
               resp == '0') { // Se a resposta for não
      return 0;
    } else { // Se a resposta for inválida
      printf("\n%s[Opção inválida!]%s\n", verm, rset);
    }
  }
}

/* Exibe a lista de transações */
int Exibe_lista(Lista *Ptl) {
  if (Ptl == NULL)
    return -1;

  No *atual = Ptl->inicio;
  while (atual != NULL) {
    Barra_div("", "\n");
    printf("%s╔═════════════════════════════╗%s\n", azul, rset);
    printf("%s║ [Transação ID: %04d]        ║%s\n", azul, atual->trans.ID, rset);
    printf("%s╚═════════════════════════════╝%s\n", azul, rset);
    printf("%sTipo:       %-20s%s\n", azul, atual->trans.tipo == 0 ? "Débito" : "Crédito", rset);
    printf("%sValor:      R$ %10.2f%s\n", azul, atual->trans.valor, rset);
    printf("%sData:       %02d/%02d/%04d%s\n", azul, atual->trans.data.dia, atual->trans.data.mes, atual->trans.data.ano, rset);
    printf("%sHora:       %02d:%02d:%02d%s\n", azul, atual->trans.hora.hora, atual->trans.hora.minuto, atual->trans.hora.segundo, rset);
    printf("%sDescrição:  %-20s%s\n", azul, atual->trans.descricao, rset);
    Barra_div("", "\n");
    atual = atual->proximo;
  }
  return 1;
}

/* Grava a lista em um arquivo */
int Grava_lista(Lista *Ptl, char *nome_arqv) {
  if (Ptl == NULL)
    return -1;
  FILE *fp = fopen(nome_arqv, "w");
  if (fp == NULL) {
    printf("\n[Erro ao abrir o arquivo %s]\n", nome_arqv);
    exit(EXIT_FAILURE);
  }
  No *atual = Ptl->inicio;
  while (atual != NULL) {
    fprintf(fp, "%d\n", atual->trans.ID);
    fprintf(fp, "%d\n", atual->trans.tipo);
    fprintf(fp, "%.2f\n", atual->trans.valor);
    fprintf(fp, "%d\n", atual->trans.data.dia);
    fprintf(fp, "%d\n", atual->trans.data.mes);
    fprintf(fp, "%d\n", atual->trans.data.ano);
    fprintf(fp, "%s\n", atual->trans.descricao);
    atual = atual->proximo;
  }
  fclose(fp);
  return 1;
}

/* Retorna a data atual */
Data Get_data() {
  Data data;
  time_t t = time(NULL);         // Obtém o tempo atual
  struct tm tm = *localtime(&t); // Converte o tempo em uma estrutura tm
  data.dia = tm.tm_mday;
  data.mes = tm.tm_mon + 1;
  data.ano = tm.tm_year + 1900;
  return data;
}

/* Retorna a hora atual */
Hora Get_hora() {
  Hora hora;
  time_t t = time(NULL);         // Obtém o tempo atual
  struct tm tm = *localtime(&t); // Converte o tempo em uma estrutura tm
  hora.hora = tm.tm_hour;
  hora.minuto = tm.tm_min;
  hora.segundo = tm.tm_sec;
  return hora;
}

/* Verifica se o ID já existe na lista */
int Existe_id(Lista *Ptl, int id) { 
  if (Ptl == NULL) // Verifica se a lista é válida
    return -1;
  No *atual = Ptl->inicio;
  while (atual != NULL) { // Percorre a lista até o final
    if (atual->trans.ID == id) { // Se o ID for encontrado
      return 1;
    }
    atual = atual->proximo;
  }
  return 0;
}

/* Função para pegar os dados da transação */
Transacao Get_transacao(Lista* Ptl) {
  /* Variáveis temporárias para armazenar os dados da transação */
  Transacao trans;
  float aux;
  int temp;
  char temp_str[100];
  do { // Loop para pegar o ID da transação
    temp = -1;
    Limpa_tela();
    printf("%s[Inserir transação]%s\n", amar, rset);
    printf("ID: ");
    scanf("%d", &temp);
    Limpa_buffer();
    if (temp < 0) { // Se o ID for negativo
      printf("\n%s[ID inválido!]%s\n", verm, rset);
    }
    if (Existe_id(Ptl, temp)) { // Verifica se o ID já existe na lista
      printf("\n%s[ID já existe!]%s\n", verm, rset);
    }
  } while (temp < 0 || Existe_id(Ptl, temp));
  trans.ID = temp;
  do { // Loop para pegar o tipo da transação
    temp = -1;
    Limpa_tela();
    printf("%s[Inserir transação]%s\n", amar, rset);
    printf("Tipo [%s0 - Débito%s | %s1 - Crédito%s]: ", azul, rset, amar, rset);
    scanf("%d", &temp);
    Limpa_buffer();
    if (temp != 0 && temp != 1) {
      printf("\n%s[Tipo inválido!]%s\n", verm, rset);
    }
  } while (temp != 0 && temp != 1);
  trans.tipo = temp;
  do { // Loop para pegar o valor da transação
    aux = -1;
    Limpa_tela();
    printf("%s[Inserir transação]%s\n", amar, rset);
    printf("Valor %sR$:%s ", amar, rset);
    scanf("%f", &aux);
    Limpa_buffer();
    if (aux <= 0) {
      printf("\n%s[Valor inválido!]%s\n", verm, rset);
    }
  } while (aux <= 0);
  trans.valor = aux;
  do { // Loop para pegar a descrição da transação
    Limpa_tela();
    printf("%s[Inserir transação]%s\n", amar, rset);
    printf("Descrição: ");
    scanf("%99[^\n]", temp_str);
    Limpa_buffer();
    if (strlen(temp_str) == 0) {
      printf("\n%s[Descrição inválida!]%s\n", verm, rset);
    }
  } while (strlen(temp_str) == 0);
  strcpy(trans.descricao, temp_str);
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
  printf("%sTipo:       %-20s%s\n", azul,
         info.tipo == DEBITO ? "Débito" : "Crédito", rset);
  printf("%sValor:      R$ %10.2f%s\n", azul, info.valor, rset);
  printf("%sData:       %02d/%02d/%04d%s\n", azul, info.data.dia, info.data.mes,
         info.data.ano, rset);
  printf("%sHora:       %02d:%02d:%02d%s\n", azul, info.hora.hora,
         info.hora.minuto, info.hora.segundo, rset);
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
    Remove_elem(Ptl, valor_ID); // Remove a transação antiga
    Insere_elem(Ptl, info); // Insere a transação atualizada
    printf("\n%s[Transação editada com sucesso!]%s\n", azul, rset);
  } else { // Se não encontrou a transação
    printf("\n%s[Transação não encontrada!]%s\n", verm, rset);
  }
  return Ptl;
}

/* Exibe transações de um tipo específico */
void Filtra_transacoes(Lista *Ptl, int tipo) {
  printf("\n%s[Filtrando transações por tipo]%s\n", amar, rset);
  No *atual = Ptl->inicio;
  while (atual != NULL) { // Percorre a lista
    if (atual->trans.tipo == tipo) { // Se o tipo da transação é igual ao tipo especificado
      Exibe_transacao(atual->trans);
    }
    atual = atual->proximo;
  }
}

/* Exibe transações dentro de um intervalo de datas */
void Exibe_transacoes_por_data(Lista *Ptl, Data inicio, Data fim) {
  printf("\n%s[Filtrando transações por intervalo de datas]%s\n", amar, rset);
  No *atual = Ptl->inicio;
  while (atual != NULL) {
    if (Compara_datas(atual->trans.data, inicio) >= 0 &&
        Compara_datas(atual->trans.data, fim) <= 0) {
      Exibe_transacao(atual->trans);
    }
    atual = atual->proximo;
  }
}

/* Calcula o saldo total */
float Calcula_saldo(Lista *Ptl) {
  float saldo = 0.0;
  No *atual = Ptl->inicio;
  while (atual != NULL) {  // Percorre a lista até o final
    if (atual->trans.tipo == DEBITO) // Se o tipo for débito
      saldo -= atual->trans.valor;
    else // Se o tipo for crédito
      saldo += atual->trans.valor;
    atual = atual->proximo;
  }
  return saldo;
}

/* Ordena transações por data */
void Ordena_transacoes_por_data(Lista *Ptl) {
  if (Ptl == NULL || Ptl->inicio == NULL) // Verifica se a lista está vazia ou não
    return;
  No *atual = Ptl->inicio;
  No *proximo = NULL;
  Transacao temp;
  int trocou; // Variável para verificar se houve troca
  do {
    trocou = 0;
    atual = Ptl->inicio;
    while (atual->proximo != proximo) { // Percorre a lista até o último elemento
      if (Compara_datas(atual->trans.data, atual->proximo->trans.data) > 0) { // Verifica se a data do atual é maior que a do próximo
        temp = atual->trans;
        atual->trans = atual->proximo->trans;
        atual->proximo->trans = temp;
        trocou = 1;
      }
      atual = atual->proximo;     
    }
  } while (trocou); // Repete o processo até não haver mais trocas
}

/* Função para exibir o menu e pegar a escolha do usuário */
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
  printf("%s[11]%s Ordenar por ID\n", cian, rset);
  printf("%s[12]%s Mesclar transações\n", cian, rset);
  Barra_div("", "\n");
  printf("%s[0]%s Sair\n", cian, rset);
  Barra_div("", "\n");
  printf("%sOpcão: %s", azul, rset);
  scanf("%d", &opcao);
  Limpa_buffer();
  return opcao;
}