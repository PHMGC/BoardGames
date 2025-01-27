#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/TicTacToe.hpp"

// va para o diretório raiz e execute os comandos:
// primeiro: transformar o TicTacToe.hpp em codigo .o
// g++ -c src/TicTacToe.cpp -Iinclude -o obj/TicTacToe.o
// segundo: 
// g++ -g -Wall tests/testes.cpp obj/TicTacToe.o -Iinclude -o tests/TesteTicTacToe

TEST_CASE("Teste Inicialização do Jogo da Velha") {
    TicTacToe ttt;

    CHECK(ttt.getName() == "Jogo da Velha");
    CHECK(ttt.board.getSize() == std::array<size_t, 2>{3, 3});
}

TEST_CASE("Teste Jogadas Válidas e Inválidas no Jogo da Velha") {
    TicTacToe ttt;
    ttt.initialize({"Jogador1", "Jogador2"});

    SUBCASE("Jogada válida") {
        CHECK_NOTHROW(ttt.board.set({0, 0}, std::make_shared<TTTPiece>(0, "Jogador1")));
        CHECK(ttt.board.get({0, 0}) != nullptr); // Verifica que a posição foi ocupada
    }

    SUBCASE("Jogada em espaço ocupado") {
        ttt.board.set({1, 1}, std::make_shared<TTTPiece>(1, "Jogador2"));
        CHECK(ttt.board.get({1, 1}) != nullptr); // Verifica que a posição está ocupada
        CHECK_THROWS(ttt.board.set({1, 1}, std::make_shared<TTTPiece>(0, "Jogador1"))); // Espaço ocupado
    }

    SUBCASE("Jogada inválida (fora do tabuleiro)") {
        CHECK_THROWS_AS(ttt.board.set({3, 3}, std::make_shared<TTTPiece>(0, "Jogador1")), std::out_of_range);
    }
}

TEST_CASE("Teste Condições de Vitória no Jogo da Velha") {
    TicTacToe ttt;
    ttt.initialize({"Jogador1", "Jogador2"});

    SUBCASE("Vitória em uma linha horizontal") {
        ttt.board.set({0, 0}, std::make_shared<TTTPiece>(0, "Jogador1"));
        ttt.board.set({1, 0}, std::make_shared<TTTPiece>(0, "Jogador1"));
        ttt.board.set({2, 0}, std::make_shared<TTTPiece>(0, "Jogador1"));

        CHECK(ttt.isWin() == true);
    }

    SUBCASE("Vitória em uma linha vertical") {
        ttt.board.set({0, 0}, std::make_shared<TTTPiece>(0, "Jogador1"));
        ttt.board.set({0, 1}, std::make_shared<TTTPiece>(0, "Jogador1"));
        ttt.board.set({0, 2}, std::make_shared<TTTPiece>(0, "Jogador1"));

        CHECK(ttt.isWin() == true);
    }

    SUBCASE("Vitória em uma diagonal") {
        ttt.board.set({0, 0}, std::make_shared<TTTPiece>(0, "Jogador1"));
        ttt.board.set({1, 1}, std::make_shared<TTTPiece>(0, "Jogador1"));
        ttt.board.set({2, 2}, std::make_shared<TTTPiece>(0, "Jogador1"));

        CHECK(ttt.isWin() == true);
    }

    SUBCASE("Sem vitória") {
        ttt.board.set({0, 0}, std::make_shared<TTTPiece>(0, "Jogador1"));
        ttt.board.set({1, 0}, std::make_shared<TTTPiece>(1, "Jogador2"));
        ttt.board.set({2, 0}, std::make_shared<TTTPiece>(0, "Jogador1"));

        CHECK(ttt.isWin() == false);
    }
}

TEST_CASE("Teste Empate no Jogo da Velha") {
    TicTacToe ttt;
    ttt.initialize({"Jogador1", "Jogador2"});

    // Simula um tabuleiro cheio sem vencedores
    ttt.board.set({0, 0}, std::make_shared<TTTPiece>(0, "Jogador1"));
    ttt.board.set({0, 1}, std::make_shared<TTTPiece>(1, "Jogador2"));
    ttt.board.set({0, 2}, std::make_shared<TTTPiece>(0, "Jogador1"));
    ttt.board.set({1, 0}, std::make_shared<TTTPiece>(1, "Jogador2"));
    ttt.board.set({1, 1}, std::make_shared<TTTPiece>(0, "Jogador1"));
    ttt.board.set({1, 2}, std::make_shared<TTTPiece>(1, "Jogador2"));
    ttt.board.set({2, 0}, std::make_shared<TTTPiece>(0, "Jogador1"));
    ttt.board.set({2, 1}, std::make_shared<TTTPiece>(1, "Jogador2"));
    ttt.board.set({2, 2}, std::make_shared<TTTPiece>(0, "Jogador1"));

    CHECK(ttt.isDraw() == true);
    CHECK(ttt.isWin() == false);
}

TEST_CASE("Teste Turnos no Jogo da Velha") {
    TicTacToe ttt;
    ttt.initialize({"Jogador1", "Jogador2"});

    // Simula dois turnos
    CHECK(ttt.playTurn() == false); // Jogada inicial inválida (sem entrada de usuário simulada)
}
