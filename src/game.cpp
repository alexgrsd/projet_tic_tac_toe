#include "game.hpp"
#include "display.hpp"
#include <iostream>

namespace game_tic_tac_toe // contient la logique du jeu
{

    Game::Game(player::Player p1, player::Player p2) : player1(p1), player2(p2) {}

    Game::Game() : player1('X', "Player 1", true), player2('O', "Player 2", true) {} // constructeur par défaut, on modifiera plus tard pour choisir les joueurs

    void Game::play() 
    {
        initialize_game(player1, player2);


    }

    const player::Player &Game::get_player(int player_number) const {
        if (player_number == 1) {
            return player1;
        } else {
            return player2;
        }
    }

    void Game::initialize_game(player::Player &p1, player::Player &p2) // fonction pour initialiser une partie et les joueurs
    {
        display::show_welcome_message();
        while (true) {
            int choice = display::show_game_mode_selection();
            if (choice == 1) { // PvP
                std::cout << "Player vs Player mode selected." << std::endl;
                p1 = display::show_player_creation(1);
                p2 = display::show_player_creation(2);
                break;
            } else if (choice == 2) {
                std::cout << "Player vs Computer mode selected." << std::endl;
                p1 = display::show_player_creation(1);
                p2 = player::create_bot();
                break;
            } else {
                std::cout << "Invalid choice. Please select again." << std::endl;
                std::cin.clear();
                std::cout << "Press Enter to continue..." << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get(); 
                continue;
            }
        }
    }

} // namespace game_tic_tac_toe