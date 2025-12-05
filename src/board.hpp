#pragma once

namespace board{
    struct Board{
        private:
            char grid[3][3];
        public:
            Board();
            char get_cell(int row, int col) const;
            bool set_cell(int row, int col, char symbol);
            bool is_full() const;
            void reset();
            char check_winner() const;
    };
}