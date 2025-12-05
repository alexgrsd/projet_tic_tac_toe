#pragma once
#include <iostream>

// Ce fichier contient la définition de la structure représentant le plateau de jeu.

const int largeur = 3;


struct Case{
    private :
    std::string state;

    public :
    void set_state(std::string new_state) {
        state = new_state;
    }
    std::string get_state() const {
        return state;
    }
    void print_state();
    bool is_empty() const;

    Case() : state("") {}
    


};

struct Board{
    private :
    int length = 0;
    Case cases[largeur][largeur];

    public :
    int verify_victory_tic_tac_toe();
    int activate_case(int x, int y, std::string state);
    void reset();
    void print_board();
};


