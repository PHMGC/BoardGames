#pragma once

#include <utility>

class Piece {
protected:
    char symbol; // Representação visual da peça, como 'X', 'O', 'P', 'p', etc.
    std::string player;
public:
    explicit Piece(const int turn, std::string  player) : symbol(turn == 0 ? 'X' : 'O'), player(std::move(player)) {}

    [[nodiscard]] char getSymbol() const { return symbol; }
    [[nodiscard]] std::string getPlayer() const { return player; }

    // Cada jogo deve implementar sua lógica de movimentação
    [[nodiscard]] virtual bool isValidMove(std::array<size_t, 2> startPos, std::array<size_t, 2> endPos) const = 0;

    virtual ~Piece() = default;
};
