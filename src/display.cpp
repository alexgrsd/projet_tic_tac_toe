#include "display.hpp"

namespace display // gere l'IHM du jeu
{
    void show_welcome_message() // affiche le message de bienvenue
    {
        terminal_ctrl::clear_screen();
        terminal_ctrl::set_title("IMACtoe - Welcome");
        std::cout << game_name_ascii << std::endl;
        std::cout << "Welcome to IMACtoe" << std::endl;
        std::cout << "Press Enter to start the game..." << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int show_game_mode_selection() // affiche le menu de sélection du mode de jeu
    {
        terminal_ctrl::clear_screen();
        terminal_ctrl::set_title("IMACtoe - Select Game Mode");
        std::cout << game_name_ascii << std::endl;
        std::cout << "Select Game Mode:" << std::endl;
        std::cout << "1. Player vs Player" << std::endl;
        std::cout << "2. Player vs Computer" << std::endl;
        std::cout << "Enter your choice (1 or 2): ";
        int choice;
        std::cin >> choice;
        return choice;
    }

    player::Player show_player_creation(int player_number) // affiche le menu de création d'un joueur et retourne le joueur créé
    { // FLAG: à améliorer, pas de vérification des entrées utilisateur on peut mettre des symboles invalides / rentrer le même symbole - nom pour les 2 joueurs
        terminal_ctrl::clear_screen();
        terminal_ctrl::set_title("IMACtoe - Create Player " + std::to_string(player_number));
        std::cout << game_name_ascii << std::endl;
        std::cout << "Creating Player " << player_number << std::endl;
        std::cout << "Enter player name: ";
        std::string name;
        while(true) {
            std::cin >> name;
            if (!name.empty()) {
                break; // valid name
            } else {
                std::cout << "Name cannot be empty. Please enter a valid name: ";
            }
        }
        char symbol;
        while (true) {
            std::cout << "Enter player symbol (single character): ";
            std::cin >> symbol;
            if (std::cin.peek() == '\n') {
                break; // valid single character
            } else {
                std::cout << "Invalid symbol. Please enter a single character." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        player::Player player(symbol, name, true);
        return player;
    }

} // namespace display
