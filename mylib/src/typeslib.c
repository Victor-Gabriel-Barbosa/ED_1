#include <typeslib.h>

/**
 * @struct DataTypeInfo
 * Estrutura que contém informações sobre os tipos de dados.
 * @var DataTypeInfo::type
 * Tipo de dado da estrutura.
 * @var DataTypeInfo::size
 * Tamanho do tipo de dado em bytes.
 */
typedef struct {
  DataType type; /**< Tipo de dado */
  size_t size;   /**< Tamanho do tipo de dado em bytes */
} DataTypeInfo;

/**
 * @enum DataType
 * Enumeração de tipos de dados suportados.
 */
DataTypeInfo dataTypeInfos[Count] = {
  {Int, sizeof(int)},        
  {Float, sizeof(float)},    
  {Double, sizeof(double)},   
  {Char, sizeof(char)},      
  {Bool, sizeof(bool)},     
  {String, sizeof(char *)},  
  {Auto, sizeof(char *)}
};

/**
 * @brief Ajusta o tamanho do tipo 'Auto'.
 *
 * Permite que o tamanho do tipo 'Auto' seja ajustado dinamicamente.
 *
 * @param newSize O novo tamanho a ser definido para o tipo 'Auto'.
 * @return Retorna 0 em caso de sucesso e -1 se ocorrer erro.
 */
DataType autoSize(size_t newSize) {
  dataTypeInfos[Auto].size = newSize;
  return Auto;
}

/**
 * @brief Retorna o tamanho de um tipo de dado.
 *
 * Esta função retorna o tamanho em bytes do tipo de dado especificado.
 * Se o tipo for inválido, ela retorna 0 e exibe uma mensagem de erro.
 *
 * @param type O tipo de dado cujo tamanho será retornado.
 * @return O tamanho do tipo de dado em bytes, ou 0 se o tipo for inválido.
 */
size_t typeGetSize(DataType type) {
  if (type >= Count) return 0;
  return dataTypeInfos[type].size;
}