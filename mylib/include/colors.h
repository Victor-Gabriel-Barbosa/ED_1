/**
 * @file colors.h
 * @brief Biblioteca para cores e efeitos de formatação de texto no terminal usando ANSI escape codes.
 * 
 * Esta biblioteca define macros para aplicar cores e efeitos de texto, como negrito, sublinhado, 
 * e cores personalizadas para o texto e o fundo. Ela facilita a aplicação de estilos no terminal de forma simples.
 * 
 * Definições disponíveis:
 * 
 * - **Efeitos de texto**:
 *   - `C_RESET`: Reseta as cores e efeitos aplicados.
 *   - `C_BOLD`: Aplica negrito ao texto.
 *   - `C_UNDERLINE`: Aplica sublinhado ao texto.
 *   - `C_BLINK`: Aplica efeito piscante ao texto.
 *   - `C_INVERT`: Inverte as cores do texto e do fundo.
 * 
 * - **Cores de texto**:
 *   - `C_BLUE`: Define a cor do texto como azul.
 *   - `C_CYAN`: Define a cor do texto como ciano.
 *   - `C_GREEN`: Define a cor do texto como verde água.
 *   - `C_RED`: Define a cor do texto como vermelho.
 *   - `C_MAGENTA`: Define a cor do texto como magenta.
 *   - `C_YELLOW`: Define a cor do texto como amarelo.
 *   - `C_PINK`: Define a cor do texto como rosa.
 *   - `C_ORANGE`: Define a cor do texto como laranja.
 *   - `C_PURPLE`: Define a cor do texto como roxo.
 *   - `C_BROWN`: Define a cor do texto como marrom.
 *   - `C_GRAY`: Define a cor do texto como cinza claro.
 *   - `C_BLACK`: Define a cor do texto como preto.
 *   - `C_WHITE`: Define a cor do texto como branco.
 * 
 * - **Cores de fundo**:
 *   - `C_BG_BLUE`: Define o fundo como azul.
 *   - `C_BG_CYAN`: Define o fundo como ciano.
 *   - `C_BG_GREEN`: Define o fundo como verde água.
 *   - `C_BG_RED`: Define o fundo como vermelho.
 *   - `C_BG_MAGENTA`: Define o fundo como magenta.
 *   - `C_BG_YELLOW`: Define o fundo como amarelo.
 *   - `C_BG_PINK`: Define o fundo como rosa.
 *   - `C_BG_ORANGE`: Define o fundo como laranja.
 *   - `C_BG_PURPLE`: Define o fundo como roxo.
 *   - `C_BG_BROWN`: Define o fundo como marrom.
 *   - `C_BG_GRAY`: Define o fundo como cinza claro.
 *   - `C_BG_BLACK`: Define o fundo como preto.
 *   - `C_BG_WHITE`: Define o fundo como branco.
 * 
 * - **Formatação de texto**:
 *   - `C_FMT(color, text)`: Aplica a formatação de uma cor especificada ao texto, com reset no final.
 *   - `C_FMT_ERROR(text)`: Formata o texto para erros, com negrito e vermelho.
 *   - `C_FMT_SUCCESS(text)`: Formata o texto para sucesso, com negrito e verde.
 *   - `C_FMT_TITLE(text)`: Formata o texto como título, com negrito e sublinhado.
 *   - `C_FMT_IF(color_true, color_false, condition, text)`: Aplica uma formatação condicional, escolhendo entre duas cores com base na condição.
 * 
 * @note Esta biblioteca usa códigos ANSI, que são suportados na maioria dos terminais Unix e em alguns terminais de sistemas Windows (como o Windows Terminal).
 * 
 * @date 12/10/2024
 * @version 1.0
 */
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
