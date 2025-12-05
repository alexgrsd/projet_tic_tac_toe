#include "main.hpp"
#include "game.hpp"
#include <iostream>

int main() {
    
    game_tic_tac_toe::Game game;
    game.play();

    std::cout << "player 1 name : " << game.get_player(1).get_name() << std::endl;
    std::cout << "player 1 symbol : " << game.get_player(1).get_symbol() << std::endl;
    std::cout << "player 2 name : " << game.get_player(2).get_name() << std::endl;
    std::cout << "player 2 symbol : " << game.get_player(2).get_symbol() << std::endl;


    return 0;
}