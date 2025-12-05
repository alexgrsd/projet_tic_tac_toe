#pragma once

namespace player
{

    struct Player
    {
    private:
        char symbol;
        const char *name;
    public:
        Player(char symbol, const char *name);
        char get_symbol() const;
        const char *get_name() const;
    };

};
