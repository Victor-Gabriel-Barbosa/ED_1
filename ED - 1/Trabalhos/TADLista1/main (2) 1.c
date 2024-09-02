#include "lista.h"
#include <stdio.h>

int main(void) {
  Lista *minhas_transacoes = Cria_lista();
  Transacao info, info2;
  int loop = 1;
  int opcao, aux;
  float temp;
  char nome[100];
  while (loop) { // Loop principal do programa
    if ((opcao = Escolha_menu()) == 1) { // Inserir transação
      if (!E_cheia(minhas_transacoes)) { // Verifica se a lista não está cheia
        Limpa_tela();
        minhas_transacoes = Insere_elem(minhas_transacoes, Get_transacao());
      } else { // Se a lista está cheia
        printf("\n%s[Lista de transações cheia!]%s\n", verm, rset);
      }
    } else if (opcao == 2) { // Excluir transação
      if (!E_vazia(minhas_transacoes)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Excluir transação]%s\n", amar, rset);
        Barra_div("", "\n");
        printf("ID: ");
        scanf("%d", &aux);
        Limpa_buffer();
        minhas_transacoes = Remove_elem(minhas_transacoes, aux);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }
    } else if (opcao == 3) { // Consultar transação
      if (!E_vazia(minhas_transacoes)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Consultar transação]%s\n", amar, rset);
        Barra_div("", "\n");
        printf("ID: ");
        scanf("%d", &aux);
        Limpa_buffer();
        if (Consulta_nodo(minhas_transacoes, aux, &info)) { // Verifica se a consulta foi bem-sucedida
          Exibe_transacao(info);
        } else { // Se a consulta não foi bem-sucedida
          printf("\n[Transação não encontrada!]\n");
        }
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }
    } else if (opcao == 4) { // Exibir transações
      if (!E_vazia(minhas_transacoes)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Exibe_lista(minhas_transacoes);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }
    } else if (opcao == 5) { // Salvar transações
      if (!E_vazia(minhas_transacoes)) {
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Baixar lista em arquivo]%s\n", amar, rset);
        Barra_div("", "\n");
        printf("Nome do arquivo: ");
        scanf("%99[^\n]", nome);
        Limpa_buffer();
        Grava_lista(minhas_transacoes, nome);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }
    } else if (opcao == 6) { // Editar transação
      if (!E_vazia(minhas_transacoes)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Editar transação]%s\n", amar, rset);
        Barra_div("", "\n");
        printf("ID: ");
        scanf("%d", &aux);
        Limpa_buffer();
        minhas_transacoes = Edita_transacao(minhas_transacoes, aux);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }
    } else if (opcao == 7) { // Filtrar transações
      if (!E_vazia(minhas_transacoes)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Filtrar transações]%s\n", amar, rset);
        Barra_div("", "\n");
        printf("Tipo (%s0 - Débito%s, %s1 - Crédito%s): ", azul, rset, amar, rset);
        scanf("%d", &aux);
        Limpa_buffer();
        Filtra_transacoes(minhas_transacoes, aux);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }   
    } else if (opcao == 8) { // Exibir transações por data
      if (!E_vazia(minhas_transacoes)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        Barra_div("", "");
        printf("\n%s[Filtrar transações por intervalo de datas]%s\n", amar, rset);
        Barra_div("", "");
        Barra_div("", "\n");
        printf("Data inicial (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &info.data.dia, &info.data.mes, &info.data.ano);
        Limpa_buffer();
        printf("Data final (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &info2.data.dia, &info2.data.mes, &info2.data.ano);
        Limpa_buffer();
        Exibe_transacoes_por_data(minhas_transacoes, info.data, info2.data);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }     
    } else if (opcao == 9) { // Calcular saldo
      if (!E_vazia(minhas_transacoes)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Calcular saldo]%s\n", amar, rset);
        Barra_div("", "\n");
        temp = Calcula_saldo(minhas_transacoes);
        printf("Saldo total: %sR$%.2f%s\n", amar, temp, rset);    
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }    
    } else if (opcao == 10) { // Ordenar transações por data
      if (!E_vazia(minhas_transacoes)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Ordenar transações por data]%s\n", amar, rset);
        Barra_div("", "\n");
        Ordena_transacoes_por_data(minhas_transacoes);
        Exibe_lista();
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }
    } else if (opcao == 0) { // Sair
      if (Sim_ou_nao("sair")) {
        printf("\n%s[Saindo...]%s\n", azul, rset);
        loop = 0;
      } else { // Se o usuário não quiser sair
        printf("\n%s[Voltando ao menu...]%s\n", azul, rset);
      }
    } else { // Opção inválida
      printf("\n%s[Opção inválida!]%s\n", verm, rset);
    }
  }
  Libera_lista(minhas_transacoes);
  return 0;
}