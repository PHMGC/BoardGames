#pragma once

#include <array>
#include <vector>
#include <memory>
#include <string>
#include <regex>
#include <iostream>
#include "Piece.hpp"

/**
 * @class Board
 * @brief Representa um tabuleiro de jogo contendo peças.
 */
class Board {
    std::array<size_t, 2> size; ///< Dimensões do tabuleiro (largura x altura).
    std::vector<std::vector<std::shared_ptr<Piece>>> grid; ///< Matriz de peças no tabuleiro.

    /**
     * @brief Imprime o cabeçalho do tabuleiro na saída padrão.
     * @param spacing Espaçamento entre as colunas.
     */
    void printHeader(const std::string &spacing) const;

public:
    /**
     * @brief Construtor da classe Board.
     * @param size Dimensões do tabuleiro.
     */
    explicit Board(const std::array<size_t, 2> size);

    /**
     * @brief Reseta o tabuleiro, removendo todas as peças.
     */
    void reset();

    /**
     * @brief Imprime o tabuleiro na saída padrão.
     */
    void print() const;

    /**
     * @brief Converte um caractere de entrada em um índice de coluna do tabuleiro.
     * @param input Caractere representando a coluna.
     * @return Índice numérico correspondente à coluna.
     */
    [[nodiscard]] size_t parseColInput(const char input) const;

    /**
     * @brief Converte uma string de entrada em coordenadas do tabuleiro.
     * @param input String representando a posição (exemplo: "A1").
     * @return Posição no tabuleiro como um array de duas dimensões.
     */
    [[nodiscard]] std::array<size_t, 2> parsePosInput(const std::string &input) const;

    /**
     * @brief Obtém o tamanho do tabuleiro.
     * @return Dimensões do tabuleiro.
     */
    [[nodiscard]] std::array<size_t, 2> getSize() const;

    /**
     * @brief Verifica se uma posição no tabuleiro é válida.
     * @param pos Coordenadas da posição.
     * @return true se a posição for válida, false caso contrário.
     */
    [[nodiscard]] bool isValid(const std::array<size_t, 2> pos) const;

    /**
     * @brief Move uma peça de uma posição inicial para uma posição final.
     * @param startPos Posição inicial da peça.
     * @param endPos Posição final para onde a peça será movida.
     * @param checkCollision Define se deve verificar colisões durante o movimento (padrão: true).
     * @return true se o movimento for bem-sucedido, false caso contrário.
     */
    bool move(const std::array<size_t, 2> startPos, const std::array<size_t, 2> endPos, const bool checkCollision = true);

    /**
     * @brief Obtém uma peça em uma posição específica do tabuleiro.
     * @param pos Coordenadas da posição.
     * @return Ponteiro compartilhado para a peça na posição especificada.
     */
    [[nodiscard]] std::shared_ptr<Piece> get(const std::array<size_t, 2> pos) const;

    /**
     * @brief Define uma peça em uma posição específica do tabuleiro.
     * @param pos Coordenadas da posição.
     * @param piece Ponteiro compartilhado para a peça a ser posicionada.
     */
    void set(const std::array<size_t, 2> pos, std::shared_ptr<Piece> piece);
};
