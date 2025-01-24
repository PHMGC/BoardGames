#pragma once

#include "Game.hpp"
#include "Piece.hpp"
#include <iostream>

class TTTPiece final : public Piece {
public:
    explicit TTTPiece(const int turn, const std::string &player)
        : Piece(turn, player) {}

    [[nodiscard]] bool isValidMove(std::array<size_t, 2> startPos , std::array<size_t, 2> endPos) const override {
        return true;
    }
};

class TicTacToe final : public Game
{
public:
    explicit TicTacToe() : Game({3, 3}, "Jogo da Velha") {}

    bool playTurn() override {
        std::cout << "Turno de " << players[turn] << ": envie sua jogada (<coluna><linha>), ou SAIR para sair: ";
        std::string input;
        std::getline(std::cin, input);

        // Permitir o comando como upper ou lowercase
        for (char& c : input) {
            c = std::toupper(c);
        }
        if (input == "SAIR") {
            isRunning = false;
            return true;
        }

        try {
            const std::array<size_t, 2> pos = this->board.parsePosInput(input);
            if (board.get(pos)) {
                std::cout << "Espaco ocupado. Tente novamente.\n";
                return false;
            }

            board.set(pos, std::make_shared<TTTPiece>(turn, players[turn]));
            return true;
        } catch (std::exception& e) {
            std::cout << "Jogada invalida: " << e.what() << "\n";
            std::cout << "Tente novamente.\n";
            return false;
        }
    }



    bool isWin() override {
        // Verifica linhas, colunas e diagonais
        for (size_t x = 0; x < this->board.getSize()[0]; ++x) {
            for (size_t y = 0; y < this->board.getSize()[1]; ++y) {
                if (checkLine({x, y}, {x + 1, y}, {x + 2, y}) || // Linha horizontal
                    checkLine({x, y}, {x, y + 1}, {x, y + 2}) || // Linha vertical
                    checkLine({x, y}, {x + 1, y + 1}, {x + 2, y + 2}) || // Diagonal principal
                    checkLine({x, y}, {x + 1, y - 1}, {x + 2, y - 2})) { // Diagonal secundária
                    return true;
                    }
            }
        }
        return false;
    }

    bool isDraw() override {
        for (size_t y = 0; y < board.getSize()[1]; ++y) {
            for (size_t x = 0; x < board.getSize()[0]; ++x) {
                if (!board.get({x, y})) {
                    return false; // Há espaços vazios
                }
            }
        }
        return true;
    }
private:
    [[nodiscard]] bool checkLine(const std::array<size_t, 2> pos1, const std::array<size_t, 2> pos2, const std::array<size_t, 2> pos3) const
    {
        const auto piece1 = board.get(pos1);
        const auto piece2 = board.get(pos2);
        const auto piece3 = board.get(pos3);

        return piece1 && piece2 && piece3 &&
               piece1->getSymbol() == piece2->getSymbol() &&
               piece2->getSymbol() == piece3->getSymbol();
    }
};
