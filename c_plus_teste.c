#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <c_plus.h>

typedef struct Pessoas {
  char nome[50];
  int idade, cpf;
} Pessoa;

int main() {
  srand(time(NULL)); 
  sizeof(int);
  sizeof(float);
  clock_t inicio, fim;
  List listaLetras = listNew(Char);
  List listaNomes = listNew(String);
  List listaPessoas = listNew(autoSize(sizeof(Pessoa)));
  Pessoa pessoas[] = {
    {.idade = 22, .nome = "Pedro",.cpf = 12345678},
    {.idade = 25, .nome = "Isabella",.cpf = 87654321},
    {.idade = 18, .nome = "João",.cpf = 98765432},
    {.idade = 28, .nome = "Carlos",.cpf = 43219876},
    {.idade = 17, .nome = "Victor",.cpf = 76543219},
    {.idade = 20, .nome = "Ana",.cpf = 32198765}
  }; 
  string Nomes[] = {
    stringInit("Ana"), stringInit("Victor"),
    stringInit("Carlos"), stringInit("Maria"),
    stringInit("João"), stringInit("Lucas"),
    stringInit("Pedro"), stringInit("Isabella")
  };

  foreach(pessoa, pessoas) listAddEnd(listaPessoas, pessoa);

  printf("\nPessoas (Desordenado)\n");
  listPrint(listaPessoas);

  listSort(listaPessoas);

  printf("\nPessoas (Ordenado)\n");
  listPrint(listaPessoas);

  int qtd = 0;
  printf("\nDigite a quantidade de letras: ");
  scanf("%d", &qtd);
  cleanBuffer(); 
  for (int i = 0; i < qtd; i++) {
    char letra = rand() % 26 + 'a';
    listAddEnd(listaLetras, &letra);
  }
  
  //printf("\nLetras:\n");
  //listPrint(listaLetras);

  inicio = clock();
  listSort(listaLetras);
  fim = clock();

  printf("\nTempo gasto: %g segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
  waitCleanScreen("Aperte ENTER para continuar...");

  if (confirm("ver a lista ordenada")) {
    printf("\nLetras Ordenadas:\n");
    listPrint(listaLetras);
  }


  foreach(Nome, Nomes) listAddEnd(listaNomes, Nome);
  listAddEnd(listaNomes, &(string){input("\nDigite um nome: ")});
  printf("\nNomes:\n");
  listPrint(listaNomes);

  listSort(listaNomes);

  printf("\nNomes em ordem alfabética:\n");
  listPrint(listaNomes);

  listaLetras = listDestroy(listaLetras);
  listaNomes = listDestroy(listaNomes);

  listaLetras = listNew(Char);
  for (int i = 0; i < qtd; i++) {
    char letra = rand() % 26 + 'A';
    listAddEnd(listaLetras, &letra);
  }
  
  if (confirm("mostrar letras maiúsculas")) {
    printf("\nLetras (maiúsculas):\n");
    listPrint(listaLetras);
  }
  listaLetras = listDestroy(listaLetras);
  return 0;
}