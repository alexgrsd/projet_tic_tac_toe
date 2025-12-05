#include "player.hpp"
#include <string>


Player create_player(const std::string& name, const std::string& symbol) {
    Player player;
    player.name = name;
    player.symbol = symbol;
    return player;
}

std::string Player::get_name() const {
    return name;
}

std::string Player::get_symbol() const {
    return symbol;
}