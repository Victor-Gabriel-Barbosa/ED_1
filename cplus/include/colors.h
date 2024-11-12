/**
 * @file colors.h
 * @brief Biblioteca para cores e efeitos de formatação de texto no terminal usando ANSI escape codes.
 * 
 * Esta biblioteca define macros para aplicar cores e efeitos de texto, como negrito, sublinhado, 
 * e cores personalizadas para o texto e o fundo. Ela facilita a aplicação de estilos no terminal de forma simples.
 * 
 * Definições disponíveis:
 * 
 * - Efeitos de texto:
 *   - 'RESET': Reseta as cores e efeitos aplicados.
 *   - 'BOLD': Aplica negrito ao texto.
 *   - 'UNDERLINE': Aplica sublinhado ao texto.
 *   - 'BLINK': Aplica efeito piscante ao texto.
 *   - 'INVERT': Inverte as cores do texto e do fundo.
 * 
 * - Cores de texto:
 *   - 'BLUE': Define a cor do texto como azul.
 *   - 'CYAN': Define a cor do texto como ciano.
 *   - 'GREEN': Define a cor do texto como verde água.
 *   - 'RED': Define a cor do texto como vermelho.
 *   - 'MAGENTA': Define a cor do texto como magenta.
 *   - 'YELLOW': Define a cor do texto como amarelo.
 *   - 'PINK': Define a cor do texto como rosa.
 *   - 'ORANGE': Define a cor do texto como laranja.
 *   - 'PURPLE': Define a cor do texto como roxo.
 *   - 'BROWN': Define a cor do texto como marrom.
 *   - 'GRAY': Define a cor do texto como cinza claro.
 *   - 'BLACK': Define a cor do texto como preto.
 *   - 'WHITE': Define a cor do texto como branco.
 * 
 * - Cores de fundo:
 *   - 'BLUE_BG': Define o fundo como azul.
 *   - 'CYAN_BG': Define o fundo como ciano.
 *   - 'GREEN_BG': Define o fundo como verde água.
 *   - 'RED_BG': Define o fundo como vermelho.
 *   - 'MAGENTA_BG': Define o fundo como magenta.
 *   - 'YELLOW_BG': Define o fundo como amarelo.
 *   - 'PINK_BG': Define o fundo como rosa.
 *   - 'ORANGE_BG': Define o fundo como laranja.
 *   - 'PURPLE_BG': Define o fundo como roxo.
 *   - 'BROWN_BG': Define o fundo como marrom.
 *   - 'GRAY_BG': Define o fundo como cinza claro.
 *   - 'BLACK_BG': Define o fundo como preto.
 *   - 'WHITE_BG': Define o fundo como branco.
 * 
 * - Formatação de texto:
 *   - 'f(color, text)': Aplica a formatação de uma cor especificada ao texto, com reset no final.
 *   - 'fLn(fmt, text)': Aplica a formatação de uma cor especificada ao texto, com reset e "\n" no final.
 *   - 'fError(text)': Formata o texto para erros, com negrito e vermelho.
 *   - 'fSuccess(text)': Formata o texto para sucesso, com negrito e verde.
 *   - 'fTitle(text)': Formata o texto como título, com negrito e sublinhado.
 *   - 'fIf(color_true, color_false, condition, text)': Aplica uma formatação condicional, escolhendo entre duas cores com base na condição.
 *   - 'c': Define uma cor de texto com código ANSI específico.
 *   - 'cBG': Define uma cor de fundo com código ANSI específico.
 * 
 * @note Esta biblioteca usa códigos ANSI, que são suportados na maioria dos terminais Unix e em alguns terminais de sistemas Windows (como o Windows Terminal).
 * 
 * @author Victor Gabriel Barbosa
 * @date 12/10/2024
 * @version 2.0
 */
#ifndef COLORS_H
#define COLORS_H

/* Efeitos de texto */
#define RESET "\033[0m"     /**< Reseta cores e efeitos */
#define BOLD "\033[1m"      /**< Negrito */
#define UNDERLINE "\033[4m" /**< Sublinhado */
#define BLINK "\033[5m"     /**< Piscante */
#define INVERT "\033[7m"    /**< Inverte as cores */

/* Cores de texto */ 
#define BLUE "\033[38;5;39m"     /**< Azul */
#define CYAN "\033[38;5;51m"     /**< Ciano */
#define GREEN "\033[38;5;46m"    /**< Verde água */
#define RED "\033[38;5;196m"     /**< Vermelho */
#define MAGENTA "\033[38;5;201m" /**< Magenta */
#define YELLOW "\033[38;5;220m"  /**< Amarelo */
#define PINK "\033[38;5;206m"    /**< Rosa */
#define ORANGE "\033[38;5;208m"  /**< Laranja */
#define PURPLE "\033[38;5;93m"   /**< Roxo */
#define BROWN "\033[38;5;94m"    /**< Marrom */
#define GRAY "\033[38;5;245m"    /**< Cinza claro */
#define BLACK "\033[38;5;16m"    /**< Preto */
#define WHITE "\033[38;5;231m"   /**< Branco */
 
/* Cores de fundo */
#define BLUE_BG "\033[48;5;39m"     /**< Fundo azul */
#define CYAN_BG "\033[48;5;51m"     /**< Fundo ciano */
#define GREEN_BG "\033[48;5;46m"    /**< Fundo verde água */
#define RED_BG "\033[48;5;196m"     /**< Fundo vermelho */
#define MAGENTA_BG "\033[48;5;201m" /**< Fundo magenta */
#define YELLOW_BG "\033[48;5;220m"  /**< Fundo amarelo */
#define PINK_BG "\033[48;5;206m"    /**< Fundo rosa */
#define ORANGE_BG "\033[48;5;208m"  /**< Fundo laranja */
#define PURPLE_BG "\033[48;5;93m"   /**< Fundo roxo */
#define BROWN_BG "\033[48;5;94m"    /**< Fundo marrom */
#define GRAY_BG "\033[48;5;245m"    /**< Fundo cinza claro */
#define BLACK_BG "\033[48;5;16m"    /**< Fundo preto */
#define WHITE_BG "\033[48;5;231m"   /**< Fundo branco */

/* Formatação de texto */

/**
 * @brief Aplica uma formatação específica ao texto e reseta a formatação ao final.
 * @param fmt A formatação aplicada ao texto (exemplo: negrito ou cor específica).
 * @param text O texto que receberá a formatação.
 */
#define f(fmt, text) fmt text RESET

/**
 * @brief Aplica uma formatação específica ao texto, reseta a formatação e adiciona '\n' ao final.
 * @param fmt A formatação aplicada ao texto (exemplo: negrito ou cor específica).
 * @param text O texto que receberá a formatação.
 */
#define fLn(fmt, text) fmt text "\n" RESET

/**
 * @brief Aplica formatação para mensagens de erro.
 * @param text O texto que receberá a formatação de erro (negrito e vermelho).
 */
#define fError(text) BOLD RED text RESET

/**
 * @brief Aplica formatação para mensagens de alerta.
 * @param text O texto que receberá a formatação de alerta (negrito e amarelo).
 */
#define fAlert(text) BOLD YELLOW text RESET

/**
 * @brief Aplica formatação para mensagens de sucesso.
 * @param text O texto que receberá a formatação de sucesso (negrito e verde).
 */
#define fSuccess(text) BOLD GREEN text RESET

/**
 * @brief Aplica formatação de título ao texto.
 * @param text O texto que receberá a formatação de título (negrito e sublinhado).
 */
#define fTitle(text) BOLD UNDERLINE text RESET

/**
 * @brief Aplica uma formatação condicional ao texto com base em uma condição.
 * @param color_true Formatação aplicada se a condição for verdadeira.
 * @param color_false Formatação aplicada se a condição for falsa.
 * @param condition A condição que determina qual formatação aplicar.
 * @param text O texto que receberá a formatação condicional.
 */
#define fIf(color_true, color_false, condition, text) \
  (condition) ? f(color_true, text) : f(color_false, text)

/**
 * @brief Define uma cor de texto com código ANSI específico.
 * @param code O código de cor ANSI a ser aplicado (de 0 a 255).
 */
#define c(code) "\033[38;5;" #code "m"

/**
 * @brief Define uma cor de fundo com código ANSI específico.
 * @param code O código de cor ANSI a ser aplicado ao fundo (de 0 a 255).
 */
#define cBG(code) "\033[48;5;" #code "m"

#endif
