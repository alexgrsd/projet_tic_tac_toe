#include "player.hpp"

namespace player
{

    Player::Player(char symbol, const char *name) : symbol(symbol), name(name) {}

    char Player::get_symbol() const
    {
        return symbol;
    }

    const char *Player::get_name() const
    {
        return name;
    }

};