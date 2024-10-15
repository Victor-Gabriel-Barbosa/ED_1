#include <stdio.h>
#include <c_plus.h>

#define SIZE_ARRAY(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef struct alunos {
  int ID;
  char nome[50];
  float media;
} Aluno;

int main() {
  String nomes[] = {
    stringInit("Ana"), stringInit("Barry"), 
    stringInit("Cecilia"), stringInit("David"),
    stringInit("Eva"), stringInit("Francisco")
  };

  Aluno alunos[] = {
    {1, "Ana", 8.5}, {2, "Barry", 9.2},
    {3, "Cecilia", 8.7}, {4, "David", 8.9},
    {5, "Eva", 9.0}, {6, "Francisco", 8.8}
  };

  printf(C_FMT(C_BLUE, "Azul"));
  
  List listaNomes = listNew(sizeof(int));
  List listaAlunos = listNew(sizeof(Aluno));
  Queue filaPacientes = queueNew(sizeof(String));
  Stack pilhaNomes = stackNew(sizeof(String));
  
  foreach(nome, nomes) listAddEnd(listaNomes, nome);
  foreach(aluno, alunos) listAddEnd(listaAlunos, aluno);
  foreach(nome, nomes) queueEnqueue(filaPacientes, nome); 
  foreach(nome, nomes) stackPush(pilhaNomes, nome);
  foreach(nome, nomes) stringPrint(stringAppend(*nome, stringInit(" ")));

  stackPush(pilhaNomes, &(String){stringInit("Demônio do gás Oculto")});

  printf("\n");
  listPrint(listaAlunos);

  printf("\n\n");

  String nome;
  queueDequeue(filaPacientes, &nome);

  queuePrint(filaPacientes);
  printf("\n");

  listRemove(listaNomes, 0);

  int index = listIndex(listaNomes, &nomes[1]);
  printf("\nIndex = %d\n", index);

  stringPrint(*(String*)listGet(listaNomes, index));
  printf("\n");
  listPrint(listaNomes);
  printf("\n");

  printf("\n\nSuper Teste:\n");
  printsf("Lista: %L\nFila: %Q\nPilha: %K\n", listaNomes, filaPacientes, pilhaNomes);

  listaNomes = listDestroy(listaNomes);
  filaPacientes = queueDestroy(filaPacientes);
  pilhaNomes = stackDestroy(pilhaNomes);

  queuePrint(filaPacientes);
  printf("\nFIM\n");
  return 0;
}