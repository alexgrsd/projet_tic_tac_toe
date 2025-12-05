#include "player.hpp"
#include <string>

namespace player
{

    Player::Player(char symbol, const std::string &name, bool is_human) : symbol(symbol), name(name), is_human(is_human) {}

    Player create_bot()
    {
        Player bot('O', "Computer", false);
        return bot;
    }

    bool Player::get_is_human() const
    {
        return is_human;
    }

    char Player::get_symbol() const
    {
        return symbol;
    }

    const std::string &Player::get_name() const
    {
        return name;
    }

} // namespace player