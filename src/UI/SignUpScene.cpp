#include <iostream>
#include "UI/SceneManager.hpp"
#include "UI/SignUpScene.hpp"

bool SignUpScene::validateInput(InputContainer& container) {
    // Verificação de entrada vazia
    container.setInvalidWarning(container.input.empty(), "Entrada obrigatoria");
    if (!container.isInputValid) return false;

    // Verificação se existe
    container.setInvalidWarning(gameManager.saveManager.isPlayer(container.input), "Jogador ja existe");
    if (!container.isInputValid) return false;

    // Validação do formato
    container.setInvalidWarning(!SaveManager::isFormatValid(container.input), "Formato invalido");
    return container.isInputValid;
}

void SignUpScene::handleAction() {
    if (currentIndex == 2 && signup.isEnabled()) {
        playerNickname.hasEnteredInput = true;
        playerName.hasEnteredInput = true;

        const auto nickname = playerNickname.input;
        const auto name = playerName.input;

        // Validação de campos vazios e formato
        bool isNicknameValid = validateInput(playerNickname);
        bool isNameValid = validateInput(playerName);

        // Se qualquer validação falhar
        if (!isNicknameValid || !isNameValid) {
            std::cout << "Entrada(s) invalida(s) detectada(s)." << std::endl;
            return;
        }

        // Tente registrar o jogador
        try {
            gameManager.saveManager.setPlayer(nickname, name);
            playerNickname.input.clear();
            playerName.input.clear();
            isSignUpSucessfull = true;
        } catch (const std::invalid_argument& e) {
            std::cout << "Erro ao cadastrar o jogador " << nickname << ": " << e.what() << std::endl;
        }
    }

    if (currentIndex == maxIndex) {
        sceneManager->setCurrentScene(SceneType::MENU);
        playerNickname.reset();
        playerName.reset();
        currentIndex = 0;
    }
}
