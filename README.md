# **BoardGames 🎲♟️🧩**

Este repositório contém o trabalho final da disciplina **Programação e Desenvolvimento de Software 2** (PDS2) da **Universidade Federal de Minas Gerais (UFMG)**. O projeto consiste na implementação de uma coleção de jogos de tabuleiro, desenvolvidos em **C++**.

---

## **🕹️ Jogos Implementados**

### 1. **Reversi**
- **Descrição**: Também conhecido como Othello, é um jogo estratégico onde dois jogadores disputam para dominar o tabuleiro com peças de sua cor.
- **Regras principais**:
    - As peças podem ser viradas ao capturar as do oponente.
    - O jogador com mais peças no final vence.

### 2. **Tic-Tac-Toe (Jogo da Velha)**
- **Descrição**: Um clássico jogo de tabuleiro onde dois jogadores tentam formar uma linha (horizontal, vertical ou diagonal) de três símbolos iguais.
- **Regras principais**:
    - O jogo termina em vitória, derrota ou empate.

### 3. **Lig4**
- **Descrição**: Jogo onde os jogadores soltam peças em colunas e tentam alinhar quatro consecutivas em qualquer direção.
- **Regras principais**:
    - Ganha quem conseguir alinhar quatro peças antes do adversário.

---

## **🎯 Estrutura do Projeto**
    BoardGames/
    ├── assets/         # Assets do projeto
    ├── bin/            # Executáveis gerados pela compilação
    ├── doc/            # Documentação do projeto
    ├── include/        # Arquivos de cabeçalho (.hpp)
    ├── obj/            # Arquivos objeto (.o)
    ├── src/            # Código-fonte (.cpp)
    ├── tests/          # Testes unitários
    ├── .gitignore      # Arquivos e pastas ignoradas pelo Git
    ├── CMakeFiles.txt  # Automização da compilação
    ├── README.md       # Este arquivo

### **Hierarquia de Classes**
#### **1. Componentes Básicos**
- **`Board`**: Representa o tabuleiro de cada jogo. Gerencia o estado do tabuleiro, exibe e manipula as peças.
- **`Piece`**: Classe base para as peças dos jogos. Armazena o símbolo e o jogador associado.

#### **2. Jogos**
- **`Game`**: Classe abstrata que define a estrutura e comportamento base dos jogos de tabuleiro. Gerencia turnos, inicialização e condições de vitória ou empate.
- **Jogos Específicos**:
    - **`Reversi`**: Implementa as regras do jogo Reversi. Inclui peças específicas (`ReversiPiece`) que podem ser viradas.
    - **`TicTacToe`**: Implementa as regras do Jogo da Velha, utilizando peças do tipo `TTTPiece`.
    - **`Lig4`**: Gerencia a lógica do Lig4, incluindo a queda das peças na coluna e verificação de vitória com a peça `Lig4Piece`.

#### **3. Gerenciamento**
- **`GameManager`**: Controla a execução dos jogos, processa comandos do jogador e inicializa as partidas.
- **`SaveManager`**: Responsável por cadastrar jogadores, salvar e carregar estatísticas (vitórias e derrotas) em um banco de dados (`data.csv`).

---

### **Cadastro de Jogadores**
- **Classe**: `SaveManager`
    - **Responsabilidades**:
        - Cadastrar jogadores com apelido único e estatísticas por jogo.
        - Listar jogadores por apelido ou nome.
        - Salvar e carregar dados de jogadores.

---

### **Execução de Partidas**
- **Classe**: `GameManager`
    - **Responsabilidades**:
        - Inicializar partidas entre dois jogadores.
        - Gerenciar comandos, como cadastro de jogadores e execução de jogos.
        - Salvar estatísticas de vitórias/derrotas.

---

## 💡 Funcionalidades Extras
- **Interface gráfica com SFML**:
- Fornece uma experiência visual interativa para os jogos.
- **Implementação de IA**:
- Jogador opcional controlado pelo computador.

## 📋 Requisitos para Compilação

Certifique-se de ter os seguintes componentes instalados antes de compilar o projeto:

1. **Compilador C++**: Recomenda-se o uso do GCC, Clang ou MSVC com suporte a C++17 ou superior.
2. **Make**: Ferramenta usada para automação da compilação do projeto.
---

## 🚀 Como Compilar e Executar
### Passo 0: Clone o repositório
Para começar, clone o repositório no local de sua escolha (certifique-se de ter git instalado):
   ```bash
   git clone https://github.com/PHMGC/BoardGames
   ```
### 1. Configurar o Build
1. Navegue até o diretório raiz:
   ```bash
   cd /caminho/para/BoardGames
   ```

### 2. Compilar o projeto com Make
```bash
make
```
### 3. Executar o Programa
O executável será gerado no diretório `bin` com o nome `BoardGames`

### 4. Limpar a compilação
Caso queira limpar os itens compilados, execute
```bash
make clean
```
---

## 🛠 Ambiente de Desenvolvimento Recomendado

* É recomendado o uso de **IDE's** (Integrated Development Environment - Ambiente de Desenvolvimento Integrado)
  para desenvolvimento desse projeto.
* Outra alternativa recomendada é o uso do editor de texto Visual Studio Code com as extensões **clangd** e **C/C++**,
  para detecção de erros e análise estática, tornando o desenvolvimento prático, produtivo e eficiente.

---

## 📑 Testes

Os testes foram implementados utilizando a biblioteca `doctest`.
Para executar os testes unitários, acesse o executável `tests` na pasta `bin` após a compilação do projeto.

## ✨ Autores

- Pedro Henrique Moreira Guimarães Cortez 🍎
- Gustavo Luiz Araújo 🍈
- João Neimerck 🍊
