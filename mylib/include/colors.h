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
 *   - `RESET`: Reseta as cores e efeitos aplicados.
 *   - `BOLD`: Aplica negrito ao texto.
 *   - `UNDERLINE`: Aplica sublinhado ao texto.
 *   - `BLINK`: Aplica efeito piscante ao texto.
 *   - `INVERT`: Inverte as cores do texto e do fundo.
 * 
 * - **Cores de texto**:
 *   - `BLUE`: Define a cor do texto como azul.
 *   - `CYAN`: Define a cor do texto como ciano.
 *   - `GREEN`: Define a cor do texto como verde água.
 *   - `RED`: Define a cor do texto como vermelho.
 *   - `MAGENTA`: Define a cor do texto como magenta.
 *   - `YELLOW`: Define a cor do texto como amarelo.
 *   - `PINK`: Define a cor do texto como rosa.
 *   - `ORANGE`: Define a cor do texto como laranja.
 *   - `PURPLE`: Define a cor do texto como roxo.
 *   - `BROWN`: Define a cor do texto como marrom.
 *   - `GRAY`: Define a cor do texto como cinza claro.
 *   - `BLACK`: Define a cor do texto como preto.
 *   - `WHITE`: Define a cor do texto como branco.
 * 
 * - **Cores de fundo**:
 *   - `BG_BLUE`: Define o fundo como azul.
 *   - `BG_CYAN`: Define o fundo como ciano.
 *   - `BG_GREEN`: Define o fundo como verde água.
 *   - `BG_RED`: Define o fundo como vermelho.
 *   - `BG_MAGENTA`: Define o fundo como magenta.
 *   - `BG_YELLOW`: Define o fundo como amarelo.
 *   - `BG_PINK`: Define o fundo como rosa.
 *   - `BG_ORANGE`: Define o fundo como laranja.
 *   - `BG_PURPLE`: Define o fundo como roxo.
 *   - `BG_BROWN`: Define o fundo como marrom.
 *   - `BG_GRAY`: Define o fundo como cinza claro.
 *   - `BG_BLACK`: Define o fundo como preto.
 *   - `BG_WHITE`: Define o fundo como branco.
 * 
 * - **Formatação de texto**:
 *   - `f(color, text)`: Aplica a formatação de uma cor especificada ao texto, com reset no final.
 *   - `fE(text)`: Formata o texto para erros, com negrito e vermelho.
 *   - `fS(text)`: Formata o texto para sucesso, com negrito e verde.
 *   - `fT(text)`: Formata o texto como título, com negrito e sublinhado.
 *   - `fIf(color_true, color_false, condition, text)`: Aplica uma formatação condicional, escolhendo entre duas cores com base na condição.
 * 
 * @note Esta biblioteca usa códigos ANSI, que são suportados na maioria dos terminais Unix e em alguns terminais de sistemas Windows (como o Windows Terminal).
 * 
 * @date 12/10/2024
 * @version 2.0
 */
#ifndef COLORS_H
#define COLORS_H

/* Efeitos de texto */
#define RESET "\033[0m"     // Reseta cores e efeitos
#define BOLD "\033[1m"      // Negrito
#define UNDERLINE "\033[4m" // Sublinhado
#define BLINK "\033[5m"     // Piscante
#define INVERT "\033[7m"    // Inverte as cores

/* Cores de texto */
#define BLUE "\033[38;5;39m"     // Azul
#define CYAN "\033[38;5;51m"     // Ciano
#define GREEN "\033[38;5;46m"    // Verde água
#define RED "\033[38;5;196m"     // Vermelho
#define MAGENTA "\033[38;5;201m" // Magenta
#define YELLOW "\033[38;5;220m"  // Amarelo
#define PINK "\033[38;5;206m"    // Rosa 
#define ORANGE "\033[38;5;208m"  // Laranja
#define PURPLE "\033[38;5;93m"   // Roxo
#define BROWN "\033[38;5;94m"    // Marrom
#define GRAY "\033[38;5;245m"    // Cinza claro
#define BLACK "\033[38;5;16m"    // Preto
#define WHITE "\033[38;5;231m"   // Branco
 
/* Cores de fundo */
#define BG_BLUE "\033[48;5;39m"     // Fundo azul
#define BG_CYAN "\033[48;5;51m"     // Fundo ciano
#define BG_GREEN "\033[48;5;46m"    // Fundo verde água
#define BG_RED "\033[48;5;196m"     // Fundo vermelho
#define BG_MAGENTA "\033[48;5;201m" // Fundo magenta
#define BG_YELLOW "\033[48;5;220m"  // Fundo amarelo
#define BG_PINK "\033[48;5;206m"    // Fundo rosa
#define BG_ORANGE "\033[48;5;208m"  // Fundo laranja
#define BG_PURPLE "\033[48;5;93m"   // Fundo roxo
#define BG_BROWN "\033[48;5;94m"    // Fundo marrom
#define BG_GRAY "\033[48;5;245m"    // Fundo cinza claro
#define BG_BLACK "\033[48;5;16m"    // Fundo preto
#define BG_WHITE "\033[48;5;231m"   // Fundo branco

/* Formatação de texto */
#define f(color, text) color text RESET          
#define fError(text) BOLD RED text RESET    
#define fSuccess(text) BOLD GREEN text RESET  
#define fTitle(text) BOLD UNDERLINE text RESET 
#define fIf(color_true, color_false, condition, text) \
  (condition) ? f(color_true, text) : f(color_false, text)

#endif
