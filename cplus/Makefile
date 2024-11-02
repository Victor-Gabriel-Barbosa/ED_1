# Variáveis
CC = gcc                               # Compilador
CFLAGS = -Iminha_biblioteca/include    # Diretório de cabeçalhos
LDFLAGS = -L./mylib/lib -lcplus        # Diretório da biblioteca e a própria biblioteca
SRC = $(wildcard *.c)                  # Busca todos os arquivos .c no diretório atual
OBJ = $(SRC:.c=.o)                      # Converte .c para .o
TARGET = meu_programa                   # Nome do executável

# Regra padrão
all: $(TARGET)

# Compilação do executável
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilação do arquivo objeto
%.o: %.c
	$(CC) -c $< $(CFLAGS)

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(TARGET)

# Regra para executar o programa
run: $(TARGET)
	./$(TARGET)