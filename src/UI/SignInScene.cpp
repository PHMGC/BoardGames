#include <iostream>
#include "UI/SceneManager.hpp"
#include "UI/SignInScene.hpp"

bool SignInScene::validatePlayerInput(InputContainer& container) {
	// Verificação inicial de entradas vazias
	container.setInvalidWarning(container.input.empty(), "Apelido obrigatorio");
	if (!container.isInputValid) return false;

	// Verifique se o jogador existe
	container.setInvalidWarning(!gameManager.saveManager.isPlayer(container.input), "Jogador nao existe");
	if (!container.isInputValid) return false;

	// Validação do formato de entrada
	container.setInvalidWarning(!SaveManager::isFormatValid(container.input), "Formato invalido");
	return container.isInputValid;
}

void SignInScene::handleAction() {
	if (currentIndex == 2 && next.isEnabled()) {
		player1.hasEnteredInput = true;
		player2.hasEnteredInput = true;

		const auto p1input = player1.input;
		const auto p2input = player2.input;

		// Validação para ambos os jogadores
		bool isPlayer1Valid = validatePlayerInput(player1);
		bool isPlayer2Valid = validatePlayerInput(player2);

		if (!isPlayer1Valid || !isPlayer2Valid) {
			std::cout << "Entrada(s) invalida(s) detectada(s)." << std::endl;
			return;
		}

		// Tudo está certo, vamos para a seleção de jogos
		player1.input.clear();
		player2.input.clear();
		currentIndex = 0;
		// sceneManager->setCurrentScene(SceneType::GAME_SELECTION);
	}

	if (currentIndex == maxIndex) {
		player1.reset();
		player2.reset();
		currentIndex = 0;
		sceneManager->setCurrentScene(SceneType::MENU);
	}
}