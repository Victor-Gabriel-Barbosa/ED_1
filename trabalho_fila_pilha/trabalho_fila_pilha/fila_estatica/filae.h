#define MAX 1000

typedef struct {
    int mensagens[MAX];
    int inicio, fim;
} FilaComandosTerraEstacao;

void inicializaFila(FilaComandosTerraEstacao* fila);
void insereMensagem(FilaComandosTerraEstacao* fila, int mensagem);
int removeMensagem(FilaComandosTerraEstacao* fila);
void imprimeFilaMensagens(FilaComandosTerraEstacao* fila);