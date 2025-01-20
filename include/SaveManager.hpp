#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <array>

class SaveManager {
	std::map<std::string, // Apelido
	std::pair<std::string, // Nome
	std::map<std::string, // Jogo
	std::array<int, 2>>> // Winrate (vitórias / derrotas)
	> data;

    std::string filename = "data.csv";

   void save(){
   		std::ofstream file(this->filename);
   		// Verificar se o arquivo foi aberto com sucesso
   		if (!file.is_open()) {
        	std::ofstream newFile(this->filename);
                if (!newFile.is_open()) {
                  throw std::runtime_error("ERRO: Nao foi possivel criar banco de dados");
                }
                else{
                  std::cout << "Banco de dados nao encontrado. Criando um novo." << std::endl;
                }
   		}
   		// Escrever cabeçalho
   		file << "Apelido,Nome,Jogo,Vitórias,Derrotas\n";

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
	SaveManager(){
        load();
	}
	~SaveManager(){
    	save();
	}

    void setPlayer(const std::string& nickname, const std::string &name){
    	if (!data.contains(nickname)) {
    		data[nickname].first = name;
    	}
        throw std::invalid_argument("ERRO: Jogador repetido");
    }

    auto getPlayer(const std::string& nickname){
		if (data.contains(nickname)) {
			return data[nickname];
		}
		throw std::invalid_argument("ERRO: Jogador inexistente");
    }

    void removePlayer(const std::string& nickname){
      	if (data.contains(nickname)) {
    		data.erase(nickname);
      	}
      	throw std::invalid_argument("ERRO: Jogador inexistente");
    }

	bool isPlayer(const std::string& nickname) {
		return data.contains(nickname);
	}

    void setWinrate(const std::string& nickname, const std::string& game, const bool isWin){
		const auto itPlayer = data.find(nickname);
		if (itPlayer == data.end()) {
			throw std::invalid_argument("ERRO: Jogador inexistente");
		}

		auto &games = itPlayer->second.second;
		const auto itGame = games.find(game);

		if (itGame == games.end()) {
			// Caso o jogador não tenha jogado o jogo, inicialize com valores padrão
			games[game] = {0, 0};
		}

		auto &winrate = games[game];
		if (isWin) {
			winrate[0]++;
		} else {
			winrate[1]++;
		}
	}

	void leaderboard(){
        for(const auto &[nickname, info] : data){
        	std::cout << nickname << info.first << std::endl;
       		for(const auto &[game, winrate] : info.second){
        		std::cout << game << " " << winrate[0] << " " << winrate[1] << std::endl;
            }
        }
	}

};