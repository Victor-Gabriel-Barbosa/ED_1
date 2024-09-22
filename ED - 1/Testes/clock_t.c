
#include <stdio.h>
#include <time.h>
typedef long clock_t;

int main() {
	int i;
     double start, finish, elapsed;
     start = (double) clock ();

     //neste exemplo, irá calcular o número de clocks necessários 
//para imprimir os números de 1 a 5000
	for(i = 0; i < 5000; i++)
		printf("\n%d", i);

     finish = (double) clock ();
     elapsed = finish - start;
     printf("\nTempo decorrido: %f", elapsed);
}