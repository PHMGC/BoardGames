#include "Game.hpp"

Game::Game(const std::array<size_t, 2> size, std::string name)
    : name(std::move(name)), board(size) {}

std::string Game::getName() {
    return this->name;
}

void Game::initialize(const std::vector<std::string>& players) {
    this->isRunning = true;
    this->players = players;
    std::cout << "Bem-vindos ao " << this->getName() << "!\n";
    this->board.print();
}

void Game::changeTurn() {
    turn = turn == 0 ? 1 : 0;
}

bool Game::isOver() {
    if (isWin()) {
        std::cout << "Jogador " << players[turn] << " venceu!\n";
        return true;
    }
    if (isDraw()) {
        std::cout << "Empate!\n";
        return true;
    }
    return !isRunning;
}

std::string Game::getWinner() {
    return this->players[turn];
}

std::string Game::getLoser() {
    return this->players[turn == 0 ? 1 : 0];
}

bool Game::parsePlace(const std::string& input, std::array<size_t, 2>& pos) {
    const std::regex pattern(R"(\b(\d+) (\d+)\b)");
    std::smatch matches;
    if (std::regex_match(input, matches, pattern)) {
        pos[0] = std::stoi(matches[1].str());
        pos[1] = std::stoi(matches[2].str());

        if (pos[0] < this->board.getSize()[0] && pos[1] < this->board.getSize()[1]) {
            return true;
        }
    }
    return false;
}

bool Game::parseMove(const std::string& input, std::array<size_t, 2>& pos1, std::array<size_t, 2>& pos2) {
    const std::regex pattern(R"(\b(\d+) (\d+) (\d+) (\d+)\b)");
    std::smatch matches;
    if (std::regex_match(input, matches, pattern)) {
        pos1[0] = std::stoi(matches[1].str());
        pos1[1] = std::stoi(matches[2].str());
        pos2[0] = std::stoi(matches[3].str());
        pos2[1] = std::stoi(matches[4].str());

        if (pos1[0] < this->board.getSize()[0] &&
            pos1[1] < this->board.getSize()[1] &&
            pos2[0] < this->board.getSize()[0] &&
            pos2[1] < this->board.getSize()[1]) {
            return true;
            }
    }
    return false;
}
