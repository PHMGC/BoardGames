/**
 * @file Game.hpp
 * @brief Definição da classe Game para gerenciar jogos baseados em tabuleiro.
 */

#pragma once

#include <utility>
#include <regex>
#include <string>
#include <vector>
#include <array>
#include <iostream>
#include "Board.hpp"

/**
 * @class Game
 * @brief Classe base para jogos baseados em tabuleiro.
 */
class Game {
protected:
    std::string name; ///< Nome do jogo
    std::vector<std::string> players; ///< Lista de jogadores
    int turn = 0; ///< Índice do jogador atual
    bool isRunning = false; ///< Indica se o jogo está em andamento

public:
    Board board; ///< Objeto do tabuleiro do jogo

    /**
     * @brief Construtor da classe Game.
     * @param size Dimensão do tabuleiro.
     * @param name Nome do jogo.
     */
    Game(const std::array<size_t, 2> size, std::string name);

    /**
     * @brief Destrutor virtual da classe Game.
     */
    virtual ~Game() = default;

    /**
     * @brief Obtém o nome do jogo.
     * @return Nome do jogo.
     */
    std::string getName();

    /**
     * @brief Inicializa o jogo com os jogadores fornecidos.
     * @param players Vetor contendo os nomes dos jogadores.
     */
    virtual void initialize(const std::vector<std::string>& players);

    /**
     * @brief Alterna o turno entre os jogadores.
     */
    void changeTurn();

    /**
     * @brief Verifica se o jogo terminou.
     * @return true se o jogo terminou, false caso contrário.
     */
    virtual bool isOver();

    /**
     * @brief Obtém o vencedor do jogo.
     * @return Nome do jogador vencedor.
     */
    virtual std::string getWinner();

    /**
     * @brief Obtém o perdedor do jogo.
     * @return Nome do jogador perdedor.
     */
    virtual std::string getLoser();

    /**
     * @brief Interpreta um comando de posicionamento.
     * @param input Entrada do usuário.
     * @param pos Referência para armazenar a posição interpretada.
     * @return true se a entrada foi válida, false caso contrário.
     */
    virtual bool parsePlace(const std::string& input, std::array<size_t, 2>& pos);

    /**
     * @brief Interpreta um comando de movimentação.
     * @param input Entrada do usuário.
     * @param pos1 Referência para armazenar a posição de origem.
     * @param pos2 Referência para armazenar a posição de destino.
     * @return true se a entrada foi válida, false caso contrário.
     */
    virtual bool parseMove(const std::string& input, std::array<size_t, 2>& pos1, std::array<size_t, 2>& pos2);

    /**
     * @brief Executa um turno do jogo (método puramente virtual).
     * @return true se o turno foi executado com sucesso, false caso contrário.
     */
    virtual bool playTurn() = 0;

    /**
     * @brief Verifica se há um vencedor (método puramente virtual).
     * @return true se houver um vencedor, false caso contrário.
     */
    virtual bool isWin() = 0;

    /**
     * @brief Verifica se houve empate (método puramente virtual).
     * @return true se o jogo empatou, false caso contrário.
     */
    virtual bool isDraw() = 0;
};