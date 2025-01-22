#pragma once

#include "Game.hpp"
#include "Piece.hpp"
#include <iostream>

class ReversiPiece final : public Piece {
public:
    explicit ReversiPiece(const int turn, const std::string& player)
        : Piece(turn, player) {}

    [[nodiscard]] bool isValidMove(std::array<size_t, 2>, std::array<size_t, 2>) const override {
        return true;
    }

    void flip(const std::string &newPlayer) {
        player = newPlayer;
        symbol = symbol == 'O' ? 'X' : 'O';
    }
};

class Reversi final : public Game {
public:
    explicit Reversi() : Game({8, 8}, "Reversi") {}

    void initialize(const std::vector<std::string> &players) override {
        this->isRunning = true;
        this->players = players;
        std::cout << "Bem-vindos ao " << this->getName() << "!\n";

        const size_t centerRow = board.getSize()[0] / 2;
        const size_t centerCol = board.getSize()[1] / 2;

        board.set({centerRow - 1, centerCol - 1}, std::make_shared<ReversiPiece>(turn, players[turn]));
        board.set({centerRow, centerCol}, std::make_shared<ReversiPiece>(turn, players[turn]));
        board.set({centerRow - 1, centerCol}, std::make_shared<ReversiPiece>(turn == 0 ? 1 : 0, players[turn == 0 ? 1 : 0]));
        board.set({centerRow, centerCol - 1}, std::make_shared<ReversiPiece>(turn == 0 ? 1 : 0, players[turn == 0 ? 1 : 0]));
        board.print();
    }

    bool playTurn() override {
        if (isTurnSkipped(players[turn])) {
            std::cout << "Nao ha jogadas validas para o jogador " << players[turn] << ".\nTurno pulado!\n";
            return true;
        }

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
            const auto pos = board.parsePosInput(input);
            if (board.get(pos)) {
                std::cout << "Espaco ocupado. Tente novamente.\n";
                return false;
            }
            if (!isValidMove(pos, players[turn]))
            {
                std::cout << "Jogada invalida: jogador deve capturar pelo menos uma peca" << std::endl;
                std::cout << "Tente novamente " << std::endl;
                return false;
            }
            board.set(pos, std::make_shared<ReversiPiece>(turn == 0 ? 'X' : 'O', players[turn]));
            flipPieces(pos, players[turn]);
            return true;
        } catch (const std::exception& e) {
            std::cout << e.what();
            std::cout << "ERRO: Jogada invalida. Tente novamente.\n";
            return false;
        }
    }

    [[nodiscard]] std::vector<std::array<size_t, 2>> possiblePlays(const std::string& player) const {
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

    [[nodiscard]] bool isValidMove(const std::array<size_t, 2>& pos, const std::string& player) const {
        const auto [rows, cols] = board.getSize();
        const std::vector<std::array<int, 2>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
        };
        const std::string opponent = players[turn == 0 ? 1 : 0];

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

    [[nodiscard]] bool isTurnSkipped(const std::string &player) const {
        return possiblePlays(player).empty();
    }

    void flipPieces(const std::array<size_t, 2>& pos, const std::string &player) const {
        const auto [rows, cols] = board.getSize();
        const std::vector<std::array<int, 2>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
        };
        const std::string opponent = players[turn == 0 ? 1 : 0];

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
                    if (piece) piece->flip(players[turn]);
                }
            }
        }
    }

    bool isDraw() override {
        if (isTurnSkipped(players[turn]) && isTurnSkipped(players[turn == 0 ? 1 : 0])) {
            const int playerOneCount = playerPieces(players[turn]);
            const int playerTwoCount = playerPieces(players[turn == 0 ? 1 : 0]);

            return playerOneCount == playerTwoCount;
        }
        return false;
    }

    bool isWin() override {
        if (isTurnSkipped(players[turn]) && isTurnSkipped(players[turn == 0 ? 1 : 0])) {
            const int playerOneCount = playerPieces(players[turn]);
            const int playerTwoCount = playerPieces(players[turn == 0 ? 1 : 0]);

            return playerOneCount != playerTwoCount;
        }
        return false;
    }

    std::string getWinner() override {
        if (isWin()){
            const int playerOneCount = playerPieces(players[turn]);
            const int playerTwoCount = playerPieces(players[turn == 0 ? 1 : 0]);
            return playerOneCount > playerTwoCount ? players[turn] : players[turn == 0 ? 1 : 0];
        }
        throw std::invalid_argument("There is no winner");
    }

    bool isOver() override {
        if (isWin()) {
            std::cout << "Jogador " << getWinner() << " venceu!\n";
            return true;
        }
        if (isDraw()){
            std::cout << "Empate!\n";
            return true;
        }

        return !isRunning;
    }

private:
    [[nodiscard]] int playerPieces(const std::string &player) const {
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
