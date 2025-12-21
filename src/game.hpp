#pragma once
#include "board.hpp"
#include "player.hpp"
#include <iostream>
#include <terminal_ctrl/terminal_ctrl.hpp>
#include <string>
#include <iostream>
#include "board.hpp"
#include "player.hpp"
#include "custom_strings.hpp"

namespace game_tic_tac_toe // contient la logique du jeu
{ 

    struct Game {
        private:
        board::Board game_board;
        player::Player player1;
        player::Player player2;

        public:
        Game(player::Player p1, player::Player p2);
        Game();
        void play();
        void initialize_game( player::Player &p1, player::Player &p2);
        void play_game( player::Player &p1, player::Player &p2, board::Board &board); 
        const player::Player &get_player(int player_number) const;
    };

    void show_welcome_message();
    int show_game_mode_selection();
    player::Player show_player_creation(int player_number,const player::Player &other_player);
    void draw_game_board(std::string board_str);
    int choose_difficulty_level();



} // namespace game_tic_tac_toe