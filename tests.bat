@echo off
set SRC_DIR=src
set OBJ_DIR=obj
set BIN_DIR=bin
set TESTS_DIR=tests
set INCLUDE_DIR=include

:: Criar diretórios se não existirem
if not exist %OBJ_DIR% mkdir %OBJ_DIR%
if not exist %BIN_DIR% mkdir %BIN_DIR%

:: Compilar arquivos fonte para objetos
echo Compilando arquivos...
g++ -std=c++20 -c %SRC_DIR%\Board.cpp -I%INCLUDE_DIR% -o %OBJ_DIR%\Board.o
g++ -std=c++20 -c %SRC_DIR%\Game.cpp -I%INCLUDE_DIR% -o %OBJ_DIR%\Game.o
g++ -std=c++20 -c %SRC_DIR%\Piece.cpp -I%INCLUDE_DIR% -o %OBJ_DIR%\Piece.o
g++ -std=c++20 -c %SRC_DIR%\Lig4.cpp -I%INCLUDE_DIR% -o %OBJ_DIR%\Lig4.o
g++ -std=c++20 -c %SRC_DIR%\Reversi.cpp -I%INCLUDE_DIR% -o %OBJ_DIR%\Reversi.o
g++ -std=c++20 -c %SRC_DIR%\TicTacToe.cpp -I%INCLUDE_DIR% -o %OBJ_DIR%\TicTacToe.o
g++ -std=c++20 -c %SRC_DIR%\SaveManager.cpp -I%INCLUDE_DIR% -o %OBJ_DIR%\SaveManager.o
g++ -std=c++20 -c %SRC_DIR%\GameManager.cpp -I%INCLUDE_DIR% -o %OBJ_DIR%\GameManager.o

:: Linkar os objetos para gerar o executável de testes
echo Linkando...
g++ -g %TESTS_DIR%\tests.cpp %OBJ_DIR%\*.o -I%INCLUDE_DIR% -o %BIN_DIR%\tests.exe

:: Mensagem de sucesso
echo Compilação concluída! Executável criado em %BIN_DIR%\tests.exe
