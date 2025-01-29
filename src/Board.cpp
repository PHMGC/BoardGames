#include "Board.hpp"

Board::Board(const std::array<size_t, 2> size) : size(size) {
    this->grid.resize(size[0], std::vector<std::shared_ptr<Piece>>(size[1], nullptr));
}

void Board::reset() {
    for (auto row = 0; row < size[0]; row++) {
        for (auto col = 0; col < size[1]; col++) {
            this->grid[row][col] = nullptr;
        }
    }
}

void Board::printHeader(const std::string &spacing) const {
    std::cout << " ";
    for (int x = 0; x < this->size[0]; ++x) {
        const char letter = 'A' + x;
        std::cout << spacing << letter << spacing;
    }
    std::cout << std::endl;
}

void Board::print() const {
    const std::string spacing = " ";

    this->printHeader(spacing);

    for (size_t y = 0; y < size[1]; y++) {
        std::cout << y + 1;
        for (size_t x = 0; x < size[0]; x++) {
            if (grid[x][y] != nullptr) {
                std::cout << spacing << grid[x][y]->getSymbol() << spacing;
            } else {
                std::cout << spacing << "-" << spacing;
            }
        }
        std::cout << y + 1 << std::endl;
    }

    this->printHeader(spacing);
}

size_t Board::parseColInput(const char input) const {
    if (!std::isalnum(input)) {
        throw std::invalid_argument("Formato invalido: esperado 'C' (ex: A ou a).");
    }
    size_t col = toupper(input) - 'A';
    if (col >= size[0]) {
        throw std::out_of_range("Movimento fora dos limites do tabuleiro.");
    }
    return col;
}

std::array<size_t, 2> Board::parsePosInput(const std::string &input) const {
    const std::regex pattern("^[a-zA-Z](1[0-9]|2[0-6]|[1-9])$");

    if (!std::regex_match(input, pattern)) {
        throw std::invalid_argument("ERRO: Movimento incorreto.");
    }

    std::array<size_t, 2> pos{};
    pos[0] = toupper(input[0]) - 'A';
    pos[1] = std::stoi(input.substr(1, input.size() - 1)) - 1;

    if (!this->isValid(pos)) {
        throw std::out_of_range("Movimento fora dos limites do tabuleiro.");
    }

    return pos;
}

std::array<size_t, 2> Board::getSize() const {
    return this->size;
}

bool Board::isValid(const std::array<size_t, 2> pos) const {
    return pos[0] < this->size[0] && pos[1] < this->size[1];
}

bool Board::move(const std::array<size_t, 2> startPos, const std::array<size_t, 2> endPos, const bool checkCollision) {
    if (startPos < this->size && endPos < this->size &&
        this->grid[startPos[0]][startPos[1]] &&
        (!checkCollision || !this->grid[endPos[0]][endPos[1]])) {
        if (const auto piece = this->grid[startPos[0]][startPos[1]]; piece->isValidMove(startPos, endPos)) {
            if (checkCollision && this->grid[endPos[0]][endPos[1]]) {
                this->grid[endPos[0]][endPos[1]].reset();
            }
            this->grid[endPos[0]][endPos[1]] = piece;
            this->grid[startPos[0]][startPos[1]] = nullptr;
            return true;
        }
    }
    return false;
}

std::shared_ptr<Piece> Board::get(const std::array<size_t, 2> pos) const {
    if (isValid(pos)) {
        return this->grid[pos[0]][pos[1]];
    }
    return nullptr;
}

void Board::set(const std::array<size_t, 2> pos, std::shared_ptr<Piece> piece) {
    if (!isValid(pos)) {
        throw std::invalid_argument("Posição fora dos limites do tabuleiro.");
    }
    if (this->grid[pos[0]][pos[1]] != nullptr) {
        throw std::invalid_argument("Tentativa de sobrescrever uma posição ocupada.");
    }
    this->grid[pos[0]][pos[1]] = std::move(piece);
}
