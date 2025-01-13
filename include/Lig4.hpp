#pragma once

#include "Game.hpp"
#include "Piece.hpp"
#include <iostream>
#include <limits>

class Lig4Piece final : public Piece {
public:
    explicit Lig4Piece(const Player player)
        : Piece(player == Player::One ? 'X' : 'O', player) {}

    [[nodiscard]] bool isValidMove(std::array<size_t, 2> startPos , std::array<size_t, 2> endPos) const override {
        return true;
    }
};

class Lig4 final : public Game {
public:
    Lig4() : Game({6, 7}, "Lig4") {}

    void initialize() override {
        std::cout << "Bem-vindo ao Lig4!\n";
        this->board.print();
    }

    bool playTurn() override {
        std::cout << "Jogador " << static_cast<int>(currentPlayer) << ", escolha sua jogada (coluna): ";
        char input;
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        try {
            const size_t col = this->board.parseColInput(input);
            this->placePieceOnCol(col);
            return true;
        } catch (std::exception& e) {
            std::cout << "Jogada invalida: " << e.what() << "\n";
            std::cout << "Tente novamente.\n";
            return false;
        }
    }

    void placePieceOnCol(const size_t col) {
        for (size_t y = this->board.getSize()[1]; y-- > 0;) { // Correção para evitar underflow
            if (!board.get({col, y})) {
                board.set({col, y}, std::make_shared<Lig4Piece>(currentPlayer));
                return;
            }
        }
        throw std::invalid_argument("Coluna cheia. Escolha outra coluna.");
    }

    bool isWin() override {
        // Verifica linhas, colunas e diagonais
        for (size_t x = 0; x < this->board.getSize()[0]; ++x) {
            for (size_t y = 0; y < this->board.getSize()[1]; ++y) {
                if (checkLine({x, y}, {x + 1, y}, {x + 2, y}, {x + 3, y}) || // Linha horizontal
                    checkLine({x, y}, {x, y + 1}, {x, y + 2}, {x, y + 3}) || // Linha vertical
                    checkLine({x, y}, {x + 1, y + 1}, {x + 2, y + 2}, {x + 3, y + 3}) || // Diagonal principal
                    checkLine({x, y}, {x + 1, y - 1}, {x + 2, y - 2}, {x + 3, y - 3})) { // Diagonal secundária
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
    [[nodiscard]] bool checkLine(const std::array<size_t, 2> pos1, const std::array<size_t, 2> pos2, const std::array<size_t, 2> pos3, const std::array<size_t, 2> pos4) const {
        // Verifica se todas as posições têm peças e se elas pertencem ao mesmo jogador
        const auto piece1 = board.get(pos1);
        const auto piece2 = board.get(pos2);
        const auto piece3 = board.get(pos3);
        const auto piece4 = board.get(pos4);

        return piece1 && piece2 && piece3 && piece4 &&
               piece1->getSymbol() == piece2->getSymbol() &&
               piece2->getSymbol() == piece3->getSymbol() &&
               piece3->getSymbol() == piece4->getSymbol();
    }
};
