#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include "utils.h"

// Estrutura para representar uma lista
typedef struct list List;

/** 
 * Cria uma nova lista vazia. 
 * 
 * @return Um ponteiro para uma nova lista.
 */
List *newList();

/** 
 * Libera a memória alocada para a lista.
 * 
 * @param list Ponteiro para a lista a ser liberada.
 * @return Um ponteiro nulo após a liberação da lista.
 */
List *destroyList(List *list);

/** 
 * Obtém o tamanho da lista.
 * 
 * @param Ptd Ponteiro para a lista.
 * @return O tamanho da lista.
 */
size_t sizeList(List *Ptd);

/** 
 * Insere um novo elemento no início da lista.
 * 
 * @param Ptd Ponteiro para a lista.
 * @param info Os dados a serem inseridos na lista.
 * @return Um ponteiro para a lista atualizada.
 */
List *insertBeginList(List *Ptd, const int info);

/** 
 * Insere um novo elemento no fim da lista.
 * 
 * @param Ptd Ponteiro para a lista.
 * @param info Os dados a serem inseridos na lista.
 * @return Um ponteiro para a lista atualizada.
 */
List *insertEndList(List *Ptd, const int info);

/** 
 * Remove um elemento da lista.
 * 
 * @param Ptd Ponteiro para a lista.
 * @param posi A posição do elemento a ser removido.
 * @return Um ponteiro para a lista atualizada.
 */
List *removeList(List *Ptd, const int pos);

/** 
 * Busca por um elemento da lista.
 * 
 * @param Ptd Ponteiro para a lista.
 * @param posi A posição do elemento a ser buscado.
 * @param info Ponteiro para armazenar os dados encontrados.
 * @return 1 se o elemento for encontrado, 0 caso contrário.
 */
int searchList(List *Ptd, const int pos, int *info); 

/** 
 * Imprime a lista.
 * 
 * @param Ptd Ponteiro para a lista.
 * @return 1 se a impressão for bem-sucedida, 0 caso contrário.
 */
int showList(List *Ptd); 
                                             
#endif
