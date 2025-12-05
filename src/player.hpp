#pragma once
#include <string>

namespace player
{

    struct Player
    {
    private:
        char symbol;
        std::string name;
        bool is_human;
    public:
        Player(char symbol, const std::string &name, bool is_human);
        char get_symbol() const;
        const std::string &get_name() const;
        bool get_is_human() const;
    };

    Player create_bot();

} // namespace player
