#pragma once
#include <string>
#include <array>

namespace board // représente le plateau de jeu
{
    struct Board{
        private:
            std::array<std::array<char, 3>, 3> grid{};
        public:
            Board();
            Board(std::array<std::array<char, 3>, 3> grid_init) : grid(grid_init) {}
            char get_cell(int row, int col) const;
            std::array<std::array<char, 3>, 3> get_grid() const;
            bool set_cell(int row, int col, char symbol);
            bool is_full() const;
            void reset();
            char check_winner() const;
            std::string to_string() const;
    };
}