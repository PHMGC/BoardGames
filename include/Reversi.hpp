/**
 * @file Reversi.hpp
 * @brief Declaração das classes ReversiPiece e Reversi para o jogo Reversi.
 */

#pragma once

#include "Game.hpp"
#include "Piece.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <string>

/**
 * @class ReversiPiece
 * @brief Representa uma peça do jogo Reversi.
 */
class ReversiPiece final : public Piece {
public:
    /**
     * @brief Construtor para uma peça de Reversi.
     * @param turn Indica a vez do jogador.
     * @param player Nome do jogador que possui a peça.
     */
    explicit ReversiPiece(int turn, const std::string& player);

    /**
     * @brief Verifica se um movimento é válido.
     * @param from Posição inicial da peça.
     * @param to Posição final desejada.
     * @return Verdadeiro se o movimento for válido, falso caso contrário.
     */
    [[nodiscard]] bool isValidMove(std::array<size_t, 2> from, std::array<size_t, 2> to) const override;

    /**
     * @brief Inverte a peça para o jogador especificado.
     * @param newPlayer Novo dono da peça.
     */
    void flip(const std::string& newPlayer);
};

/**
 * @class Reversi
 * @brief Implementação do jogo Reversi.
 */
class Reversi final : public Game {
public:
    /**
     * @brief Construtor da classe Reversi.
     */
    explicit Reversi();

    /**
     * @brief Inicializa o jogo com os jogadores fornecidos.
     * @param players Vetor contendo os nomes dos jogadores.
     */
    void initialize(const std::vector<std::string>& players) override;

    /**
     * @brief Executa um turno do jogo.
     * @return Verdadeiro se o turno foi jogado com sucesso, falso caso contrário.
     */
    bool playTurn() override;

    /**
     * @brief Retorna as jogadas possíveis para um jogador específico.
     * @param player Nome do jogador.
     * @return Vetor contendo as posições das jogadas possíveis.
     */
    [[nodiscard]] std::vector<std::array<size_t, 2>> possiblePlays(const std::string& player) const;

    /**
     * @brief Verifica se um movimento é válido.
     * @param pos Posição do movimento.
     * @param player Nome do jogador.
     * @return Verdadeiro se o movimento for válido, falso caso contrário.
     */
    [[nodiscard]] bool isValidMove(const std::array<size_t, 2>& pos, const std::string& player) const;

    /**
     * @brief Verifica se um jogador deve pular sua vez.
     * @param player Nome do jogador.
     * @return Verdadeiro se o jogador precisar pular a vez, falso caso contrário.
     */
    [[nodiscard]] bool isTurnSkipped(const std::string& player) const;

    /**
     * @brief Inverte as peças afetadas por um movimento.
     * @param pos Posição do movimento.
     * @param player Nome do jogador que fez a jogada.
     */
    void flipPieces(const std::array<size_t, 2>& pos, const std::string& player) const;

    /**
     * @brief Verifica se o jogo terminou em empate.
     * @return Verdadeiro se houver empate, falso caso contrário.
     */
    bool isDraw() override;

    /**
     * @brief Verifica se há um vencedor.
     * @return Verdadeiro se houver um vencedor, falso caso contrário.
     */
    bool isWin() override;

    /**
     * @brief Retorna o nome do jogador vencedor.
     * @return Nome do jogador vencedor.
     */
    std::string getWinner() override;

    /**
     * @brief Verifica se o jogo terminou.
     * @return Verdadeiro se o jogo acabou, falso caso contrário.
     */
    bool isOver() override;

private:
    /**
     * @brief Conta a quantidade de peças de um jogador no tabuleiro.
     * @param player Nome do jogador.
     * @return Número de peças pertencentes ao jogador.
     */
    [[nodiscard]] int playerPieces(const std::string& player) const;
};
