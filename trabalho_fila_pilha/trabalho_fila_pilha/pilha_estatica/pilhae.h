#define MAX 1000

typedef struct {
    int componentes[MAX];
    int topo;
} PilhaEstoqueFabrica;

void inicializaPilha(PilhaEstoqueFabrica* pilha);
void insereComponenteEstoque(PilhaEstoqueFabrica* pilha, int numero_serie);
int removeComponenteEstoque(PilhaEstoqueFabrica* pilha);
void imprimeEstoqueFabrica(PilhaEstoqueFabrica* pilha);