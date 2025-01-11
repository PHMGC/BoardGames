#pragma once

#include "Game.hpp"
#include "Piece.hpp"
#include <iostream>

class TTTPiece final : public Piece {
public:
    explicit TTTPiece(const Player player)
        : Piece(player == Player::One ? 'X' : 'O', player) {}

    [[nodiscard]] bool isValidMove(std::array<size_t, 2> startPos , std::array<size_t, 2> endPos) const override {
        return true;
    }
};

class TicTacToe final : public Game {
public:
    TicTacToe() : Game({3, 3}, "TicTacToe") {}

    void initialize() override {
        std::cout << "Bem-vindo ao Jogo da Velha!\n";
        this->board.print();
    }

    bool playTurn() override {
        std::cout << "Jogador " << static_cast<int>(currentPlayer) << ", escolha sua jogada (linha e coluna): ";
        std::string input;
        std::getline(std::cin, input);
        try
        {
            const std::array<size_t, 2> pos = this->board.parseInput(input);
            if (board.get({pos[0], pos[1]})) {
                std::cout << "Espaco ocupado. Tente novamente.\n";
                return false;
            }
            return true;

        } catch (std::exception& e)
        {
            std::cout << "Jogada invalida: " << e.what() << std::endl;
            std::cout << "Tente novamente.\n";
            return false;
        }
    }

    bool isWin() override {
        // Verifica linhas, colunas
        for (size_t i = 0; i < 3; ++i) {
            if (checkLine({i, 0}, {i, 1}, {i, 2}) || checkLine({0, i}, {1, i}, {2, i})) {
                return true;
            }
        }
        // Verifica diagonais
        return checkLine({0, 0}, {1, 1}, {2, 2}) || checkLine({0, 2}, {1, 1}, {2, 0});
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
