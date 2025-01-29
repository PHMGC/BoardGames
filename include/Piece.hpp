#pragma once

#include <string>
#include <array>
#include <utility>

/**
 * @class Piece
 * @brief Representa uma peça genérica em um jogo de tabuleiro.
 *
 * A classe Piece serve como uma classe base abstrata para diferentes tipos de peças
 * dentro de um jogo. Cada peça tem um símbolo característico e pertence a um jogador específico.
 * Além disso, cada peça deve implementar a lógica de movimentação específica do jogo.
 */
class Piece {
protected:
    char symbol; ///< Representação visual da peça (ex.: 'X', 'O', 'P', 'p').
    std::string player; ///< Nome ou identificador do jogador dono da peça.

public:
    /**
     * @brief Constrói uma nova peça.
     * @param turn Indica o turno no qual a peça foi criada.
     * @param player Nome ou identificador do jogador dono da peça.
     */
    explicit Piece(int turn, std::string player);

    /**
     * @brief Obtém o símbolo da peça.
     * @return O símbolo que representa a peça.
     */
    [[nodiscard]] char getSymbol() const;

    /**
     * @brief Obtém o nome do jogador que controla a peça.
     * @return String com o nome do jogador.
     */
    [[nodiscard]] std::string getPlayer() const;

    /**
     * @brief Verifica se um movimento da peça é válido.
     *
     * Esse método é abstrato e deve ser implementado pelas classes derivadas.
     * Cada jogo pode definir regras diferentes de movimentação para suas peças.
     *
     * @param startPos Posição inicial da peça no tabuleiro.
     * @param endPos Posição final desejada no tabuleiro.
     * @return true se o movimento for válido, false caso contrário.
     */
    [[nodiscard]] virtual bool isValidMove(std::array<size_t, 2> startPos, std::array<size_t, 2> endPos) const = 0;

    /**
     * @brief Destrói a peça.
     */
    virtual ~Piece();
};
