#include "game.hpp"
//#include "display.hpp"


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
        terminal_ctrl::clear_screen();
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

    void Game::initialize_game(player::Player &p1, player::Player &p2) // fonction pour initialiser une partie et les joueurs
    {
        show_welcome_message();
        while (true)
        {
            int choice = show_game_mode_selection();
            if (choice == 1)
            { // PvP
                std::cout << "Player vs Player mode selected." << std::endl;
                p1 = show_player_creation(1, p2);
                p2 = show_player_creation(2, p1);
                break;
            }
            else if (choice == 2)
            {
                std::cout << "Player vs Computer mode selected." << std::endl;
                int difficulty_choice;
                difficulty_choice = choose_difficulty_level();
                p1 = player::create_bot(difficulty_choice);
                p2 = show_player_creation(2, p1);

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
            draw_game_board(board.to_string());
            std::cout << current_player->get_name() << "'s turn (" << current_player->get_symbol() << "):" << std::endl;

            if (current_player->get_is_human())
            {
                play_human_turn(*current_player, board);
            }
            else
            {
                int difficulty = current_player->get_difficulty_level();
                switch (difficulty)
                {
                case 1:
                    current_player->play_bot_move_easy(board);
                    break;
                case 2:
                    current_player->play_bot_move_medium(board, p1);
                    break;
                case 3:
                    current_player->play_bot_move_hard(board, p1);
                    break;
                default:
                    break;
                }
            }

            char winner = board.check_winner();
            if (winner != ' ')
            {
                draw_game_board(board.to_string());
                std::cout << current_player->get_name() << " wins!" << std::endl;
                game_over = true;
            }
            else if (board.is_full())
            {
                draw_game_board(board.to_string());
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