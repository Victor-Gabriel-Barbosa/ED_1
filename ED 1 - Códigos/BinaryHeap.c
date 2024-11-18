#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
  int dados[MAX];
  int topo;
} Pilha;

typedef struct {
  int dados[MAX];
  int cauda;
  int cabeca;
} Fila;

typedef struct {
  int dados[MAX];
  int tam;
} FilaPrioridade;

void pilhaCria(Pilha* pilha) { 
  pilha->topo = -1; 
}

void pilhaAdiciona(Pilha* pilha, int x) { 
  pilha->dados[++pilha->topo] = x; 
}

int pilhaRemove(Pilha* pilha) { 
  return pilha->dados[pilha->topo--]; 
}

void filaCria(Fila* fila) { 
  fila->cauda = fila->cabeca = -1; 
}

void filaAdiciona(Fila* fila, int x) {
  if (fila->cabeca == -1) fila->cauda = fila->cabeca = 0;
  else fila->cabeca++;
  fila->dados[fila->cabeca] = x;
}

int filaRemove(Fila *fila) {
  int x = fila->dados[fila->cauda];
  if (fila->cauda == fila->cabeca) fila->cauda = fila->cabeca = -1;
  else fila->cauda++;
  return x;
}
void filaPrioridadeCria(FilaPrioridade *fP) { 
  fP->tam = 0; 
}

void filaPrioridadeAdiciona(FilaPrioridade* fP, int x) {
  int i = fP->tam++;
  while (i > 0 && fP->dados[(i - 1) / 2] < x) {
    fP->dados[i] = fP->dados[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  fP->dados[i] = x;
}
int filaPrioridadeMaximo(FilaPrioridade* fP) {
  int maximo = fP->dados[0];
  fP->dados[0] = fP->dados[--fP->tam];
  int i = 0, j;
  while (2 * i + 1 < fP->tam) {
    j = 2 * i + 1;
    if (j + 1 < fP->tam && fP->dados[j + 1] > fP->dados[j]) j++;
    if (fP->dados[i] >= fP->dados[j]) break;
    int temp = fP->dados[i];
    fP->dados[i] = fP->dados[j];
    fP->dados[j] = temp;
    i = j;
  }
  return maximo;
}
void saida(int n, int operacoes[][2]) {
  Pilha pilha;
  Fila fila;
  FilaPrioridade filaPrioridade;
  int auxPilha = 1, auxFila = 1, auxFilaPrioridade = 1;

  pilhaCria(&pilha);
  filaCria(&fila);
  filaPrioridadeCria(&filaPrioridade);

  for (int i = 0; i < n; i++) {
    if (operacoes[i][0] == 1) {
      pilhaAdiciona(&pilha, operacoes[i][1]);
      filaAdiciona(&fila, operacoes[i][1]);
      filaPrioridadeAdiciona(&filaPrioridade, operacoes[i][1]);
    } else {
      if (auxPilha && (pilha.topo == -1 || pilhaRemove(&pilha) != operacoes[i][1])) auxPilha = 0;
      if (auxFila && (fila.cauda == -1 || filaRemove(&fila) != operacoes[i][1])) auxFila = 0;
      if (auxFilaPrioridade && (filaPrioridade.tam == 0 || filaPrioridadeMaximo(&filaPrioridade) != operacoes[i][1])) auxFilaPrioridade = 0;
    }
  }

  if (auxPilha && !auxFila && !auxFilaPrioridade) printf("stack\n");
  else if (!auxPilha && auxFila && !auxFilaPrioridade) printf("queue\n");
  else if (!auxPilha && !auxFila && auxFilaPrioridade) printf("priority queue\n");
  else if (!auxPilha && !auxFila && !auxFilaPrioridade) printf("impossible\n");
  else printf("not sure\n");
}
int main() {
  int n;
  int operacoes[MAX][2];

  while (scanf("%d", &n) != EOF) {
    for (int i = 0; i < n; i++) scanf("%d %d", &operacoes[i][0], &operacoes[i][1]);
    saida(n, operacoes);
  }

  return 0;
}