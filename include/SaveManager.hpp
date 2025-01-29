#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <array>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <algorithm>

/**
 * @class SaveManager
 * @brief Gerencia a persistência de dados de jogadores e seus winrates em diferentes jogos.
 */
class SaveManager {
private:
    /**
     * @brief Estrutura de dados armazenando informações dos jogadores.
     *
     * O mapa utiliza:
     * - `std::string`: Apelido do jogador
     * - `std::pair<std::string, std::map<std::string, std::array<int, 2>>>`:
     *   - Primeiro elemento: Nome real do jogador
     *   - Segundo elemento: Mapa de winrates, onde:
     *     - `std::string`: Nome do jogo
     *     - `std::array<int, 2>`: Array contendo vitórias e derrotas
     */
    std::map<std::string, std::pair<std::string, std::map<std::string, std::array<int, 2>>>> data;

    std::string filename; ///< Nome do arquivo para salvar e carregar dados.
    std::vector<std::string> gamesNames; ///< Lista de nomes dos jogos suportados.

    /**
     * @brief Salva os dados no arquivo.
     */
    void save();

    /**
     * @brief Carrega os dados do arquivo.
     */
    void load();

    /**
     * @brief Verifica se uma string contém caracteres não alfanuméricos.
     * @param str String a ser verificada.
     * @return `true` se houver caracteres não alfanuméricos, `false` caso contrário.
     */
    static bool hasNonAlphanumeric(const std::string& str);

public:
    /**
     * @brief Construtor da classe SaveManager.
     * @param gamesNames Vetor contendo os nomes dos jogos suportados.
     * @param filename Nome do arquivo de dados (padrão: "data.csv").
     */
    explicit SaveManager(const std::vector<std::string>& gamesNames, const std::string& filename = "data.csv");

    /**
     * @brief Destrutor da classe SaveManager.
     */
    ~SaveManager();

    /**
     * @brief Define um jogador no sistema.
     * @param nickname Apelido do jogador.
     * @param name Nome real do jogador.
     */
    void setPlayer(const std::string& nickname, const std::string& name);

    /**
     * @brief Obtém informações de um jogador pelo apelido.
     * @param nickname Apelido do jogador.
     * @return Dados do jogador (nome e estatísticas) ou um da um throw se não
     * existir.
     */
    std::pair<std::string, std::map<std::string, std::array<int, 2>>>
    getPlayer(const std::string &nickname);

    /**
     * @brief Remove um jogador pelo apelido.
     * @param nickname Apelido do jogador a ser removido.
     */
    void removePlayer(const std::string& nickname);

    /**
     * @brief Verifica se um jogador existe no sistema.
     * @param nickname Apelido do jogador.
     * @return `true` se o jogador existir, `false` caso contrário.
     */
    bool isPlayer(const std::string& nickname) const;

    /**
     * @brief Atualiza o winrate de um jogador em um determinado jogo.
     * @param nickname Apelido do jogador.
     * @param game Nome do jogo.
     * @param isWinner `true` para vitória, `false` para derrota.
     */
    void setWinrate(const std::string& nickname, const std::string& game, const bool isWinner);

    /**
     * @brief Exibe o ranking dos jogadores.
     * @param byNickname Se `true`, ordena por apelido; caso contrário, ordena por winrate.
     */
    void leaderboard(const bool byNickname);
};
