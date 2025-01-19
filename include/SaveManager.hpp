#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

class SaveManager {
	std::string id;
	std::string name;
	std::array<int, 2> winrate; // wins / loses
public:
	SaveManager();
	~SaveManager();
	// Funções para salvar e carregar um único objeto Data
	void save(std::ofstream& out) const {
		size_t len1 = id.size();
		size_t len2 = name.size();
		out.write(reinterpret_cast<const char*>(&len1), sizeof(len1));
		out.write(id.c_str(), len1);
		out.write(reinterpret_cast<const char*>(&len2), sizeof(len2));
		out.write(name.c_str(), len2);
		out.write(reinterpret_cast<const char*>(&winrate[0]), sizeof(winrate[0]));
		out.write(reinterpret_cast<const char*>(&winrate[1]), sizeof(winrate[1]));
	}

	void load(std::ifstream& in) {
		size_t len1, len2;
		in.read(reinterpret_cast<char*>(&len1), sizeof(len1));
		id.resize(len1);
		in.read(&id[0], len1);
		in.read(reinterpret_cast<char*>(&len2), sizeof(len2));
		name.resize(len2);
		in.read(&name[0], len2);
		in.read(reinterpret_cast<char*>(&winrate[0]), sizeof(winrate[0]));
		in.read(reinterpret_cast<char*>(&winrate[1]), sizeof(winrate[1]));
	}

	static void saveVector(const std::vector<Data>& vec, const std::string& filename) {
		std::ofstream out(filename, std::ios::binary);
		if (!out) {
			std::cerr << "Erro ao abrir o arquivo para salvar.\n";
			return;
		}
		size_t size = vec.size();
		out.write(reinterpret_cast<const char*>(&size), sizeof(size));
		for (const auto& item : vec) {
			item.save(out);
		}
		out.close();
	}

	static void loadVector(std::vector<Data>& vec, const std::string& filename) {
		std::ifstream in(filename, std::ios::binary);
		if (!in) {
			std::cerr << "Erro ao abrir o arquivo para carregar.\n";
			return;
		}
		size_t size;
		in.read(reinterpret_cast<char*>(&size), sizeof(size));
		vec.resize(size);
		for (auto& item : vec) {
			item.load(in);
		}
		in.close();
	}

};