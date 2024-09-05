typedef struct no Lista;
typedef struct Ingresso {
  int ID, assento;
  char filme[50];
} Ingresso;

Lista* Cria_lista(void);

Lista* Libera_lista(Lista* Ptl);

int E_vazia(Lista* Ptl);

int E_cheia(Lista* Ptl);

Lista* Insere_elem(Lista* Ptl, Ingresso elem);

Lista* Remove_elem(Lista* Ptl, Ingresso elem);

int Tamanho_lista(Lista* Ptl);

int Consulta_nodo(Lista* Ptl, int pos, Ingresso *elem);

Lista* Vender_ingresso(Lista* Ptl, Lista* Ptc, int pos);

Lista* Cancelar_venda(Lista* Ptl, Lista* Ptc, int pos);

void Listar_ingressos(Lista* Ptl);

void Listar_ingressos_vendidos(Lista* Ptc);

int Escolha_menu();

void Limpa_buffer();

void Limpa_tela();