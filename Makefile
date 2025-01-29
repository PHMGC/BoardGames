# Nome do projeto e compilador
PROJECT = BoardGames
TEST_PROJECT = tests
CXX = g++
CXXFLAGS = -Wall -Wextra -g -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TESTS_DIR = tests

# Lista de arquivos fonte do projeto (sem incluir main.cpp)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
SRCS_NO_MAIN = $(filter-out $(SRC_DIR)/main.cpp, $(SRCS)) # Exclui main.cpp dos testes
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_NO_MAIN = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS_NO_MAIN)) # Objetos sem main.o

# Arquivo de testes
TEST_SRCS = $(TESTS_DIR)/tests.cpp
TEST_OBJS = $(OBJ_DIR)/tests.o

# Regra padrão: compilar tudo
all: $(BIN_DIR)/$(PROJECT) $(BIN_DIR)/$(TEST_PROJECT)

# Compilar o jogo principal
$(BIN_DIR)/$(PROJECT): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilar os testes (sem incluir main.o)
$(BIN_DIR)/$(TEST_PROJECT): $(TEST_OBJS) $(OBJS_NO_MAIN) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilar arquivos do projeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar arquivos de teste
$(OBJ_DIR)/tests.o: $(TESTS_DIR)/tests.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criando diretórios, se não existirem
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpeza dos arquivos compilados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean run-tests
