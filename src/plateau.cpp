#include "plateau.hpp"
#include <iostream>

void Case::print_state() { // print l'etat de la case
    if (state == "") {
        std::cout << ".";
    } else {
        std::cout << state;
    }
}


int Board::verify_victory_tic_tac_toe() { // un peu hideux mais fait le taff jusqu'ici
    // Vérification des lignes
    for (int i = 0; i < largeur; ++i) {
        if (cases[i][0].get_state() != "" &&
            cases[i][0].get_state() == cases[i][1].get_state() &&
            cases[i][1].get_state() == cases[i][2].get_state()) {
            return (cases[i][0].get_state() == "X") ? 1 : 2;
        }
    }

    // Vérification des colonnes
    for (int j = 0; j < largeur; ++j) {
        if (cases[0][j].get_state() != "" &&
            cases[0][j].get_state() == cases[1][j].get_state() &&
            cases[1][j].get_state() == cases[2][j].get_state()) {
            return (cases[0][j].get_state() == "X") ? 1 : 2;
        }
    }

    // Vérification des diagonales
    if (cases[0][0].get_state() != "" &&
        cases[0][0].get_state() == cases[1][1].get_state() &&
        cases[1][1].get_state() == cases[2][2].get_state()) {
        return (cases[0][0].get_state() == "X") ? 1 : 2;
    }
    if (cases[0][2].get_state() != "" &&
        cases[0][2].get_state() == cases[1][1].get_state() &&
        cases[1][1].get_state() == cases[2][0].get_state()) {
        return (cases[0][2].get_state() == "X") ? 1 : 2;
    }

    // verifie si le plateau est plein
    bool is_full = true;
    for (int i = 0; i < largeur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            if (cases[i][j].get_state() == "") {
                is_full = false;
                break;;
            }
        }
        if (!is_full) {
            break;
        }
    }
    if (is_full) {
        return 3; // Match nul
    }

    return 0; // Pas de gagnant
    
}

int Board::activate_case(int x,int y,std::string state) {
    if (!Board::cases[x][y].is_empty()) {
        std ::cout << "Case occupée: ";
        cases[x][y].print_state();
        std::cout << std::endl;
        return 1; // Case déjà occupée
    }
    if (x >= 0 && x < largeur && y >= 0 && y < largeur) {
        cases[x][y].set_state(state);
    }
    else return 2; // Coordonnées invalides
    return 0; // Succès
}
void Board::reset() {
    for (int i = 0; i < largeur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            cases[i][j].set_state("");
        }
    }
}
void Board::print_board() {
    for (int i = 0; i < largeur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            std::string symbole = cases[i][j].get_state();
            if (symbole == "") {
                symbole = ".";
            }
            std::cout << symbole << " ";
        }
        std::cout << std::endl;
    }
}

