# BoardGames 🎲♟️🧩 #

Este repositório contém o trabalho final da disciplina **Programação e Desenvolvimento de Software 2** (PDS2) da **Universidade Federal de Minas Gerais (UFMG)**. O projeto consiste na implementação de uma coleção de jogos de tabuleiro, desenvolvidos em **C++** com o uso da biblioteca **SFML (Simple and Fast Multimedia Library)**.

---

## 🕹️ Jogos Implementados

### 1. **Reversi**
- **Descrição**: Também conhecido como Othello, é um jogo estratégico onde dois jogadores disputam para dominar o tabuleiro com peças de sua cor.
- **Regras principais**:
    - As peças podem ser viradas ao capturar as do oponente.
    - O jogador com mais peças no final vence.

### 2. **Lig4**
- **Descrição**: TODO
- **Objetivo**: TODO

### 3. **Tic-Tac-Toe (Jogo da Velha)**
- **Descrição**: Um clássico jogo de tabuleiro onde dois jogadores tentam formar uma linha (horizontal, vertical ou diagonal) de três símbolos iguais.
- **Regras principais**:
    - O jogo termina em vitória, derrota ou empate.

### 4. **Chess (Xadrez)**
- **Descrição**: Jogo de estratégia num tabuleiro 8x8 com peças específicas para cada jogador.
- **Regras principais**:
    - Objetivo é dar xeque-mate no rei adversário.
    - Movimentos e capturas seguem as regras tradicionais do xadrez.

### 5. **Checkers (Damas)**
- **Descrição**: Jogo onde os jogadores movem as suas peças diagonalmente e capturam as do oponente ao pular sobre elas.
- **Regras principais**:
    - Peças podem ser promovidas a damas, ganhando movimentos extras.

### 6. **Dots and Boxes**
- **Descrição**: Os jogadores desenham linhas num tabuleiro de pontos. Ao fechar um quadrado, o jogador ganha pontos e continua jogando.
- **Objetivo**: Fechar o maior número de quadrados.


### 7. **Chomp**
- **Descrição**: TODO
- **Regras principais**:
    - TODO

---

## 🎯 Estrutura do Projeto

### **Hierarquia de Classes para os Jogos**
#### Interface Base
- **Classe abstrata**: `BoardGames`
    - **Responsabilidades**:
        - Definir o comportamento comum a todos os jogos de tabuleiro.
        - Métodos virtuais:
            - `move()`: Realiza uma jogada.
            - `readMove()`: Lê e valida a entrada do jogador.
            - `checkMove()`: Verifica se o movimento é válido.
            - `checkWin()`: Determina se o jogo terminou em vitória.
            - `printBoard()`: Imprime o estado atual do tabuleiro.
    - **Atributos**:
        - Tamanho do tabuleiro.
        - Peças do tabuleiro.

#### Implementações Específicas
- **`Reversi`**: Implementa as regras e mecânicas do Reversi.
- **`TicTacToe`**: Adapta o jogo da velha para diferentes tamanhos de tabuleiro.
- **`Chess`**: Implementa as regras do xadrez, incluindo peças e movimentos.
- **`Checkers`**: Implementa o jogo de damas com promoção de peças.
- **`DotsAndBoxes`**: Gerencia a lógica de criar e fechar quadrados.
- **`Chomp`**: (Detalhes em desenvolvimento).

---

### **Cadastro de Jogadores**
- **Classe**: `Jogador`
    - **Responsabilidades**:
        - Gerenciar o nome, apelido único e estatísticas de vitórias/derrotas (winrate).
        - Listar jogadores ordenados por apelido ou nome.
    - **Colaborações**:
        - Sistema de registro e consulta.

---

### **Execução de Partidas**
- **Classe**: `Partida`
    - **Responsabilidades**:
        - Iniciar e finalizar o jogo.
        - Controlar o tabuleiro e os jogadores.
        - Registrar o vencedor ou empate.
    - **Colaborações**:
        - `BoardGames` (jogo atual).
        - `Jogador`.

---

## 💡 Funcionalidades Extras
- **Interface gráfica com SFML**:
    - Fornece uma experiência visual interativa para os jogos.
- **Implementação de IA**:
    - Jogador opcional controlado pelo computador.
- **Configuração personalizada**:
    - Permite ao usuário escolher o tamanho do tabuleiro para jogos compatíveis.

---

## 📋 Requisitos para Compilação

Certifique-se de ter os seguintes componentes instalados antes de compilar o projeto:

1. **Compilador C++**: Recomenda-se o uso do GCC, Clang ou MSVC com suporte a C++17 ou superior.
2. **CMake**: Ferramenta para gerenciar o processo de build. Baixe em [CMake - Download](https://cmake.org/download/).
    - Caso esteja em um computador Linux sem acesso ao sudo (como o computador do dcc), utilize o script .sh disponível no link de download acima para instalar localmente
3. **GNU Make** (Opcional): Usado para facilitar a automação do build. Instale-o via [GNU Make - Download](https://www.gnu.org/software/make/#download) ou pelo gerenciador de pacotes de seu sistema.

---

## 🚀 Como Compilar e Executar
### Passo 0: Clone o repositório
Para começar, clone o repositório no local de sua escolha (certifique-se de ter git instalado):
   ```bash
   git clone https://github.com/PHMGC/MiniGames.git
   ```
### 1. Configurar o Build
1. Navegue até o diretório raiz:
   ```bash
   cd /caminho/para/MiniGames
   ```
2. Crie um diretório de build:
   ```bash
   mkdir build
   cd build
   ```

### 2. Gerar o Build com CMake
```bash
cmake ..
```

### 3. Compilar o Projeto
```bash
cmake --build .
```

### 4. Executar o Programa
O executável será gerado no diretório `bin`. Execute-o com:
```bash
../bin/MiniGames.exe
```

---

## 🛠 Ambiente de Desenvolvimento Recomendado

* É recomendado o uso de **IDE's** (Integrated Development Environment - Ambiente de Desenvolvimento Integrado)
  para desenvolvimento desse projeto
* Outra alternativa recomendada é o uso do editor de texto Visual Studio Code com as extensões **clangd** e **C/C++**,
  para detecção de erros e análise estática, tornando o desenvolvimento prático, produtivo e eficiente.
---

## ✨ Autores

- Pedro Henrique Moreira Guimarães Cortez - [@github](https://github.com/PHMGC)
- Gustavo Luiz Araújo - [@github](https://github.com/Gustav0Luiz)
- João Neimerck - [@github](https://github.com/joaoneimerck)