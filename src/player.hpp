#pragma once
#include <string>
#include "board.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace player
{

    struct Player
    {
    private:
        char symbol;
        std::string name;
        bool is_human;
        int difficulty_level;
    public:
        Player(char symbol, const std::string &name, bool is_human);
        Player(char symbol, const std::string &name, bool is_human, int difficulty_level);
        int get_difficulty_level() const;
        char get_symbol() const;
        const std::string &get_name() const;
        bool get_is_human() const;
        void play_bot_move_easy(board::Board &board);
        void play_bot_move_medium(board::Board &board, Player const &human); // bloquera juste une victoire imminente de l'adversaire
        void play_bot_move_hard(board::Board &board, Player const &human); // sera normalement "imbattable" (on y croit)
    };

    Player create_bot(int &difficulty_level);

} // namespace player



