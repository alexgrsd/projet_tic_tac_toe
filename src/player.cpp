#include "player.hpp"
namespace player
{

    Player::Player(char symbol, const std::string &name, bool is_human) : symbol(symbol), name(name), is_human(is_human) {}
    Player::Player(char symbol, const std::string &name, bool is_human, int difficulty_level): symbol(symbol), name(name), is_human(is_human), difficulty_level(difficulty_level) {}


    Player create_bot(int &difficulty_level)
    {
        Player bot('O', "Computer", false, difficulty_level);
        return bot;
    }

    int Player::get_difficulty_level() const
    {
        return difficulty_level;
    }



    void Player::play_bot_move_easy(board::Board &board) // joue une case disponible au hasard
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        int next_case[2] = {std::rand() % 3, std::rand() % 3};
        while (true)
        {
            if (board.get_cell(next_case[0], next_case[1]) == ' ')
            {
                board.set_cell(next_case[0], next_case[1], this->get_symbol());
                return;
            }
            else
            {
                next_case[0] = std::rand() % 3;
                next_case[1] = std::rand() % 3;
            }
        }
    }

        bool detect_victory(board::Board &board, char symbol, int &row, int &col) // dectecte si une victoire est possible au prochain coup pour le symbole donné, et remplit row et col avec la position gagnante
    {
        board::Board temp_board = board::Board(board.get_grid());
        size_t size = board.get_grid().size();

        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++) // on itere sur chaque case
            {
                if (temp_board.get_cell(i, j) == ' ')
                { 
                    temp_board.set_cell(i, j, symbol);
                    if (temp_board.check_winner() == symbol) // si la case est vide on check si un coup la ferait gagner
                    {
                        row = i;
                        col = j;
                        return true;
                    }
                    else
                    {
                        temp_board = board::Board(board.get_grid()); // reset temp_board
                    }
                }
            }
        }
        return false;
    }

    void Player::play_bot_move_medium(board::Board &board, Player const &human) // bloque si défaite gagne si possible sinon joue totalement au hasard
    {
        char opponent_symbol = human.get_symbol();
        int row{0}, col{0};

        if (detect_victory(board, this->get_symbol(), row, col))
        {                                                                // si le bot peut gagner ce tour ci le bot gagne
            board.set_cell(row, col, this->get_symbol());
            return;
        }
        if (detect_victory(board, opponent_symbol, row, col))
        {                                                                  // si l'adversaire peut gagner ce tour ci le bot bloque
            board.set_cell(row, col, this->get_symbol());
            return;
        }
        play_bot_move_easy(board);              // si aucune menace, joue aléatoirement en énorme légendre
    }

    int minimax(board::Board &board, bool is_bot_turn, char bot_symbol, char human_symbol) // retourne le score de la position donnée pour le bot hard
    {
        char winner = board.check_winner();
        if (winner == bot_symbol)
            return 10;
        if (winner == human_symbol)
            return -10;
        if (board.is_full())
            return 0;

        int best_score = is_bot_turn ? -1000 : 1000;
        board::Board temp_board = board::Board(board.get_grid());

        for (size_t i = 0; i < 3; ++i)
        {
            for (size_t j = 0; j < 3; ++j)
            {
                if (temp_board.get_cell(i, j) == ' ')
                {
                    temp_board.set_cell(i, j, is_bot_turn ? bot_symbol : human_symbol);

                    int score = minimax(temp_board, !is_bot_turn, bot_symbol, human_symbol);
                    temp_board = board::Board(board.get_grid());

                    if (is_bot_turn)
                        best_score = std::max(best_score, score);
                    else
                        best_score = std::min(best_score, score);
                }
            }
        }
        return best_score;
    }

    void Player::play_bot_move_hard(board::Board &board, Player const &human)
    {
        char bot_symbol = this->get_symbol();
        char human_symbol = human.get_symbol();
        board::Board temp_board = board::Board(board.get_grid());

        int best_score = -1000;
        size_t best_i = 0, best_j = 0;

        for (size_t i = 0; i < 3; ++i)
        {
            for (size_t j = 0; j < 3; ++j)
            {
                if (temp_board.get_cell(i, j) == ' ')
                {
                    temp_board.set_cell(i, j, bot_symbol);

                    int score = minimax(temp_board, false, bot_symbol, human_symbol);
                    temp_board = board::Board(board.get_grid());

                    if (score > best_score)
                    {
                        best_score = score;
                        best_i = i;
                        best_j = j;
                    }
                }
            }
        }
        board.set_cell(best_i, best_j, bot_symbol);
    }

    bool Player::get_is_human() const
    {
        return is_human;
    }

    char Player::get_symbol() const
    {
        return symbol;
    }

    const std::string &Player::get_name() const
    {
        return name;
    }

} // namespace player
