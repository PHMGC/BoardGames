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

private:
    void printHeader(const std::string& spacing) const {
        // Espaçamento inicial para alinhar o header com os índices laterais
        std::cout << " ";
        for (int x = 0; x < this->size[0]; ++x) {
            const char letter = 'A' + x;
            std::cout << spacing << letter << spacing;
        }
        std::cout << std::endl;
    }
public:

    void print() const {
        const std::string spacing = " "; // Espaçamento fixo entre as colunas

        // Superior horizontal header
        this->printHeader(spacing);

        // Corpo do tabuleiro
        for (size_t y = 0; y < size[1]; y++) {
            // Índice da linha na lateral esquerda
            std::cout << y + 1;
            for (size_t x = 0; x < size[0]; x++) {
                if (grid[x][y] != nullptr) {
                    std::cout << spacing << grid[x][y]->getSymbol() << spacing;;
                } else {
                    // Espaço vazio para células sem peça
                    std::cout << spacing << "-" << spacing;
                }
            }
            // Índice da linha na lateral direita
            std::cout << y + 1 << std::endl;
        }

        // Inferior horizontal header
        this->printHeader(spacing);
    }

    [[nodiscard]] std::array<size_t, 2> parseInput(const std::string &input) const
    {
        // Expressão regular para validar o formato 'CN' (char e número)
        const std::regex pattern("^[a-zA-Z](1[0-9]|2[0-6]|[1-9])$");

        // Valida o formato do movimento
        if (!std::regex_match(input, pattern)) {
            throw std::invalid_argument("Formato invalido: esperado 'CN' (ex: A1 ou a1).");
        }

        std::array<size_t, 2> pos{};
        // Converte a primeira posição
        // Índice da linha
        pos[0] = toupper(input[0]) - 'A';
        // Índice da coluna (1 ou 2 dígitos)
        pos[1] = std::stoi(input.substr(1, input[2] == ' ' ? 1 : 2)) - 1;

        // Verifica se as posições estão no intervalo válido
        if (!this->isValid(pos)) {
            const std::string maxPos = std::string(1, static_cast<char>('A' + static_cast<int>(this->size[0]) - 1)) + //coluna máxima (letra)
                std::to_string(this->size[1]); // linha máxima (número)
            throw std::out_of_range(
                "Movimento fora dos limites do tabuleiro (valido: A1 a " + maxPos + ")."
            );
        }

        return pos;
    }

    [[nodiscard]] std::array<size_t, 2> getSize() const { return this->size; }

    [[nodiscard]] bool isValid(const std::array<size_t, 2> pos) const
    {
        return pos[0] < this->size[0] && pos[1] < this->size[1];
    }


    bool set(const std::array<size_t, 2> pos, std::shared_ptr<Piece> piece) {
        if (isValid(pos) && !this->grid[pos[0]][pos[1]]) {
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
        if (isValid(pos)) {
            return this->grid[pos[0]][pos[1]];
        }
        return nullptr;
    }
};
