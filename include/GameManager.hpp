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
    std::string player1, player2;

public:
    GameManager() {
        // Adicione jogos disponíveis ao vetor
        games.push_back(std::make_unique<TicTacToe>());
        games.push_back(std::make_unique<Lig4>());
        games.push_back(std::make_unique<Reversi>());
    }

    static void playGame(Game& game) {
        game.initialize();
        while (true) {
            if (game.playTurn()) {
                if (game.isOver()) { // Verifica vitória ou empate após jogada válida
                    game.board.print();
                    game.board.reset();
                    std::cout << "Jogo encerrado." << std::endl;
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
            }
        }
        return substring;
    }

    static size_t parseGameIndex(const std::string& symbol) {
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

    void parseCommand(const std::string& command) {
        std::istringstream stream(command);
        std::string word;
        std::vector<std::string> words;
        while (stream >> word) {
            words.push_back(word);
        }
        // Permitir o input como upper ou lowercase
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
            if (words.size() >= 2 && words[0] == "LJ") {
                save_manager.leaderboard();
                return;
            }
            // Executar partida

            if (words.size() == 4 && words[0] == "EP") {
                const size_t gameIndex = parseGameIndex(words[1]);
                if (gameIndex == -1) {
                    throw std::invalid_argument("ERRO: Jogo invalido");
                }
                if (!save_manager.isPlayer(words[2]) && !save_manager.isPlayer(words[3])) {
                    throw std::invalid_argument("ERRO: Jogador 1 e Jogador 2 inexistentes");
                } if (!save_manager.isPlayer(words[2])) {
                    throw std::invalid_argument("ERRO: Jogador 1 inexistente");
                } if (!save_manager.isPlayer(words[3])) {
                    throw std::invalid_argument("ERRO: Jogador 2 inexistente");
                }
                player1 = words[2];
                player2 = words[3];
                playGame(*this->games[gameIndex]);
                return;
            }
            if (words.size() == 1 && words[0] == "FS") {
                std::exit(0);
            }
            if (words.size() == 1 && words[0] == "H") {
                printCommands();
                return;
            }
        }
        throw std::invalid_argument("ERRO: Comando invalido");
    }

    void printCommands() {
        std::cout << "Cadastrar Jogador: CJ <Apelido> <Nome>" << std::endl;
        std::cout << "Remover Jogador: RJ <Apelido>" << std::endl;
        std::cout << "Listar jogadores: LJ [A|N]" << std::endl;
        std::cout << "Executar Partida: EP <Jogo: (R|L|V)> <Apelido Jogador 1> <Apelido Jogador 2>" << std::endl;
        std::cout << "Finalizar sistema: FS" << std::endl;
        std::cout << "Imprimir todos os comandos disponiveis: H" << std::endl;
    }

    void run() {
        std::cout << "Bem-vindo a Board Games!" << std::endl;
        std::cout << "Para exibir os comandos disponiveis, use o comando H" << std::endl;
        while (true) {
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
