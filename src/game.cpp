#include "game.hpp"
#include "display.hpp"
#include "board.hpp"
#include <iostream>

namespace game_tic_tac_toe // contient la logique du jeu
{

    Game::Game(player::Player p1, player::Player p2) : player1(p1), player2(p2) {}

    Game::Game() : player1('X', "Player 1", true), player2('O', "Player 2", true) {} // constructeur par défaut, on modifiera plus tard pour choisir les joueurs

    void Game::play()
    {
        initialize_game(player1, player2);
        play_game(player1, player2, game_board);
    }

    const player::Player &Game::get_player(int player_number) const
    {
        if (player_number == 1)
        {
            return player1;
        }
        else
        {
            return player2;
        }
    }

    void play_human_turn(player::Player &current_player, board::Board &game_board)
    {
        int row, col;
        while (true)
        {
            std::cout << "Enter row and column (0, 1, or 2) separated by space: ";
            std::cin >> row >> col;
            // Validate input
            if (row < 0 || row > 2 || col < 0 || col > 2)
            {
                std::cout << "Invalid input. Row and column must be between 0 and 2." << std::endl;
                std::cin.clear();
                std::cin.ignore(255, '\n');
                continue;
            }
            if (game_board.set_cell(row, col, current_player.get_symbol()))
            {
                break;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(255, '\n');
                std::cout << "Invalid move. Try again." << std::endl;
            }
        }
    }

    void Game::initialize_game(player::Player &p1, player::Player &p2) // fonction pour initialiser une partie et les joueurs
    {
        display::show_welcome_message();
        while (true)
        {
            int choice = display::show_game_mode_selection();
            if (choice == 1)
            { // PvP
                std::cout << "Player vs Player mode selected." << std::endl;
                p1 = display::show_player_creation(1);
                p2 = display::show_player_creation(2);
                break;
            }
            else if (choice == 2)
            {
                std::cout << "Player vs Computer mode selected." << std::endl;
                p1 = display::show_player_creation(1);
                int difficulty_choice;
                difficulty_choice = display::choose_difficulty_level();
                p2 = player::create_bot(difficulty_choice);
                break;
            }
            else
            {
                std::cout << "Invalid choice. Please select again." << std::endl;
                std::cin.clear();
                std::cout << "Press Enter to continue..." << std::endl;
                std::cin.ignore(255, '\n');
                std::cin.get();
                continue;
            }
        }
    }

    void Game::play_game(player::Player &p1, player::Player &p2, board::Board &board) // fonction pour lancer une partie avec les joueurs donnés
    {
        bool game_over = false;
        player::Player *current_player = &p1;

        while (!game_over)
        {
            display::draw_game_board(board.to_string());
            std::cout << current_player->get_name() << "'s turn (" << current_player->get_symbol() << "):" << std::endl;

            if (current_player->get_is_human())
            {
                play_human_turn(*current_player, board);
            }
            else
            {
                int difficulty = current_player->get_difficulty_level();
                if (difficulty == 1)
                {
                    current_player->play_bot_move_easy(board);
                }
                else if (difficulty == 2)
                {
                    current_player->play_bot_move_medium(board, p1);
                }
                else if (difficulty == 3)
                {
                    current_player->play_bot_move_hard(board, p1);
                }
            }

            char winner = board.check_winner();
            if (winner != ' ')
            {
                display::draw_game_board(board.to_string());
                std::cout << current_player->get_name() << " wins!" << std::endl;
                game_over = true;
            }
            else if (board.is_full())
            {
                display::draw_game_board(board.to_string());
                std::cout << "It's a draw!" << std::endl;
                game_over = true;
            }
            else
            {
                current_player = (current_player == &p1) ? &p2 : &p1;
            }
        }
    }
}

// namespace game_tic_tac_toe