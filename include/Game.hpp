#pragma once

#include <utility>
#include <regex>

#include "Board.hpp"

class Game {
protected:
    std::string name;
    Player currentPlayer;
public:
    Board board;
    Game(const std::array<size_t,2> size, std::string name, const Player firstPlayer = Player::One)
    : name(std::move(name)), currentPlayer(firstPlayer), board(size) {}

    virtual ~Game() = default;

    std::string getName() { return this->name; }

    void changeTurn()
    {
        this->currentPlayer = currentPlayer == Player::One ? Player::Two : Player::One;
    }
    virtual bool isOver()
    {
        if (isWin()) {
            std::cout << "Jogador " << static_cast<int>(currentPlayer) << " venceu!\n";
            return true;
        }
        if (isDraw())
        {
            std::cout << "Empate!\n";
            return true;
        }
        return false;
    }

    virtual bool parsePlace(const std::string& input, std::array<size_t, 2> &pos)
    {
        const std::regex pattern(R"(\b(\d+) (\d+)\b)");

        std::smatch matches;
        if (std::regex_match(input, matches, pattern))
        {
            pos[0] = std::stoi(matches[1].str());
            pos[1] = std::stoi(matches[2].str());

            // Verifica se os números estão dentro dos limites do tabuleiro
            if (pos[0] < this->board.getSize()[0] && pos[1] < this->board.getSize()[1])
            {
                return true;
            }
        }
        return false;
    }


    virtual bool parseMove(const std::string& input, std::array<size_t, 2> &pos1, std::array<size_t, 2> &pos2)
    {
        const std::regex pattern(R"(\b(\d+) (\d+) (\d+) (\d+)\b)");

        std::smatch matches;
        if (std::regex_match(input, matches, pattern))
        {
            pos1[0] = std::stoi(matches[1].str());
            pos1[1] = std::stoi(matches[2].str());
            pos2[0] = std::stoi(matches[3].str());
            pos2[1] = std::stoi(matches[4].str());

            // Verifica se todos os números estão dentro dos limites do tabuleiro
            if (pos1[0] < this->board.getSize()[0] &&
                pos1[1] < this->board.getSize()[1] &&
                pos2[0] < this->board.getSize()[0] &&
                pos2[1] < this->board.getSize()[1])
            {
                return true;
            }
        }
        return false;
    }


    // Pure virtual methods
    virtual void initialize() = 0;

    virtual bool playTurn() = 0;

    virtual bool isWin() = 0;
    virtual bool isDraw() = 0;
};

