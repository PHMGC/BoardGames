#pragma once

#include <array>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>

#include "Piece.hpp"

class Board {
    std::array<size_t, 2> size;
    std::vector<std::vector<std::shared_ptr<Piece>>> grid;
public:
    explicit Board(const std::array<size_t, 2> size) : size(size) {
        this->grid.resize(size[0], std::vector<std::shared_ptr<Piece>>(size[1], nullptr));
    }


    void print() const {
        for (size_t y = 0; y < size[1]; y++) {
            for (size_t x = 0; x < size[0]; x++) {
                if (x > 0) std::cout << " ";
                if (grid[x][y] != nullptr) {
                    std::cout << grid[x][y]->getSymbol();
                } else {
                    std::cout << ".";
                }
            }
            std::cout << std::endl;
        }
    }

    [[nodiscard]] std::array<size_t, 2> getSize() const
    {
        return this->size;
    }


    bool set(const std::array<size_t, 2> pos, std::shared_ptr<Piece> piece) {
        if (pos[0] < size[0] && pos[1] < size[1] && !this->grid[pos[0]][pos[1]]) {
            this->grid[pos[0]][pos[1]] = std::move(piece);
            return true;
        }
        return false;
    }

    bool move(const std::array<size_t, 2> startPos, const std::array<size_t, 2> endPos, const bool checkCollision = true) {
        if (startPos < this->size && endPos < this->size &&
            this->grid[startPos[0]][startPos[1]] &&
            (!checkCollision || !this->grid[endPos[0]][endPos[1]])) {
            if (const auto piece = this->grid[startPos[0]][startPos[1]]; piece->isValidMove(startPos, endPos)) {
                if (checkCollision && this->grid[endPos[0]][endPos[1]])
                {
                    this->grid[endPos[0]][endPos[1]].reset();
                }
                this->grid[endPos[0]][endPos[1]] = piece;
                this->grid[startPos[0]][startPos[1]] = nullptr;
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] std::shared_ptr<Piece> get(const std::array<size_t, 2> pos) const {
        if (pos[0] < size[0] && pos[1] < size[1]) {
            return this->grid[pos[0]][pos[1]];
        }
        return nullptr;
    }
};
