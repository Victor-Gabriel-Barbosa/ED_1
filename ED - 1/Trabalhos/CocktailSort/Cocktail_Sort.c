#include <stdio.h>
#include <stdbool.h>

// Função para ordenar a lista usando o Cocktail Sort
void ordenarCocktailSort(int vetor[], int tamanho) {
  bool trocou;
  int inicio = 0;
  int fim = tamanho - 1;
  do { // Loop principal do algoritmo
    trocou = false;
    for (int i = inicio; i < fim; i++) { // Percorrer da esquerda para a direita
      if (vetor[i] > vetor[i + 1]) { // Trocar elementos se estiverem na ordem errada
        int aux = vetor[i];
        vetor[i] = vetor[i + 1];
        vetor[i + 1] = aux;
        trocou = true;
      }
    }
    if (!trocou) break; // Se nenhuma troca foi feita, a lista já está ordenada
    trocou = false;
    fim--;
    for (int i = fim - 1; i >= inicio; i--) { // Percorrer da direita para a esquerda
      if (vetor[i] > vetor[i + 1]) { // Trocar elementos se estiverem na ordem errada
        int aux = vetor[i];
        vetor[i] = vetor[i + 1];
        vetor[i + 1] = aux;
        trocou = true;
      }
    }
    inicio++;
  } while (trocou);
}

// Função principal
int main() {
    int vetor[] = {5, 3, 8, 4, 2, 1, 9, 6, 7};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    printf("[🫢 ]Vetor desordenado: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }

    ordenarCocktailSort(vetor, tamanho);

    printf("\nVetor ordenado: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }

    return 0;
}