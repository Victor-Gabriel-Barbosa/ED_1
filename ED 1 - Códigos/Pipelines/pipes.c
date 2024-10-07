#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];  // Array para guardar os descritores de arquivo do pipe
    pipe(fd);   // Cria o pipe: fd[0] para leitura, fd[1] para escrita

    pid_t pid = fork();  // Cria um processo filho

    if (pid == 0) {  // Código do processo filho
        close(fd[1]);  // Fecha a extremidade de escrita no filho
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));  // Lê do pipe
        printf("Filho leu: %s\n", buffer);
        close(fd[0]);
    } else {  // Código do processo pai
        close(fd[0]);  // Fecha a extremidade de leitura no pai
        const char *msg = "Olá do processo pai!";
        write(fd[1], msg, strlen(msg) + 1);  // Escreve no pipe
        close(fd[1]);
    }

    return 0;
}
