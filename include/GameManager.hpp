#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "TicTacToe.hpp"
#include "Lig4.hpp"
#include "Reversi.hpp"

class GameManager {
    std::vector<std::unique_ptr<Game>> games; // Lista de jogos disponíveis

public:
    GameManager() {
        // Adicione jogos disponíveis ao vetor
        games.push_back(std::make_unique<TicTacToe>());
        games.push_back(std::make_unique<Lig4>());
        games.push_back(std::make_unique<Reversi>());
    }

    void listGames() const
    {
        std::cout << "Jogos disponiveis:\n";
        for (size_t i = 0; i < games.size(); ++i) {
            std::cout << i + 1 << ". " << games[i]->getName() << "\n";
        }
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

    void run() const {
        while (true) {
            this->listGames(); // Lista os jogos disponíveis
            std::cout << "Escolha um jogo (0 para sair): ";

            std::string input;
            std::getline(std::cin, input);

            try {
                const int choice = std::stoi(input); // Agora é seguro converter para inteiro
                // Verifica se a entrada é numérica
                if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
                    std::cout << "Erro: Entrada inválida! Por favor, insira um número." << std::endl;
                    continue; // Volta ao início do loop
                }

                if (choice == 0) {
                    std::cout << "Saindo do programa." << std::endl;
                    break; // Encerra o programa
                }

                if (choice < 1 || choice > static_cast<int>(games.size())) {
                    std::cout << "Escolha inválida! Insira um número entre 1 e " << games.size() << "." << std::endl;
                    continue; // Volta ao início do loop
                }

                // Jogue o jogo selecionado
                playGame(*this->games[choice - 1]);
            }
            catch (std::invalid_argument& e) {
                std::cout << "Erro: Entrada inválida! Por favor, insira um número." << std::endl;
            }

        }
    }


};
