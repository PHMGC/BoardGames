#pragma once

enum class Player { One = 1, Two = 2 };


class Piece {
protected:
    char symbol; // Representação visual da peça, como 'X', 'O', 'P', 'p', etc.
    Player player;
public:
    explicit Piece(const char symbol, const Player player) : symbol(symbol), player(player) {}

    [[nodiscard]] char getSymbol() const { return symbol; }
    [[nodiscard]] Player getPlayer() const { return player; }

    // Cada jogo deve implementar sua lógica de movimentação
    [[nodiscard]] virtual bool isValidMove(std::array<size_t, 2> startPos, std::array<size_t, 2> endPos) const = 0;

    virtual ~Piece() = default;
};
