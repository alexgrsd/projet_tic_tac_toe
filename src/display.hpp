#pragma once
#include <terminal_ctrl/terminal_ctrl.hpp>
#include <string>
#include <iostream>
#include "board.hpp"
#include "player.hpp"
#include "custom_strings.hpp"

namespace display // fonctions d'affichage
{
    void show_welcome_message();
    int show_game_mode_selection();
    player::Player show_player_creation(int player_number,const player::Player &other_player);
    void draw_game_board(std::string board_str);
    int choose_difficulty_level();

} // namespace display
