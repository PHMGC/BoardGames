#pragma once

#include "Game.hpp"
#include "Piece.hpp"
#include <iostream>

class ReversiPiece final : public Piece {
public:
    explicit ReversiPiece(const Player player)
        : Piece(player == Player::One ? 'X' : 'O', player) {}

    [[nodiscard]] bool isValidMove(std::array<size_t, 2> startPos , std::array<size_t, 2> endPos) const override {
        return true;
    }
};

class Reversi final : public Game {
public:
    Reversi() : Game({3, 3}, "Reversi") {}

    void initialize() override {
        std::cout << "Bem-vindo ao Jogo da Velha!\n";
        this->board.print();
    }

    bool playTurn() override {
        std::cout << "Jogador " << static_cast<int>(currentPlayer) << ", escolha sua jogada (linha e coluna): ";
        std::string input;
        std::getline(std::cin, input);
        try {
            const std::array<size_t, 2> pos = this->board.parsePosInput(input);
            if (board.get(pos)) {
                std::cout << "Espaco ocupado. Tente novamente.\n";
                return false;
            }
            board.set(pos, std::make_shared<ReversiPiece>(currentPlayer));
            return true;
        } catch (std::exception& e) {
            std::cout << "Jogada invalida: " << e.what() << "\n";
            std::cout << "Tente novamente.\n";
            return false;
        }
    }


    bool isWin() override {
        throw std::runtime_error("Not implemented");
    }

    bool isDraw() override {
        throw std::runtime_error("Not implemented");
    }

    std::vector<std::array<size_t, 2>> possiblePlays(Player player) {
        std::vector<std::array<size_t, 2>> possiblePlays;
        // checar APENAS os movimentos em que o jogador consegue capturar PELO MENOS UMA peça do inimigo
        return possiblePlays;
    }

    int playerPieces(Player player) {
        int playerPieces = 0;
        for (size_t x = 0; x < this->board.getSize()[0]; x++) {
            for (size_t y = 0; y < this->board.getSize()[1]; y++) {
                if (this->board.get({x, y})->getPlayer() == player) {
                    playerPieces++;
                }
            }
        }
      return playerPieces;
    }

    bool isOver() override {
        int curPlayerPieces = this->playerPieces(currentPlayer);
        Player otherPlayer = this->currentPlayer == Player::One ? Player::One : Player::Two;
        int curOtherPlayerPieces = this->playerPieces(otherPlayer);
	    if (possiblePlays(this->currentPlayer).empty()) {
		    if (possiblePlays(otherPlayer).empty()) {
                if (curPlayerPieces > curOtherPlayerPieces) {
                    std::cout << "Jogador " << curPlayerPieces << "venceu!\n";
                }
                else if (curOtherPlayerPieces > curPlayerPieces) {
                    std::cout << "Jogador " << curOtherPlayerPieces << "venceu!\n";
                }
                else{
                  std::cout << "Empate!\n";
                }

			    return true;
		    }
	    }
	    return false;
    }

};
