#pragma once

#include "Game.hpp"
#include "Piece.hpp"
#include <array>
#include <string>

/**
 * @class TTTPiece
 * @brief Representa uma peça no jogo da velha.
 *
 * Essa classe herda de Piece e adiciona lógica específica do jogo da velha.
 */
class TTTPiece final : public Piece {
public:
    /**
     * @brief Construtor da classe TTTPiece.
     * @param turn Número do turno.
     * @param player Nome do jogador associado à peça.
     */
    explicit TTTPiece(int turn, const std::string &player);

    /**
     * @brief Verifica se um movimento é válido.
     * @param startPos Posição inicial no tabuleiro.
     * @param endPos Posição final no tabuleiro.
     * @return true se o movimento for válido, false caso contrário.
     */
    [[nodiscard]] bool isValidMove(std::array<size_t, 2> startPos, std::array<size_t, 2> endPos) const override;
};

/**
 * @class TicTacToe
 * @brief Implementação do jogo da velha.
 *
 * Esta classe gerencia o fluxo do jogo da velha, incluindo lógica de jogadas e verificações de vitória/empate.
 */
class TicTacToe final : public Game {
public:
    /**
     * @brief Construtor da classe TicTacToe.
     */
    explicit TicTacToe();

    /**
     * @brief Executa um turno do jogo.
     * @return true se o turno foi jogado com sucesso, false caso contrário.
     */
    bool playTurn() override;

    /**
     * @brief Verifica se o jogo foi vencido.
     * @return true se houver um vencedor, false caso contrário.
     */
    bool isWin() override;

    /**
     * @brief Verifica se o jogo terminou em empate.
     * @return true se o jogo estiver empatado, false caso contrário.
     */
    bool isDraw() override;

private:
    /**
     * @brief Verifica se três posições formam uma linha vencedora.
     * @param pos1 Primeira posição.
     * @param pos2 Segunda posição.
     * @param pos3 Terceira posição.
     * @return true se as três posições formam uma linha vencedora, false caso contrário.
     */
    [[nodiscard]] bool checkLine(std::array<size_t, 2> pos1,
                                 std::array<size_t, 2> pos2,
                                 std::array<size_t, 2> pos3) const;
};
