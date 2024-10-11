#include <stdio.h>
#include <stringlib.h>
#include <list.h>
#include <utils.h>

#define SIZE_ARRAY(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef struct Pessoas {
  char nome[50];
  int ID;
  int num;
} Pessoa;

int main() {
  String nome;
  Pessoa pessoa;

  String nomes[] = {
    stringInit("Ana"), stringInit("Barry"), 
    stringInit("Cecilia"), stringInit("David"),
    stringInit("Eva"), stringInit("Francisco")
  };
  Pessoa pessoas[] = {
    {"Alice", 1, 123456789},
    {"Bob", 2, 987654321},
    {"Charlie", 3,  555555555},
    {"Marie", 4, 145987411},
    {"Nancy", 5, 666666666},
    {"Mario", 6, 145888888}
  };
  
  List listaNomes = listNew(sizeof(String));
  List listaPessoas = listNew(sizeof(Pessoa));

  foreach(nome, nomes) listAddEnd(listaNomes, &nome);
  foreach(pessoa, pessoas) listAddEnd(listaPessoas, &pessoa);

  listRemove(listaNomes, 0);
  listRemove(listaPessoas, 1);

  int index = listIndex(listaNomes, &nomes[2]);
  printf("\nIndex = %d\n", index);

  stringPrint(*(String*)listGet(listaNomes, index));
  printf("\n");
  listPrint(listaNomes);
  printf("\n");
  listPrint(listaPessoas);

  listDestroy(listaNomes);
  listDestroy(listaPessoas);
  printf("\nFIM\n");
  return 0;
}