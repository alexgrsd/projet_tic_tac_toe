#pragma once
#include "board.hpp"
#include "player.hpp"

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
        const player::Player &get_player(int player_number) const;
    };



} // namespace game_tic_tac_toe