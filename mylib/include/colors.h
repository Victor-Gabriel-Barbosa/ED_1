#ifndef COLORS_H
#define COLORS_H

/* Efeitos de texto */
#define C_RESET "\033[0m"     // Reseta cores e efeitos
#define C_BOLD "\033[1m"      // Negrito
#define C_UNDERLINE "\033[4m" // Sublinhado
#define C_BLINK "\033[5m"     // Piscante
#define C_INVERT "\033[7m"    // Inverte as cores

/* Cores de texto */
#define C_BLUE "\033[38;5;39m"     // Azul
#define C_CYAN "\033[38;5;51m"     // Ciano
#define C_GREEN "\033[38;5;46m"    // Verde água
#define C_RED "\033[38;5;196m"     // Vermelho
#define C_MAGENTA "\033[38;5;201m" // Magenta
#define C_YELLOW "\033[38;5;220m"  // Amarelo
#define C_PINK "\033[38;5;206m"    // Rosa 
#define C_ORANGE "\033[38;5;208m"  // Laranja
#define C_PURPLE "\033[38;5;93m"   // Roxo
#define C_BROWN "\033[38;5;94m"    // Marrom
#define C_GRAY "\033[38;5;245m"    // Cinza claro
#define C_BLACK "\033[38;5;16m"    // Preto
#define C_WHITE "\033[38;5;231m"   // Branco
 
/* Cores de fundo */
#define C_BG_BLUE "\033[48;5;39m"     // Fundo azul
#define C_BG_CYAN "\033[48;5;51m"     // Fundo ciano
#define C_BG_GREEN "\033[48;5;46m"    // Fundo verde água
#define C_BG_RED "\033[48;5;196m"     // Fundo vermelho
#define C_BG_MAGENTA "\033[48;5;201m" // Fundo magenta
#define C_BG_YELLOW "\033[48;5;220m"  // Fundo amarelo
#define C_BG_PINK "\033[48;5;206m"    // Fundo rosa
#define C_BG_ORANGE "\033[48;5;208m"  // Fundo laranja
#define C_BG_PURPLE "\033[48;5;93m"   // Fundo roxo
#define C_BG_BROWN "\033[48;5;94m"    // Fundo marrom
#define C_BG_GRAY "\033[48;5;245m"    // Fundo cinza claro
#define C_BG_BLACK "\033[48;5;16m"    // Fundo preto
#define C_BG_WHITE "\033[48;5;231m"   // Fundo branco

/* Formatação de texto */
#define C_FMT(color, text) color text C_RESET             // Formatação padrão
#define C_FMT_ERROR(text) C_BOLD C_RED text C_RESET       // Formatação p/ mensagens de erro 
#define C_FMT_SUCCESS(text) C_BOLD C_GREEN text C_RESET   // Formatação p/ mensagens de sucesso 
#define C_FMT_TITLE(text) C_BOLD C_UNDERLINE text C_RESET // Formatação p/ títulos
#define C_FMT_IF(color_true, color_false, condition, text) \
  (condition) ? C_FMT(color_true, text) : C_FMT(color_false, text)

#endif
