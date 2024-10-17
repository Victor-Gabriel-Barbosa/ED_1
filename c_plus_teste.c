#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <cplus.h>
#include <tree.h>

typedef struct sorvetes {
  int preco;
  char nome[50];
} Sorvete;

int main() {
  srand(time(NULL));
  clock_t inicio, fim;
  int vet[] = {11, 1, 2, 22, 4, 5, 6, 7, 8};
  String nomes[] = {
    stringInit("Ana"), stringInit("Mara"),
    stringInit("Matheus"), stringInit("Marta")};
  char *pessoas[] = {
    "Ana", "Mara", "Matheus", "Marta"
  };
  Sorvete sorvets[] = {
    {.nome = "Morango", .preco = 5}, {.nome = "Chocolate", .preco = 6},
    {.nome ="Laranja", .preco = 7}, {.nome = "Maracuja", .preco =8}
  };
  Tree map = treeNew();
  List vector = listNew();
  List char_p = listNew();
  List strings = listNew();
  List sorvetes = listNew();
  List listas = listNew();
  foreach(num, vet) treeInsert(map, AUTO(*num));
  foreach (num, vet) listAddEnd(vector, AUTO(*num));
  foreach (nome_c, pessoas) listAddEnd(char_p, AUTO(*nome_c));
  foreach (nome, nomes) listAddEnd(strings, AUTO(*nome));
  foreach (sorvete, sorvets) listAddEnd(sorvetes, AUTO(sorvete));
  listAddEnd(listas, AUTO(vector));
  listAddEnd(listas, AUTO(char_p));
  listAddEnd(listas, AUTO(strings));
  listAddEnd(listas, AUTO(sorvetes));
  printf("\nÁrvore:\n");
  treePrint(map);
  printf("\n");
  listSort(vector);
  listSort(char_p);
  listPrint(vector);
  listPrint(char_p);
  listPrint(strings);
  listPrint(sorvetes);
  listPrint(listas);
  vector = listDestroy(vector);
  char_p = listDestroy(char_p);
  strings = listDestroy(strings);
  sorvetes = listDestroy(sorvetes);
}