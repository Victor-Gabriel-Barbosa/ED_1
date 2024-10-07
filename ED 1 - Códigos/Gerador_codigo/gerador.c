#include <stdio.h>
#include <stdlib.h>

int main() {
    // Abrir o arquivo para escrever o código-fonte gerado
    FILE *file = fopen("codigo_gerado.c", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    // Escrever o código-fonte gerado no arquivo
    fprintf(file,
        "#include <stdio.h>\n\n"
        "int main() {\n"
        "    printf(\"Hello, World!\\n\");\n"
        "    return 0;\n"
        "}\n"
    );

    fclose(file);

    // Compilar o código gerado (assumindo que o compilador seja gcc)
    system("gcc codigo_gerado.c -o codigo_gerado");

    // Executar o código compilado
    system(".\\codigo_gerado");

    return 0;
}
