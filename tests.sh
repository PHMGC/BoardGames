#!/bin/bash

# Diretórios
SRC_DIR="src"
OBJ_DIR="obj"
BIN_DIR="bin"
TESTS_DIR="tests"
INCLUDE_DIR="include"

# Criar diretórios se não existirem
mkdir -p $OBJ_DIR
mkdir -p $BIN_DIR

# Compilar arquivos fonte para objetos
echo "Compilando arquivos..."
g++ -std=c++20 -c $SRC_DIR/Board.cpp -I$INCLUDE_DIR -o $OBJ_DIR/Board.o
g++ -std=c++20 -c $SRC_DIR/Game.cpp -I$INCLUDE_DIR -o $OBJ_DIR/Game.o
g++ -std=c++20 -c $SRC_DIR/Piece.cpp -I$INCLUDE_DIR -o $OBJ_DIR/Piece.o
g++ -std=c++20 -c $SRC_DIR/Lig4.cpp -I$INCLUDE_DIR -o $OBJ_DIR/Lig4.o
g++ -std=c++20 -c $SRC_DIR/Reversi.cpp -I$INCLUDE_DIR -o $OBJ_DIR/Reversi.o
g++ -std=c++20 -c $SRC_DIR/TicTacToe.cpp -I$INCLUDE_DIR -o $OBJ_DIR/TicTacToe.o
g++ -std=c++20 -c $SRC_DIR/SaveManager.cpp -I$INCLUDE_DIR -o $OBJ_DIR/SaveManager.o
g++ -std=c++20 -c $SRC_DIR/GameManager.cpp -I$INCLUDE_DIR -o $OBJ_DIR/GameManager.o

# Linkar os objetos para gerar o executável de testes
echo "Linkando..."
g++ -g $TESTS_DIR/tests.cpp $OBJ_DIR/*.o -I$INCLUDE_DIR -o $BIN_DIR/tests

# Mensagem de sucesso
echo "Compilação concluída! Executável criado em $BIN_DIR/tests"
