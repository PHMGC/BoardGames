#include "SaveManager.hpp"

SaveManager::SaveManager(const std::vector<std::string>& gamesNames, const std::string& filename)
    : filename(filename), gamesNames(gamesNames) {  // Ordem corrigida
    load();
}

SaveManager::~SaveManager() {
    save();
}

void SaveManager::save() {
    std::ofstream file(this->filename);
    if (!file.is_open()) {
        std::ofstream newFile(this->filename);
        if (!newFile.is_open()) {
            throw std::runtime_error("ERRO: Nao foi possivel criar banco de dados");
        }
        file = std::move(newFile);
        std::cout << "Criando um novo banco de dados" << std::endl;
    }

    file << "Apelido,Nome,Jogo,Vitorias,Derrotas\n";
    for (const auto& [apelido, pairData] : data) {
        const std::string& nome = pairData.first;
        const auto& jogos = pairData.second;

        for (const auto& [jogo, winrate] : jogos) {
            file << apelido << "," << nome << "," << jogo << "," << winrate[0] << "," << winrate[1] << "\n";
        }
    }

    file.close();
    std::cout << "Dados salvos no arquivo " << this->filename << " com sucesso!" << std::endl;
}

void SaveManager::load() {
    std::ifstream file(this->filename);
    if (!file.is_open()) {
        std::cout << "Banco de dados nao encontrado. Dados nao foram carregados." << std::endl;
        return;
    }

    std::string line;
    bool isHeader = true;

    while (std::getline(file, line)) {
        if (isHeader) {
            isHeader = false;
            continue;
        }

        std::stringstream ss(line);
        std::string apelido, nome, jogo, vitoriasStr, derrotasStr;

        if (std::getline(ss, apelido, ',') &&
            std::getline(ss, nome, ',') &&
            std::getline(ss, jogo, ',') &&
            std::getline(ss, vitoriasStr, ',') &&
            std::getline(ss, derrotasStr, ',')) {

            int vitorias = std::stoi(vitoriasStr);
            int derrotas = std::stoi(derrotasStr);

            data[apelido].first = nome;
            data[apelido].second[jogo] = {vitorias, derrotas};
        }
    }

    file.close();
    std::cout << "Dados carregados do arquivo " << filename << " com sucesso!" << std::endl;
}

bool SaveManager::hasNonAlphanumeric(const std::string& str) {
    for (const char c : str) {
        if (c != ' ' && !std::isalnum(static_cast<unsigned char>(c))) {
            return true;
        }
    }
    return false;
}

void SaveManager::setPlayer(const std::string &nickname,
                            const std::string &name) {
    if (hasNonAlphanumeric(nickname) || hasNonAlphanumeric(name)) {
        throw std::invalid_argument("ERRO: Cadastro invalido");
    }
    if (data.find(nickname) != data.end()) {  // Substituição de .contains() por find()
        throw std::invalid_argument("ERRO: Jogador repetido");
    }
    data[nickname].first = name;

    for (const std::string &gameName : gamesNames) {
        data[nickname].second[gameName] = {0, 0};
    }

    std::cout << "Jogador " << nickname << " cadastrado com sucesso" << std::endl;
}

std::pair<std::string, std::map<std::string, std::array<int, 2>>>
SaveManager::getPlayer(const std::string &nickname) {
    if (data.find(nickname) != data.end()) {  // Substituição de .contains() por find()
        return data[nickname];
    }
    throw std::invalid_argument("ERRO: Jogador inexistente");
}

void SaveManager::removePlayer(const std::string& nickname) {
    if (data.find(nickname) == data.end()) {  // Substituição de .contains() por find()
        throw std::invalid_argument("ERRO: Jogador inexistente");
    }
    data.erase(nickname);
    std::cout << "Jogador " << nickname << " removido com sucesso" << std::endl;
}

bool SaveManager::isPlayer(const std::string& nickname) const {
    return data.find(nickname) != data.end();  // Substituição de .contains() por find()
}

void SaveManager::setWinrate(const std::string& nickname, const std::string& game, const bool isWinner) {
    if (data.find(nickname) == data.end()) {  // Substituição de .contains() por find()
        throw std::invalid_argument("ERRO: Jogador inexistente");
    }

    if (data[nickname].second.find(game) == data[nickname].second.end()) {  // Substituição de .contains() por find()
        throw std::runtime_error("ERRO: Jogo invalido");
    }

    if (isWinner) {
        data[nickname].second[game][0]++;
    } else {
        data[nickname].second[game][1]++;
    }
}

void SaveManager::leaderboard(const bool byNickname) {
    std::vector<std::pair<std::string, std::pair<std::string, std::map<std::string, std::array<int, 2>>>>> sortedData(data.begin(), data.end());

    if (byNickname) {
        std::sort(sortedData.begin(), sortedData.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
    } else {
        std::sort(sortedData.begin(), sortedData.end(), [](const auto& a, const auto& b) {
            return a.second.first < b.second.first;
        });
    }

    size_t maxGameNameLength = 0;
    for (const auto& [nickname, info] : this->data) {
        for (const auto& [game, winrate] : info.second) {
            maxGameNameLength = std::max(maxGameNameLength, game.length());
        }
    }

    for (const auto& [nickname, info] : this->data) {
        std::cout << nickname << " " << info.first << std::endl;
        for (const auto& [game, winrate] : info.second) {
            std::cout << std::left << std::setw(maxGameNameLength) << game
                      << " - V: " << winrate[0] << " D: " << winrate[1] << std::endl;
        }
        std::cout << std::endl;
    }
}
