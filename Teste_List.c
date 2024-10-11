#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <list.h>
#include <queue.h>
#include <stack.h>
#include <utils.h>

typedef struct alunos {
  int matricula;
  char nome[50];
  float notas[3];
} Aluno;

#define SIZE_ARRAY(arr) (sizeof(arr) / sizeof((arr)[0]))

int main() {
  srand(time(NULL));

  List numeros1 = newList(sizeof(int));
  for (int i = 0; i < 100; i++) insertAtBegin(numeros1, &(int){rand() % 10});
  
  sortList(numeros1);
  printf("\nLista 1 ordenada:\n");
  for (int i = 0; i < sizeList(numeros1); i++) {
    int num;
    searchAt(numeros1, i, &num);
    printf("%d ", num);
  }

  List numeros2 = newList(sizeof(int));
  for (int i = 0; i < 100; i++) insertAtBegin(numeros2, &(int){rand() % 10});

  sortList(numeros2);
  printf("\nLista 2 ordenada:\n");
  for (int i = 0; i < sizeList(numeros2); i++) {
    int num;
    searchAt(numeros2, i, &num);
    printf("%d ", num);
  }

  List R = mergeLists(numeros1, numeros2);
  printf("\nMerge List:\n");
  for (int i = 0; i < sizeList(R); i++) {
    int num;
    searchAt(R, i, &num);
    printf("%d ", num);
  }

  Aluno alunos[] = {
    {1234, "Julio", {1, 2, 3}},
    {3871, "Mario", {7, 1, 5}},  
    {2345, "Pedro", {9, 8, 7}},
    {6789, "Ana", {4, 3, 2}}
  };
  Aluno temp;
  Aluno ext = {456, "Maria", {11, 22, 33}};
  printf("\n<>Lista:\n");
  List mylist = newList(sizeof(Aluno));
  for (int i = 0; i < SIZE_ARRAY(alunos); i++) {
    insertAtBegin(mylist, &alunos[i]);
  }
  
  int index = indexOf(mylist, &alunos[2]);
  printf("\nIndex: %d\n", index);
  searchAt(mylist, 0, &temp);
  printf("Matricula: %d, Nome: %s, Notas: %.1f, %.1f, %.1f\n", temp.matricula, temp.nome, temp.notas[0], temp.notas[1], temp.notas[2]);
  destroyList(mylist);

  printf("\n>>Queue:\n");
  Queue myqueue = newQueue(sizeof(Aluno));
  for (int i = 0; i < SIZE_ARRAY(alunos); i++) {
    enqueue(myqueue, &alunos[i]);
  }
  dequeue(myqueue, &temp);
  printf("Matricula: %d, Nome: %s, Notas: %.1f, %.1f, %.1f\n", temp.matricula, temp.nome, temp.notas[0], temp.notas[1], temp.notas[2]);
  destroyQueue(myqueue);

  printf("\n^^Stack:\n");
  Stack mystack = newStack(sizeof(Aluno));
  for (int i = 0; i < SIZE_ARRAY(alunos); i++) {
    push(mystack, &alunos[i]);
  }
  pop(mystack, &temp);
  printf("Matricula: %d, Nome: %s, Notas: %.1f, %.1f, %.1f\n", temp.matricula, temp.nome, temp.notas[0], temp.notas[1], temp.notas[2]);
  destroyStack(mystack);
  return 0;
}