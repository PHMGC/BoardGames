#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

#include "TicTacToe.hpp"
#include "Lig4.hpp"
#include "Reversi.hpp"
#include "SaveManager.hpp"

/**
 * @class GameManager
 * @brief Gerencia os jogos e comandos do sistema.
 *
 * A classe GameManager é responsável por armazenar os jogos disponíveis,
 * carregar e salvar estados de jogo e interpretar comandos do usuário.
 */
class GameManager {
    std::vector<std::unique_ptr<Game>> games; ///< Lista de jogos disponíveis.
    SaveManager save_manager; ///< Gerenciador de salvamento de jogos.
    bool isRunning = true; ///< Indica se o gerenciador de jogos está em execução.

public:
    /**
     * @brief Construtor padrão do GameManager.
     */
    GameManager();

    /**
     * @brief Inicializa o sistema e retorna uma lista de comandos disponíveis.
     * @return Um vetor de strings com os comandos disponíveis.
     */
    std::vector<std::string> init();

    /**
     * @brief Executa um jogo específico com os jogadores fornecidos.
     * @param game Referência ao jogo a ser executado.
     * @param players Vetor contendo os nomes dos jogadores.
     */
    void playGame(Game& game, const std::vector<std::string>& players);

    /**
     * @brief Obtém uma substring a partir de um vetor de palavras.
     * @param words Vetor de palavras.
     * @param startIndex Índice inicial da substring.
     * @return A substring resultante.
     */
    static std::string getSubString(const std::vector<std::string>& words, const size_t startIndex);

    /**
     * @brief Converte um símbolo de string para um índice numérico.
     * @param symbol String contendo o símbolo a ser convertido.
     * @return O índice numérico correspondente.
     */
    static size_t parseGameIndex(std::string& symbol);

    /**
     * @brief Analisa e executa um comando de entrada.
     * @param input Comando digitado pelo usuário.
     */
    void parseCommand(const std::string& input);

    /**
     * @brief Exibe os comandos disponíveis para o usuário.
     */
    static void printCommands();

    /**
     * @brief Inicia o loop principal do GameManager.
     */
    void run();
};
