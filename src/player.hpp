#pragma once
#include <string>

struct Player{
    private:
    std::string name;
    std::string symbol;

    public:
    std::string get_name() const;
    std::string get_symbol() const;


};

Player create_player(const std::string& name, const std::string& symbol);