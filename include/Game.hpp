#pragma once

#include <utility>
#include <regex>

#include "Board.hpp"

class Game {
protected:
    std::string name;
    std::vector<std::string> players;
    int turn = 0;
    bool isRunning = false;
public:
    Board board;
    Game(const std::array<size_t,2> size, std::string name)
    : name(std::move(name)), board(size) {}

    virtual ~Game() = default;

    std::string getName() { return this->name; }

    virtual void initialize(const std::vector<std::string> &players) {
        this->isRunning = true;
        this->players = players;
        std::cout << "Bem-vindos ao " << this->getName() << "!\n";
        this->board.print();
    }

    void changeTurn()
    {
        const std::string temp = players[0];
        players[0] = players[1];
        players[1] = temp;
        turn = turn == 0 ? 1 : 0;
    }
    virtual bool isOver()
    {
        if (isWin()) {
            std::cout << "Jogador " << players[turn] << " venceu!\n";
            return true;
        }
        if (isDraw())
        {
            std::cout << "Empate!\n";
            return true;
        }
        return !isRunning;
    }

    virtual std::string getWinner() {
        return this->players[turn];
    }

    virtual std::string getLoser() {
        return this->players[turn == 0 ? 1 : 0];
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
    virtual bool playTurn() = 0;

    virtual bool isWin() = 0;
    virtual bool isDraw() = 0;
};

