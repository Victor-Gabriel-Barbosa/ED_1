@echo off
setlocal

REM Obter o diretório onde o script está localizado
set "SCRIPT_DIR=%~dp0"

REM Definir os diretórios com base no local do script
set "INCLUDE_DIR=%SCRIPT_DIR%include"
set "SRC_DIR=%SCRIPT_DIR%src"
set "MINGW_INCLUDE=C:\MinGW\include"
set "MINGW_LIB=C:\MinGW\lib"

REM Mover para o diretório de inclusão
cd /d %INCLUDE_DIR%
if %errorlevel% neq 0 (
    echo Erro: Não foi possível acessar o diretório %INCLUDE_DIR%.
    exit /b %errorlevel%
)

REM Copiar os arquivos de cabeçalho para o MinGW
for %%f in (cplus.h typeslib.h colors.h stringlib.h utils.h list.h queue.h stack.h tree.h) do (
    copy %%f %MINGW_INCLUDE%\
    if %errorlevel% neq 0 (
        echo Erro ao copiar %%f para %MINGW_INCLUDE%.
        exit /b %errorlevel%
    )
)

REM Mover para o diretório de src
cd /d %SRC_DIR%
if %errorlevel% neq 0 (
    echo Erro: Não foi possível acessar o diretório %SRC_DIR%.
    exit /b %errorlevel%
)

REM Compilar os arquivos .c
gcc -c *.c -I%INCLUDE_DIR%
if %errorlevel% neq 0 (
    echo Erro ao compilar os arquivos .c.
    exit /b %errorlevel%
)

REM Criar a biblioteca estática
ar rcs libcplus.a *.o
if %errorlevel% neq 0 (
    echo Erro ao criar a biblioteca estática.
    exit /b %errorlevel%
)

REM Copiar a biblioteca para o MinGW
copy libcplus.a %MINGW_LIB%\
if %errorlevel% neq 0 (
    echo Erro ao copiar libcplus.a para %MINGW_LIB%.
    exit /b %errorlevel%
)

echo Biblioteca atualizada com sucesso!