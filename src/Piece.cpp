#include "piece.hpp"

// Construtor
Piece::Piece(int turn, std::string player)
    : symbol(turn == 0 ? 'X' : 'O'), player(std::move(player)) {}

// Métodos de acesso
char Piece::getSymbol() const {
    return symbol;
}

std::string Piece::getPlayer() const {
    return player;
}

// Destrutor virtual
Piece::~Piece() = default;
