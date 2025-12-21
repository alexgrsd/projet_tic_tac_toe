#include "board.hpp"

namespace board // représente le plateau de jeu
{
    Board::Board()
    {
        reset();
    }

    char Board::get_cell(int row, int col) const
    {
        return grid[row][col];
    }

    std::array<std::array<char, 3>, 3> Board::get_grid() const
    {
        return grid;
    }

    bool Board::set_cell(int row, int col, char symbol)
    {
        if (grid[row][col] == ' ')
        {
            grid[row][col] = symbol;
            return true; // la cellule est set
        }
        return false; // cellule déja occumpé D:
    }

    bool Board::is_full() const
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (grid[i][j] == ' ') // on check chaque case du plateau
                {
                    return false; // au moins une case est vide
                }
            }
        }
        return true; // le plateau est plein
    } // peut être inutile, a voir si je check pas le nombre de tour directement dans le main

    void Board::reset() // pour vider le plateau avant une partie
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                grid[i][j] = ' ';
            }
        }
    }

    char Board::check_winner() const
    {
        // verification lignes / colonnes
        for (int i = 0; i < 3; ++i)
        {
            if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
                return grid[i][0];
            if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
                return grid[0][i];
        }
        // verification diagonales
        if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
            return grid[0][0];
        if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
            return grid[0][2];

        return ' '; // personne gagne (rip)
    }

    std::string Board::to_string() const // retourne une représentation en chaîne de caractères du plateau
    {
        std::string board_str;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                board_str += grid[i][j];
            }
        }
        return board_str;
    }

} // namespace board
