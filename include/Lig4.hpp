#pragma once

#include "Piece.hpp"
#include <array>
#include <string>
#include "Game.hpp"
#include <iostream>

/**
 * @class Lig4Piece
 * @brief Representa uma peça do jogo Lig4 (Lig-4).
 *
 * Esta classe herda de Piece e define a peça usada no jogo Lig-4.
 */
class Lig4Piece final : public Piece {
public:
    /**
     * @brief Constrói uma peça do Lig-4.
     *
     * @param turn Número do turno do jogador.
     * @param player Nome do jogador que possui a peça.
     */
    explicit Lig4Piece(int turn, const std::string& player);

    /**
     * @brief Verifica se um movimento é válido.
     *
     * @param startPos Posição inicial da peça.
     * @param endPos Posição final da peça.
     * @return true se o movimento for válido, false caso contrário.
     */
    [[nodiscard]] bool isValidMove(std::array<size_t, 2> startPos, std::array<size_t, 2> endPos) const override;
};

/**
 * @class Lig4
 * @brief Implementa o jogo Lig-4.
 *
 * Esta classe herda de Game e implementa a lógica do jogo Lig-4.
 */
class Lig4 final : public Game {
public:
    /**
     * @brief Constrói um objeto Lig4.
     */
    explicit Lig4();

    /**
     * @brief Executa um turno do jogo.
     *
     * @return true se o turno foi jogado com sucesso, false caso contrário.
     */
    bool playTurn() override;

    /**
     * @brief Coloca uma peça na coluna especificada.
     *
     * @param col Índice da coluna onde a peça será inserida.
     */
    void placePieceOnCol(size_t col);

    /**
     * @brief Verifica se um jogador venceu o jogo.
     *
     * @return true se houver um vencedor, false caso contrário.
     */
    bool isWin() override;

    /**
     * @brief Verifica se o jogo terminou em empate.
     *
     * @return true se o jogo estiver empatado, false caso contrário.
     */
    bool isDraw() override;

private:
    /**
     * @brief Verifica se quatro peças formam uma linha vencedora.
     *
     * @param pos1 Posição da primeira peça.
     * @param pos2 Posição da segunda peça.
     * @param pos3 Posição da terceira peça.
     * @param pos4 Posição da quarta peça.
     * @return true se as quatro peças formarem uma linha vencedora, false caso contrário.
     */
    [[nodiscard]] bool checkLine(std::array<size_t, 2> pos1,
                                 std::array<size_t, 2> pos2,
                                 std::array<size_t, 2> pos3,
                                 std::array<size_t, 2> pos4) const;
};
