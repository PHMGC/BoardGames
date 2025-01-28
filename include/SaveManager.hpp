#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <array>
#include <iomanip>

class SaveManager {
	std::map<std::string, // Apelido
	std::pair<std::string, // Nome
	std::map<std::string, // Jogo
	std::array<int, 2>>> // Winrate (vitórias / derrotas)
	> data;

    std::string filename = "data.csv";

	std::vector<std::string> gamesNames;

   void save(){
		std::ofstream file(this->filename);
		// Verificar se o arquivo foi aberto com sucesso
		if (!file.is_open()) {
		std::ofstream newFile(this->filename);
	    if (!newFile.is_open()) {
		throw std::runtime_error("ERRO: Nao foi possivel criar banco de dados");
	    }
			file = std::move(newFile);
			std::cout << "Criando um novo banco de dados" << std::endl;
		}
		// Escrever cabeçalho
		file << "Apelido,Nome,Jogo,Vitorias,Derrotas\n";

		// Iterar sobre os dados e escrever no arquivo
		for (const auto &[apelido, pairData] : data) {
			const std::string &nome = pairData.first;
			const auto &jogos = pairData.second;

			for (const auto &[jogo, winrate] : jogos) {
				file << apelido << "," << nome << "," << jogo << "," << winrate[0] << "," << winrate[1] << "\n";
			}
		}

		file.close();
		std::cout << "Dados salvos no arquivo " << this->filename << " com sucesso!" << std::endl;

   }
   void load(){
	std::ifstream file(this->filename);
	// Verificar se o arquivo foi aberto com sucesso
	if (!file.is_open()) {
		std::cout << "Banco de dados nao encontrado. Dados nao foram carregados." << std::endl;
	  return;
	}
	std::string line;
	bool isHeader = true; // Ignorar o cabeçalho

	while (std::getline(file, line)) {
		// Ignorar a primeira linha (cabeçalho)
		if (isHeader) {
			isHeader = false;
			continue;
		}

		std::stringstream ss(line);
		std::string apelido, nome, jogo, vitoriasStr, derrotasStr;

		// Ler campos separados por vírgula
		if (std::getline(ss, apelido, ',') &&
		   std::getline(ss, nome, ',') &&
		   std::getline(ss, jogo, ',') &&
		   std::getline(ss, vitoriasStr, ',') &&
		   std::getline(ss, derrotasStr, ',')) {

			// Converter vitórias e derrotas para inteiros
			int vitorias = std::stoi(vitoriasStr);
			int derrotas = std::stoi(derrotasStr);

			// Inserir os dados no mapa
			data[apelido].first = nome; // Nome
			data[apelido].second[jogo] = {vitorias, derrotas}; // Jogo e winrate
			   }
	}

	file.close();
	std::cout << "Dados carregados do arquivo " << filename << " com sucesso!" << std::endl;
   }

public:
	explicit SaveManager(const std::vector<std::string>& gamesNames)
	: gamesNames(gamesNames) {
		load();
	}
	~SaveManager(){
		save();
	}

	static bool isFormatValid(const std::string& str) {
		for (const char c : str) {
			if (c != ' ' && !std::isprint(c) || c == ',') {
				return false;
			}
		}
		return true;
	}

	void setPlayer(const std::string& nickname, const std::string &name){
		if (!isFormatValid(nickname) || !isFormatValid(name)) {
			throw std::invalid_argument("ERRO: Cadastro invalido");
		}
		if (data.contains(nickname)) {
			throw std::invalid_argument("ERRO: Jogador repetido");
		}
		data[nickname].first = name;

		for (const std::string& gameName : gamesNames) {
			data[nickname].second[gameName] = {0, 0};
		}

		std::cout << "Jogador " << nickname << " cadastrado com sucesso" << std::endl;
    }

    auto getPlayer(const std::string& nickname){
		if (data.contains(nickname)) {
			return data[nickname];
		}
		throw std::invalid_argument("ERRO: Jogador inexistente");
    }

    void removePlayer(const std::string& nickname){
		if (!data.contains(nickname)) {
			throw std::invalid_argument("ERRO: Jogador inexistente");
		}
			data.erase(nickname);
			std::cout << "Jogador " << nickname << " removido com sucesso" << std::endl;
	}

	[[nodiscard]] bool isPlayer(const std::string& nickname) const {
		if (isFormatValid(nickname)) {
			return data.contains(nickname);
		}
		return false;
	}

    void setWinrate(const std::string& nickname, const std::string& game, const bool isWinner){
		if (!data.contains(nickname)) {
			throw std::invalid_argument("ERRO: Jogador inexistente");
		}

		if (!data[nickname].second.contains(game)) {
			throw std::runtime_error("ERRO: Jogo invalido");
		}

		if (isWinner) {
			data[nickname].second[game][0]++;
		} else {
			data[nickname].second[game][1]++;
		}
	}

	void leaderboard(const bool byNickname) {
		// Contêiner auxiliar para armazenar e ordenar os dados
		std::vector<std::pair<std::string, std::pair<std::string, std::map<std::string, std::array<int, 2>>>>> sortedData(data.begin(), data.end());

		// Ordenar pelo critério escolhido
		if (byNickname) {
			std::sort(sortedData.begin(), sortedData.end(), [](const auto &a, const auto &b) {
				return a.first < b.first; // Ordena pelo nickname
			});
		} else {
			std::sort(sortedData.begin(), sortedData.end(), [](const auto &a, const auto &b) {
				return a.second.first < b.second.first; // Ordena pelo name
			});
		}

		size_t maxGameNameLength = 0;
		for (const auto& [nickname, info] : this->data) {
			for (const auto& [game, winrate] : info.second) {
				maxGameNameLength = std::max(maxGameNameLength, game.length());
			}
		}

		// Imprimir os dados formatados
		for (const auto& [nickname, info] : this->data) {
			std::cout << nickname << " " << info.first << std::endl;
			for (const auto& [game, winrate] : info.second) {
				// Impressão com espaçamento dinâmico
				std::cout << std::left << std::setw(maxGameNameLength) << game
						  << " - V: " << winrate[0] << " D: " << winrate[1] << std::endl;
			}
			std::cout << std::endl; // Separar cada jogador
		}
	}

};