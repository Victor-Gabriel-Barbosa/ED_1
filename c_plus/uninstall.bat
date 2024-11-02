@echo off
setlocal

REM Diretórios do MinGW
set "MINGW_INCLUDE=C:\MinGW\include"
set "MINGW_LIB=C:\MinGW\lib"

REM Arquivos de cabeçalho que serão removidos
set "HEADERS=cplus.h typeslib.h colors.h stringlib.h utils.h list.h queue.h stack.h tree.h"
set "LIBRARY=libcplus.a"

REM Remover arquivos de cabeçalho do MinGW/include
echo Removendo arquivos de cabeçalho...
for %%f in (%HEADERS%) do (
    if exist %MINGW_INCLUDE%\%%f (
        del /f %MINGW_INCLUDE%\%%f
        echo %%f removido de %MINGW_INCLUDE%.
    ) else (
        echo Aviso: %%f não encontrado em %MINGW_INCLUDE%.
    )
)

REM Remover biblioteca estática do MinGW/lib
echo.
echo Removendo biblioteca estática...
if exist %MINGW_LIB%\%LIBRARY% (
    del /f %MINGW_LIB%\%LIBRARY%
    echo %LIBRARY% removido de %MINGW_LIB%.
) else (
    echo Aviso: %LIBRARY% não encontrado em %MINGW_LIB%.
)

echo.
echo Desinstalação concluída!