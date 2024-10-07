#include "lista.h"
#include <stdio.h>

int main(void) {
  Lista *trans1 = Cria_lista();
  Lista *trans2 = Cria_lista();
  Lista *trans3 = Cria_lista();
  trans2 = Insere_elem(trans2, (Transacao){DEBITO, 1066, 100.0, Get_data(), Get_hora(), "Pagamento"});
  Transacao info, info2;
  int loop = 1;
  int opcao, aux;
  float temp;
  char nome[100];
  while (loop) { // Loop principal do programa
    if ((opcao = Escolha_menu()) == 0) { // Sair
      if (Sim_ou_nao("sair")) { // Se o usuário quiser sair
        printf("\n%s[Saindo...]%s\n", azul, rset);
        loop = 0;
      } else { // Se o usuário não quiser sair
        printf("\n%s[Voltando ao menu...]%s\n", azul, rset);
      }
    } else if (opcao == 1) { // Inserir transação
      trans1 = Insere_elem(trans1, Get_transacao(trans1));
    } else if (opcao == 2) { // Excluir transação
      if (!E_vazia(trans1)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Excluir transação]%s\n", amar, rset);
        Barra_div("", "\n");
        printf("ID: ");
        scanf("%d", &aux);
        Limpa_buffer();
        trans1 = Remove_elem(trans1, aux);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }
    } else if (opcao == 3) { // Consultar transação
      if (!E_vazia(trans1)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Consultar transação]%s\n", amar, rset);
        Barra_div("", "\n");
        printf("ID: ");
        scanf("%d", &aux);
        Limpa_buffer();
        if (Consulta_nodo(trans1, aux, &info)) { // Verifica se a consulta foi bem-sucedida
          Exibe_transacao(info);
        } else { // Se a consulta não foi bem-sucedida
          printf("\n[Transação não encontrada!]\n");
        }
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }
    } else if (opcao == 4) { // Exibir transações
      if (!E_vazia(trans1)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Exibe_lista(trans1);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }
    } else if (opcao == 5) { // Salvar transações
      if (!E_vazia(trans1)) { //
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Baixar lista em arquivo]%s\n", amar, rset);
        Barra_div("", "\n");
        printf("Nome do arquivo: ");
        scanf("%99[^\n]", nome);
        Limpa_buffer();
        Grava_lista(trans1, nome);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }
    } else if (opcao == 6) { // Editar transação
      if (!E_vazia(trans1)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Editar transação]%s\n", amar, rset);
        Barra_div("", "\n");
        printf("ID: ");
        scanf("%d", &aux);
        Limpa_buffer();
        trans1 = Edita_transacao(trans1, aux);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }
    } else if (opcao == 7) { // Filtrar transações
      if (!E_vazia(trans1)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Filtrar transações]%s\n", amar, rset);
        Barra_div("", "\n");
        printf("Tipo (%s0 - Débito%s, %s1 - Crédito%s): ", azul, rset, amar, rset);
        scanf("%d", &aux);
        Limpa_buffer();
        Filtra_transacoes(trans1, aux);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }   
    } else if (opcao == 8) { // Exibir transações por data
      if (!E_vazia(trans1)) { // Verifica se a lista não está vazia
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
        Exibe_transacoes_por_data(trans1, info.data, info2.data);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }     
    } else if (opcao == 9) { // Calcular saldo
      if (!E_vazia(trans1)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Calcular saldo]%s\n", amar, rset);
        Barra_div("", "\n");
        temp = Calcula_saldo(trans1);
        printf("Saldo total: %sR$%.2f%s\n", amar, temp, rset);    
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }    
    } else if (opcao == 10) { // Ordenar transações por data
      if (!E_vazia(trans1)) { // Verifica se a lista não está vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Ordenar transações por data]%s\n", amar, rset);
        Barra_div("", "\n");
        Ordena_transacoes_por_data(trans1);
        Exibe_lista(trans1);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }
    } else if (opcao == 11) { // Ordenar por ID
      if (!E_vazia(trans1)) { // Verifica se a lista não é vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Ordenar por ID]%s\n", amar, rset);
        Barra_div("", "\n");
        trans1 = Ordena_lista(trans1);
        Exibe_lista(trans1);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }  
    } else if (opcao == 12) { // Mesclar transações
      if (!E_vazia(trans1)) { // Verifica se a lista não é vazia
        Limpa_tela();
        Barra_div("", "");
        printf("\n%s[Mesclar transações]%s\n", amar, rset);
        Barra_div("", "\n");
        if (!E_ordenada(trans1)) { // Verifica se a lista não está ordenada
          Ordena_lista(trans1);
        }
        if (!E_ordenada(trans2)) { // Verifica se a lista não está ordenada
          Ordena_lista(trans2);
        }
        trans3 = Mescla_listas(trans1, trans2);
        Exibe_lista(trans3);
      } else { // Se a lista está vazia
        printf("\n%s[Lista de transações vazia!]%s\n", verm, rset);
      }            
    } else { // Opção inválida
      printf("\n%s[Opção inválida!]%s\n", verm, rset);
    }
  }
  Libera_lista(trans1);
  return 0;
}