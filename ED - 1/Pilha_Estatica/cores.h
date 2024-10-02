#ifndef CORES_H
#define CORES_H

/* Efeitos de texto */
#define C_RESET "\033[0m"      // Reseta cores e efeitos
#define C_NEGRITO "\033[1m"    // Negrito
#define C_SUBLINHADO "\033[4m" // Sublinhado
#define C_PISCANTE "\033[5m"   // Piscante
#define C_INVERTE "\033[7m"    // Inverte as cores

/* Cores de texto */
#define C_AZUL "\033[38;5;39m"      // Azul
#define C_VERDE "\033[38;5;46m"     // Verde água
#define C_CIANO "\033[38;5;51m"     // Ciano
#define C_VERMELHO "\033[38;5;196m" // Vermelho
#define C_MAGENTA "\033[38;5;201m"  // Magenta
#define C_AMARELO "\033[38;5;220m"  // Amarelo
#define C_ROSA "\033[38;5;206m"     // Rosa 
#define C_LARANJA "\033[38;5;208m"  // Laranja
#define C_ROXO "\033[38;5;93m"      // Roxo
#define C_MARROM "\033[38;5;94m"    // Marrom
#define C_CINZA "\033[38;5;245m"    // Cinza claro
#define C_PRETO "\033[38;5;16m"     // Preto
#define C_BRANCO "\033[38;5;231m"   // Branco
 
/* Cores de fundo */
#define C_FND_AZUL "\033[48;5;39m"      // Fundo azul
#define C_FND_VERDE "\033[48;5;46m"     // Fundo verde água
#define C_FND_CIANO "\033[48;5;51m"     // Fundo ciano
#define C_FND_VERMELHO "\033[48;5;196m" // Fundo vermelho
#define C_FND_MAGENTA "\033[48;5;201m"  // Fundo magenta
#define C_FND_AMARELO "\033[48;5;220m"  // Fundo amarelo
#define C_FND_ROSA "\033[48;5;206m"     // Fundo rosa
#define C_FND_LARANJA "\033[48;5;208m"  // Fundo laranja
#define C_FND_ROXO "\033[48;5;93m"      // Fundo roxo
#define C_FND_MARROM "\033[48;5;94m"    // Fundo marrom
#define C_FND_CINZA "\033[48;5;245m"    // Fundo cinza claro
#define C_FND_PRETO "\033[48;5;16m"     // Fundo preto
#define C_FND_BRANCO "\033[48;5;231m"   // Fundo branco

/* Formatação de texto */
#define C_FMT(cor, texto) cor texto C_RESET                      // Formatação padrão
#define C_FMT_ERRO(texto) C_NEGRITO C_VERMELHO texto C_RESET     // Formatação p/ mensagens de erro 
#define C_FMT_SUCESSO(texto) C_NEGRITO C_VERDE texto C_RESET     // Formatação p/ mensagens de sucesso 
#define C_FMT_TITULO(texto) C_NEGRITO C_SUBLINHADO texto C_RESET // Formatação p/ títulos
#define C_FMT_IF(cor_verdade, cor_falso, condicao, texto) \
  (condicao) ? C_FMT(cor_verdade, texto) : C_FMT(cor_falso, texto) 

#endif