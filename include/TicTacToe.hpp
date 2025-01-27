#pragma once

#include "Game.hpp"
#include "Piece.hpp"
#include <iostream>
#include <memory>
#include <array>
#include <string>

class TTTPiece final : public Piece {
public:
    explicit TTTPiece(const int turn, const std::string &player);

    [[nodiscard]] bool isValidMove(std::array<size_t, 2> startPos, std::array<size_t, 2> endPos) const override;
};

class TicTacToe final : public Game {
public:
    explicit TicTacToe();

    bool playTurn() override;
    bool isWin() override;
    bool isDraw() override;

private:
    [[nodiscard]] bool checkLine(const std::array<size_t, 2> pos1,
                                 const std::array<size_t, 2> pos2,
                                 const std::array<size_t, 2> pos3) const;
};
