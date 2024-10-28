typedef struct Componente {
    int numero_serie;
    struct Componente* proximo;
} Componente;

typedef struct {
    Componente* topo;
} PilhaEstoqueHardware;

void inicializaPilha(PilhaEstoqueHardware* pilha);
void insereComponente(PilhaEstoqueHardware* pilha, int numero_serie);
int removeComponente(PilhaEstoqueHardware* pilha);
void imprimeEstoqueHardware(PilhaEstoqueHardware* pilha);