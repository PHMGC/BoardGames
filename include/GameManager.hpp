#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "TicTacToe.hpp"
//#include "Lig4.hpp"
//#include "Reversi.hpp"

class GameManager {
    std::vector<std::unique_ptr<Game>> games; // Lista de jogos disponíveis

public:
    GameManager() {
        // Adicione jogos disponíveis ao vetor
        games.push_back(std::make_unique<TicTacToe>());
        //games.push_back(std::make_unique<Lig4>());
        //games.push_back(std::make_unique<Reversi>());
    }

    void listGames() const
    {
        std::cout << "Jogos disponiveis:\n";
        for (size_t i = 0; i < games.size(); ++i) {
            std::cout << i + 1 << ". " << games[i]->getName() << "\n";
        }
    }

    static void playGame(Game& game)
    {
        game.initialize();
        while (!game.isOver()) {
            if (game.playTurn())
            {
                game.changeTurn();
            }
            game.printBoard();
        }
    }

    void run() const {
        while (true) {
            this->listGames();
            std::cout << "Escolha um jogo (0 para sair): ";
            int choice;
            std::cin >> choice;
            std::cout << std::endl;

            if (choice == 0) break; // Encerrar programa
            if (choice < 1 || choice > static_cast<int>(games.size())) {
                std::cout << "Escolha invalida! Tente novamente." << std::endl;
                continue;
            }

            // Jogue o jogo selecionado
            playGame(*this->games[choice - 1]);
        }
    }

};
