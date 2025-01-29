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
   cd /caminho/para/BoardGames
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
../bin/BoardGames.exe
```

---

## 🛠 Ambiente de Desenvolvimento Recomendado

* É recomendado o uso de **IDE's** (Integrated Development Environment - Ambiente de Desenvolvimento Integrado)
  para desenvolvimento desse projeto
* Outra alternativa recomendada é o uso do editor de texto Visual Studio Code com as extensões **clangd** e **C/C++**,
  para detecção de erros e análise estática, tornando o desenvolvimento prático, produtivo e eficiente.
---
