#include <stdio.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>

int main() {
    SQLHENV hEnv;
    SQLHDBC hConn;
    SQLRETURN ret; // Para armazenar o retorno das funções

    // Aloca o ambiente ODBC
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    // Aloca a conexão
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hConn);

    // Conecta ao banco de dados (substitua os parâmetros com os apropriados)
    ret = SQLDriverConnect(hConn, NULL, 
                           "DRIVER={SQL Server};SERVER=localhost;DATABASE=mydb;UID=user;PWD=password;", 
                           SQL_NTS, 
                           NULL, 0, NULL, SQL_DRIVER_COMPLETE);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        printf("Conexão bem-sucedida!\n");
        
        // Aqui você pode executar suas consultas SQL
        
    } else {
        printf("Erro ao conectar ao banco de dados.\n");
    }

    // Finaliza a conexão e libera os recursos
    SQLDisconnect(hConn);
    SQLFreeHandle(SQL_HANDLE_DBC, hConn);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}
