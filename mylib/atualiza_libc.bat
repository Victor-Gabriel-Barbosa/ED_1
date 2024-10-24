@echo off

REM Mover para o diretório de inclusão
cd "C:\Users\usuario\Desktop\Programas\ED_1\mylib\include"

REM Copiar os arquivos de cabeçalho para o MinGW
copy cplus.h C:\MinGW\include\
copy typeslib.h C:\MinGW\include\
copy colors.h C:\MinGW\include\
copy stringlib.h C:\MinGW\include\
copy utils.h C:\MinGW\include\
copy list.h C:\MinGW\include\
copy queue.h C:\MinGW\include\
copy stack.h C:\MinGW\include\
copy map.h C:\MinGW\include\

REM Mover para o diretório de src
cd "C:\Users\usuario\Desktop\Programas\ED_1\mylib\src"

REM Compilar os arquivos .c
gcc -c *.c -I../include

REM Criar a biblioteca estática
ar rcs libc_plus.a *.o

REM Copiar a biblioteca para o MinGW
copy libc_plus.a C:\MinGW\lib\

echo Biblioteca atualizada com sucesso!