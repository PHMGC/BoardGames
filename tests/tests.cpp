#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "TicTacToe.hpp"
#include "GameManager.hpp"
#include "SaveManager.hpp"

#include <memory>

// Testes para Board
TEST_CASE("Testando Board") {
    Board board({3, 3});
    CHECK(board.getSize()[0] == 3);
    CHECK(board.getSize()[1] == 3);
    board.reset();
    CHECK(board.get({0, 0}) == nullptr);
}

// Testes para SaveManager (Cadastro de Jogadores)
TEST_CASE("Testando Cadastro de Jogadores") {
    SaveManager saveManager({"TicTacToe", "Lig4", "Reversi"}, "test_db.csv");

    CHECK_THROWS_AS(saveManager.setPlayer("!Invalid", "Alice"), std::invalid_argument);
    CHECK_THROWS_AS(saveManager.setPlayer("Alice", "!Invalid"), std::invalid_argument);

    if(!saveManager.isPlayer("Alice")){
        saveManager.setPlayer("Alice", "Alice Silva");
    }
    CHECK_NOTHROW(saveManager.getPlayer("Alice"));

    CHECK_THROWS_AS(saveManager.setPlayer("Alice", "Outra Alice"), std::invalid_argument);
    CHECK(saveManager.isPlayer("Alice"));

    saveManager.removePlayer("Alice");
    CHECK_THROWS_AS(saveManager.getPlayer("Alice"), std::invalid_argument);
    CHECK_FALSE(saveManager.isPlayer("Alice"));

    saveManager.setPlayer("Alice", "Alice Silva");
    CHECK_NOTHROW(saveManager.getPlayer("Alice"));
    if(!saveManager.isPlayer("Bob")){
        saveManager.setPlayer("Bob", "Bob Silva");
    }
    CHECK_NOTHROW(saveManager.getPlayer("Bob"));
}

// Testes para TicTacToe
TEST_CASE("Testando TicTacToe") {
    TicTacToe game;
    game.initialize({"Alice", "Bob"});
    CHECK(game.getName() == "Jogo da Velha");
    CHECK(game.isDraw() == false);

    // Simulando jogadas válidas
    game.board.set({0, 0}, std::make_shared<TTTPiece>(0, "Alice"));
    CHECK(game.board.get({0, 0})->getPlayer() == "Alice");

    game.board.set({1, 1}, std::make_shared<TTTPiece>(1, "Bob"));
    CHECK(game.board.get({1, 1})->getPlayer() == "Bob");

    game.board.set({0, 1}, std::make_shared<TTTPiece>(0, "Alice"));
    game.board.set({0, 2}, std::make_shared<TTTPiece>(0, "Alice"));
    CHECK(game.isWin() == true); // Alice vence
}

