typedef struct Comando {
    int mensagem;
    struct Comando* proximo;
} Comando;

typedef struct {
    Comando* primeiro;
    Comando* ultimo;
} FilaComunicacaoEspacial;

void inicializaFila(FilaComunicacaoEspacial* fila);
void insereComando(FilaComunicacaoEspacial* fila, int mensagem);
int removeComando(FilaComunicacaoEspacial* fila);
void imprimeFilaComunicacao(FilaComunicacaoEspacial* fila);