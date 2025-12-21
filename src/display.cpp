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
        std::cin.ignore(255, '\n');
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

    player::Player show_player_creation(int player_number, const player::Player &other_player) // affiche le menu de création d'un joueur et retourne le joueur créé
    {                                                                                          // on met un other_player qui sera a 0 si pas de joueur à comparer (très ghetto en vrai)
        // terminal_ctrl::clear_screen();
        terminal_ctrl::set_title("IMACtoe - Create Player " + std::to_string(player_number));
        std::cout << game_name_ascii << std::endl;
        std::cout << "Creating Player " << player_number << std::endl;
        std::string name;
        while (true)
        {
            std::cout << "Enter player name: ";
            std::cin >> name;
            if (name.empty())
            {
                std::cout << "Name cannot be empty. Please enter a valid name: ";
                name.clear();
                continue;
            }
            // on vérifie que le nom ne contient que des caractères alphanumériques
            for (char c : name)
            {
                if (!std::isalnum(c))
                {
                    std::cout << "Name can only contain alphanumeric characters. \n";
                    name.clear();
                    std::cin.ignore(255, '\n');
                    continue;
                }
            }
            if (player_number == 2)
            { // on vérifie que le nom n'est pas déjà pris par l'autre joueur
                if (name == other_player.get_name())
                {
                    std::cout << "Name already taken by other player. \n";
                    name.clear();
                    std::cin.ignore(255, '\n');
                    continue;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        char symbol;
        while (true)
        {
            std::cout << "Enter player symbol (single character): ";
            std::cin >> symbol;
            if (std::cin.fail() || std::cin.peek() != '\n')
            {
                std::cout << "Invalid input. Please enter a single character for the symbol." << std::endl;
                std::cin.clear();
                std::cin.ignore(255, '\n');
                continue;
            }
            if (player_number == 2 && other_player.get_symbol() == symbol)
            {
                std::cout << "Symbol already taken by other player." << std::endl;
                std::cin.clear();
                std::cin.ignore(255, '\n');
                continue;
            }
            break;
        }
        player::Player player(symbol, name, true);
        return player;
    }

    void draw_game_board(std::string board_str) // affiche le plateau de jeu a partir d'une chaîne de caractères, ex: "X O X   O  "
    {
        terminal_ctrl::clear_screen();
        terminal_ctrl::set_title("IMACtoe - Game Board");
        std::cout << game_name_ascii << std::endl;
        std::cout << "  0   1   2 " << std::endl;
        for (int i = 0; i < 3; ++i)
        {
            std::cout << i << " ";
            for (int j = 0; j < 3; ++j)
            {
                std::cout << " " << board_str[i * 3 + j] << " ";
                if (j < 2)
                    std::cout << "|";
            }
            if (i < 2)
                std::cout << "\n  ---+---+---\n";
        }
        std::cout << std::endl;
    }

    int choose_difficulty_level()
    {
        terminal_ctrl::clear_screen();
        terminal_ctrl::set_title("IMACtoe - Select Difficulty Level");
        std::cout << game_name_ascii << std::endl;
        std::cout << "Select Difficulty Level for Computer:" << std::endl;
        std::cout << "1. Easy" << std::endl;
        std::cout << "2. Medium" << std::endl;
        std::cout << "3. Hard" << std::endl;
        std::cout << "Enter your choice (1, 2 or 3): ";
        int choice;
        while (true)
        {
            std::cin >> choice;
            if (choice >= 1 && choice <= 3)
            {
                break; // valid choice
            }
            else
            {
                std::cout << "Invalid choice. Please enter 1, 2 or 3: ";
                std::cin.clear();
                std::cin.ignore(255, '\n');
            }
        }
        return choice;
    }

} // namespace display
