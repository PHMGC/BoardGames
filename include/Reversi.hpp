#pragma once

#include "Game.hpp"
#include "Piece.hpp"
#include <iostream>

class ReversiPiece final : public Piece {
public:
    explicit ReversiPiece(const Player player)
        : Piece(player == Player::One ? 'X' : 'O', player) {}

    [[nodiscard]] bool isValidMove(std::array<size_t, 2>, std::array<size_t, 2>) const override {
        return true;
    }

    void flip() {
        player = (player == Player::One) ? Player::Two : Player::One;
        symbol = (player == Player::One) ? 'X' : 'O';
    }
};

class Reversi final : public Game {
public:
    Reversi() : Game({8, 8}, "Reversi") {}

    void initialize() override {
        std::cout << "Bem-vindo ao Reversi!\n";

        const size_t centerRow = board.getSize()[0] / 2;
        const size_t centerCol = board.getSize()[1] / 2;
        const Player opponent = (currentPlayer == Player::One) ? Player::Two : Player::One;

        board.set({centerRow - 1, centerCol - 1}, std::make_shared<ReversiPiece>(currentPlayer));
        board.set({centerRow, centerCol}, std::make_shared<ReversiPiece>(currentPlayer));
        board.set({centerRow - 1, centerCol}, std::make_shared<ReversiPiece>(opponent));
        board.set({centerRow, centerCol - 1}, std::make_shared<ReversiPiece>(opponent));
        board.print();
    }

    bool playTurn() override {
        if (isTurnSkipped(currentPlayer)) {
            std::cout << "Nao ha jogadas validas para o jogador " << static_cast<int>(currentPlayer) << ".\nTurno pulado!\n";
            return true;
        }

        std::cout << "Jogador " << static_cast<int>(currentPlayer) << ", escolha sua jogada (linha e coluna): ";
        std::string input;
        std::getline(std::cin, input);

        try {
            const auto pos = board.parsePosInput(input);
            if (board.get(pos)) {
                std::cout << "Espaco ocupado. Tente novamente.\n";
                return false;
            }
            if (!isValidMove(pos, currentPlayer))
            {
                std::cout << "Jogada invalida: jogador deve capturar pelo menos uma peca" << std::endl;
                std::cout << "Tente novamente " << std::endl;
                return false;
            }
            board.set(pos, std::make_shared<ReversiPiece>(currentPlayer));
            flipPieces(pos, currentPlayer);
            return true;
        } catch (const std::exception& e) {
            std::cout << "Jogada invalida: " << e.what() << "\nTente novamente.\n";
            return false;
        }
    }

    [[nodiscard]] bool isWin() override { throw std::runtime_error("Not implemented"); }
    [[nodiscard]] bool isDraw() override { throw std::runtime_error("Not implemented"); }

    [[nodiscard]] std::vector<std::array<size_t, 2>> possiblePlays(Player player) const {
        std::vector<std::array<size_t, 2>> plays;
        const auto [rows, cols] = board.getSize();

        for (size_t x = 0; x < rows; ++x) {
            for (size_t y = 0; y < cols; ++y) {
                if (!board.get({x, y}) && isValidMove({x, y}, player)) {
                    plays.push_back({x, y});
                }
            }
        }
        return plays;
    }

    [[nodiscard]] bool isValidMove(const std::array<size_t, 2>& pos, Player player) const {
        const auto [rows, cols] = board.getSize();
        const std::vector<std::array<int, 2>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
        };
        const Player opponent = (player == Player::One) ? Player::Two : Player::One;

        for (const auto& dir : directions) {
            size_t cx = pos[0] + dir[0], cy = pos[1] + dir[1];
            bool hasOpponent = false;

            while (cx < rows && cy < cols && board.get({cx, cy}) && board.get({cx, cy})->getPlayer() == opponent) {
                hasOpponent = true;
                cx += dir[0];
                cy += dir[1];
            }

            if (hasOpponent && cx < rows && cy < cols && board.get({cx, cy}) && board.get({cx, cy})->getPlayer() == player) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] bool isTurnSkipped(const Player player) const {
        return possiblePlays(player).empty();
    }

    void flipPieces(const std::array<size_t, 2>& pos, const Player player) const {
        const auto [rows, cols] = board.getSize();
        const std::vector<std::array<int, 2>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
        };
        const Player opponent = (player == Player::One) ? Player::Two : Player::One;

        for (const auto& dir : directions) {
            std::vector<std::array<size_t, 2>> toFlip;
            size_t cx = pos[0] + dir[0], cy = pos[1] + dir[1];

            while (cx < rows && cy < cols && board.get({cx, cy}) && board.get({cx, cy})->getPlayer() == opponent) {
                toFlip.push_back({cx, cy});
                cx += dir[0];
                cy += dir[1];
            }

            if (cx < rows && cy < cols && board.get({cx, cy}) && board.get({cx, cy})->getPlayer() == player) {
                for (const auto& p : toFlip) {
                    auto piece = std::dynamic_pointer_cast<ReversiPiece>(board.get(p));
                    if (piece) piece->flip();
                }
            }
        }
    }

    bool isOver() override {
        if (isTurnSkipped(currentPlayer) && isTurnSkipped((currentPlayer == Player::One) ? Player::Two : Player::One)) {
            const int playerOneCount = playerPieces(Player::One);
            const int playerTwoCount = playerPieces(Player::Two);

            if (playerOneCount != playerTwoCount) {
                std::cout << "Jogador " << ((playerOneCount > playerTwoCount) ? "1" : "2") << " venceu!\n";
            } else {
                std::cout << "Empate!\n";
            }
            return true;
        }
        return false;
    }

private:
    [[nodiscard]] int playerPieces(Player player) const {
        int count = 0;
        const auto [rows, cols] = board.getSize();

        for (size_t x = 0; x < rows; ++x) {
            for (size_t y = 0; y < cols; ++y) {
                if (board.get({x, y}) && board.get({x, y})->getPlayer() == player) {
                    ++count;
                }
            }
        }
        return count;
    }
};
