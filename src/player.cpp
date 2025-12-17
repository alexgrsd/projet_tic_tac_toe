#include "player.hpp"
#include <string>

namespace player
{

    Player::Player(char symbol, const std::string &name, bool is_human) : symbol(symbol), name(name), is_human(is_human) {}

    Player create_bot()
    {
        Player bot('O', "Computer", false);
        return bot;
    }

    void player::Player::play_bot_move(board::Board& board) 
    {
        
        board::Board current_board = board;
        auto current_state = current_board.get_grid();
        // s'il risque de perdre au prochain coup, il bloque l'adversaire
        char opponent_symbol = (this->get_symbol() == 'X') ? 'O' : 'X';
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (current_state[i][j] == ' ') {
                    current_board.set_cell(i, j, opponent_symbol);
                    if (current_board.check_winner() == opponent_symbol) {
                        board.set_cell(i, j, this->get_symbol());
                        return; // coup joué
                    }
                }
            }
        }
        current_board = board; // reset l'état du plateau
        current_state = current_board.get_grid();
        // si le bot peut gagner au prochain coup, il le fait
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (current_state[i][j] == ' ') {
                    current_board.set_cell(i, j, this->get_symbol());
                    if (current_board.check_winner() == this->get_symbol()) {
                        board.set_cell(i, j, this->get_symbol());
                        return; // coup joué
                    }
                }
            }
        }
        current_board = board; // reset l'état du plateau
        current_state = current_board.get_grid();
        // sinon, jouer un coup aléatoire
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (current_state[i][j] == ' ') {
                    board.set_cell(i, j, this->get_symbol());
                    return; // coup joué
                }
            }
        }

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