#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "TicTacToe.hpp"
#include "Lig4.hpp"
#include "Reversi.hpp"
#include "SaveManager.hpp"

class GameManager {
    std::vector<std::unique_ptr<Game>> games; // Lista de jogos disponíveis
    SaveManager save_manager;

    bool isRunning = true;

public:
    GameManager() {
        // Adicione jogos disponíveis ao vetor
        games.push_back(std::make_unique<TicTacToe>());
        games.push_back(std::make_unique<Lig4>());
        games.push_back(std::make_unique<Reversi>());
    }

    void playGame(Game& game, const std::vector<std::string>& players) {
        game.initialize(players);
        while (true) {
            if (game.playTurn()) {
                if (game.isOver()) { // Verifica vitória ou empate após jogada válida
                    if (game.isWin()) {
                        save_manager.setWinrate(game.getWinner(), game.getName(), true);
                        save_manager.setWinrate(game.getLoser(), game.getName(), false);
                    }
                    game.board.print();
                    game.board.reset();
                    std::cout << "Jogo encerrado." << std::endl;
                    std::cout << "Para exibir os comandos disponiveis, use o comando H" << std::endl;
                    break;
                }
                game.changeTurn();
            }
            game.board.print();
        }
    }

    static std::string getSubString(const std::vector<std::string> &words, const size_t startIndex) {
        std::string substring;
        for (size_t i = 0; i < words.size(); i++) {
            if (i >= startIndex) {
                substring += words[i];
                substring += " ";
            }
        }
        return substring;
    }

    static size_t parseGameIndex(std::string& symbol) {
        // Permitir o comando como upper ou lowercase
        for (char& c : symbol) {
            c = std::toupper(c);
        }

        // Jogo da Velha
        if (symbol == "V") {
            return 0;
        }
        // Lig4
        if (symbol == "L") {
            return 1;
        }
        // Reversi
        if (symbol == "R") {
            return 2;
        }

        return -1;
    }

    void parseCommand(const std::string& input) {
        std::istringstream stream(input);
        std::string word;
        std::vector<std::string> words;
        while (stream >> word) {
            words.push_back(word);
        }
        // Permitir o comando como upper ou lowercase
        for (char& c : words[0]) {
            c = std::toupper(c);
        }

        if (!words.empty()) {
            // Cadastrar jogador
            // CJ <Apelido> <Nome>
            if (words.size() > 2 && words[0] == "CJ") {
                save_manager.setPlayer(words[1], getSubString(words, 2));
                return;
            }
            // Remover jogador
            // RJ <Apelido>
            if (words.size() == 2 && words[0] == "RJ") {
                save_manager.removePlayer(words[1]);
                return;
            }
            // Listar jogadores (leaderboard)
            // LJ [A|N]
            // TODO: entender essa merda aqui
            // Ele não especifica nas instruções que deve ser impresso apenas o jogador do input
            if (words.size() == 1 && words[0] == "LJ") {
                save_manager.leaderboard();
                return;
            }
            // Executar partida
            // EP <Jogo: (R|L|V)> <Apelido Jogador 1> <Apelido Jogador 2>
            if (words.size() == 4 && words[0] == "EP") {
                std::string player1 = words[2];
                std::string player2 = words[3];
                const size_t gameIndex = parseGameIndex(words[1]);
                if (gameIndex == -1) {
                    throw std::invalid_argument("ERRO: Jogo invalido");
                }
                if (!save_manager.isPlayer(player1) && !save_manager.isPlayer(player2)) {
                    throw std::invalid_argument("ERRO: Jogador 1 e Jogador 2 inexistentes");
                } if (!save_manager.isPlayer(player1)) {
                    throw std::invalid_argument("ERRO: Jogador 1 inexistente");
                } if (!save_manager.isPlayer(player2)) {
                    throw std::invalid_argument("ERRO: Jogador 2 inexistente");
                }
                playGame(*this->games[gameIndex], {player1, player2});
                return;
            }
            if (words.size() == 1 && words[0] == "FS") {
                isRunning = false;
                return;
            }
            if (words.size() == 1 && words[0] == "H") {
                printCommands();
                return;
            }
        }
        throw std::invalid_argument("ERRO: Comando invalido");
    }

    static void printCommands() {
        std::cout << "Cadastrar Jogador: CJ <Apelido> <Nome>" << std::endl;
        std::cout << "Remover Jogador: RJ <Apelido>" << std::endl;
        std::cout << "Listar jogadores: LJ [A|N]" << std::endl;
        std::cout << "Executar Partida: EP <Jogo: (R|L|V)> <Apelido Jogador 1> <Apelido Jogador 2>" << std::endl;
        std::cout << "Finalizar sistema: FS" << std::endl;
        std::cout << "Imprimir todos os comandos disponiveis: H" << std::endl;
        std::cout << "Observacao: os comandos nao sao case sensitive" << std::endl;
    }

    void run() {
        std::cout << "Bem-vindos a Board Games!" << std::endl;
        std::cout << "Para exibir os comandos disponiveis, use o comando H" << std::endl;
        while (isRunning) {
            std::string input;
            std::getline(std::cin, input);
            try {
                parseCommand(input);
            } catch (std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
        }

    }


};
